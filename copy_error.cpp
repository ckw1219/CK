#include<iostream>
#include<cstring>

using namespace std;

class Cexample
{
    public:
        int a, b, c;
        char* str;

    public:
        Cexample(int tb)
        {
            a = tb;
            b = tb + 1;
            c = tb + 2;
            str = (char*) malloc(sizeof(char) * 10);

            strcpy(str, "123456789");
            cout << "creat" << endl;
        }

        ~Cexample()
        {
            cout << "delete:" << endl;
        }

        Cexample(const Cexample& C)
        {
            a = C.a;
            b = C.b;
            c = C.c;
            str = (char*)malloc(sizeof(char) * 10);
            strcpy(str, C.str);
            cout << "copy" << endl;
        }
};

void g_Fun(Cexample C)
{
    C.a = 0;
    C.b = 0;
    C.c = 0;
    strcpy(C.str, "aaabbbccc");
    cout << "test" << endl;
}

int main()
{
    Cexample test(1);
    cout<<"str:"<<test.str<<" a="<<test.a<<" b="<<test.b<<" c="<<test.c<<endl;
    g_Fun(test);//传入对象
    cout<<"str:"<<test.str<<" a="<<test.a<<" b="<<test.b<<" c="<<test.c<<endl;
    getchar();
    return 0;
}