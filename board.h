#pragma once
#include <vector>

class Board {

public:
    Board(); // Constructor

    // Initialize the board to its initial state
    void set_new_board();

    // Print the current state of the board
    void print_board();

    // Check if a specific square is empty
    bool check_empty_square(int square);

    // Get a list of empty squares on the board
    std::vector<int> get_empty_squares();

    // Place a move on the board
    void move(int player, int square);

    // Remove a move from the board (undo)
    void remove(int square);

    // Check if a player has won the game
    int check_win();

    // Check if the game is a draw
    bool check_draw();

    // Size of the board (assuming a square board)
    static const int size = 3;

private:
    // The actual board data
    int board[size][size];

    // Check for a vertical win
    int check_vertical();

    // Check for a horizontal win
    int check_horizontal();

    // Check for a diagonal win
    int check_diagonal();
};
