
OS := $(shell uname)

.PHONY: help clean
.DEFAULT_GOAL := help

########################################
## help
help: ## Makefile help
	@echo "Active Targets:"
	@echo "==============="
	@$(GREP) -E '^[.a-zA-Z0-9_-]+:.*?## .*$$' $(MAKEFILE_LIST) \
	| $(SED) -n 's/^\(.*\): \(.*\)##\(.*\)/\1,\3/p' \
	| $(COLUMN) -t  -s ','

# END-OF-FILE
