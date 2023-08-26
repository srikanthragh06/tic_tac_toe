#include <random>
#include <iostream>
#include <vector>
#include "custom_exception.h"
#include "board.h"
#include "ai.h"
#include "utils.h"

int main() {
    using namespace std;

    try {
        // Initialize the game components
        Board board;
        bool game_over = false;
        AI ai;
        int turn = -1; // -1 represents 'O' and 1 represents 'X'

        cout << "TIC-TAC-TOE" << endl << endl;

        while (!game_over) {
            if (turn == 1) {
                cout << "X turn!" << endl;

                bool correct_input = false;
                while (!correct_input) {
                    try {
                        int input_square;
                        cout << "Enter square value (0-8) :";
                        cin >> input_square;
                        if (std::cin.fail()) {
                            THROW_CUSTOM_EXCEPTION("Input square should be an integer");
                        }

                        cout << "Entered input square is " << input_square << endl;
                        board.move(turn, input_square);
                        correct_input = true;
                    }
                    catch (const CustomException& e) {
                        // Handle input exceptions
                        std::cerr << "Exception occurred: " << e.what() << std::endl;
                        std::cerr << "File: " << e.getFile() << ", Line: " << e.getLine() << std::endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
            }
            else if (turn == -1) {
                cout << "O turn!" << endl;
                // Choose the best move for 'O' using AI
                int input_square = ai.ai_best_move(board, turn);
                cout << "Entered input square is " << input_square << endl;
            }

            // Print the current game board
            board.print_board();
            cout << endl << endl;

            // Check if the game is over
            if (board.check_win() == 1) {
                game_over = true;
                cout << "X wins!" << endl;
            }
            else if (board.check_win() == -1) {
                game_over = true;
                cout << "O wins!" << endl;
            }
            else if (board.check_draw()) {
                game_over = true;
                cout << "The game is a draw!" << endl;
            }

            // Switch turns between 'X' and 'O'
            turn *= -1;
        }

    }
    catch (const CustomException& e) {
        // Handle exceptions at the top level
        std::cerr << "Exception occurred: " << e.what() << std::endl;
        std::cerr << "File: " << e.getFile() << ", Line: " << e.getLine() << std::endl;
    }

    return 0;
}
