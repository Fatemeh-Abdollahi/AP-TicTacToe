#include "Client.h"
Client::Client(tcp::socket* server_sock) {
     this->server_sock = server_sock;
}

int Client::return_size_char(const char* msg) {
    int size = 0;
    while (msg[size] != '\0') size++;
    return size - 1;
}
void Client::setGame_running(bool gr) {
    game_running = gr;
}
bool Client::getClient_turn() {
    return client_turn;
}
void Client::setClient_turn(bool setValue) {
    client_turn = setValue;
}

bool Client::getGame_running() {
    return game_running;

}
void Client::setClient_on(bool setValue) {
    client_on = setValue;
}
int Client::turn_char_int(const char* ans, int size) {
    int integer = 0;
    int _size = size;
    for (int i = 0; i < size; i++)
    {

        int ai = (int)ans[i];
        integer += (ai - 48) * (int)pow(10, _size - 1);
        _size--;
    }
    return integer;
}
void Client::setChoosing_ground(bool choosing_ground) {
    this->choosing_ground = choosing_ground;
}
bool Client::getChoosing_ground() {
    return choosing_ground;
}
void Client::setRequested(bool setValue) {
    requested = setValue;
}
void Client::setBSF(BoardForServer BSF) {
    board = BSF;
}
BoardForServer Client::getBFS() {
    return board;
}
void Client::showStatus() {
    send_message("resault:");
    if((*client1_obj).getClient_on())
        send_message("client1 is online");
    else
        send_message("client1 is offline");
    send_message("-----------------------");
    if ((*client2_obj).getClient_on())
        send_message("client2 is online");
    else
        send_message("client2 is offline");
    send_message("-----------------------");
    send_message("");
}
bool Client::correctAns(const char* msg, int size) {
    if (game_running == false && (requested == false && choosing_ground == false)) {
        if (msg[0] == '1' || msg[0] == '2')
            return true;
        else return false;
    }
    else if (game_running == false && requested == true && choosing_ground == false) {
        if (msg[0] == 'Y' || msg[0] == 'y' || msg[0] == 'n' || msg[0] == 'N')
            return true;
        else return false;
    }
    else if (game_running == true && requested == false && choosing_ground == false) {
        for (int i = 0; i < size; i++)
        {
            if (!((int)msg[i] > 47) && !((int)msg[i] < 58))
                return false;

        }
        if (client1_obj->getBFS().correctAnswer(msg, return_size_char(msg)))
            return true;
        else
            return false;
    }
    else if (game_running == false && (requested == false && choosing_ground == true)) {
        if (game_running == false && (requested == false && choosing_ground == false)) {

            if (msg[0] == '1' || msg[0] == '2')

                return true;
            
            if (msg[0] == '3')
                return true;
        }
        return false;
    }
}
bool Client::getClient_on() {
    return client_on;
}
void Client::reset() {
    client_on = true;
    game_running = false;
    requested = false;  
    
    client_turn = false;
}
void Client::read() {
    try {
        
        while (true) {
            
                
              
                
                boost::asio::streambuf buff;
                read_until(*server_sock, buff, "\n");
                const char* msg = buffer_cast<const char*>(buff.data());      
               
                int size = return_size_char(msg);
                
            if (correctAns(msg, size)) {
                
                if ((!game_running) && (!requested) && (!choosing_ground)) {
             
                    if (msg[0] == '1') {
                        showStatus();
                        send_message(message1);
                        read();
                    }
                    else {
                        
                        if (this != client1_obj) {
                            (*client1_obj).setRequested(true);
                            if(!((*client1_obj).send_message("you have request from client 2 (y/n)")))
                             send_message("the player is off");
                            
                            
                            else 
                                send_message("the request sent please wait we will inform you when accepted");

                            
                            send_message(message1);
                        }
                        else {
                            (*client2_obj).setRequested(true);
                            if (!((*client2_obj).send_message("you have request from client 2(y/n)")))
                                send_message("the player is off");
                            else
                                send_message("the request sent please wait we will inform you when accepted");
                            send_message(message1);
                        }
                    }
                    
                }
                else if (game_running) {
                 
                    if (client_turn) {
                        board.updateTheBoard(msg, return_size_char(msg));
                        (*client1_obj).getBFS().sendTheBoard((*client1_obj).getServerSocket());
                        (*client2_obj).getBFS().sendTheBoard((*client2_obj).getServerSocket());

                        if (board.win_the_game()) {
                            send_message("you win the game :)");
                            send_message(message1);
                            reset();
                            if (this == client1_obj) {
                                (*client2_obj).send_message("you lose the game :(");
                                (*client2_obj).reset();
                                (*client2_obj).send_message(message1);


                            }
                            else {
                                (*client1_obj).send_message("you lose the game");
                                (*client1_obj).reset();
                                (*client1_obj).send_message(message1);

                            }

                        }
                        else {
                            client_turn = false;
                            if (this == client1_obj) {
                                (*client2_obj).setClient_turn(true);
                                (*client2_obj).send_message("now it is your turn");
                                thread t1(timer, client2_obj);
                                t1.join();
                            }
                            else {
                                (*client1_obj).setClient_turn(true);
                                (*client1_obj).send_message("now it is your turn");
                                thread t1(timer, client1_obj);
                                t1.join();
                            }
                        }
                       
                    }
                    else {
                        send_message("it is not your turn");
                        board.sendTheBoard(getServerSocket());
                      
                    }
                }
                else if (requested) {
                    
                    if (msg[0] == 'y' || msg[0] == 'Y')
                    {
                        if (this != client1_obj) {
                            requested = false;
                            (*client1_obj).send_message("the request got accepted");
                            (*client1_obj).send_message(message1);
                          
                            send_message("choose the ground (1/2/3)");
                            choosing_ground = true;
                           

                           
                        }
                        else {
                            requested = false;
                            (*client2_obj).send_message("the request got accepted");
                            (*client2_obj).send_message(message1);
                            send_message("choose the ground (1/2/3)");
                            choosing_ground = true;
                        }
                    }
                    else {
                        if (this != client1_obj) {
                            requested = false;
                            (*client1_obj).send_message("the request didnt get accepted");
                            (*client1_obj).send_message(message1);
                            send_message(message1);
                        }
                        else {
                            requested = false;
                            (*client2_obj).send_message("the request didnt get accepted");
                            (*client2_obj).send_message(message1);
                            send_message(message1);
                        }
                    }
                }
                else if (choosing_ground) {
                    if (msg[0] == '1') {
                        BoardForServer _board(1);
                        (*client1_obj).setBSF(_board);
                        (*client2_obj).setBSF(_board);
                        (*client1_obj).setChoosing_ground(false);
                        (*client2_obj).setChoosing_ground(false);
                        if (!((*client1_obj).send_message("")) && !((*client2_obj).send_message("")))
                        {
                            send_message("the player is off");
                            send_message(message1);
                        }
                        else {
                            (*client2_obj).setGame_running(true);
                            (*client1_obj).setGame_running(true);
                            client_turn = true;
                            (*client1_obj).getBFS().sendTheBoard((*client1_obj).getServerSocket());
                            (*client2_obj).getBFS().sendTheBoard((*client2_obj).getServerSocket());

                            

                        }

                    }
                    else if (msg[0] == '2') {
                        BoardForServer _board(2);
                        (*client1_obj).setBSF(_board);
                        (*client2_obj).setBSF(_board);
                        (*client1_obj).setChoosing_ground(false);
                        (*client2_obj).setChoosing_ground(false);
                        
                        
                       
                           
                           if (!((*client1_obj).send_message("")) && !((*client2_obj).send_message("")))
                           {
                               send_message("the player is off");
                               send_message(message1);
                           }

                            else {
                               (*client2_obj).setGame_running(true);
                               (*client1_obj).setGame_running(true);
                               client_turn = true;
                               (*client1_obj).getBFS().sendTheBoard((*client1_obj).getServerSocket());
                               (*client2_obj).getBFS().sendTheBoard((*client2_obj).getServerSocket());

                               
                                
                            }

                          
                        
                    }
                    
                    else if (msg[0] == '3') {
                        BoardForServer _board(3);
                        (*client1_obj).setBSF(_board);
                        (*client2_obj).setBSF(_board);
                        (*client1_obj).setChoosing_ground(false);
                        (*client2_obj).setChoosing_ground(false);
                        if (!((*client1_obj).send_message("")) && !((*client2_obj).send_message("")))
                        {
                            send_message("the player is off");
                            send_message(message1);
                        }
                        else {
                            (*client2_obj).setGame_running(true);
                            (*client1_obj).setGame_running(true);
                            client_turn = true;
                            (*client1_obj).getBFS().sendTheBoard((*client1_obj).getServerSocket());
                            (*client2_obj).getBFS().sendTheBoard((*client2_obj).getServerSocket());

                         

                        }
                    }
                    
                }
            }
            else {
                send_message("wrong input");
            }
          
        }
    }
    catch (boost::wrapexcept<boost::system::system_error>(e)) {
       
        client_on = false;
    }
    
}
void Client::setServerSock(tcp::socket* server_sock) {
    this->server_sock = server_sock;
}
tcp::socket* Client::getServerSocket() {
    return server_sock;
}
void Client::start() {
    switch (game_running) {
    case false:
        send_message(message1);
        read();
        break;
    case true:
        board.sendTheBoard(getServerSocket());
        read();
        break;
    }
}
bool Client::send_message(string msg) {
    try {
        
        msg +="\n";
      
            write(*server_sock, boost::asio::buffer(msg));
        
            return true;
    }
  
        catch (boost::wrapexcept<boost::system::system_error>(e)) {
            client_on = false;
         
            return false;
            }
        }
   

