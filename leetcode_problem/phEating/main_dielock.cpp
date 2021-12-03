/*
哲学家就餐问题，模拟死锁和避免死锁

哲学家的活动：思考，饥饿，进食（需要两把叉子）

程序思路：
需要六个线程，主线程用于显示功能描述；五个哲学家线程用于模拟哲学家的活动，即不停的思考、
饥饿、进食。相邻的两个哲学家线程需要共享他们中间的同一根筷子，因此对每一根筷子的使用要互斥，
利用互斥数组h_mutex_chopsticks来实现。主线程创建五个哲学家线程后要等待所有哲学家结束，利用
线程句柄数组h_thread来表示五个线程，主线程通过等待这五个线程句柄来实现同步。

七个函数：
main():显示主菜单，接受用户的选择并执行相应的功能

deadlock_philosopher():演示死锁情况下的哲学家线程

deadlock():初始化函数，创建五个哲学家线程并且等待它们结束。

ordered_allocation_philosopher():通过按序分配法死锁的哲学家线程函数

ordered_allocation():初始化函数，创建五个哲学家等待它们结束。

pre_allocation_philosopher():通过预先分配法防止死锁的哲学家线程函数

pre_allocation():初始化函数，创建五个哲学家等待它们结束。

*/

#include"ph.h"
#include"mysemop.h"
using namespace std;

void* philosopher(int i);

int chopstick[MAX_PH]; //筷子数组
sem_t ph_self[MAX_PH]; //哲学家线程句柄数组

int main(int argc, char* argv[])
{
    for (int i = 0; i < MAX_PH; i++)
    {
        chopstick[i] = CreateSem(1);
    }

    int fpid = 1;
    int amount = MAX_PH;
    while (fpid != 0 && --amount)//fpid != 0,则运行的是父进程
    {
        fpid = fork();
    }

    philosopher(amount);

    return 0;
}

void* philosopher(int i)
{
    printf("my i = %d\n", i);
    while (1)
    {
        thinking(i);
        Psem(chopstick[i]);
        printf("philosopher %d get left\n", i);

        Psem(chopstick[(i+1)%MAX_PH]);
        printf("philosopher %d get right\n", i);

        eating(i);

        Vsem(chopstick[i]);

        printf("philosopher %d put down left\n", i);

        Vsem(chopstick[(i+1)%MAX_PH]);
        printf("philosopher %d put down right\n", i);
    }
}


