
OS := $(shell uname)
ifeq ($(OS),Linux)
	DISTRO := $(shell cat /etc/os-release | grep -e "^ID=" | cut -d= -f2 | tr -d '"')
else ifeq ($(OS),Darwin)
	DISTRO := "macos"
endif

########################################
## System Packages

HOMEBREW = brew
DNF = dnf

########################################
## System Commands

GREP = grep
SED = sed
COLUMN = column

########################################
## Compiler Flags

SOURCE=test_j.c
BINARY=test_j

ifeq ($(OS),Darwin)

	PROFILE_TARGETS = profile.llvm profile.gprof

	CC = clang

	CFLAGS = -g -O2 -Wall -fprofile-instr-generate -fcoverage-mapping -pg
	LDFLAGS = -fprofile-instr-generate -pg -L/opt/homebrew/lib
	LIBS = -lprofiler -ltcmalloc -lm

	PPROF = /opt/go/bin/pprof
	PPROF_TMPDIR = $(CURDIR)/pprof

	LLVM_PROF_DATA = /Library/Developer/CommandLineTools/usr/bin/llvm-profdata
	LLVM_PROF_COV = /Library/Developer/CommandLineTools/usr/bin/llvm-cov

	PROFILER_DATA=test_j.profdata
	PROFILER_FILE=test_j.prof
	PROFILER_CPU=test_j.cpu

else ifeq ($(OS),Linux)

	PROFILE_TARGETS = profile.perf profile.gprof

	CC = gcc

	CFLAGS = -g -O2 -Wall -pg
	LDFLAGS = -pg
	LIBS = -lm

	PERF = perf

endif

########################################
## Target Helpers

.PHONY: help clean
.DEFAULT_GOAL := help

########################################
## help
help: ## Makefile help
	@echo "==============="
	@echo "Platform: $(OS) ($(DISTRO))"
	@echo "Active Targets:"
	@echo "==============="
	@$(GREP) -E '^[.a-zA-Z0-9_-]+:.*?## .*$$' $(firstword $(MAKEFILE_LIST)) \
	| $(SED) -n 's/^\(.*\): \(.*\)##\(.*\)/\1,\3/p' \
	| $(COLUMN) -t  -s ','
	
########################################
## depends
depends: ## Project Dependencies
ifeq ($(OS),Darwin)
	$(HOMEBREW) install git gcc llvm make gperf gperftools
else ifeq ($(DISTRO),fedora)
	sudo $(DNF) -y install git binutils binutils-gprofng strace @c-development @development-tools
else ifeq ($(DISTRO),rhel)
	sudo $(DNF) -y install git binutils
else ifeq ($(DISTRO),centos)
	sudo $(DNF) -y groupinstall "Development Tools"
	sudo $(DNF) -y install git binutils binutils-devel binutils-gold strace
else
	@echo "detected unsupported system $(OS)"
	exit 1
endif

########################################
## clean
clean: ## Clean build artifacts
	rm -f $(BINARY) $(BINARY).out
	rm -f *.o *.dSYM
	rm -f *.profraw *.profdata *.prof
	rm -f *.counts *.cov *.cpu

########################################
## object files
$(BINARY).o: $(BINARY).c
	$(CC) $(CFLAGS) -c $(BINARY).c

########################################
## executables
$(BINARY): $(BINARY).o
	$(CC) $(LDFLAGS) $(BINARY).o -o $(BINARY) $(LIBS)

########################################
## profile
profile: $(PROFILE_TARGETS) ## Profile the binary

########################################
## profile.llvm
profile.llvm: test_j ## Profile binary with LLVM tools
	@echo "running...llvm"
	LLVM_PROFILE_FILE=$(PROFILER_DATA) ./$(BINARY) | tee $(BINARY).out 
	$(LLVM_PROF_DATA) merge -output=$(PROFILER_FILE) -instr $(PROFILER_DATA)
	@echo "=========="
	$(LLVM_PROF_DATA) show -all-functions -counts -ic-targets $(BINARY).prof | tee $(BINARY).counts
	@echo "=========="
	$(LLVM_PROF_COV) show $(BINARY) -instr-profile=test_j.prof | tee $(BINARY).cov
	@echo "=========="

########################################
## profile.prof
profile.gprof: test_j ## Profile binary with gprof tools
	@echo "running...gprof"
	CPUPROFILE=$(PROFILER_CPU) ./test_j | tee $(BINARY).out 
	$(PPROF) --call_tree --addresses --text $(BINARY) $(PROFILER_CPU)
	@echo "=========="

########################################
## profile.perf
profile.perf: test_j ## Profile binary with Linux perf tool
	@echo "running...perf"
	$(PERF) record ./$(BINARY) \
		-g \
		--all-cpus --branch-any --data \
		--event cpu-clock \
		--mmap-pages 3000 \
		--no-samples 2000 \
		--output $(BINARY).data

	$(PERF) report -i $(BINARY).data


## END-OF-FILE
