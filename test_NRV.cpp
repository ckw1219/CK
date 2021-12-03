#include<iostream>

using namespace std;

class A
{
    public:
        A()
        {
            cout << "constructor\n" << endl;
        }

        A(const A &a) 
        {
            cout << "copy constructor\n" << endl;
        }

        A(A && a)
        {
            cout << "move constructor\n" << endl;
        }

        A &operator=(const A &a)
        {
            cout << "copy assignment constructor\n" << endl;
            if (this == &a)
            {
                return *this;
            }
            else 
            {
                this->i = a.i;
            }

            return *this;
        }

        A &operator=(A &&a)
        {
            cout << "move assignment constructor\n" << endl;
            return *this;
        }

        ~A()
        {
            cout << "destructor\n" << endl;
        }
    private:
     int i;   
};


inline A foo()
{
    return A();
}

int main()
{
    auto x = foo();
    return 0;
}