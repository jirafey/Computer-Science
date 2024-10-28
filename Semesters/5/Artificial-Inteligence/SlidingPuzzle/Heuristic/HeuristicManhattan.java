package games.SlidingPuzzle.Heuristic;

import games.SlidingPuzzle.SlidingPuzzle;
import sac.State;
import sac.StateFunction;

public class HeuristicManhattan extends StateFunction {
    @Override
    public double calculate(State state) {
        SlidingPuzzle slidingPuzzle = (SlidingPuzzle) state;
        int n = slidingPuzzle.returnN();
        byte[][] board = slidingPuzzle.returnBoard();
        int distance = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != 0) {
                    int istar = board[i][j] / n;
                    int jstar = board[i][j] % n;
                    distance += Math.abs(i - istar) + Math.abs(j - jstar);
                }
            }
        }
        return distance;
    }
}
