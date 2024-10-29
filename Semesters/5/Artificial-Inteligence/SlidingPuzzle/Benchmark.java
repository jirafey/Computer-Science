package games.SlidingPuzzle;

import games.SlidingPuzzle.Heuristic.HeuristicManhattan;
import games.SlidingPuzzle.Heuristic.HeuristicMisplacedTiles;
import sac.graph.AStar;
import sac.graph.GraphSearchAlgorithm;

public class Benchmark {


    public static void benchmark(int n, int testn, int heuristicCount, int scrambleMovestoDo) {

        long[] time_arr = new long[testn * heuristicCount];
        int[] close_arr = new int[testn * heuristicCount];
        int[] open_arr = new int[testn * heuristicCount];
        int[] length_arr = new int[testn * heuristicCount];

        long start_manhattan = System.currentTimeMillis();
        SlidingPuzzle[] array = new SlidingPuzzle[testn] ;

        SlidingPuzzle.setHFunction(new HeuristicManhattan());
        for (int j = 0; j < testn; j++) {
            SlidingPuzzle slidingPuzzle = new SlidingPuzzle(n);
            slidingPuzzle.scrambleBoard(scrambleMovestoDo);
            array[j] = slidingPuzzle;

            GraphSearchAlgorithm algo = new AStar(slidingPuzzle);
            algo.execute();

            time_arr[j] = algo.getDurationTime();
            open_arr[j] = algo.getClosedStatesCount();
            close_arr[j] = algo.getOpenSet().size();
            SlidingPuzzle solution = (SlidingPuzzle) algo.getSolutions().getFirst();
            length_arr[j] = solution.getMovesAlongPath().size();

            if (j ==0){
                System.out.println(slidingPuzzle);
                System.out.println(solution);
                System.out.println("Moves along path: " + solution.getMovesAlongPath());
            }

        }


        long manhattan_total_time = System.currentTimeMillis() - start_manhattan;
//        System.out.printf("Total time for Manhattan tests: %.2f seconds\n\n", manhattan_total_time/1000.0);

        long start_misplaced = System.currentTimeMillis();

        SlidingPuzzle.setHFunction(new HeuristicMisplacedTiles());
        for (int j = 0; j < testn; j++) {
            SlidingPuzzle slidingPuzzle = array[j];

            GraphSearchAlgorithm algo = new AStar(slidingPuzzle);
            algo.execute();

            int index = testn + j;  // Store in second half of arrays
            time_arr[index] = algo.getDurationTime();
            open_arr[index] = algo.getClosedStatesCount();
            close_arr[index] = algo.getOpenSet().size();
            SlidingPuzzle solution = (SlidingPuzzle) algo.getSolutions().getFirst();
            length_arr[index] = solution.getMovesAlongPath().size();
        }

        long misplaced_total_time = System.currentTimeMillis() - start_misplaced;
//        System.out.printf("Total time for Misplaced Tiles tests: %.2f seconds\n\n", misplaced_total_time/1000.0);

        double sum_time_manhattan = 0.0;
        double sum_close_manhattan = 0.0;
        double sum_open_manhattan = 0.0;
        double sum_length_manhattan = 0.0;

        double sum_time_misplaced = 0.0;
        double sum_close_misplaced = 0.0;
        double sum_open_misplaced = 0.0;
        double sum_length_misplaced = 0.0;

        for (int i = 0; i < testn; i++) {
            sum_time_manhattan += time_arr[i];
            sum_open_manhattan += open_arr[i];
            sum_close_manhattan += close_arr[i];
            sum_length_manhattan += length_arr[i];
        }

        for (int i = testn; i < testn * 2; i++) {
            sum_time_misplaced += time_arr[i];
            sum_open_misplaced += open_arr[i];
            sum_close_misplaced += close_arr[i];
            sum_length_misplaced += length_arr[i];
        }

        System.out.println("N: " + n);
        System.out.println("Random puzzles: " + testn);
        System.out.println("Scramble moves done: " + scrambleMovestoDo);
        System.out.println("\n=== Manhattan Distance Heuristic Results ===");
        System.out.printf("Average Time [ms]: %.2f\n", sum_time_manhattan / testn);
        System.out.printf("Average Closed States: %.2f\n", sum_close_manhattan / testn);
        System.out.printf("Average Open States: %.2f\n", sum_open_manhattan / testn);
        System.out.printf("Average Path Length: %.2f\n\n", sum_length_manhattan / testn);

        System.out.println("=== Misplaced Tiles Heuristic Results ===");
        System.out.printf("Average Time [ms]: %.2f\n", sum_time_misplaced / testn);
        System.out.printf("Average Closed States: %.2f\n", sum_close_misplaced / testn);
        System.out.printf("Average Open States: %.2f\n", sum_open_misplaced / testn);
        System.out.printf("Average Path Length: %.2f\n\n", sum_length_misplaced / testn);
    }
}