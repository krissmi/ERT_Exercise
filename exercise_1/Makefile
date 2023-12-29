
OS := $(shell uname)

ROOTDIR := $(CURDIR)
INSTALLPATH_ROOT = $(ROOTDIR)/local
INSTALLPATH_LIB = $(INSTALLPATH_ROOT)/lib
INSTALLPATH_BIN = $(INSTALLPATH_ROOT)/bin
INSTALLPATH_DAT = $(INSTALLPATH_ROOT)/dat

MAKE := $(shell type -a make | head -1 | cut -d' ' -f1)

SUBDIRS := $(wildcard iri*/.)

.PHONY: help clean all depends $(SUBDIRS)
.DEFAULT_GOAL := help

########################################
## help
help: ## Makefile help
	@echo "Active Targets:"
	@echo "==============="
	@grep -E '^[.a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| sed -n 's/^\(.*\): \(.*\)##\(.*\)/\1,\3/p' \
	| column -t  -s ','

$(SUBDIRS): 
	$(MAKE) -C $@ $(MAKECMDGOALS)

########################################
## all
all: $(SUBDIRS) install ## Build all project subdirectories

########################################
## depends
depends: ## Project Dependencies
ifeq ($(OS),Darwin)
	brew install gcc make cmake gnuplot
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
	mkdir -p $(INSTALLPATH_DAT)
	cp -rvp $(CURDIR)/common/*.asc $(INSTALLPATH_DAT)
	###### copy index data files
	mkdir -p $(INSTALLPATH_DAT)
	cp -rvp $(CURDIR)/indices/*.dat $(INSTALLPATH_DAT)

# END_OF_FILE
