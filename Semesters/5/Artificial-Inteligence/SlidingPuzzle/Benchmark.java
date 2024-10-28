package games.SlidingPuzzle;

import games.SlidingPuzzle.Heuristic.HeuristicManhattan;
import games.SlidingPuzzle.Heuristic.HeuristicMisplacedTiles;
import sac.graph.AStar;
import sac.graph.GraphSearchAlgorithm;

public class Benchmark {
    public static void benchmark(int n, int testn, int heuristicCount, int scramebleMovestoDo){

        // Make arrays exactly sized for the total number of tests
        long[] time_arr = new long[testn * heuristicCount];
        int[] close_arr = new int[testn * heuristicCount];
        int[] open_arr = new int[testn * heuristicCount];
        int[] length_arr = new int[testn * heuristicCount];

        for (int i = 0; i < heuristicCount; i++) {
            // Set heuristic only once per batch
            if (i == 0) {
                SlidingPuzzle.setHFunction(new HeuristicManhattan());
            } else {
                SlidingPuzzle.setHFunction(new HeuristicMisplacedTiles());
            }

            for (int j = 0; j < testn; j++) {
                SlidingPuzzle slidingPuzzle = new SlidingPuzzle(n);
                slidingPuzzle.scrambleBoard(scramebleMovestoDo);

                GraphSearchAlgorithm algo = new AStar(slidingPuzzle);
                algo.execute();

                // Calculate correct index for storing results
                int index = i * testn + j;
                time_arr[index] = algo.getDurationTime();
                open_arr[index] = algo.getClosedStatesCount();
                close_arr[index] = algo.getOpenSet().size();
                SlidingPuzzle solution = (SlidingPuzzle) algo.getSolutions().getFirst();
                length_arr[index] = solution.getMovesAlongPath().size();
            }
        }

        // Calculate averages for Manhattan heuristic
        double sum_time_manhattan = 0.0;
        double sum_close_manhattan = 0.0;
        double sum_open_manhattan = 0.0;
        double sum_length_manhattan = 0.0;

        // Calculate averages for Misplaced Tiles heuristic
        double sum_time_misplaced = 0.0;
        double sum_close_misplaced = 0.0;
        double sum_open_misplaced = 0.0;
        double sum_length_misplaced = 0.0;

        // Sum up results for Manhattan heuristic (first batch)
        for (int i = 0; i < testn; i++) {
            sum_time_manhattan += time_arr[i];
            sum_open_manhattan += open_arr[i];
            sum_close_manhattan += close_arr[i];
            sum_length_manhattan += length_arr[i];
        }

        // Sum up results for Misplaced Tiles heuristic (second batch)
        for (int i = testn; i < testn * 2; i++) {
            sum_time_misplaced += time_arr[i];
            sum_open_misplaced += open_arr[i];
            sum_close_misplaced += close_arr[i];
            sum_length_misplaced += length_arr[i];
        }

        // Print results with clear formatting
        System.out.println("N: "+ n);
        System.out.println("Random puzzles: "+ testn);
        System.out.println("Scramble moves done: "+ scramebleMovestoDo);
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
