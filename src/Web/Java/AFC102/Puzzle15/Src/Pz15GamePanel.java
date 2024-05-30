//
// (c) 1997 Microsoft Corporation.  All rights reserved.
//
import java.awt.Image;
import java.awt.Insets;
import java.awt.Event;
import com.ms.ui.*;
import com.ms.fx.*;

class Pz15GamePanel extends UIGroup implements Pz15Consts
{
        private Pz15Data puzzle;
        private Pz15Callbacks pzctrl;

        private Pz15AccGrfxBtn  btns[] = new Pz15AccGrfxBtn[NUM_BUTTONS];
        private Pz15AccGrfxBtn  btnhole;
        private FxTexture tex;

        public Pz15GamePanel(Pz15Data puzzle, Pz15Callbacks pzctrl)
        {
                super();
                this.puzzle = puzzle; this.pzctrl = pzctrl;
                makeButtons();
                draw();
                setVisible(true);
        }

        public void draw()
        {
                setLayout(new UIGridLayout(PDIM, PDIM, 1, 1));

                for (int i = 0 ; i < SIZE ; i++) {
                        // Look for blank button
                        if ( puzzle.current[i] == 0 )
                                add(btnhole);
                        else
                                add(btns[puzzle.current[i]-1]);
                }
                btnhole.setBackground(null);
                btnhole.setStyle(0);
                btnhole.setEnabled(true); btnhole.setValid(true); btnhole.setEnabled(false);
                setValid(true);
        }

        private void makeButtons()
        {
                // Create "Hole" button and disable it
                btnhole = new Pz15AccGrfxBtn();
                btnhole.setEnabled(false);

                // Create numbered buttons
                for (int i = 0 ; i < SIZE-1 ; i++) {
                        btns[i] = new Pz15AccGrfxBtn(PIECES+i, pzctrl);
                        btns[i].setBackground(BaseColor.getColor (new FxTexture(Pz15Images.get(BKGRND+i),
                                                                                                FxTexture.STRETCH_ALL,
                                                                                                0, 0, -1, -1, false, 185, 185, 185)));
                }
        }

        public void setInitialFocus()
        {
                int index;

                if ( puzzle.hole > 11 )
                        index = puzzle.hole + O_UP;
                else
                        index = puzzle.hole + O_DOWN;

                btns[puzzle.current[index]-1].requestFocus();
        }

        public void update(int move)
        {
                int index = move + puzzle.hole;

                if ( move > 0 ) { // hole is moving DOWN or RIGHT
                        move(index, puzzle.hole);
                        move(puzzle.hole+1, index);
                }
                else { // hole must be moving UP or LEFT
                        move(puzzle.hole, index);
                        move(index+1, puzzle.hole);
                }

                btns[puzzle.current[index]-1].requestFocus();
                // This setValid(false) is neccesary because of a bug in move()
                setValid(false);
                setValid(true);

                // Now that we have updated the game board, we can update the internal
                //   representation of the puzzle.
                puzzle.update(move);

                pzctrl.enableUndo(!puzzle.movstk.isEmpty());
                pzctrl.enableRestart(!puzzle.movstk.isEmpty());
                pzctrl.setNumMoves(puzzle.movstk.size());
                pzctrl.setMinMoves(puzzle.current_cost);
                if ( pzctrl.getSolverStatus() ) {
                        if ( (puzzle.movstk.size() + puzzle.current_cost) > pzctrl.getOptimalCost() )
                                pzctrl.setMarqueeString(MRQ_NOHOPE, S_NOHOPE);
                        else
                                pzctrl.setMarqueeString(MRQ_OPTIMALFND, S_OPTFND);
                }
        }

        private MultMoves genMoves(int btn)
        {
                // hole will move...
                int delta = puzzle.hole - btn;
                switch ( delta ) {
                case 4: case 8: case 12:
                        return new MultMoves(O_UP, delta/4);

                case -4: case -8: case -12:
                        return new MultMoves(O_DOWN, -delta/4);

                case 1: case 2: case 3:
                        if ( btn/4 == puzzle.hole/4 )
                                return new MultMoves(O_LEFT, delta);
                        break;

                case -1: case -2: case -3:
                        if ( btn/4 == puzzle.hole/4 )
                                return new MultMoves(O_RIGHT, -delta);
                        break;
                }
                return new MultMoves(NO_MOVE, 0);
        }

