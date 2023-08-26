#include "Board.h"
#include <iostream>
#include <stdexcept>
#include <random>
#include "custom_exception.h"
#include "ai.h"
#include "utils.h"
#include <vector>

AI::AI() {
    // Constructor
}

int AI::ai_random_move(Board& board, int player) {
    // Get a list of available empty squares
    std::vector<int> zero_indices = board.get_empty_squares();
    if (zero_indices.empty()) {
        THROW_CUSTOM_EXCEPTION("The board is full!");
    }

    // Select a random empty square
    int random_square = get_random_int(zero_indices);

    // Make the selected move on the board
    board.move(player, random_square);

    return random_square;
}

int AI::ai_best_move(Board& board, int player) {
    // Get a list of available empty squares
    std::vector<int> empty_squares = board.get_empty_squares();
    if (empty_squares.empty()) {
        THROW_CUSTOM_EXCEPTION("The board is full!");
    }

    int best_square = empty_squares[0];
    int best_score = -1000;

    // Handle the best starting move separately
    if (empty_squares.size() >= (board.size * board.size - 1)) {
        best_square = ai_get_best_start_move(board, player);
    }
    else {
        // Iterate through each empty square to find the best move
        for (int square : empty_squares) {
            board.move(player, square);

            int score;
            if (board.check_win() == 1) {
                score = -100 - board.get_empty_squares().size() * 10;
            }
            else if (board.check_win() == -1) {
                score = +100 + board.get_empty_squares().size() * 10;
            }
            else if (board.check_draw()) {
                score = 0;
            }
            else {
                score = minimax_score(board, -player);
            }

            // Update best move if a better score is found
            if (score >= best_score) {
                best_score = score;
                best_square = square;
            }

            board.remove(square);
        }
    }

    // Make the best move on the board
    board.move(player, best_square);
    return best_square;
}

int AI::minimax_score(Board& board, int player) {
    // Initialize best score based on player
    int best_score = player == -1 ? -1000 : 1000;
    std::vector<int> empty_squares = board.get_empty_squares();

    // Iterate through empty squares and calculate scores
    for (int square : empty_squares) {
        int score;
        board.move(player, square);

        if (board.check_win() == 1) {
            score = -100 - board.get_empty_squares().size() * 10;
        }
        else if (board.check_win() == -1) {
            score = +100 + board.get_empty_squares().size() * 10;
        }
        else if (board.check_draw()) {
            score = 0;
        }
        else {
            score = minimax_score(board, -player);
        }

        // Update best score based on player's turn
        if (player < 0) {
            best_score = score >= best_score ? score : best_score;
        }
        else {
            best_score = score <= best_score ? score : best_score;
        }

        board.remove(square);
    }

    return best_score;
}

int AI::ai_get_best_start_move(Board& board, int player) {
    // Get a list of available empty squares
    std::vector<int> empty_squares = board.get_empty_squares();
    std::vector<int> corner_sqs = { 0,2,6,8 };
    int best_corner_sq = get_random_int(corner_sqs);

    if (empty_squares.size() == (board.size * board.size)) {
        // If the board is empty, return a corner square
        return best_corner_sq;
    }
    else if (empty_squares.size() == (board.size * board.size - 1)) {
        // If only one move has been played, prioritize center or corner
        if (board.check_empty_square((board.size * board.size) / 2)) {
            return (board.size * board.size) / 2;
        }
        else {
            return best_corner_sq;
        }
    }
    else {
        THROW_CUSTOM_EXCEPTION("Board has more than 2 moves played");
    }
}
