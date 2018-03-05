#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */





/*

HI AARON!!!!!!!! CAN YOU SEE THIS ?!?!?!?!?!??!!?!!?!?!?!?! 
*/

// howdy do

Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = new Board;
    my_side = side;

    if (side == WHITE)
    {
    	opposite_side = BLACK;
    }
    else
    {
    	opposite_side = WHITE;
    }


   
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */


vector<Move*> Player::get_moves(Side side)
{
	vector<Move*> moves;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Move* move = new Move(i, j);
			if (board->checkMove(move, side) == true)
			{
				moves.push_back(move);
			}
			else
			{
				delete move;
			}
			
		}
	}
	
	return moves;

}

Move *Player::randomMove(vector<Move*> moves)
{
	unsigned int random = rand() % moves.size();
	Move* my_move = moves[random];
	return my_move;

}

Move *Player::doMove(Move *opponentsMove, int msLeft) 
{
    /*
    * TODO: Implement how moves your AI should play here. You should first
    * process the opponent's opponents move before calculating your own move
    */
    if (msLeft == 0)
    {
    	return nullptr;
    }


	this->board->doMove(opponentsMove, opposite_side);


	vector<Move*> moves = this->get_moves(this->my_side);
	if (moves.size() == 0)
	{
		return nullptr;
	}


	Move* myMove = randomMove(moves);
	this->board->doMove(myMove, my_side);
	return myMove;
}
