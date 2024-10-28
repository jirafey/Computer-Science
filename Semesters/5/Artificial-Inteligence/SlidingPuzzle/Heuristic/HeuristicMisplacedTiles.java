package games.SlidingPuzzle.Heuristic;

import games.SlidingPuzzle.SlidingPuzzle;
import sac.State;
import sac.StateFunction;

public class HeuristicMisplacedTiles extends StateFunction {
    @Override
    public double calculate (State state) {
        SlidingPuzzle slidingPuzzle = (SlidingPuzzle) state;
        int n = slidingPuzzle.returnN();
        byte[][] board = slidingPuzzle.returnBoard();
        int correctCounter=0;
        int wrongCounter=0;

        for (int i=0; i<n;i++){
            for (int j=0; j<n;j++) {
                if (board[i][j] == correctCounter){
                    correctCounter++;
                    continue;
                }
                if (board[i][j] != correctCounter){
                    wrongCounter++;

                }
            }
        }
        return wrongCounter;
    }
}
