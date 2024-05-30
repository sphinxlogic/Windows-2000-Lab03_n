//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.util.Stack;
import java.util.Random;
import java.lang.Math;

public class Pz15Data implements Pz15Consts
{
	public int current[] = new int[16];
	public int original[] = new int[16];
	public int hole;
	public Stack movstk;
	public int initial_cost, current_cost;
	public boolean solved;

	public Pz15Data()
	{
		setToGoal();
	}

	public void genNew(int numscramble) 
	{
		setToGoal();
		scramble(numscramble);
		init();
	}

	private void setToGoal()
	{
		// Set Puzzle to goal
		for ( int i = 0 ; i < SIZE ; i++ ) {
			original[i] = (i + 1) % SIZE; // original[i] = i;
			current[i] = original[i];
		}
		hole = 15; // hole = 0;
		solved = true;
	}

	public void genNew(int puzzle[])
	{
		for ( int i = 0; i < SIZE; i++ ) {
			original[i] = puzzle[i];
			if ( puzzle[i] == 0 )
				hole = i;
		}
		init();
	}

	public void init()
	{
		movstk = new Stack();

		// Set current to original
		resetToOrg();

		initial_cost = getCost();
		current_cost = initial_cost;

		if ( initial_cost != 0 )
			solved = false;
	}

	public void scramble(int num)
	{
		// Since we cannot generate a random puzzle and guarantee or even 
		// verify that it is achievable. We will take a goal puzzle and 
		// scramble it by making moves.
		
		Random rand = new Random();
		int move, lastmove = NO_MOVE, i = 0;

		while ( i < ((num <= MAX_DEPTH) ? num : MAX_DEPTH) ) {
			move = Math.abs(rand.nextInt()) % 4;
			move = validateMove(MOVES[move]);
			if ( (move != NO_MOVE) && (move != -lastmove) ) {
				lastmove = move;
				i++;
				// Swap hole and button that corresponds to move
				original[hole] = original[hole+move];
				original[hole+move] = 0;
				// Set hole index to point to hole
				hole += move;
			}
		}
	}

	// gets cost of original puzzle
	public int getCost()
	{
		int cost = 0;

		for ( int i = 0; i < SIZE; i++ ) {
			if ( original[i] != 0 )
				cost += Math.abs(((original[i]-1)/4) - i/4) + 
					    Math.abs(((original[i]-1)%4) - i%4);
				//cost += Math.abs(((original[i])/4) - i/4) + 
				//	    Math.abs(((original[i])%4) - i%4);
		}
		return cost;
	}

	/* 
	** getCost - Get cost of making move, either increases by 1 or 
	**           decreases by 1.
	**
	** Determines cost by determining the row/column that the piece which
	** the hole will be swapped with belongs in, and then determining if 
	** piece will be move farther away from it's goal (+1), or closer to its
	** goal (-1).
	**
	*/
	public int getCost(int move)
	{
		int goal;

		switch ( move ) {
		case O_UP:
		case O_DOWN:
			goal = (current[hole+move] - 1) / 4;
			//goal = current[hole+move] / 4;
			if ( Math.abs(hole/4 - goal) > Math.abs((hole+move)/4 - goal) )
				return +1;
			else
				return -1;

		case O_LEFT:
		case O_RIGHT:
			goal = (current[hole+move] - 1) % 4;
			//goal = current[hole+move] % 4;
			if ( Math.abs(hole%4 - goal) > Math.abs((hole+move)%4 - goal) )
				return +1;
			else
				return -1;

		default: 
			break;
		}
		return 0;
	}

	// returns offset that hole will be moving
	public int validateMove(int move)
	{
		switch ( move ) {
		case O_UP: if ( hole >= 4 ) return O_UP; break;
		case O_LEFT: if ( (hole % 4) != 0 ) return O_LEFT; break;
		case O_RIGHT: if ( (hole % 4) != 3 ) return O_RIGHT; break;
		case O_DOWN: if ( hole < 12 ) return O_DOWN; break;
		default: break;
		}
		return NO_MOVE;
	}

	public void resetToOrg()
	{
		for ( int i = 0; i < SIZE; i++ ) {
			current[i] = original[i];
			if ( original[i] == 0 )
				hole = i;
		}
	}

	public void update(int move)
	{
		if ( !movstk.empty() ) {
			Object stktop = movstk.peek();

			if ( (stktop instanceof Integer) && 
				 (((Integer)stktop).intValue() == -move) )
				movstk.pop();
			else
				movstk.push(new Integer(move));
		}
		else
			movstk.push(new Integer(move));

		current_cost += getCost(move);
		current[hole] = current[hole+move];
		hole += move;
		current[hole] = 0;
		if ( current_cost == 0 )
			solved = true;
	}
}