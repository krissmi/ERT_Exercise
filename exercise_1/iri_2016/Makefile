
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

MAKE := $(shell type -a make | head -1 | cut -d' ' -f1)
GFORTRAN := $(shell type -a gfortran | head -1 | cut -d' ' -f1)

########################################
## Compiler Flags

SOURCES := $(wildcard *.for)
FILEBASE := $(basename $(SOURCES))
OBJECTS = $(addsuffix .o, $(FILEBASE))

LIBVER = 0.1
LIBVER_COMPAT = 1.0.0
LIBNAME = iri_2016#.$(LIBVER)

LIBRARY = lib$(LIBNAME).so
LIBSRC = cira.for igrf.for iridreg.for iriflip.for irifun.for irisub.for iritec.for irirtam.for
LIBASE = $(basename $(LIBSRC))
LIBOBJ = $(addsuffix .o, $(LIBASE))

IRITEST = iritest

CFLAGS = -fall-intrinsics -isysroot -fPIC
LDFLAGS=

########################################
## Target Helpers

.PHONY: all clean depends help
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
all: install ## Build the library

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
	rm -f *.dylib *.so
	rm -f $(IRITEST)

########################################
## object files
%.o: %.for
	$(GFORTRAN) -g -fall-intrinsics -fno-underscoring -fno-second-underscore -fPIC -std=legacy -c $< $@

########################################
## shared library
$(LIBRARY): $(LIBOBJ) ## Compile fortran source files and build shared library
	$(GFORTRAN) -g -fall-intrinsics -fno-underscoring -fno-second-underscore -std=legacy \
	-dynamiclib \
	-fPIC -shared \
	-o $(LIBRARY) \
	$(LIBOBJ)

########################################
## test binary
$(IRITEST): $(IRITEST).o $(LIBRARY) ## Compile and link test module
	$(GFORTRAN) -g -fall-intrinsics -fno-underscoring -fno-second-underscore -std=legacy \
		-fPIC \
		-Wl,-rpath,$(CURDIR) \
		-Wl,-rpath,$(INSTALLPATH_LIB) \
		-o $@ -L$(CURDIR) $< -l$(LIBNAME) -lgfortran

########################################
## install
install: $(LIBRARY) $(IRITEST) ## Install test module and shared library to local path $(INSTALLPATH_ROOT)
	@echo "using root path: $(INSTALLPATH_ROOT)"
	###### copy shared library
	mkdir -p $(INSTALLPATH_LIB)
	cp -rvp $(LIBRARY) $(INSTALLPATH_LIB)
	###### copy test binary
	mkdir -p $(INSTALLPATH_BIN)
	cp -rvp $(IRITEST) $(INSTALLPATH_BIN)
	###### copy data files
	mkdir -p $(INSTALLPATH_DAT)
	cp -rvp $(CURDIR)/*.dat $(INSTALLPATH_DAT)

# END_OF_FILE
