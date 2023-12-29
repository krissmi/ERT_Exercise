
OS := $(shell uname)

CC = clang

SOURCE=test_j.c
BINARY=test_j

CFLAGS = -g -O2 -Wall -fprofile-instr-generate -fcoverage-mapping -pg
LDFLAGS = -fprofile-instr-generate -pg -L/opt/homebrew/lib
LIBS = -lm -lprofiler -ltcmalloc

PPROF = /opt/go/bin/pprof
PPROF_TMPDIR = $(CURDIR)/pprof

LLVM_PROF_DATA = /Library/Developer/CommandLineTools/usr/bin/llvm-profdata
LLVM_PROF_COV = /Library/Developer/CommandLineTools/usr/bin/llvm-cov

PROFILER_DATA=test_j.profdata
PROFILER_FILE=test_j.prof
PROFILER_CPU=test_j.cpu

.PHONY: help clean
.DEFAULT_GOAL := help

########################################
## help

help: ## Makefile help
	@echo "Active Targets:"
	@echo "==============="
	@grep -E '^[.a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| sed -n 's/^\(.*\): \(.*\)##\(.*\)/\1,\3/p' \
	| column -t  -s ','

########################################
## all
all: profile_llvm profile_prof ## Run all profile targets
	
########################################
## clean
clean: ## Clean build artifacts
	rm -f test_j test_j.out
	rm -f test_j.o test_j.dSYM
	rm -f *.profraw *.profdata *.prof
	rm -f *.counts *.cov *.cpu

########################################
## object files
test_j.o: test_j.c
	clang $(CFLAGS) -c test_j.c

########################################
## executables
test_j: test_j.o
	clang $(LDFLAGS) test_j.o -o test_j $(LIBS)

########################################
## profile_llvm
profile_llvm: test_j ## Profile binary with LLVM tools
	@echo "running..."
	LLVM_PROFILE_FILE=$(PROFILER_DATA) ./test_j | tee test_j.out 
	$(LLVM_PROF_DATA) merge -output=$(PROFILER_FILE) -instr $(PROFILER_DATA)
	@echo "=========="
	$(LLVM_PROF_DATA) show -all-functions -counts -ic-targets test_j.prof | tee test_j.counts
	@echo "=========="
	$(LLVM_PROF_COV) show test_j -instr-profile=test_j.prof | tee test_j.cov
	@echo "=========="

########################################
## profile_prof
profile_prof: test_j ## Profile binary with gperf tools
	@echo "running..."
	CPUPROFILE=$(PROFILER_CPU) ./test_j | tee test_j.out 
	$(PPROF) --call_tree --addresses --text test_j $(PROFILER_CPU)
	@echo "=========="

## END-OF-FILE