        public boolean action(Event e, Object arg)
        {
                if ( puzzle.solved )
                        return super.action(e, arg);

                if ( arg instanceof UIPushButton ) {
                        MultMoves moves = genMoves(getComponentIndex((UIPushButton)arg));

                        for ( int i = 0; i < moves.count; i++ ) {
                                update(moves.move);
                                if ( puzzle.solved ) {
                                        congratulate();
                                        break;
                                }
                        }
                }
                return super.action(e, arg);
        }

        public boolean keyDown(Event e, int key)
        {
                int move = NO_MOVE;

                if ( e.modifiers == 0 ) {
                        switch ( key ) {
                        case Event.UP: case Event.LEFT: case Event.RIGHT: case Event.DOWN:
                                if ( puzzle.solved )
                                        return super.keyDown(e, key);
                                switch ( pzctrl.getNavMode() ) {
                                case M_BLANK: move = blankKeyDown(key); break;
                                case M_BUTTON: move = buttonKeyDown(key); break;
                                case M_SELECT: return super.keyDown(e, key);
                                default: break; // Can't get to here:
                                                                //   navmode is always one of three above
                                }
                                break;
                        default: return super.keyDown(e, key);
                        }
                }
                else
                        return super.keyDown(e, key);

                if ( move != NO_MOVE ) {
                        update(move);
                        if ( puzzle.solved )
                                congratulate();
                }
                return true; // keyDown was handled if we get to here
        }

        private int blankKeyDown(int key)
        {
                int move = NO_MOVE;

                switch ( key ) {
                case Event.UP: move = puzzle.validateMove(O_UP); break;
                case Event.LEFT: move = puzzle.validateMove(O_LEFT); break;
                case Event.RIGHT: move = puzzle.validateMove(O_RIGHT); break;
                case Event.DOWN: move = puzzle.validateMove(O_DOWN); break;
                default: break; // Can't get to here since function is only called when
                                                //   key is already verified to be one of U,L,R,D
                }
                return move;
        }

        private int buttonKeyDown(int key)
        {
                int move = NO_MOVE;

                switch ( key ) {
                case Event.UP: move = puzzle.validateMove(O_DOWN); break;
                case Event.LEFT: move = puzzle.validateMove(O_RIGHT); break;
                case Event.RIGHT: move = puzzle.validateMove(O_LEFT); break;
                case Event.DOWN: move = puzzle.validateMove(O_UP); break;
                default: break; // Can't get to here since function is only called when
                                                //   key is already verified to be one of U,L,R,D
                }
                return move;
        }

        private void congratulate()
        {
                drawBlank();
                pzctrl.enableUndo(false);
                if ( pzctrl.getSolverStatus() ) {
                        if ( puzzle.movstk.size() == pzctrl.getOptimalCost() )
                                pzctrl.setMarqueeString(MRQ_CONGRATS, S_RESET);
                        else
                                pzctrl.setMarqueeString(MRQ_OK, S_RESET);
                }
                else
                        pzctrl.setMarqueeString(MRQ_OK_NOOPT, S_RESET);

                pzctrl.congratulate();
                requestFocus();
        }

        public void drawBlank()
        {
                btnhole.setStyle(UIPushButton.RAISED | UIPushButton.THICK);
                btnhole.setBackground(BaseColor.getColor (new FxTexture(Pz15Images.get(BKGRND+SIZE-1),
                                                                                                FxTexture.STRETCH_ALL,
                                                                                                0, 0, -1, -1, false, 185, 185, 185)));
                // repaint background
                btnhole.setEnabled(true); btnhole.setValid(true); btnhole.setEnabled(false);
        }

        public Insets getInsets() { return(new Insets(7,6,5,7)); }
}

class MultMoves
{
        public int move;
        public int count;

        public MultMoves(int mv, int cnt) {     move = mv; count = cnt; }
}
