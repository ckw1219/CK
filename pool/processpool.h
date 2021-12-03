#ifndef PROCESSPOOL_H
#define PROCESSPOOL_H
/*
项目名称：半同步/半异步并发模式的进程池
即：为了避免在父子进程中传递文件描述符，我们将接受新连接的操作放到子进程中

异步的父进程(主进程)：只管理监听socket，连接socket由工作子进程来处理。
每个进程都维持自己的事件循环，它们各自独立地监听不同的事件。

并发模式中的同步和异步的概念：

同步：程序完全按照代码序列的顺序执行。
异步：程序的执行需要由系统事件来驱动。
*/


#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/epoll.h>
#include<signal.h>
#include<sys/wait.h>
#include<sys/stat.h>

/*一个描述子进程的类，m_pid是目标子进程的PID，m_pipefd是父进程和子进程通信的管道*/
class process
{
    public:
        process() : m_pid(-1) {}
    public:
        pid_t m_pid;
        int m_pipefd[2];
};

/*进程池类，将它定义为模板类是为了代码复用。其模板参数是处理逻辑任务的类*/
template<typename T>
class processpool
{
    private:
    /* 将构造函数定义为私有，因此我们只能通过后面的create静态函数来创建processpool实例(单例模式)*/
        processpool(int listenfd, int process_number = 8);

    public:
        static processpool<T>* create(int listenfd, int process_number = 8)
        {
            if (!m_instance)
            {
                m_instance = new processpool<T> (listenfd, process_number);
            }
            return m_instance;
        }

        ~processpool()
        {
            delete [] m_sub_process;
        }

        void run();
    
    private:
        void setup_sig_pipe();
        void run_parent();
        void run_child();

    private:
        static const int MAX_PROCESS_NUMBER = 16;
        static const int USER_PER_PROCESS = 65536;
        static const int MAX_EVENT_NUMBER = 10000;
        /*进程池中的进程总数*/
        int m_process_number;
        /*子进程在池中的序号，从0开始*/
        int m_idx;
        /*每个进程都有一个epoll内核事件表，用m_epollfd标识*/
        int m_epollfd;
        /*监听socket*/
        int m_listened;
        /*子进程通过m_stop来决定是否停止运行*/
        int m_stop;
        /*保存所有子进程的描述信息*/
        process* m_sub_process;

        /*进程池静态实例*/
        static processpool<T>* m_instance;
}

//单例模式，保证只有一个进程池类的实体
template<typename T> 
processpool<T>* processpool<T>::m_instance = NULL; //类内静态成员变量的类外初始化

/* 用于处理信号的管道，以实现统一事件源。后面称之为信号管道 */
static int sig_pipefd[2];

/*将socket设置成非阻塞模式*/
static int setnonblocking(int fd)
{
    int old_option = fcntl(fd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_option)
    return old_option;
}

static void addfd(int epollfd, int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &event);
    setnonblocking(fd);
}

/*从epollfd标识的epoll内核事件表中删除fd上的所有注册事件*/
static void removefd(int epollfd, int fd)
{
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, 0);
    close(fd);
}

static void sig_handler(int sig) // 信号处理函数
{
    int save_errno = errno;
    int msg = sig;
    send(sig_pipefd[1], (char*)&msg, 1, 0);
    errno = save_errno;
}

static void addsig(int sig, void(handler)(int), bool restart = true)
{
    struct sigcation sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = handler;
    if (restart)
    {
        sa.sa_flags |= SA_RESTART;
    }
    sigfillset(&sa.sa_mask);
    assert( sigacation(sig, &sa, NULL) != -1);
}

/*进程池构造函数。 参数:listenfd是监听socket，它必须在创建进程池之前被创建，否则子进程无法直接引它。process_number指定进程池中子进程的数量*/
template <typename T>
processpool<T>::processpool(int listenfd, int process_number) :m_listened(listenfd), m_process_number(process_number),m_idx(-1),m_stop(false)
{
    assert((process_number > 0) && (process_number <= MAX_PROCESS_NUMBER));

    m_sub_process = new process[process_number];

    /*创建process_number个子进程，并建立它们与父进程之间的管道*/
    for (int i = 0; i < process_number; ++i)
    {
        int ret = socketpair(PF_UNIX,SOCK_STREAM,0,m_sub_process[i].m_pipefd);
        assert( ret == 0);

        m_sub_process[i].m_pid = fork();
        assert(m_sub_process[i].m_pid >= 0)
        
        if (m_sub_process[i].m_pid > 0)
        {//父进程中的操作
            close(m_sub_process[i].m_pipefd[1]);
            continue;
        }
        else{
            close(m_sub_process[i].m_pipefd[0]);
            m_idx = i;
            break;
        }
        /*
        读写分离：因为从一个套接字写入后，再读的话会造成套接字阻塞，因此，一端只写，一端只读。
        */
    }
}

