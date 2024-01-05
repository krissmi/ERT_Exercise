
OS = $(shell uname)
ifeq ($(OS),Linux)
	DISTRO = $(shell cat /etc/os-release | grep -e "^ID=" | cut -d= -f2 | tr -d '"')
else ifeq ($(OS),Darwin)
	DISTRO = "macos"
endif

########################################
## Make Environment

ROOTDIR := $(shell dirname $(CURDIR))
INSTALLPATH_ROOT = $(ROOTDIR)/local
INSTALLPATH_LIB = $(INSTALLPATH_ROOT)/lib
INSTALLPATH_BIN = $(INSTALLPATH_ROOT)/bin
INSTALLPATH_DAT = $(INSTALLPATH_ROOT)/dat

########################################
## System Commands

GREP = grep
SED = sed
COLUMN = column

########################################
## Compiler Flags

CC = gcc
MAKE := $(shell type -a make | head -1 | cut -d' ' -f1)

BINARY = iri_edp

LIBRARY = iri_2016

########################################
## Target Helpers

.PHONY: all clean depends help $(PROJECTDIRS)
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
## all
all: install ## Build the binary

########################################
## depends
depends: ## Project Dependencies
ifeq ($(OS),Darwin)
	$(HOMEBREW) install gcc make gnuplot
else ifeq ($(DISTRO),fedora)
	sudo $(DNF) -y install gcc-gfortran binutils @c-development @development-tools
else ifeq ($(DISTRO),rhel)
	sudo $(DNF) -y install gcc-gfortran binutils
else ifeq ($(DISTRO),centos)
	sudo $(DNF) -y groupinstall "Development Tools"
	sudo $(DNF) -y install gcc-gfortran binutils
else
	@echo "detected unsupported system $(OS)"
	exit 1
endif

########################################
## clean
clean: ## Remove build artifacts
	rm -f *.o
	rm -f $(BINARY)

########################################
## object files
$(BINARY).o : $(BINARY).c ## Compile iri_edp source files
	$(CC) -g -fPIC -c $<

########################################
## Main binary
$(BINARY): $(BINARY).o ## Build iri_edp binary
	$(CC) -g -Wall \
		-fPIC \
		-Wl,-rpath,$(INSTALLPATH_LIB) \
		-o $@ -L$(INSTALLPATH_LIB) $< -l$(LIBRARY)

########################################
## install
install: $(BINARY) ## Install edp module to local installation path $(INSTALLPATH_ROOT)
	cp -vp $(CURDIR)/$(BINARY) $(INSTALLPATH_BIN)

# END-OF-FILE
