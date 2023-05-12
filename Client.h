#include "BoardForServer.cpp"
class Client {
public:
    Client(tcp::socket* server_sock);
    void start();
    bool send_message(string msg);
    bool getClient_on();
   
    void setServerSock(tcp::socket* server_sock);
    void setClient_on(bool setValue);
    void setRequested(bool setValue);
    void setBSF(BoardForServer BFS);
    BoardForServer getBFS();
    tcp::socket* getServerSocket();
    void setChoosing_ground(bool choosing_ground);
    bool getChoosing_ground();
    void setGame_running(bool gr);
    bool getGame_running();
    void make_board(int side);
    void reset();
    void setClient_turn(bool setValue);
    bool getClient_turn();
   

private:
    tcp::socket* server_sock;
    bool client_on = true ;
    bool game_running = false;
    bool requested = false;
   
    bool client_turn = false;
    void read();
    int return_size_char(const char* msg);
    bool correctAns(const char* msg, int size);
    void showStatus();
    int turn_char_int(const char* msg,int size);
    bool choosing_ground;
    bool answered = false;

    BoardForServer board;
    
    
};