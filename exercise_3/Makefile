
OS := $(shell uname)
ifeq ($(OS),Linux)
	DISTRO := $(shell cat /etc/os-release | grep -e "^ID=" | cut -d= -f2 | tr -d '"')
else ifeq ($(OS),Darwin)
	DISTRO := "macos"
endif

########################################
## Python virtual environment
include Makefile.venv

PYTHON=$(VENV)/python3
PIP=$(VENV)/pip3

## Packages
POETRY = $(VENV)/poetry

########################################
## System Commands

GREP = grep
SED = sed
COLUMN = column

########################################
## System Packages

HOMEBREW = brew
DOCKER = docker
COLIMA = colima

DNF = dnf

PACKAGE_NAME = swpctools
PACKAGE_FILE = $(PACKAGE_NAME)-0.1.0.tar.gz

########################################
## Target Helpers

.PHONY: help clean depends package.remove service.run
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
## clean
clean: ## Clean build artifacts
	rm -rf __pycache__
	rm -rf data/ dist/ logs/

########################################
## depends
depends: ## Setup project dependencies (requires: macOS 14.x)
	$(PIP) install --no-cache --upgrade pip

ifeq ($(OS),Darwin)
	$(HOMEBREW) install docker docker-buildx colima
else ifeq ($(DISTRO),fedora)
	sudo $(DNF) -y install python3-devel python3.11-devel
	sudo $(DNF) -y install git binutils binutils-gprofng strace @c-development @development-tools
	sudo $(DNF) -y install lynx
	sudo $(DNF) -y install dnf-plugins-core
	sudo $(DNF) -y config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo
	sudo $(DNF) -y install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
	sudo systemctl start docker
else ifeq ($(DISTRO),rhel)
	sudo $(DNF) -y install python3-devel python3.11-devel
	sudo $(DNF) -y groupinstall "Development Tools"
	sudo $(DNF) -y install git dnf-utils device-mapper-persistent-data lvm2
	sudo $(DNF) -y install lynx
	sudo $(DNF) -y config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
	sudo $(DNF) -y install docker-ce
	sudo systemctl start docker
else ifeq ($(DISTRO),centos)
	sudo $(DNF) -y install python3-devel python3.11-devel
	sudo $(DNF) -y groupinstall "Development Tools"
	sudo $(DNF) -y install git dnf-utils device-mapper-persistent-data lvm2
	sudo $(DNF) -y install lynx
	sudo $(DNF) -y config-manager --add-repo https://download.docker.com/linux/centos/docker-ce.repo
	sudo $(DNF) -y install docker-ce
	sudo systemctl start docker
else
	@echo "detected unsupported system $(OS)"
	exit 1
endif

	$(PIP) install poetry  # python package support
	$(PIP) install --requirement requirements.txt

########################################
## pull_rtsw
pull.rtsw: ## Pull RTSW records from endpoint and update local data store
	$(PYTHON) $(CURDIR)/swpctools.py rtsw pull

########################################
## dumo_rtsw
dump.rtsw: ## Pull RTSW records from local data store and save to CSV file
	$(PYTHON) $(CURDIR)/swpctools.py rtsw dump

########################################
## package
package.build: export GIT_DISCOVERY_ACROSS_FILESYSTEM = 1
package.build: depends ## Build python package
	rm -f dist/*
	$(POETRY) build -vvv --format=sdist

########################################
## install
package.install:  ## Install python package
	$(PIP) install --only-binary=:all: dist/$(PACKAGE_FILE)

########################################
## install
package.remove: ## Remove installed python package
	$(PIP) uninstall --yes $(PACKAGE_NAME)

########################################
## service_build
service.build: package.build ## Build the docker image and run SWPC daemon
ifeq ($(OS),Darwin)
	$(COLIMA) start
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
	@echo "#### Containers"
	$(DOCKER) container ls --all
	@echo "#### Networking"
	$(DOCKER) exec swpc ip -4 -o address

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
endif

# END-OF-FILE