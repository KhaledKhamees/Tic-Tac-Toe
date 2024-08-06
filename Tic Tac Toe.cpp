#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

// Define the size of the board as a constant
const int XO_SIZE = 4;

// Function to initialize the game board
void initializeBoard(char board[][XO_SIZE]) {
    for (int i = 0; i < XO_SIZE; ++i) {
        for (int j = 0; j < XO_SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}

// Function to display the game board
void displayBoard(char board[][XO_SIZE]) {
    cout << "  ";
    for (int i = 0; i < XO_SIZE; ++i) {
        cout << i << " ";
    }
    cout << endl;

    for (int i = 0; i < XO_SIZE; ++i) {
        cout << i << " ";
        for (int j = 0; j < XO_SIZE; ++j) {
            char symbol = board[i][j];
            // Change text color for 'X' (red) and 'O' (blue)
#ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            if (symbol == 'X')
                SetConsoleTextAttribute(hConsole, 12); // Red color for 'X'
            else if (symbol == 'O')
                SetConsoleTextAttribute(hConsole, 9); // Blue color for 'O'
#else
            if (symbol == 'X')
                cout << "\033[31m"; // Red color for 'X' (ANSI escape code)
            else if (symbol == 'O')
                cout << "\033[34m"; // Blue color for 'O' (ANSI escape code)
#endif
            cout << symbol << " ";
            // Reset text color
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, 7); // Reset to default color
#else
            cout << "\033[0m"; // Reset to default color (ANSI escape code)
#endif
        }
        cout << endl;
    }
}

// Function to check if a player has won
bool checkWin(char player, char board[][XO_SIZE]) {
    // Check rows and columns
    for (int i = 0; i < XO_SIZE; ++i) {
        bool row_win = true;
        bool col_win = true;
        for (int j = 0; j < XO_SIZE; ++j) {
            if (board[i][j] != player)
                row_win = false;
            if (board[j][i] != player)
                col_win = false;
        }
        if (row_win || col_win)
            return true;
    }

    // Check diagonals
    bool diag1_win = true;
    bool diag2_win = true;
    for (int i = 0; i < XO_SIZE; ++i) {
        if (board[i][i] != player)
            diag1_win = false;
        if (board[i][XO_SIZE - 1 - i] != player)
            diag2_win = false;
    }

    return diag1_win || diag2_win;
}

// Function to check if the game has ended in a draw
bool checkDraw(char board[][XO_SIZE]) {
    for (int i = 0; i < XO_SIZE; ++i) {
        for (int j = 0; j < XO_SIZE; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Function to ask the user if they want to play again
bool playAgain() {
    char response;
    cout << "Do you want to play again? (y/n): ";
    cin >> response;
    return (response == 'y' || response == 'Y');
}

int main() {
    char board[XO_SIZE][XO_SIZE]; // Define the game board

    // Main game loop
    while (true) {
        initializeBoard(board); // Initialize the game board

        char currentPlayer = 'X'; // Player 'X' starts the game
        bool gameOver = false;

        // Game loop
        while (!gameOver) {
            system("cls"); // Clear the command prompt (for Windows)

            // Display the current state of the game board
            displayBoard(board);

            int row, col;
            cout << "Player " << currentPlayer << "'s turn. Enter row and column (e.g., 0 0): ";
            cin >> row >> col;

            // Check if the move is valid
            if (row < 0 || row >= XO_SIZE || col < 0 || col >= XO_SIZE || board[row][col] != ' ') {
                cout << "Invalid move. Try again." << endl;
                continue;
            }

            // Update the game board
            board[row][col] = currentPlayer;

            // Check win and draw conditions
            if (checkWin(currentPlayer, board)) {
                system("cls");
                // Display the final state of the game board
                displayBoard(board);
                cout << "Player " << currentPlayer << " wins!" << endl;
                gameOver = true;
            }
            else if (checkDraw(board)) {
                system("cls");
                // Display the final state of the game board
                displayBoard(board);
                cout << "It's a draw!" << endl;
                gameOver = true;
            }

            // Switch to the next player
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }

        if (!playAgain())
            break; // Exit the loop if the user doesn't want to play again
    }

    cout << "Thanks for playing!" << endl;

    return 0;
}
