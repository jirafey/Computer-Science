package games.SlidingPuzzle;

import sac.graph.*;

import java.util.*;

import static games.SlidingPuzzle.Benchmark.*;

public class SlidingPuzzle extends GraphStateImpl {
    private static Random getRandom() {
        return new Random(System.nanoTime());
    }
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
        boolean canMove;
        Random random = getRandom();  // Get new Random instance with current nanoTime
        int i = 0;

        while (i < scrambleMovestoDo) {
            int randomizedMove = random.nextInt(4);
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
        long startTotalTime = System.currentTimeMillis();

        long start1 = System.currentTimeMillis();
//        benchmark(3, 100, 2, 1000);  // This will create 100 distinct puzzles
        benchmark(4, 10, 2, 30);  // This will create 100 distinct puzzles
        long time1 = System.currentTimeMillis() - start1;
        System.out.printf("Total time for the test: %.2f seconds\n\n", time1/1000.0);

    }
}

