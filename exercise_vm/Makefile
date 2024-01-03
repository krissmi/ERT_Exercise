
OS = $(shell uname)
ifeq ($(OS),Linux)
	DISTRO = $(shell cat /etc/os-release | grep -e "^ID=" | cut -d= -f2 | tr -d '"')
else ifeq ($(OS),Darwin)
	DISTRO = "macos"
endif

########################################
## Python virtual environment
include Makefile.venv

PYTHON=$(VENV)/python3
PIP=$(VENV)/pip3

########################################
## System Packages

HOMEBREW = brew

ANSIBLE_PLAYBOOK = ansible-playbook
ANSIBLE_INVENTORY = ansible-inventory

VAGRANT = vagrant

########################################
## System Commands

GREP = grep
SED = sed
COLUMN = column
SSH_ADD = ssh-add
MKDIR = mkdir

########################################
## Virtual Machine

export VAGRANT_HOME := $(CURDIR)/provision/data/.vagrant.d
export VAGRANT_DOTFILE_PATH := $(CURDIR)/provision/data/.vagrant
export ANSIBLE_HOME := $(CURDIR)/provision/data/.ansible

ifeq ($(PLATFORM),fedora)
	export BOX_NAME = file://boxes/fedora-39-aarch64.box
endif

ifeq ($(PLATFORM),centos)
	export BOX_NAME = file://boxes/centos-9-aarch64.box
endif

ifeq ($(PLATFORM),rhel)
	export BOX_NAME = file://boxes/rhel-9.3-aarch64.box
endif

########################################
## Target Helpers

.PHONY: help clean vm.depends vm.build vm.start vm.kill vm.shell vm.clean
.DEFAULT_GOAL := help

.ONESHELL:
.SHELLFLAGS = -xe

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
clean: vm.clean ## Clean build artifacts
	rm -rf __pycache__

########################################
## depends
depends: venv ## Setup project dependencies
	$(PIP) install --no-cache --upgrade pip
	$(PIP) install --requirement requirements.txt
	$(PIP) list --verbose

vm.depends: depends ## Virtual machine dependencies
	$(HOMEBREW) install vagrant
	mkdir -p $(CURDIR)/provision/data
	$(VAGRANT) plugin install vagrant-parallels

vm.build: vm.depends ## Create the virtual machine
	$(VAGRANT) box add --force --provider parallels --name $(BOX_NAME) $(BOX_NAME)

vm.list: ## Virtual machine status
	$(VAGRANT) box list
	@echo "=========="
	@$(VAGRANT) status
	@echo "=========="
	@$(VAGRANT) global-status

vm.start: ## Start the virtual machine
	@echo "<=============================>"
	@echo "<=== !! PASSWORD PROMPT !! ===>"
	@echo "<=============================>"
	@$(SSH_ADD) ~/.ssh/id_rsa
	@$(SSH_ADD) -l
	$(VAGRANT) up --provision

vm.kill: ## Stop (and destroy) the virtual machine
	-$(VAGRANT) destroy --force

vm.shell: ## Open a shell to the virtual machine
	-$(VAGRANT) ssh

vm.config: ## Show machine configuration
	-$(VAGRANT) ssh-config

vm.reload: ## Restart the VM
	$(VAGRANT) reload --provision

vm.clean: vm.kill ## Clean virtual machine artifacts
	-$(VAGRANT) box list | cut -f1 -d' ' | xargs -L 1 $(VAGRANT) box remove --all --force
	rm -rf shared .vagrant
	rm -rf $(CURDIR)/provision/data

## END-OF-FILE
