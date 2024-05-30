//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.*;

class Pz15ControlPanel extends UIPanel implements Pz15Consts, Pz15Callbacks, Runnable
{
	private Pz15GamePanel	gameboard;
	private	UIFrame			frame;
	private Pz15Options		props;
	private Pz15Data		puzzle;
	private Pz15Menu		menu;
	private Pz15InfoPanel	info;
	private Pz15Solver		pzsolver;
	private Thread			solver;
	private boolean			can_undo, can_restart;

	public Pz15ControlPanel(UIApplet applet, UIFrame frame)
	{
		setLayout(new UIBorderLayout(0,0));

		// Options Property Pages
		if ( applet != null )
			this.frame = FxToolkit.getHelperUIFrame();
		else
			this.frame = frame;

		props = new Pz15Options(this.frame, "Game...", true, UIPropertyDialog.MEDIUM);
		props.addPage("...Options", new Pz15PropGame(props));
		props.addPage("...Navigation", new Pz15PropNav(props));

		can_undo = false; can_restart = false;

		puzzle = new Pz15Data();

		// Initialized load on demand images
		Pz15Images.init(applet, frame);

		gameboard = new Pz15GamePanel(puzzle, this);
		gameboard.drawBlank();
		menu = new Pz15Menu(this, applet == null);
		info = new Pz15InfoPanel();

		//
		// Create instance of solver whether he is used or not.
		//   pzsolver will always be instantiated, solver (the thread )
		//   will only be instantiated if needed.
		//
		pzsolver = new Pz15Solver();
		pzsolver.registerCallback(this, this.frame);

		add(menu, "North");
		UIPanel pnl = new UIPanel();
		pnl.setLayout(new UISplitLayout(UISplitLayout.HORIZONTAL,300));
		pnl.add(gameboard, "nw"); pnl.add(info, "se");
		add(pnl, "Center");
	}

	public void run()
	{
		// Display Options
		Object ret = props.display();
		if ( (ret instanceof IUIComponent) && 
				(((IUIComponent)ret).getID() != UIButtonBar.ID_CANCEL) ) {
			// Scramble puzzle according to user input
			puzzle.genNew(props.numscramble);
			// Start new game
			newGame();
		}
		else
			setMarqueeString(MRQ_START, S_RESET);
		// Turn on marquee
		info.marquee.is_on = true;
		// give focus to gameboard
		gameboard.requestFocus();
	}

	public void initialize()
	{
		Thread th = new Thread(this);
		th.start();
	}

	public void hideProperties()
	{
		if ( props != null )
			props.setVisible(false);
	}

	public void restartGame()
	{
		puzzle.init();
		reset();
		// If solver hasn't solved the puzzle, it will update marquee with progress.
		if ( pzsolver.solved ) 
			setMarqueeString(MRQ_OPTIMALFND, S_OPTFND);
	}

	public void newGame()
	{
		stopSolver(); // You can call stop on an already stopped thread
		puzzle.genNew(props.numscramble);
		reset();
		enableShowSolution(false);
		setOptMoves(puzzle.initial_cost, puzzle.solved);
		startSolver();
	}

	private void reset()
	{
		gameboard.removeAll();
		gameboard.draw();
		gameboard.setVisible(true);
		gameboard.setInitialFocus();
		setNumMoves(0);
		setMinMoves(puzzle.initial_cost);
		enableUndo(false);
		enableRestart(false);
	}

	private void initSolver()
	{
		pzsolver.genNew(puzzle.original);
		solver = new Thread(pzsolver, "Solver");
		solver.setPriority(Thread.MIN_PRIORITY);
		solver.start();
		setMarqueeString(MRQ_SEARCHING + " 0 nodes.", S_RESET);
	}

	private void startSolver()
	{
		if ( props.cpuactive ) {
			if ( solver != null ) {
				// you can't start a thread that has been stopped, you need 
				//  to create a new instance
				stopSolver();
				initSolver();
			}
			else if ( !pzsolver.solved )
				initSolver();
		}
		else {
			stopSolver();
			solver = null;
			setMarqueeString(MRQ_NOTSEARCHING, S_RESET);
		}
	}

