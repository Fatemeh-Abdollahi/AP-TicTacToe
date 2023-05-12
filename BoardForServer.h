#include <iostream>
#include <boost/asio.hpp>
#include<thread>
#include <vector>
using namespace std;
using namespace boost::asio;
using namespace ip;
const string message1 = "1-see the status ---- 2-request to play \n"; // it is the introduction message

vector<string> main_board;

class Client;
class BoardForServer;
thread t_p;
Client* client1_obj;
Client* client2_obj;
int c1 = 0;
int c2 = 0;
void timer(Client* obj_p);
class BoardForServer {

public:
    BoardForServer();
    BoardForServer(int side);
    void updateTheBoard(const char* ans, int size);
    void sendTheBoard(tcp::socket* server_sock);
    bool correctAnswer(const char* ans, int size);
    int turn_char_to_int(const char* ans, int size);
    bool win_the_game();
    void setSide(int side);
    int getSide();
private:
    void defaultInitialize();
    void send_message(tcp::socket* server_sock, string msg);
  
    int side;
    static int XorO; // if 1 -> x if 2 ->y
};