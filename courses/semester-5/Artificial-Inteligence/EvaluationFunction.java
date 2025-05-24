package games.Connect4.Heuristic;

import games.Connect4.Connect4;
import sac.State;
import sac.StateFunction;

public class EvaluationFunction extends StateFunction {
    private static final int BOARD_HEIGHT = 6;
    private static final int BOARD_WIDTH = 7;
    private static final int CONSECUTIVE_EMPTIES_THRESHOLD = 3;
    private static final int[][] DIRECTIONS = {{0, 1}, {1, 0}, {1, 1}, {1, -1}}; // Right, Down, Down-Right, Down-Left

    @Override
    public double calculate(State state) {
        var c4 = (Connect4) state;

        if (c4.isWin()) {
            return c4.isMaximizingTurnNow() ? Double.NEGATIVE_INFINITY : Double.POSITIVE_INFINITY;
        }

        if (c4.isTie()) {
            return 0;
        }

        return returnScoreForEmpties(c4);
    }

    private int returnScoreForEmpties(Connect4 c4) {
        byte[][] board = c4.getBoard();
        int totalScore = 0;

        for (int col = 0; col < BOARD_WIDTH; col++) {
            int row = findFirstEmptyRow(board, col);
            if (row != -1) {
                totalScore += calculateScoreForPosition(board, row, col);
            }
        }

        return totalScore;
    }

    private int findFirstEmptyRow(byte[][] board, int col) {
        for (int row = 0; row < BOARD_HEIGHT; row++) {
            if (board[row][col] == Connect4.EMPTY) {
                return row;
            }
        }
        return -1;
    }

    private int calculateScoreForPosition(byte[][] board, int row, int col) {
        int score = 0;
        for (int[] direction : DIRECTIONS) {
            score += countConsecutiveEmpties(board, row, col, direction[0], direction[1]);
        }
        return score;
    }

    private int countConsecutiveEmpties(byte[][] board, int row, int col, int rowDelta, int colDelta) {
        int consecutiveEmpties = 0;

        while (isInBounds(row, col) && board[row][col] == Connect4.EMPTY && consecutiveEmpties < CONSECUTIVE_EMPTIES_THRESHOLD) {
            consecutiveEmpties++;
            row += rowDelta;
            col += colDelta;
        }

        return consecutiveEmpties == CONSECUTIVE_EMPTIES_THRESHOLD ? 1 : 0;
    }

    private boolean isInBounds(int row, int col) {
        return row >= 0 && row < BOARD_HEIGHT && col >= 0 && col < BOARD_WIDTH;
    }
}