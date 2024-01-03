
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
	sudo $(DNF) -y install git binutils strace
else ifeq ($(DISTRO),centos)
	sudo $(DNF) -y groupinstall "Development Tools"
	sudo $(DNF) -y install git binutils binutils-gprofng strace
else
	@echo "detected unsupported system $(OS)"
	exit 1
endif

########################################
## clean
clean: $(SUBDIRS) ## Remove build artifacts
	rm -rf *.o

# END-OF-FILE
