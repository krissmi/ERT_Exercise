## <ins>C-code optimization</ins>

1. What would be your general approach to reducing the computational time of the following code by making the computation or algorithm more efficient?
2. Compile and test-run the accompanying C code test_j.c. To compile with gcc, for example, add the flag -lm. 
3. Assess its performance using any methods available to you. Use profiling tools such as GPROF and PERF to identify and quantify the steps that are most time-consuming.
4. Modify the code to reduce the computational time. Any details are welcome. Compare the performance between the original and modified versions.
5. Explain your achievement, any challenges or blockers encountered, any lessons or insights you have gained during this exercise.

## <ins>Dependencies</ins>

| module       | version   | location                                              |
|--------------|-----------|-------------------------------------------------------|
| clang        | >= 15.0.0 | <https://clang.llvm.org>                              |
| llvm (tools) | >= 17.0.6 | <https://llvm.org/>                                   |
| gcc-13       | >= 13.0.0 | <https://gcc.gnu.org/>                                |
| gperftools   | 2.13      | <https://github.com/gperftools/gperftools>            |

## <ins>Thoughts and Solution (partial)</ins>

1. Make contant values within function static
2. Use standard math library PI macro
3. Optimize MAX function (macro) to prevent side-effects
4. Compile with optimizations turned on
5. Blocked by:
	- Minimal understanding of the problem domain
	- Lack of documentation

## <ins>Quick Start</ins>

1. Clone the repository to your local machine
`git clone https://github.com/krissmi/ERT_Exercise.git`

Once you have a local copy of the repository, you may build the binary:

2. Change to the exercise_4 directory
`cd ERT_Exercise/exercise_4`

3. Run `make all` to compile the C program and execute the profilers.  Profiler output is display to the default console.
