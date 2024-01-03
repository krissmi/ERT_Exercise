
OS = $(shell uname)
ifeq ($(OS),Linux)
	DISTRO = $(shell cat /etc/os-release | grep -e "^ID=" | cut -d= -f2 | tr -d '"')
else ifeq ($(OS),Darwin)
	DISTRO = "macos"
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

MKDIR = mkdir
CP = cp

MAKE := $(shell type -a make | head -1 | cut -d' ' -f1)

########################################
## Make Environment

ROOTDIR := $(CURDIR)
INSTALLPATH_ROOT = $(ROOTDIR)/local
INSTALLPATH_LIB = $(INSTALLPATH_ROOT)/lib
INSTALLPATH_BIN = $(INSTALLPATH_ROOT)/bin
INSTALLPATH_DAT = $(INSTALLPATH_ROOT)/dat

SUBDIRS := $(wildcard iri*/.)

########################################
## Target Helpers

.PHONY: help clean all depends $(SUBDIRS)
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
## subdirectories

$(SUBDIRS): 
	$(MAKE) -C $@ $(MAKECMDGOALS)

########################################
## all
all: $(SUBDIRS) install ## Build all project subdirectories

########################################
## depends
depends: ## Project Dependencies
ifeq ($(OS),Darwin)
	$(HOMEBREW) install gcc make gnuplot
else ifeq ($(DISTRO),fedora)
	sudo $(DNF) -y install gcc-gfortran binutils @c-development @development-tools
else ifeq ($(DISTRO),rhel)
	sudo $(DNF) -y groupinstall "Development Tools"
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
clean: $(SUBDIRS) ## Remove build artifacts
	rm -rf $(INSTALLPATH_ROOT)

########################################
## install
install: $(SUBDIRS) ## Install test data files to local path $(INSTALLPATH_ROOT)
	@echo "using root path: $(INSTALLPATH_ROOT)"
	###### copy common data files
	$(MKDIR) -p $(INSTALLPATH_DAT)
	$(CP) -rvp $(CURDIR)/common/*.asc $(INSTALLPATH_DAT)
	###### copy index data files
	$(MKDIR) -p $(INSTALLPATH_DAT)
	$(CP) -rvp $(CURDIR)/indices/*.dat $(INSTALLPATH_DAT)

# END_OF_FILE