/*统一事件源*/
template<typename T>
void processpool<T>::setup_sig_pipe()
{
    /*创建epoll事件监听表和信号管道*/
    m_epollfd = epoll_create(5);
    assert(m_epollfd != -1);

    int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, sig_pipefd);
    assert (ret != -1);
    setnonblocking(sig_pipefd[1]);
    addfd(m_epollfd, sig_pipefd[0]);

    addsig(SIGCHID, sig_handler);
    addsig(SIGTERM,sig_handler);
    addsig(SIGINT,sig_handler);
    addsig(SIGPIPE,SIG_ING);
}

/*父进程中m_idx的值为1，子进程中m_idx的值大于等于0*/
template<typename T>
void processpool<T>::run()
{
    if (m_idx != -1)
    {
        run_child();
        return;
    }
    run_parent();
}

template<typename T>
void processpool<T>::run_child()
{
    setup_sig_pipe();
    /*每个子进程都通过其在进程池中的序号值m_idx找到与父进程通信的管道*/
    int pipefd = m_sub_process[m_idx].m_pipefd[1];
    /*子进程需要监听管道文件描述符pipefd,因为父进程将通过它来通知子进程accept新连接*/
    addfd(m_epollfd, pipefd);

    epoll_event events[MAX_EVENT_NUMBER];
    T* users = new T [USER_PER_PROCESS];
    assert(users);
    int number = 0;
    int ret = -1;

    while (!m_stop)
    {
        number = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER, -1);
        if ((number < 0) && (errno != EINTR))
        {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; ++i)
        {
            int sockfd = events[i].data.fd;
            if ((sockfd == pipefd) && (events[i].events & EPOLLIN))
            {
                int client = 0;
                ret = recv(sockfd, (char*)&client, sizeof(client), 0);
                if (((ret < 0) && (errno != EAGAIN)) || ret == 0)
                {
                    continue;
                }
                else 
                {
                    struct sockaddr_in client_address;
                    socklen_t client_addrlength = sizeof(client_address);
                    int connfd = accept(m_listened, (struct sockaddr*)&client_address, &client_addrlength);
                    if (connfd < 0)
                    {
                        printf("errno is: %d\n", errno);
                        continue;
                    }
                    addfd(m_epollfd, connfd);
                    users[connfd].init(m_epollfd, connfd, client_address);
                }
            }
            /*处理子进程接收到的信号*/
            else if ((sockfd == sig_pipefd[0]) && (events[i].events & EPOLLIN))
            {
                int sig;
                char signals[1024];
                ret = recv(sig_pipefd[0], signals, sizeof(signals), 0);
                if (ret <= 0)
                {
                    continue;
                }
                else 
                {
                    for(int i = 0; i < ret; ++i)
                    {
                        switch(signals[i])
                        {
                            case SIGCHLD:
                            {
                                pid_t pid;
                                int stat;
                                while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
                                {
                                    continue;
                                }
                                break;
                            }
                            case SIGTERM:
                            case SIGINT:
                            {
                                m_stop = True;
                                break;
                            }
                            default:
                            {
                                break;
                            }
                        }
                    }
                }
            }
            else if (events[i].events & EPOLLIN)
            {
                users[sockfd].process();
            }
            else{
                continue;
            }

            delete [] users;
            users = NULL;
            close(pipefd);
            close(m_epollfd);
        }
    }
}

template<typename T>
void processpool<T>::run_parent()
{
    setup_sig_pipe();

    /*父进程监听m_listenfd*/
    addfd(m_epollfd, m_listenfd);

    epoll_event events[MAX_EVENT_NUMBER];
    int sub_process_counter = 0;
    int new_conn = 1;
    int number = 0;
    int ret = -1;

    while (!m_stop)
    {
        number = epoll_wait(m_epollfd, events, MAX_EVENT_NUMBER);
        if ((number < 0) && (errno != EINTR))
        {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; ++i)
        {
            int sockfd = events[i].data.fd;
            if (sockfd == m_listened)
            {
                
            }
        }
    }
}
#endif