#include "BoardForServer.h"
BoardForServer::BoardForServer() {
    side = 0;
}
BoardForServer::BoardForServer(int side) {
    this->side = side;
    defaultInitialize();


}
void BoardForServer::setSide(int side) {
    this->side = side;
    defaultInitialize();
}
int BoardForServer::getSide() {
    return side;
}
int  BoardForServer::XorO = 0;
void BoardForServer::sendTheBoard(tcp::socket* server_sock) {
    if (side == 1) {
        send_message(server_sock, main_board.at(0)  + "-------" + main_board.at(1)  +"-------" + main_board.at(2));
        send_message(server_sock, "|        |        |");
        send_message(server_sock, "|        |        |");
        send_message(server_sock, "|        |        |");
        send_message(server_sock, "|        |        |");
        send_message(server_sock, main_board.at(3)  + "-------" + main_board.at(4)  + "-------" + main_board.at(5));
        send_message(server_sock, "|       |       |");
        send_message(server_sock, "|       |       |");
        send_message(server_sock, "|       |       |");
        send_message(server_sock, "|       |       |");
        send_message(server_sock, main_board.at(6)  + "-------" + main_board.at(7)  + "-------" + main_board.at(8));
    }
    else if (side == 2) {
        send_message(server_sock, main_board.at(0) + "----------" + main_board.at(1) + "----------" + main_board.at(2));
        send_message(server_sock, "|           |           |");
        send_message(server_sock, "|           |           |");
        send_message(server_sock, "|           |           |");
        send_message(server_sock, "|    " + main_board.at(3) + "-----" + main_board.at(4) + "-----" + main_board.at(5) + "   |");
        send_message(server_sock, "|    |             |    |");
        send_message(server_sock, "|    |             |    |");
        send_message(server_sock, main_board.at(6) + "---" + main_board.at(7) + "            " + main_board.at(8) + "---" + main_board.at(9));
        send_message(server_sock, "|    |             |    |");
        send_message(server_sock, "|    |             |    |");
        send_message(server_sock, "|    " + main_board.at(10) + "-----" + main_board.at(11) + "-----" + main_board.at(12) + "   |");
        send_message(server_sock, "|           |           |");
        send_message(server_sock, "|           |           |");
        send_message(server_sock, "|           |           |");
        send_message(server_sock, main_board.at(13) + "----------" + main_board.at(14) + "----------" + main_board.at(15));
    }
    else if (side == 3) {
        send_message(server_sock, main_board.at(0) + "-------------------" + main_board.at(1) + "--------------------" + main_board.at(2));
        send_message(server_sock, "|                    |                     |");
        send_message(server_sock, "|                    |                     |");
        send_message(server_sock, "|                    |                     |");
        send_message(server_sock, "|                    |                     |");
        send_message(server_sock, "|                    |                     |");
        send_message(server_sock, "|                    |                     |");
        send_message(server_sock, "|                    |                     |");
        send_message(server_sock, "|                    |                     |");
        send_message(server_sock, "|        " + main_board.at(3) + "----------" + main_board.at(4) + "-----------" + main_board.at(5) + "       |");
        send_message(server_sock, "|        |           |            |        |");
        send_message(server_sock, "|        |           |            |        |");
        send_message(server_sock, "|        |           |            |        |");
        send_message(server_sock, "|        |           |            |        |");
        send_message(server_sock, "|        |    " + main_board.at(6) + "-----" + main_board.at(7) + "-----" + main_board.at(8) + "    |        |");
        send_message(server_sock, "|        |    |             |     |        |");
        send_message(server_sock, "|        |    |             |     |        |");
        send_message(server_sock, main_board.at(9) + "-------" + main_board.at(10) + "---" + main_board.at(11) + "            " + main_board.at(12) + "----" + main_board.at(13) + "-------" + main_board.at(14));
        send_message(server_sock, "|        |    |             |     |        |");
        send_message(server_sock, "|        |    |             |     |        |");
        send_message(server_sock, "|        |    " + main_board.at(15) + "------------" + main_board.at(16) + "    |        |");
        send_message(server_sock, "|        |   /                \\   |        |");
        send_message(server_sock, "|        |  /                  \\  |        |");
        send_message(server_sock, "|        | /                    \\ |        |");
        send_message(server_sock, "|        |/                      \\|        |");
        send_message(server_sock, "|        " + main_board.at(17) + "-----------------------" + main_board.at(18) + "       |");
        send_message(server_sock, "|       /                          \\       |");
        send_message(server_sock, "|      /                            \\      |");
        send_message(server_sock, "|     /                              \\     |");
        send_message(server_sock, "|    /                                \\    |");
        send_message(server_sock, "|   /                                  \\   |");
        send_message(server_sock, "|  /                                    \\  |");
        send_message(server_sock, "| /                                      \\ |");
        send_message(server_sock, "|/                                        \\|");
        send_message(server_sock, main_board.at(19) + "-----------------------------------------" + main_board.at(20));

    }
}
bool BoardForServer::win_the_game() {
    switch (side) {
    case 1:
        for (int i = 0; i < 5; i += 3)
            if (main_board.at(i) == main_board.at(i + 1) && main_board.at(i + 1) == main_board.at(i + 2))
                return true;
        for (int i = 0; i < 2; i++)
            if (main_board.at(i) == main_board.at(i + 3) && main_board.at(i + 3) == main_board.at(i + 6))
                return true;
        return false;
        break;
    case 2:
        if (main_board.at(0) == main_board.at(1) && main_board.at(1) == main_board.at(2))
            return true;
        else if (main_board.at(3) == main_board.at(4) && main_board.at(4) == main_board.at(5))
            return true;
        else if (main_board.at(10) == main_board.at(11) && main_board.at(11) == main_board.at(12))
            return true;
        else if (main_board.at(13) == main_board.at(14) && main_board.at(14) == main_board.at(15))
            return true;
        else if (main_board.at(0) == main_board.at(6) && main_board.at(6) == main_board.at(13))
            return true;
        else if (main_board.at(3) == main_board.at(7) && main_board.at(7) == main_board.at(10))
            return true;
        else if (main_board.at(5) == main_board.at(8) && main_board.at(8) == main_board.at(12))
            return true;
        else if (main_board.at(2) == main_board.at(9) && main_board.at(9) == main_board.at(15))
            return true;
        else
            return false;
        break;
    case 3:
        if (main_board.at(0) == main_board.at(1) && main_board.at(1) == main_board.at(2))
            return true;
        else if (main_board.at(3) == main_board.at(4) && main_board.at(4) == main_board.at(5))
            return true;
        else if (main_board.at(7) == main_board.at(8) && main_board.at(8) == main_board.at(9))
            return true;
        else if (main_board.at(10) == main_board.at(11) && main_board.at(11) == main_board.at(12))
            return true;
        else if (main_board.at(13) == main_board.at(14) && main_board.at(14) == main_board.at(15))
            return true;
        else if (main_board.at(0) == main_board.at(9) && main_board.at(9) == main_board.at(19))
            return true;
        else if (main_board.at(3) == main_board.at(10) && main_board.at(10) == main_board.at(17))
            return true;
        else if (main_board.at(6) == main_board.at(11) && main_board.at(11) == main_board.at(15))
            return true;
        else if (main_board.at(1) == main_board.at(4) && main_board.at(4) == main_board.at(7))
            return true;
        else if (main_board.at(8) == main_board.at(12) && main_board.at(12) == main_board.at(16))
            return true;
        else if (main_board.at(5) == main_board.at(13) && main_board.at(13) == main_board.at(18))
            return true;
        else if (main_board.at(2) == main_board.at(14) && main_board.at(14) == main_board.at(20))
            return true;
        else if (main_board.at(15) == main_board.at(17) && main_board.at(17) == main_board.at(19))
            return true;
        else if (main_board.at(16) == main_board.at(18) && main_board.at(18) == main_board.at(20))
            return true;
        else
            return false;
        break;
    }
}
void BoardForServer::send_message(tcp::socket* server_sock, string msg) {
    msg = msg + "\n";
    write(*server_sock, boost::asio::buffer(msg));
    this_thread::sleep_for(5ms);

}
void BoardForServer::defaultInitialize() {
    main_board.clear();
    switch (side) {
    case 1:
        for (int i = 1; i < 10; i++) {
            
            string a = to_string(i);
            main_board.push_back(a);
        }
        break;
    case 2:
        for (int i = 1; i < 17; i++) {
            string a = to_string(i);
            if (i <= 9)
                main_board.push_back(a + " ");
            else
                main_board.push_back(a);
        }
        break;
    case 3:
        for (int i = 1; i < 22; i++) {
            string a = to_string(i);
            if (i <= 9)
                main_board.push_back(a + " ");
            else
                main_board.push_back(a);
        }
        break;
    }
}
bool BoardForServer::correctAnswer(const char* ans, int size) {
   


    for (int i = 0; i < size; i++)
    {
        if (!(ans[i] > 47 && ans[i] < 58))
            return false;
    }


    int index = turn_char_to_int(ans, size) - 1;

    switch (side) {
    case 1:
        if (size == 1) {
            if (index >= 0 && index < 9) {
                if (main_board.at(index) == "X " || main_board.at(index) == "O ")
                    return false;
                else
                    return true;
            }
            else
                return false;
        }
        else
            return false;
        break;
    case 2:
        if (size == 1 || size == 2) {
            if (index >= 0 && index < 16) {
                if (main_board.at(index) == "X " || main_board.at(index) == "O ")
                    return false;
                else
                    return true;
            }
            else
                return false;
        }
        else
            return false;
        break;
    case 3:
        if (size == 1 || size == 2) {
            if (index >= 0 && index < 22) {
                if (main_board.at(index) == "X " || main_board.at(index) == "O ")
                    return false;
                else
                    return true;
            }
            else
                return false;
        }
        else
            return false;
        break;

    }

    return true;

}
int BoardForServer::turn_char_to_int(const char* ans, int size) {
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
void BoardForServer::updateTheBoard(const char* ans, int size) {
    if (XorO % 2 == 0) {
        main_board.at(turn_char_to_int(ans, size) - 1) = "X ";
    }
    else {
        main_board.at(turn_char_to_int(ans, size) - 1) = "O ";
    }
    XorO++;
}
const int return_size_constChar(const char* msg) {
    int size = 0;
    while (msg[size] != '\0') size++;
    return size - 1;
}