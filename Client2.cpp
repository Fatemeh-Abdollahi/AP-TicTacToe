#include <iostream>

#include <boost/asio.hpp>
using namespace std;
using namespace boost::asio;
using namespace ip;
void getFromServer(tcp::socket& sock) {
    while (true) {
        boost::asio::streambuf buff;
        read_until(sock, buff, "\n");
        const char* msg0 = buffer_cast<const  char*>(buff.data());
        cout << "server: " << msg0 << endl;
    }
}
void sendToServer(tcp::socket& sock) {
    while (true) {
        string msg;
        getline(cin, msg);
        msg += "\n";
        write(sock, boost::asio::buffer(msg));
    }
}
int main()
{



    io_service io;
    tcp::socket sock(io);
    sock.connect(tcp::endpoint(address::from_string("127.0.0.1"), 5678));
    thread t1(getFromServer, ref(sock));
    thread t2(sendToServer, ref(sock));
    t1.join();
    t2.join();

    /*
    string msg;
    getline(cin, msg);
    msg += "\n";
    write(sock, boost::asio::buffer(msg));
    boost::asio::streambuf buff;
    read_until(sock, buff, "\n");
    cout << "server:  " << buffer_cast<const char*> (buff.data());*/


}