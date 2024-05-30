//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.FxFont;

class Pz15Menu extends UIBandBox implements Pz15Consts
{
	private Pz15Callbacks pzctrl;
	private UIMenuItem m_new, m_undo, m_restart, m_soln, m_opts, m_exit;

	public Pz15Menu(Pz15Callbacks pzctrl, boolean app)
	{
		this.pzctrl = pzctrl;

		UIBand    mainmenu = new UIBand();
		UIMenuList gamemenu = new UIMenuList();
		gamemenu.setFont(new FxFont("Courier", FxFont.BOLD, 12));

		add(mainmenu);
		mainmenu.add(new UIMenuButton("Game", 0, gamemenu));

		m_new =     new UIMenuItem("New Game           F2");
		m_restart = new UIMenuItem("Restart Game       F4"); m_restart.setEnabled(false);
		m_undo =    new UIMenuItem("Undo Move      Ctrl-Z"); m_undo.setEnabled(false);
		m_soln =	new UIMenuItem("Show Optimal Soln  F3"); m_soln.setEnabled(false);
		m_opts =    new UIMenuItem("Game Options...    F7");
		m_exit =	new UIMenuItem("Exit           Ctrl-X");
		if ( !app )
			m_exit.setEnabled(false);

		gamemenu.add(m_new); gamemenu.add(m_restart); gamemenu.add(new UILine());
		gamemenu.add(m_undo); gamemenu.add(new UILine());
		gamemenu.add(m_soln); gamemenu.add(new UILine());
		gamemenu.add(m_opts); gamemenu.add(new UILine());
		gamemenu.add(m_exit);
	}

	public void enable(int idx, boolean set)
	{
		if ( idx == ID_SOLUTION )
			m_soln.setEnabled(set);
		else if ( idx == ID_UNDO )
			m_undo.setEnabled(set);
		else if ( idx == ID_RESTART )
			m_restart.setEnabled(set);
	}

	public boolean action(Event e, Object arg)
	{
		if ( arg instanceof UIMenuItem )
		{
			UIMenuItem item = (UIMenuItem)arg;

			if ( item == m_new )
				pzctrl.newGame();
			else if ( item == m_restart )
				pzctrl.restartGame();
			else if ( item == m_undo )
				pzctrl.undoMove();
			else if ( item == m_opts )
				pzctrl.displayOptionsDialog();
			else if ( item == m_soln )
				pzctrl.displayOptimalSolution();
			else if ( item == m_exit ) {
				pzctrl.stopSolver();
				System.exit(0);
			}
			return true;
		}
		return super.action(e, arg);
	}
}
