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

int Player::get_num_moves(Side side)
{
	int count = 0;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Move* move = new Move(i, j);
			if (board->checkMove(move, side) == true)
			{
				count++;
			}
			else
			{
				delete move;
			}
		}
	}
	return count;
}



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


int Player::heuristicScore(Move* move)
{
	int my_moves;
	int opp_moves;
	int mobility;
	//int score;

	

	
	// get mobility
	Board* copy = this->board->copy();
	copy->doMove(move, my_side);

	my_moves = get_num_moves(my_side);
	opp_moves = get_num_moves(opposite_side);
	mobility = my_moves - opp_moves;


	//getting tokens taken on turn
	int tokens_before;
	int tokens_after;
	int tokens_taken;
	tokens_before = this->board->count(my_side);
	tokens_after = copy->count(my_side);
	tokens_taken = tokens_after - tokens_before;

	//cerr << "mobility:" << mobility << endl << "tokens:" << tokens_taken << endl;

	//checking corners
	int corner = 0;
	int x, y;
	x = move->x;
	y = move->y;
	if ((x==0 && y == 0) || (x==7 && y==7) || (x==0 && y==7) || (x==7 && y==0))
	{
		corner = 30;
		cerr << "CORNER" << endl;
		
	}

	//checking edges
	int edge = 0;
	if ( (x==0) || (x==7) || (y == 0) || (y==7) )
	{
		edge = 7;
	}

	//checking *bad* spots
	int bad = 0;
	if ( (x==1 && y==1) || (x==6 && y==6) || (x==1 && y==6) || (x==6 && y ==1))
	{
		bad = -5;
	}



	return (mobility * 1.5)  + (tokens_taken * 1.5) + corner + edge + bad;



}

Move *Player::doMove(Move *opponentsMove, int msLeft) 
{
    /*
    * TODO: Implement how moves your AI should play here. You should first
    * process the opponent's opponents move before calculating your own move
    */
	int best;
	int best_index = 0;
	int current;

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

	/* Activate the below line to use a random player
	Move* myMove = randomMove(moves); */
	best = heuristicScore(moves[0]);
	for (unsigned int i = 1; i < moves.size(); i++)
	{
		current = heuristicScore(moves[1]);
		if (current > best)
		{
			best = current;
			best_index = i;
		}
	}
	Move* myMove = moves[best_index];

	this->board->doMove(myMove, my_side);
	return myMove;
}
