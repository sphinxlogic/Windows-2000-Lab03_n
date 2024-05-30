//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//

public interface Pz15Callbacks
{
	public void restartGame();
	public void newGame();
	public void stopSolver();
	public void undoMove();
	public void enableUndo(boolean enable);
	public void enableRestart(boolean enable);
	public void enableShowSolution(boolean enable);
	public void displayOptimalSolution();
	public void displayOptionsDialog();
	public void setNumMoves(int nmoves);
	public void setMinMoves(int nmoves);
	public void setOptMoves(int nmoves, boolean optimal);
	public void setMarqueeString(String str, int state);
	public int getNavMode();
	public int getOptimalCost(); 
	public boolean getSolverStatus();
	public void congratulate();
}
