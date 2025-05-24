    package games.Connect4;

    import java.util.ArrayList;
    import java.util.Arrays;
    import java.util.List;
    import java.util.Scanner;

    import games.Connect4.Heuristic.EvaluationFunction;
    import sac.game.*;

    public class Connect4 extends GameStateImpl {
        public static boolean IS_MAX_AI = true;
        public static final boolean IS_MIN_AI = false;

        public static final int row = 6;
        public static final int col = 7;
        public static final byte O = 1; // MAX player
        public static final byte EMPTY = 0;
        public static final byte X = -1; // MIN player
        public static final String[] SYMBOLS = new String[] {"X", ".", "O"};

        private byte[][] board;
        private int iLast = -1;
        public int getILast(){
            return iLast;
        }
        private int jLast = -1;
        public int getJLast(){
            return jLast;
        }
        private boolean isCeilingRule;
        private boolean isCeilingReached = false;
        private byte ceilingWinner;

        public Connect4() {
            board = new byte[row][col];
            for (int i = 0; i < row; i++)
                for (int j = 0; j < col; j++)
                    board[i][j] = EMPTY;
        }
        public Connect4(Connect4 parent) {
            board = new byte[row][col];
            for (int i = 0; i < row; i++)
                for (int j = 0; j < col; j++)
                    board[i][j] = parent.board[i][j];
            setMaximizingTurnNow(parent.isMaximizingTurnNow());
        }


        @Override
        public String toString() {
            StringBuilder txt = new StringBuilder();
            for (int j = 0; j < col; j++) {
                txt.append(" ");
                txt.append(j);
            }
            txt.append("\n");
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < col; j++) {
                    txt.append("|");
                    txt.append(SYMBOLS[board[i][j] + 1]);
                }
                txt.append("|\n");
            }
            for (int j = 0; j < col; j++) {
                txt.append(" ");
                txt.append(j);
            }
            return txt.toString();
        }

        public boolean move(int j) {

            int i = row - 1;

            for (; i >= 0; i--)
                if (board[i][j] == EMPTY)
                    break;
            if (i < 0)
                return false;
            byte currentPlayer = (isMaximizingTurnNow()) ? O : X;
            if (isCeilingRule && i == 0 && ceilingWinner == EMPTY) {
                isCeilingReached = true;
                ceilingWinner = currentPlayer;
            }
            board[i][j] = (isMaximizingTurnNow()) ? O : X;
            setMaximizingTurnNow(!isMaximizingTurnNow());
            iLast = i;
            jLast = j;
            return true;
        }
        public void setCeilingRule(boolean enabled) {
            this.isCeilingRule = enabled;
        }

        public boolean isWin() {
            if ((iLast < 0) || (jLast < 0))
                return false;
            if (isCeilingRule && isCeilingReached) {
                return true;
            }
            byte symbol = board[iLast][jLast];
            // right-left
            int counter = 0;
            for (int k = 1; k < 4; k++) {
                if ((jLast + k >= col) || (board[iLast][jLast + k] != symbol))
                    break;
                counter++;
            }
            for (int k = 1; k < 4; k++) {
                if ((jLast - k < 0) || (board[iLast][jLast - k] != symbol))
                    break;
                counter++;
            }
            if (counter >= 3)
                return true;
            // down-up
            counter = 0;
            for (int k = 1; k < 4; k++) {
                if ((iLast + k >= row) || (board[iLast + k][jLast] != symbol))
                    break;
                counter++;
            }
            for (int k = 1; k < 4; k++) {
                if ((iLast - k < 0) || (board[iLast - k][jLast] != symbol))
                    break;
                counter++;
            }
            if (counter >= 3)
                return true;
            // NE-SW
            counter = 0;
            for (int k = 1; k < 4; k++) {
                if ((iLast - k < 0) || (jLast + k >= col) || (board[iLast - k][jLast + k] != symbol))
                    break;
                counter++;
            }
            for (int k = 1; k < 4; k++) {
                if ((iLast + k >= row) || (jLast - k < 0) || (board[iLast + k][jLast - k] != symbol))
                    break;
                counter++;
            }
            if (counter >= 3)
                return true;
            // NW-SE
            counter = 0;
            for (int k = 1; k < 4; k++) {
                if ((iLast - k < 0) || (jLast - k < 0) || (board[iLast - k][jLast - k] != symbol))
                    break;
                counter++;
            }
            for (int k = 1; k < 4; k++) {
                if ((iLast + k >= row) || (jLast + k >= col) || (board[iLast + k][jLast + k] != symbol))
                    break;
                counter++;
            }
            if (counter >= 3)
                return true;
            return false;
        }

        public boolean isTie(){
            for (int j = 0; j< col; j++){
                if (board[0][j] == EMPTY){
                    return false;
                }
            }
            return true;
        }

        @Override
        public List<GameState> generateChildren() {
            List<GameState> children = new ArrayList<>();
            for (int j = 0; j < col; j++){
                Connect4 child = new Connect4(this);
                if(child.move(j)){
                    children.add(child);
    //                child.setMoveName("col "+j);
                    child.setMoveName(Integer.toString(j));
                }
            }
            return children;
        }
        @Override
        public int hashCode(){
            byte[] flat = new byte[row*col];
            int k =0;
            for (int i =0;i<row; i++){
                for (int j =0;j<col; j++){
                    flat[k++] = board[i][j];
                }
            }
            return Arrays.hashCode(flat);
        }
        public byte[][] getBoard(){
            return board;
        }

        public static void main(String[] args) {
            Connect4 c4 = new Connect4();
            c4.setCeilingRule(true);
            Connect4.setHFunction(new EvaluationFunction());
            System.out.println(c4);
            Scanner scanner = new Scanner(System.in);
            GameSearchConfigurator conf = new GameSearchConfigurator();
            conf.setDepthLimit(5.5);
//            GameSearchAlgorithm algo = new MinMax(); // default depth = 3.5 ruchu 7 półruchów
            GameSearchAlgorithm algo = new AlphaBetaPruning(); // default depth = 3.5 ruchu 7 półruchów
            algo.setConfigurator(conf);
            while (true) {
                // max
                if (!IS_MAX_AI) {
                    boolean moveLegal = false;
                    do {
                        System.out.print("MAX PLAYER 'O' - YOUR MOVE: ");
                        int jMove = Integer.valueOf(scanner.nextLine());
                        moveLegal = c4.move(jMove);
                    } while (!moveLegal);
                }
                else {
                    // ai later
                    algo.setInitial(c4);
                    algo.execute();
                    System.out.println("MOVES SCORES: "+ algo.getMovesScores());
                    System.out.println("CLOSED: "+ algo.getClosedStatesCount());
                    System.out.println("DEPTH: "+ algo.getDepthReached());
                    System.out.println("TIME [ms]: "+ algo.getDurationTime());
                    int bestMove = Integer.valueOf(algo.getFirstBestMove());
                    System.out.println("MOVE PLAYED: "+ bestMove);
                    c4.move(bestMove);
                    // "0" -> -3.5, "1" -> 7, "4" -> inf
                }
                System.out.println(c4);
                if (c4.isWin()) {
                    System.out.println("MAX PLAYER 'O' WINS!");
                    break;
                }
                if (c4.isTie()) {
                    System.out.println("GAME TIED!");
                    break;
                }
                // min
                if (!IS_MIN_AI) {
                    boolean moveLegal = false;
                    do {
                        System.out.print("MIN PLAYER 'X' - YOUR MOVE: ");
                        int jMove = Integer.valueOf(scanner.nextLine());
                        moveLegal = c4.move(jMove);
                    } while (!moveLegal);
                }
                else {
                    // ai later
                    algo.setInitial(c4);
                    algo.execute();
                    System.out.println("MOVES SCORES: "+ algo.getMovesScores());
                    System.out.println("CLOSED: "+ algo.getClosedStatesCount());
                    System.out.println("DEPTH: "+ algo.getDepthReached());
                    System.out.println("TIME [ms]: "+ algo.getDurationTime());
                    int bestMove = Integer.valueOf(algo.getFirstBestMove());
                    System.out.println("MOVE PLAYED: "+ bestMove);
                    c4.move(bestMove);
                    // "0" -> -3.5, "1" -> 7, "4" -> inf
                }
                System.out.println(c4);
                if (c4.isWin()) {
                    System.out.println("MIN PLAYER 'X' WINS!");
                    break;
                }
                if (c4.isTie()) {
                    System.out.println("GAME TIED!");
                    break;
                }
            }
            scanner.close();
        }
    }