# GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  gbsh_config = debug
endif
ifeq ($(config),release)
  gbsh_config = release
endif

PROJECTS := gbsh

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

gbsh:
ifneq (,$(gbsh_config))
	@echo "==== Building gbsh ($(gbsh_config)) ===="
	@${MAKE} --no-print-directory -C build/gbsh -f Makefile config=$(gbsh_config)
endif

clean:
	@${MAKE} --no-print-directory -C build/gbsh -f Makefile clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   gbsh"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"