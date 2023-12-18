
OS := $(shell uname)

GREP = grep
SED = sed
COLUMN = column
PYTHON = python3
POETRY = poetry
PIP = pip
HOMEBREW = brew
DOCKER = docker
COLIMA = colima

PACKAGE_NAME = swpctools
PACKAGE_FILE = $(PACKAGE_NAME)-0.1.0.tar.gz

.PHONY: clean depends help package.remove service.run
.DEFAULT_GOAL := help

########################################
## help
help: ## Makefile help
	@echo "Active Targets:"
	@echo "==============="
	@$(GREP) -E '^[.a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| $(SED) -n 's/^\(.*\): \(.*\)##\(.*\)/\1,\3/p' \
	| $(COLUMN) -t  -s ','

########################################
## clean
clean: ## Clean build artifacts
	rm -rf __pycache__
	rm -rf data/ dist/ logs/

########################################
## pull_rtsw
pull.rtsw: ## Pull RTSW records from endpoint and update local data store
	$(PYTHON) $(CURDIR)/swpc.py rtsw --pull

########################################
## dumo_rtsw
dump.rtsw: ## Pull RTSW records from local data store and save to CSV file
	$(PYTHON) $(CURDIR)/swpc.py rtsw --dump

########################################
## depends
depends: ## Setup project dependencies (requires: macOS 14.x)
	$(PIP) install --requirement requirements.txt
ifeq ($(OS),Darwin)
	$(HOMEBREW) install docker docker-buildx colima
else
	@echo "detected unsupported system $(OS)"
	exit 1
endif

########################################
## package
package.build: depends ## Build python package
	rm -f dist/*
	$(POETRY) build -vv --format=sdist

########################################
## install
package.install: package.build ## Install python package
	$(PIP) install --only-binary=:all: dist/$(PACKAGE_FILE)

########################################
## install
package.remove: ## Remove installed python package
	$(PIP) uninstall --yes $(PACKAGE_NAME)

########################################
## service_build
service.build: depends package.build ## Build the docker image and run SWPC daemon
ifeq ($(OS),Darwin)
	$(COLIMA) start
else
	@echo "detected unsupported system $(OS)"
	exit 1
endif
	-$(DOCKER) container rm --force swpc
	-$(DOCKER) image rm --force swpc
	$(DOCKER) build --tag swpc --progress=plain .
	$(DOCKER) image ls --all

########################################
## service_run
service.run: ## Start the service listener
	-$(DOCKER) container rm --force swpc
	$(DOCKER) --debug run --name swpc --publish 8000:8080 --interactive --tty --log-driver=syslog swpc
	$(DOCKER) container ls --all

########################################
## service_kill
service.kill: ## Stop the service listener
	$(DOCKER) container stop --signal SIGSTOP --time 5 swpc

########################################
## service_shell
service.shell: ## Open a shell to the service host
	$(DOCKER) container exec --interactive --tty swpc /bin/bash

########################################
## service_clean
service.clean: ## Remove the service host and all service related runtime artifacts
	-$(DOCKER) stop swpc
	-$(DOCKER) system prune --all --volumes --force
ifeq ($(OS),Darwin)
	$(COLIMA) stop
else
	@echo "detected unsupported system $(OS)"
	exit 1
endif

# END-OF-FILE