package games.SlidingPuzzle;

import sac.graph.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

import static games.SlidingPuzzle.Benchmark.benchmark;

public class SlidingPuzzle extends GraphStateImpl {
    public  int n;
    private byte[][] board;
    int zeroRow, zeroCol;
    public int returnN() {
        return this.n;
    }

    public byte[][] returnBoard() {
        return this.board;
    }


    public SlidingPuzzle(SlidingPuzzle toCopy) {
        this.n = toCopy.n;
        this.board = new byte[n][n];
        this.zeroRow = toCopy.zeroRow;
        this.zeroCol = toCopy.zeroCol;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                this.board[i][j] = toCopy.board[i][j];
            }
        }
    }
    @Override
    public String toString() {

        StringBuilder txt = new StringBuilder();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                txt.append(board[i][j]);
                txt.append(",");
            }
            txt.append("\n");
        }
        return txt.toString();
    }

    @Override
    public int hashCode() {
        byte[] flat = new byte[n * n];
        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                flat[k++] = board[i][j];
            }
        }
        return Arrays.hashCode(flat);
        // return Arrays.deepHashCode(board);
    }
    @Override
    public List<GraphState> generateChildren() {
        List<GraphState> children = new ArrayList<>();

        for (MoveEnum move : MoveEnum.values()) {
            SlidingPuzzle child = new SlidingPuzzle(this);

            if (child.Move(move)) {
                child.setMoveName(String.valueOf(move));
                children.add(child);
            }
        }

        return children;
    }
    public boolean Move(MoveEnum moveEnum){
        int newRow = zeroRow;
        int newCol = zeroCol;

        switch (moveEnum){ // where to move
            case L -> newCol--;
            case R -> newCol++;
            case U -> newRow--;
            case D -> newRow++;
        }
        if (newRow < 0 || newRow >=n || newCol <0 || newCol >=n) { // check bounds
            return false;
        }
        board[zeroRow][zeroCol] = board[newRow][newCol]; // replace
        board[newRow][newCol] = 0; // move

        // update zero coordinates
        zeroRow = newRow;
        zeroCol = newCol;
        return true;
    }
    public SlidingPuzzle(int n) {
        this.n = n;

        board = new byte[n][n];

        byte x = 0;

        this.zeroRow = 0;
        this.zeroCol = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = x;
                x++;
            }
        }
    }

    public void scrambleBoard(int scrambleMovestoDo) {
        Random rand = new Random(0);
        boolean canMove;
        int i = 0;

        while (i < scrambleMovestoDo) {
            int randomizedMove = rand.nextInt(4);
            canMove = switch (randomizedMove) {
                case 0 -> Move(MoveEnum.L);
                case 1 -> Move(MoveEnum.R);
                case 2 -> Move(MoveEnum.U);
                case 3 -> Move(MoveEnum.D);
                default -> false;
            };

            if (canMove) i++;
        }

    }

    @Override
    public boolean isSolution() {
        byte x = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] != x) {
                    return false;
                }
                x++;
            }
        }
        return true;
    }


    public static void main(String[] args) {
        int n = 3;
        int testn = 100;
        int scrambleMovestoDo = 1000;
        int heuristicCount = 2;

        benchmark(n,testn,heuristicCount,scrambleMovestoDo);

//        Na życzenie prowadzącego mieć możliwość szybkiego nastawienia eksperymentu analogicznego do poprzedniego dla:
//        n = 4,
//        10 losowych układanek powstałych poprzez
//        30 ruchów mieszających.
        n = 4;
        testn = 10;
        scrambleMovestoDo = 30;

        benchmark(n,testn,heuristicCount,scrambleMovestoDo);
    }
}
