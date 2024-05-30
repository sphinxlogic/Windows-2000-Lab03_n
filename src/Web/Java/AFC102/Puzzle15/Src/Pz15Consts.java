//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
public interface Pz15Consts
{
	public static final String IMG_NAMES[] = { 
		"piece_01.gif",	"piece_02.gif",	"piece_03.gif",	"piece_04.gif",
		"piece_05.gif",	"piece_06.gif",	"piece_07.gif",	"piece_08.gif",
		"piece_09.gif",	"piece_10.gif",	"piece_11.gif",	"piece_12.gif",
		"piece_13.gif",	"piece_14.gif",	"piece_15.gif",
		"bkgrnd01.gif",	"bkgrnd02.gif",	"bkgrnd03.gif",	"bkgrnd04.gif",
		"bkgrnd05.gif",	"bkgrnd06.gif",	"bkgrnd07.gif",	"bkgrnd08.gif",
		"bkgrnd09.gif",	"bkgrnd10.gif",	"bkgrnd11.gif",	"bkgrnd12.gif",
		"bkgrnd13.gif",	"bkgrnd14.gif",	"bkgrnd15.gif", "bkgrnd16.gif",
		"congrats.gif"};

	public static final int PIECES = 0;
	public static final int BKGRND = 15;
	public static final int CONGRATS = 31;
	public static final int NUM_IMAGES = 32;
	public static final int NUM_IMAGES_HOT = 15;
	public static final int NUM_BUTTONS = 15;

	public static final int PDIM = 4;
	public static final int SIZE = PDIM * PDIM;
	public static final int MAX_DEPTH = 200;
	public static final int MAX_MOVES = 3*MAX_DEPTH + 1;

	public static final int MIN_SCRAMBLE = 10;
	public static final int MAX_SCRAMBLE = 200;

	public static final int NO_MOVE =  0;
	public static final int O_UP	= -4;
	public static final int O_LEFT	= -1;
	public static final int O_RIGHT	=  1;
	public static final int O_DOWN	=  4;
	public static final int MOVES[] = { O_UP, O_LEFT, O_RIGHT, O_DOWN };

	public static final int M_BUTTON = 551;
	public static final int M_BLANK  = 552;
	public static final int M_SELECT = 553;

	public static final int S_RESET = 0;
	public static final int S_NORESET = 1;
	public static final int S_NOHOPE = 2;
	public static final int S_OPTFND = 3;

	public static final int ID_SOLUTION = 0;
	public static final int ID_UNDO = 1;
	public static final int ID_RESTART = 2;

	public final static String MRQ_CONGRATS = 
		"Congratulations! You have found an optimal solution. Press F2 for a new puzzle.";
	public final static String MRQ_OK =
		"You didn't find an optimal solution. Press F4 to restart this puzzle," +
		" or F2 for a new puzzle.";
	public final static String MRQ_OK_NOOPT =
		"Congratulations! You solved the puzzle. Press F4 to restart this puzzle," +
		" or F2 for a new puzzle.";
	public final static String MRQ_START =
		"Press F2 to scramble the puzzle. You can then unscramble it, or let the " +
		"computer unscramble it for you.";
	public final static String MRQ_SEARCHING = 
		"Searching for optimal solution, so far I have expanded ";
	public final static String MRQ_NOTSEARCHING = 
		"Searching for optimal solution... NOT!";
	public final static String MRQ_OPTIMALFND = 
		"I have found an optimal solution, you can display it by pressing F3.";
	public final static String MRQ_NOHOPE = 
		"You have no hope of finding the optimal solution, you can restart at " +
		"the beginning by pressing F4.";

	public final static String CONGRATS_STR1 = 
						 "Congratulations! You solved the puzzle.\n\n";
	public final static String CONGRATS_STR2 = 
						 "Press F2 to start a new game or F4 to restart\n" +
						 "the puzzle you just solved.";
	public final static String CONGRATS_OPT = 
						 "Press F2 to start a new game, F4 to restart\n" +
						 "the puzzle you just solved, or F3 to display\n" +
						 "the optimal solution found by your computer.";
}

