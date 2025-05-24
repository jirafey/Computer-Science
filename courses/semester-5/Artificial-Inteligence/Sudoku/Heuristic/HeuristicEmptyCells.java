package games.Sudoku.Heuristic;

import games.Sudoku.Sudoku;
import sac.State;
import sac.StateFunction;

public class HeuristicEmptyCells extends StateFunction {
    @Override
    public double calculate(State state) {
        Sudoku s = (Sudoku) state;
        return s.getZeros();
    }
}