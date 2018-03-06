#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <vector> 
#include <cstdlib>
#include <stdlib.h>
#include "common.hpp"
#include "board.hpp"

using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Board* board;

    Move* minimax();
    int get_num_moves(Side side);
    int heuristicScore(Move* move);
    int naiveHeuristic(Move* move, Board* board, Side side);
    Move *randomMove(vector<Move*> moves);
    vector<Move*> get_moves(Side side, Board* board);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;


private:
	Side my_side;
	Side opposite_side;
};

#endif
