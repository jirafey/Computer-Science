# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++11 # Optimization level 2, C++11 standard
OMP_FLAG = -fopenmp
LDFLAGS = -fopenmp # Needed for linking OpenMP runtime

# Source files and executables
SRC_L1 = main_loop1.cpp
SRC_L2 = main_loop2.cpp
SRC_L3 = main_loop3.cpp
EXEC_L1 = matrix_multiply_l1
EXEC_L2 = matrix_multiply_l2
EXEC_L3 = matrix_multiply_l3

# Experiment parameters
SIZES = 100 500 1000 2000
THREADS = 2 4 8 16
# Define schedules with chunk sizes
SCHEDULES_STATIC = static,10 static,50 static,100
SCHEDULES_DYNAMIC = dynamic,10 dynamic,50 dynamic,100
SCHEDULES_GUIDED = guided,10 guided,50 guided,100
ALL_SCHEDULES = $(SCHEDULES_STATIC) $(SCHEDULES_DYNAMIC) $(SCHEDULES_GUIDED)

# Output file for results
RESULTS_FILE = sprawozdanie_results.txt

# Default target
all: $(EXEC_L1) $(EXEC_L2) $(EXEC_L3)

# Compilation rules
$(EXEC_L1): $(SRC_L1) main_common.hpp
	$(CXX) $(CXXFLAGS) $(OMP_FLAG) $< -o $@ $(LDFLAGS)

$(EXEC_L2): $(SRC_L2) main_common.hpp
	$(CXX) $(CXXFLAGS) $(OMP_FLAG) $< -o $@ $(LDFLAGS)

$(EXEC_L3): $(SRC_L3) main_common.hpp
	$(CXX) $(CXXFLAGS) $(OMP_FLAG) $< -o $@ $(LDFLAGS)

# Target to run all experiments
run_all: all clean_results
	@echo "Running all experiments... Output will be appended to $(RESULTS_FILE)"
	$(MAKE) run_loop1
	$(MAKE) run_loop2
	$(MAKE) run_loop3
	@echo "All experiments complete. Results saved in $(RESULTS_FILE)"

# Target to run experiments for loop 1
run_loop1: $(EXEC_L1)
	@echo "--- Running Loop 1 Parallelization ---" >> $(RESULTS_FILE)
	@for size in $(SIZES); do \
	    echo "--- Matrix Size: $$size x $$size ---" >> $(RESULTS_FILE); \
	    for threads in $(THREADS); do \
	        echo "*** Threads: $$threads ***" >> $(RESULTS_FILE); \
	        echo "Schedule: Default (Static)" >> $(RESULTS_FILE); \
	        ./$(EXEC_L1) $$threads $$size >> $(RESULTS_FILE); \
	        for sched in $(ALL_SCHEDULES); do \
	            echo "Schedule: $$sched" >> $(RESULTS_FILE); \
	            OMP_SCHEDULE="$$sched" ./$(EXEC_L1) $$threads $$size >> $(RESULTS_FILE); \
	        done; \
	    done; \
	done

# Target to run experiments for loop 2
run_loop2: $(EXEC_L2)
	@echo "--- Running Loop 2 Parallelization ---" >> $(RESULTS_FILE)
	@for size in $(SIZES); do \
	    echo "--- Matrix Size: $$size x $$size ---" >> $(RESULTS_FILE); \
	    for threads in $(THREADS); do \
	        echo "*** Threads: $$threads ***" >> $(RESULTS_FILE); \
	        echo "Schedule: Default (Static)" >> $(RESULTS_FILE); \
	        ./$(EXEC_L2) $$threads $$size >> $(RESULTS_FILE); \
	        for sched in $(ALL_SCHEDULES); do \
	            echo "Schedule: $$sched" >> $(RESULTS_FILE); \
	            OMP_SCHEDULE="$$sched" ./$(EXEC_L2) $$threads $$size >> $(RESULTS_FILE); \
	        done; \
	    done; \
	done

# Target to run experiments for loop 3
run_loop3: $(EXEC_L3)
	@echo "--- Running Loop 3 Parallelization ---" >> $(RESULTS_FILE)
	@for size in $(SIZES); do \
	    echo "--- Matrix Size: $$size x $$size ---" >> $(RESULTS_FILE); \
	    for threads in $(THREADS); do \
	        echo "*** Threads: $$threads ***" >> $(RESULTS_FILE); \
	        echo "Schedule: Default (Static)" >> $(RESULTS_FILE); \
	        ./$(EXEC_L3) $$threads $$size >> $(RESULTS_FILE); \
	        for sched in $(ALL_SCHEDULES); do \
	            echo "Schedule: $$sched" >> $(RESULTS_FILE); \
	            OMP_SCHEDULE="$$sched" ./$(EXEC_L3) $$threads $$size >> $(RESULTS_FILE); \
	        done; \
	    done; \
	done

# Clean up executables
clean:
	rm -f $(EXEC_L1) $(EXEC_L2) $(EXEC_L3) *.o

# Clean up results file
clean_results:
	rm -f $(RESULTS_FILE)

.PHONY: all clean clean_results run_all run_loop1 run_loop2 run_loop3