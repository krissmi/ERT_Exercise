
OS := $(shell uname)

ROOTDIR := $(shell dirname $(CURDIR))
INSTALLPATH_ROOT = $(ROOTDIR)/local
INSTALLPATH_LIB = $(INSTALLPATH_ROOT)/lib
INSTALLPATH_BIN = $(INSTALLPATH_ROOT)/bin
INSTALLPATH_DAT = $(INSTALLPATH_ROOT)/dat

MAKE := $(shell type -a make | head -1 | cut -d' ' -f1)
GFORTRAN := $(shell type -a gfortran | head -1 | cut -d' ' -f1)

SOURCES := $(wildcard *.for)
FILEBASE := $(basename $(SOURCES))
OBJECTS = $(addsuffix .o, $(FILEBASE))

LIBVER = 0.1
LIBVER_COMPAT = 1.0.0
LIBNAME = iri_2016.$(LIBVER)

LIBRARY = lib$(LIBNAME).dylib
LIBSRC = cira.for igrf.for iridreg.for iriflip.for irifun.for irisub.for iritec.for irirtam.for
LIBASE = $(basename $(LIBSRC))
LIBOBJ = $(addsuffix .o, $(LIBASE))

IRITEST = iritest

CFLAGS = -fall-intrinsics -isysroot -fPIC
LDFLAGS=

.PHONY: all clean depends help
.DEFAULT_GOAL := help

help: ## Makefile help
	@echo "Active Targets:"
	@echo "==============="
	@grep -E '^[a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| sed -n 's/^\(.*\): \(.*\)##\(.*\)/\1,\3/p' \
	| column -t  -s ','

all: install ## Build the library

depends: ## Project Dependencies
ifeq ($(OS),Darwin)
	brew install gcc make cmake 
else
	@echo "detected unsupported system $(OS)"
	exit 1
endif

clean: ## Remove build artifacts
	rm -f *.o
	rm -f *.dylib *.so
	rm -f $(IRITEST)

%.o: %.for
	$(GFORTRAN) -g -fall-intrinsics -fno-underscoring -fno-second-underscore -fPIC -std=legacy -c $< $@

$(LIBRARY): $(LIBOBJ) ## Compile fortran source files and build shared library
	$(GFORTRAN) -g -fall-intrinsics -fno-underscoring -fno-second-underscore -fPIC -std=legacy \
	-dynamiclib \
	-Wl,-headerpad_max_install_names \
	-compatibility_version $(LIBVER_COMPAT) \
	-current_version $(LIBVER) \
	-o $(LIBRARY) \
	-install_name @rpath/$(LIBRARY) \
	$(LIBOBJ)

$(IRITEST): $(IRITEST).o $(LIBRARY) ## Compile and link test module
	$(GFORTRAN) -g -fall-intrinsics -fno-underscoring -fno-second-underscore -fPIC -std=legacy \
		-Wl,-rpath,$(CURDIR) \
		-Wl,-rpath,$(INSTALLPATH_LIB) \
		-o $@ -L$(CURDIR) $< -l$(LIBNAME) -lgfortran

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
