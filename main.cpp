#include "Client.cpp"
int main()
{
    thread t1(client1);
    thread t2(client2);
    t1.join();
    t2.join();
}