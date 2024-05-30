//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.lang.Math;
import com.ms.ui.*;
import com.ms.fx.*;

public class Pz15Solver extends Pz15Data implements Runnable, Pz15Consts
{
	public int costbound;

	private Pz15Callbacks pzctrl;
	private ChildNode movelist[] = new ChildNode[MAX_MOVES];
	private int moveptr[] = new int[MAX_DEPTH];
	private int	depth;
	private long total_nodes, num_nodes;
	private UIMessageBox optsoln = null;
	private String solnstr = new String("");
	private boolean firstdisplay;

	public Pz15Solver()
	{
		super();
		solved = false;
	}

	// In lieu of a constructor
	public void registerCallback(Pz15Callbacks pzctrl, UIFrame frame)
	{
		this.pzctrl = pzctrl;
		// Create Message Box for displaying optimal solution
		optsoln = new UIMessageBox(frame, "Optimal Solution", "",
									UIMessageBox.INFORMATION, UIButtonBar.OK);
		optsoln.setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
	}
	
	public void run()
	{
		firstdisplay = true;
		moveptr[0] = 0;
		movelist[0] = new ChildNode(NO_MOVE, initial_cost);

		// Check to see if goal puzzle is passed in
		if ( movelist[0].cost == 0 ) 
			return;

		costbound = movelist[0].cost;

		total_nodes = 0;
		num_nodes = 0;

		while ( !solved ) {
			depth = 1;
			genChildren(movelist[0]);
			while ( depth > 0 ) {
				// if there are no children, BACKTRACK
				if ( moveptr[depth] == moveptr[depth-1] ) {
					depth--;
					if ( depth != 0 )
						privUpdate(-movelist[moveptr[depth]--].move);
				}
				else {
					ChildNode node = movelist[moveptr[depth]];
					privUpdate(node.move);
					if ( solved )
						break; // break out of depth while loop
					else  {
						depth++;
						genChildren(node);
					}
				}
			}			

			if ( !solved ) 
				costbound += 2;
			else
				pzctrl.setMarqueeString(MRQ_OPTIMALFND, S_RESET);

			pzctrl.setOptMoves(costbound, solved);
		}
		// If we get to here puzzle is solved
		pzctrl.enableShowSolution(true);
	}

	public void displayOptimalSolution()
	{
		if ( firstdisplay ) {
			firstdisplay = false;
			solnstr = "" + total_nodes + " total nodes expanded.\n\n";

			int navmode = pzctrl.getNavMode();
			for ( int i = 0; i <= depth; i++ ) {
				switch (movelist[moveptr[i]].move) {
				case O_UP: solnstr += (navmode == M_BUTTON ? "D":"U"); break;
				case O_LEFT: solnstr += (navmode == M_BUTTON ? "R":"L"); break;
				case O_RIGHT: solnstr += (navmode == M_BUTTON ? "L":"R"); break;
				case O_DOWN: solnstr += (navmode == M_BUTTON ? "U":"D"); break;
				}
				if ( (i != 0) && (i != depth) && ((i % 4) == 0) ) solnstr += ",";
				if ( (i != 0) && (i != depth) && ((i % 20) == 0) ) solnstr += "\n";
			}
			solnstr += ".\n";
			optsoln.setText(solnstr);
		}
		optsoln.doModal();
	}

	private void privUpdate(int move)
	{
		current_cost += getCost(move);
		current[hole] = current[hole+move];
		hole += move;
		current[hole] = 0;
		if ( current_cost == 0 )
			solved = true;
	}

	private void genChildren(ChildNode node)
	{
		int i, index;
		int numChildren = 0;
		int possible[] = { NO_MOVE, NO_MOVE, NO_MOVE, NO_MOVE };

		moveptr[depth] = moveptr[depth-1];

		// Find out which moves are possible
		for ( i = 0; i < 4; i++ )
			possible[i] = validateMove(MOVES[i]);
		
		for ( i = 0; i < 4; i++ ) {
			// don't do NO_MOVE or reverse move
			if ( !((possible[i] == NO_MOVE) || (possible[i] == -node.move)) ) {
				int cost = node.cost + 1 + getCost(possible[i]);
				if ( cost <= costbound ) {
					numChildren++;
					index = ++moveptr[depth];
					addChild(numChildren, index, possible[i], cost);
				}
			}
		}
		if ( numChildren > 0 ) {
			total_nodes++;
			num_nodes++;
			if ( num_nodes == 50000 )
			{
				num_nodes = 0;
				pzctrl.setMarqueeString(MRQ_SEARCHING + genDisplay(total_nodes) + " nodes.",
										S_NORESET);
			}
		}
	}

	private void addChild(int numChildren, int index, int move, int cost)
	{
		switch (numChildren) {
		case 4:
			if ( cost > movelist[index-3].cost) {
				movelist[index] = movelist[index-1];
				movelist[index-1] = movelist[index-2];
				movelist[index-2] = movelist[index-3];
				movelist[index-3] = new ChildNode(move, cost);
				break;
			}
			// FALL-THROUGH when if statement is FALSE
		case 3:
			if ( cost > movelist[index-2].cost ) {
				movelist[index] = movelist[index-1];
				movelist[index-1] = movelist[index-2];
				movelist[index-2] = new ChildNode(move, cost);
				break;
			}
			// FALL-THROUGH when if statement is FALSE
		case 2:
			if ( cost > movelist[index-1].cost ) {
				movelist[index] = movelist[index-1];
				movelist[index-1] = new ChildNode(move, cost);
				break;
			}
			// FALL-THROUGH when if statement is FALSE
		case 1:
			movelist[index] = new ChildNode(move, cost);
			break;

		default:
			break;
		}
	}

	private String genDisplay(long num)
	{
		if ( num >= 1000000000000L )	return "";

		String disp = "";
		int i, firstnz;
		long digits[] = new long[12];

		for ( i = 0; i < 12; i++ )
			digits[11-i] = (num/Math.round(Math.pow(10,i))) % 10;

		for ( firstnz = 0; firstnz < 12; firstnz++ )
			if ( digits[firstnz] != 0 )	break;

		switch( firstnz % 3 ) {
		case 0: disp += digits[firstnz] + "" + digits[firstnz+1] + "" + digits[firstnz+2]; break;
		case 1: disp += digits[firstnz] + "" + digits[firstnz+1] + "." + digits[firstnz+2]; break;
		case 2: disp += digits[firstnz] + "." + digits[firstnz+1] + "" + digits[firstnz+2]; break;
		}

		if ( firstnz < 3 ) disp += " billion";
		else if ( firstnz < 6 ) disp += " million";
		else if ( firstnz < 9 ) disp += " thousand";

		return disp;
	}
}

class ChildNode
{
	public int move;
	public int cost;

	public ChildNode(int move, int cost)
	{
		this.move = move;
		this.cost = cost;
	}
}