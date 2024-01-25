#include <iostream>
#include <vector>

using namespace std;

class TicTacToe {
public:
    /* Constructor */
    TicTacToe() {
        /* Initialize defaults here */
    }

    /* This is your game board*/
    vector<vector<char>> gameBoard
            {
                    {'1', '2', '3'},
                    {'4', '5', '6'},
                    {'7', '8', '9'}
            };

    /* This prints your game board*/
    void printGameBoard() {
        for (int i = 0; i < gameBoard.size(); i++) {
            for (int j = 0; j < gameBoard[i].size(); j++) {
                cout << gameBoard[i][j] << " ";
            }
            cout << endl;
        }
    }

    /* This method modifies the game board*/
    void modifyGameBoard(char player, int position) {
        for (int i = 0; i < gameBoard.size(); i++) {
            for (int j = 0; j < gameBoard[i].size(); j++) {
                if (gameBoard[i][j] == position + '0') {
                    gameBoard[i][j] = player;
                    return;
                }
            }
        }
    }

    /* This method checks if a player has won*/
    bool checkWinner(char player) {
        // Check rows and columns
        for (int i = 0; i < 3; i++) {
            if ((gameBoard[i][0] == player && gameBoard[i][1] == player && gameBoard[i][2] == player) ||
                (gameBoard[0][i] == player && gameBoard[1][i] == player && gameBoard[2][i] == player)) {
                return true;
            }
        }

        // Check diagonals
        if ((gameBoard[0][0] == player && gameBoard[1][1] == player && gameBoard[2][2] == player) ||
            (gameBoard[0][2] == player && gameBoard[1][1] == player && gameBoard[2][0] == player)) {
            return true;
        }

        return false;
    }
};

int main() {
    TicTacToe game;
    char currentPlayer = 'X';
    int position;

    cout << "TIC TAC TOE" << endl;

    while (true) {
        game.printGameBoard();

        cout << "Player " << currentPlayer << " Enter Position: ";
        cin >> position;

        if (position < 1 || position > 9) {
            cout << "Invalid position. Please enter a number between 1 and 9." << endl;
            continue;
        }

        game.modifyGameBoard(currentPlayer, position);

        if (game.checkWinner(currentPlayer)) {
            cout << "Player " << currentPlayer << " Wins!!!" << endl;
            break;
        }

        // Switch player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    cout << "GAME OVER" << endl;

    return 0;
}