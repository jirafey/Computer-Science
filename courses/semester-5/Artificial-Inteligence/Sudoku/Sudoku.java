package games.Sudoku;

import games.Sudoku.Heuristic.HeuristicEmptyCells;
import sac.graph.*;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Sudoku extends GraphStateImpl {
    public static int n = 3;
    public static int n2 = n * n;
    private byte[][] board = null;
    private int zeros = n2*n2; // 81 for 3x3
    public Sudoku() {
        board = new byte[n2][n2];
        for (int i = 0; i < n2; i++)
            for (int j = 0; j < n2; j++)
                board[i][j] = 0;
    }
    public Sudoku(Sudoku toCopy) {
        board = new byte[n2][n2];
        for (int i = 0; i < n2; i++)
            for (int j = 0; j < n2; j++)
                board[i][j] = toCopy.board[i][j];
        zeros = toCopy.zeros;
    }

//    @Override
//    public boolean isSolution() {
//        return false;
//    }

    public void fromString(String txt) {
        int k = 0;
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++, k++) {
                board[i][j] = Byte.valueOf(txt.substring(k, k + 1));
            }
        }
        refreshZeros();
    }

    private static boolean isGroupLegal(byte[] group) {
        boolean[] visited = new boolean[n2 + 1];
        for (int i = 1; i <= n2; i++) {
            visited[i] = false;
        }
        for (int i = 0; i < n2; i++) {
            if (group[i] == 0) {
                continue;
            }
            if (visited[group[i]]) {
                return false;
            }
            visited[group[i]] = true;
        }
        return true;
    }

    public boolean isLegal() {
        byte[] group = new byte[n2];
        // wiersze
        for (int i = 0; i < n2; i++) {
//            for (int j = 0; j < n2; j++)
//                group[j] = board[i][j];
            if (!Sudoku.isGroupLegal(board[i])) {
                return false;
            }
        }

        // kolumny
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                group[j] = board[j][i];
            }
            if (!Sudoku.isGroupLegal(group)) {
                return false;
            }
        }
        // podkwadraty
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int q = 0;
                for (int k=0; k < n; k++) {
                    for (int l = 0; l < n; l++) {
                        // k lokalne dla wiersza, l lokalne dla kolumny
                        // co 3 jest n
                        group[q++] = board[i*n + k][j*n+l];
                    }
                }
                if (!Sudoku.isGroupLegal(group)) {
                    return false;
                }
            }
        }
        return true;
    }

    //  informacja ilości niewiadomych
    private void refreshZeros(){
        zeros = 0;
        for (int i =0; i< n2; i++){
            for (int j = 0; j < n2; j++){
                if (board[i][j] == 0)
                    zeros++;
            }
        }
    }

    @Override
    public List<GraphState> generateChildren() {
        List<GraphState> children = new ArrayList<GraphState>();
        int i = 0, j = 0;
        zeroFinder:
        for (i = 0; i < n2; i++){
            for (j = 0; j < n2; j++){
                if (board[i][j] == 0){
                    break zeroFinder;
                }
            }
        }
        if (i == n2) // na obsluzenie przypadku rozwiazanego sudoku
            return children;
        // jakby goto bo wyjscie breakiem to tylko z wewnetrznej petli
        for (byte k = 1; k <= n2; k++) {
            Sudoku child = new Sudoku(this);
            child.board[i][j] = k; // lub int k i castowac k na byte
            if (child.isLegal()){
                children.add(child);
                child.zeros--;
            }
        }
        return children;
    }

    @Override
    public String toString() {
        StringBuilder txt = new StringBuilder();
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                txt.append(board[i][j]);
                txt.append(",");
            }
            txt.append("\n");
        }
        return txt.toString();
    }

    @Override
    public int hashCode() { // zamienia na napis a potem z napisu integer
        /*byte[] flat = new byte[n2*n2];
        int k = 0;
        for (int i = 0; i < n2; i++) {
            for (int j = 0; j < n2; j++) {
                flat[k++] = board[i][j];
            }
        }*/
        return Arrays.deepHashCode(board);
    }

    public int getZeros() {
        return zeros;
    }

    @Override
    public boolean isSolution() {
        return ((zeros == 0) && (isLegal()));
    }

    public static void main(String[] args) {
        String sudokuAsTxt = "000000000000305001001806400008102900700000008006708200002609500800203009005010300";
        Sudoku s = new Sudoku();
        s.fromString(sudokuAsTxt);
        System.out.println(s);


        GraphSearchConfigurator conf = new GraphSearchConfigurator();
        conf.setWantedNumberOfSolutions(Integer.MAX_VALUE);

        GraphSearchAlgorithm algo = new BestFirstSearch(s,conf);
        Sudoku.setHFunction(new HeuristicEmptyCells());
        algo.execute();
        List<GraphState> solutions = algo.getSolutions();
        for (GraphState sol : solutions)
            System.out.println(sol);

        System.out.println("Time [ms]: " + algo.getDurationTime());
        System.out.println("Closed: " + algo.getClosedStatesCount());
        System.out.println("Open: " + algo.getOpenSet().size());
        System.out.println("Solutions: " + algo.getSolutions().size());
    }
}