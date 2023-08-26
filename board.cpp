#include "Board.h"
#include <iostream>
#include <stdexcept>
#include "custom_exception.h"
#include <vector>
#include <string>

// Constructor: Initializes the board by setting all squares to empty
Board::Board() {
    set_new_board();
}

// Initialize the board to its initial state (all squares empty)
void Board::set_new_board() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = 0;
        }
    }
}

// Print the current state of the board
void Board::print_board() {
    for (int i = 0; i < size; i++) {
        std::cout << "|";
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 1) {
                std::cout << "X"; // Print 'X' for player 1
            }
            else if (board[i][j] == -1) {
                std::cout << "O"; // Print 'O' for player -1
            }
            else if (board[i][j] == 0) {
                std::cout << " "; // Print empty space for unoccupied squares
            }
            std::cout << "|";
        }
        std::cout << "\n";
    }
}

// Check if a specific square is empty
bool Board::check_empty_square(int square) {
    if (square < 0 || square > 8) {
        THROW_CUSTOM_EXCEPTION("Parameter square should be between 0-8");
    }
    int row = square / size;
    int col = square % size;

    return board[row][col] == 0;
}

// Get a list of empty squares on the board
std::vector<int> Board::get_empty_squares() {
    std::vector<int> zero_indices;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                int index = i * size + j;
                zero_indices.push_back(index);
            }
        }
    }
    return zero_indices;
}

// Place a move on the board
void Board::move(int player, int square) {
    if (player != -1 && player != 1) {
        THROW_CUSTOM_EXCEPTION("Player parameter should be 1 or -1");
    }

    int row = square / size;
    int col = square % size;

    if (check_empty_square(square)) {
        board[row][col] = player;
    }
    else {
        THROW_CUSTOM_EXCEPTION("Selected square should be empty");
    }
}

// Remove a move from the board (undo)
void Board::remove(int square) {
    board[square / size][square % size] = 0;
}

// Check if a player has won the game
int Board::check_win() {
    int vertical = check_vertical();
    int horizontal = check_horizontal();
    int diagonal = check_diagonal();

    if (vertical == 1 || horizontal == 1 || diagonal == 1) {
        return 1; // Player 1 wins
    }
    else if (vertical == -1 || horizontal == -1 || diagonal == -1) {
        return -1; // Player -1 (AI) wins
    }
    else {
        return 0; // No winner yet
    }
}

// Check for a vertical win
int Board::check_vertical() {
    for (int col = 0; col < size; col++) {
        int sum = 0;

        for (int row = 0; row < size; row++) {
            sum += board[row][col];
        }

        if (sum == size) {
            return 1; // Player 1 wins vertically
        }
        else if (sum == -size) {
            return -1; // Player -1 (AI) wins vertically
        }
    }
    return 0; // No vertical win
}

// Check for a horizontal win
int Board::check_horizontal() {
    for (int row = 0; row < size; row++) {
        int sum = 0;

        for (int col = 0; col < size; col++) {
            sum += board[row][col];
        }

        if (sum == size) {
            return 1; // Player 1 wins horizontally
        }
        else if (sum == -size) {
            return -1; // Player -1 (AI) wins horizontally
        }
    }
    return 0; // No horizontal win
}

// Check for a diagonal win
int Board::check_diagonal() {
    int sum = 0;

    for (int i = 0; i < size; i++) {
        sum += board[i][i];
    }

    if (sum == size) {
        return 1; // Player 1 wins diagonally
    }
    else if (sum == -size) {
        return -1; // Player -1 (AI) wins diagonally
    }

    sum = 0;
    for (int i = 0; i < size; i++) {
        sum += board[i][size - i - 1];
    }

    if (sum == size) {
        return 1; // Player 1 wins diagonally
    }
    else if (sum == -size) {
        return -1; // Player -1 (AI) wins diagonally
    }
    return 0; // No diagonal win
}

// Check if the game is a draw
bool Board::check_draw() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                return false; // Game is not a draw yet
            }
        }
    }
    return true; // All squares are occupied, game is a draw
}
