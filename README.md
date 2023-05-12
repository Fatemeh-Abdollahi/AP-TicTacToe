# AP-TicTacToe
this is a project for AP in AUT

Tic-Tac-Toe

This is a two-player game which runs using one server and two clients. After running the game, a menu will appear on each player’s screen.On the menu ,players can see the status of the clients. They can as well send a request to the fellow player for starting the game.Following the acceptance, an another menu will show up, on which the players can choose a board out of 3 different ones.Then the game will start.

Alternatively the players place the pieces on the chosen square. Each player is given 30 seconds to choose where to place the piece. If the player fail to do so within 30 seconds, the game will automatically come to an end and the other player will be the winner.If one loses the connection to the server during the game, they’ll have to re-connect within the remaining time, or again the other player will be announced as the winner.

Players should, depending on the board they’ve chosen, place the pieces in a row of three pieces on any line drawn on the board.The client who achieves this, will win and the game will end.

also If during the game, users enter wrong inputs, they will be informed that the input is not acceptable.

In this code ,we used "Boost" library which allows us to communicate between the server and clients.
