
OS := $(shell uname)

ROOTDIR := $(shell dirname $(CURDIR))
INSTALLPATH_ROOT = $(ROOTDIR)/local
INSTALLPATH_LIB = $(INSTALLPATH_ROOT)/lib
INSTALLPATH_BIN = $(INSTALLPATH_ROOT)/bin
INSTALLPATH_DAT = $(INSTALLPATH_ROOT)/dat

CC = gcc
MAKE := $(shell type -a make | head -1 | cut -d' ' -f1)

BINARY = iriedp

.PHONY: all clean depends help $(PROJECTDIRS)
.DEFAULT_GOAL := help

help: ## Makefile help
	@echo "Active Targets:"
	@echo "==============="
	@grep -E '^[.a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| sed -n 's/^\(.*\): \(.*\)##\(.*\)/\1,\3/p' \
	| column -t  -s ','

all: install ## Build the binary

depends: ## Project Dependencies
ifeq ($(OS),Darwin)
	brew install gcc make cmake 
else
	@echo "detected unsupported system $(OS)"
	exit 1
endif

clean: ## Remove build artifacts
	rm -f *.o
	rm -f $(BINARY)

$(BINARY).o : $(BINARY).c ## Compile iri_edp source files
	$(CC) -g -c $<

$(BINARY): $(BINARY).o ## Build iri_edp binary
	$(CC) -g -Wall -Wl,-rpath,$(INSTALLPATH_LIB) \
		 -o $@ -L$(INSTALLPATH_LIB) $< -liri_2016.0.1

install: $(BINARY) ## Install edp module to local path $(INSTALLPATH_ROOT)
	@echo "using root path: $(INSTALLPATH_ROOT)"
	###### copy binary file
	cp -vp $(CURDIR)/$(BINARY) $(INSTALLPATH_BIN)

# END-OF-FILE
