#pragma once
#include "board.h"

class AI {

public:
    // Constructor
    AI();

    // Generate a random move for the AI
    int ai_random_move(Board& board, int player);

    // Find the best move for the AI using the minimax algorithm
    int ai_best_move(Board& board, int player);

private:
    // Calculate the score of a move using the minimax algorithm
    int minimax_score(Board& board, int player);

    // Determine the best starting move for the AI
    int ai_get_best_start_move(Board& board, int player);

};
