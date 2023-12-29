
OS := $(shell uname)

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

SSH_ADD = ssh-add

########################################
## Virtual Machine

export VAGRANT_HOME := $(CURDIR)/provision/data/.vagrant.d
export VAGRANT_DOTFILE_PATH := $(CURDIR)/provision/data/.vagrant
export ANSIBLE_HOME := $(CURDIR)/provision/data/.ansible

########################################
## Target Helpers

.PHONY: help clean vm.depends vm.build vm.start vm.kill vm.shell vm.clean
.DEFAULT_GOAL := help

.ONESHELL:
.SHELLFLAGS = -xe

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
clean: vm.clean ## Clean build artifacts
	rm -rf __pycache__

########################################
## depends
depends: venv ## Setup project dependencies
	$(PIP) install --no-cache --upgrade pip
	$(PIP) install --requirement requirements.txt
	$(PIP) list --verbose

vm.depends: depends ## Virtual machine dependencies
	$(HOMEBREW) install utm vagrant
	mkdir -p $(CURDIR)/provision/data
	$(VAGRANT) plugin install vagrant-parallels

vm.build: vm.depends ## Create virtual machine
	$(VAGRANT) box add --force --provider parallels bento/fedora-38-arm64

vm.list: ## Virtual machine status
	$(VAGRANT) box list
	@echo "=========="
	@$(VAGRANT) status
	@echo "=========="
	@$(VAGRANT) global-status

vm.start: vm.depends vm.build ## Start the virtual machine
	@echo "<=============================>"
	@echo "<=== !! PASSWORD PROMPT !! ===>"
	@echo "<=============================>"
	@$(SSH_ADD) ~/.ssh/id_rsa
	@$(SSH_ADD) -l
	$(VAGRANT) up --provision

vm.kill: ## Stop (and destroy) the virtual machine
	-$(VAGRANT) destroy --force

vm.shell: vm.start ## Open a shell to the virtual machine
	$(VAGRANT) ssh

vm.clean: vm.kill ## Clean virtual machine artifacts
	-$(VAGRANT) box remove --all bento/fedora-38-arm64
	rm -rf shared
	rm -rf $(CURDIR)/provision/data

## END-OF-FILE