	public void stopSolver()
	{
		if ( solver != null )
			solver.stop();
	}

	public void undoMove()
	{
		if ( puzzle.solved ) 
			return;

		if ( puzzle.movstk.size() > 0 ) {
			Object move = puzzle.movstk.peek();
			if ( move instanceof Integer ) {
				int mov = -((Integer)move).intValue();
				gameboard.update(mov);
			}
		}
	}

	public void displayOptionsDialog()
	{
		boolean solversuspended = false;
		if ( solver != null ) {
			synchronized (this) {
				if ( solver.isAlive() ) {
					solver.suspend();
					solversuspended = true;
				}
			}
		}
		
		info.marquee.is_on = false;
		props.display();
		info.marquee.is_on = true;
		gameboard.requestFocus();

		if ( props.cpuactive ) {
			if ( !pzsolver.solved ) {
				if ( solversuspended )
					solver.resume();
				else
					startSolver();
			}
		}
		else {
			if ( solversuspended )
				solver.stop();
			pzsolver.solved = false;
		}
	}

	public void setOptMoves(int nmoves, boolean optimal)	
	{ 
		if ( optimal )
			info.optmoves.setName("Exactly " + nmoves + " moves");
		else
			info.optmoves.setName("At least " + nmoves + " moves"); 
	}

	public void displayOptimalSolution()
	{ 
		info.marquee.is_on = false;
		pzsolver.displayOptimalSolution();
		info.marquee.is_on = true;
		gameboard.requestFocus();
	}

	public void setMarqueeString(String str, int state)
	{
		info.mrqstr = str;
		// if we are already displaying the correct string do not reset
		if ( (state == S_RESET) || ((state != S_NORESET) && (state != info.marquee.state)) )
			info.marquee.reset = true;
		info.marquee.state = state;
	}

	public void congratulate()
	{
		String str = new String(CONGRATS_STR1);

		if ( pzsolver.solved )
			str += CONGRATS_OPT;
		else
			str += CONGRATS_STR2;

		UIMessageBox mbox = new UIMessageBox(frame, "Congratulations!", str, 
												Pz15Images.get(CONGRATS),
												new UIButtonBar(UIButtonBar.OK, 
																UIButtonBar.RAISED));
		mbox.setFont(new FxFont("Dialog", FxFont.PLAIN, 14));
		info.marquee.is_on = false;
		mbox.doModal();
		info.marquee.is_on = true;
	}

	public void setNumMoves(int nmoves)	{ info.nummoves.setName("" + nmoves); }

	public void setMinMoves(int nmoves)	{ info.minmoves.setName("" + nmoves); }

	public void enableUndo(boolean enable)
	{
		can_undo = enable;
		menu.enable(ID_UNDO, enable);
	}

	public void enableRestart(boolean enable)
	{
		can_restart = enable;
		menu.enable(ID_RESTART, enable);
	}

	public int getNavMode() { return props.navmode; }

	public boolean getSolverStatus() { return pzsolver.solved; }

	public int getOptimalCost() { return pzsolver.costbound; }

	public void enableShowSolution(boolean enable) { menu.enable(ID_SOLUTION, enable); }

	public boolean keyDown(Event e, int key)
	{
		if ( e.modifiers == 0 ) {
			switch ( key ) {
			case Event.F2: newGame(); break;
			case Event.F4: if ( can_restart ) restartGame(); break;
			case Event.F3: if ( pzsolver.solved ) displayOptimalSolution(); break;
			case Event.F7: displayOptionsDialog(); break;
			default: return super.keyDown(e, key);
			}
		}
		else if ( e.modifiers == Event.CTRL_MASK ) {
			switch ( key ) {
			case 'x'-'a'+1:
				stopSolver();
				System.exit(0);
				break;
			case 'z'-'a'+1:
				if ( can_undo ) undoMove();
				return true;
			default:
				return super.keyDown(e, key);
			}
		}
		return true; // keyDown was handled if we get to here
	}

	public void requestFocus() { gameboard.requestFocus(); }
}