void client1() {
   
    while (true) {
        
        
            io_service io;
            tcp::socket server_sock(io);
            tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), 1234));
            acc.accept(server_sock);
           
        
        c1++;
    
        if (c1 != 1) {
            (*client1_obj).setClient_on(true);
            (*client1_obj).start();
        }
        else {
            Client cl1(&server_sock);
            client1_obj = &cl1;
            cl1.start();
        }
      
    }
}
void client2() {
   
    while (true) {
       
        io_service io;
        tcp::socket server_sock(io);
        tcp::acceptor acc(io, tcp::endpoint(tcp::v4(), 5678));
        acc.accept(server_sock);
       
        c2++;
        if (c2 != 1) {
            (*client2_obj).setClient_on(true);
            (*client2_obj).start();
        }
        else {
            Client cl2(&server_sock);
            client2_obj = &cl2;
            cl2.start();
        }
     
    }
}
void timer(Client* obj_p) {
    if (obj_p->getClient_turn()) {
        int s = 0;
        while (s < 600 && obj_p->getClient_turn())
        {
            s++;
            this_thread::sleep_for(50ms);
            if (s % 100 == 0)
                obj_p->send_message("5s");
        }
        if (obj_p->getClient_turn()) {
            
           
            if (obj_p == client1_obj) {
                client2_obj->send_message("you won the game :)");
                client2_obj->send_message(message1);
                client1_obj->send_message("you lose because you didnt answer in the limited time :(");
                client1_obj->send_message(message1);
                client1_obj->reset();
                client2_obj->reset();
            }
            else {
                client1_obj->send_message("you won the game :)");
                client1_obj->send_message(message1);
                client2_obj->send_message("you lose because you didnt answer in the limited time :(");
                client2_obj->send_message(message1);
                client1_obj->reset();
                client2_obj->reset();
            }
        }
    }
}