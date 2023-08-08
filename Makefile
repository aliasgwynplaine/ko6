#---------------------------------------------------------------------------------------------------
#  _     ___    __
# | |__ /'v'\  / /   	\date       2023-02-24
# | / /(     )/ _ \   	\copyright  2021-2023 Sorbonne University
# |_\_\ x___x \___/                 https://opensource.org/licenses/MIT
#
# see https://www.gnu.org/software/make/manual/make.html for documentation on make
#---------------------------------------------------------------------------------------------------

# Parameters
# --------------------------------------------------------------------------------------------------

APP    ?= hello#					app name
MAKOPT ?= -s#						comment the -s to get command details
SOC    ?= almo1-mips#				defaut SOC name
NTTYS  ?= 2#						default number of ttys
NCPUS  ?= 1#						default number of CPUS
VERBOSE?= 0#						verbose mode to print INFO(), BIP(), ASSERT, VAR()
BLDDIR  = build#           			build directory
SWDIR   = src/soft#        			software directory
SOCDIR	= $(SWDIR)/hal/arch/$(SOC)#	SOC specific sources directory
FROM   ?= 000000#					first cycle to trace
LAST   ?= 500000#					last cycle to execute
DLOG    = ~/kO6-debug.log#			debug file
APPS	= $(shell ls -l src/soft/uapp | grep "^d" | awk '{print $$NF}')

# Rules (here they are used such as simple shell scripts)
# --------------------------------------------------------------------------------------------------

.PHONY: help compil clean exec debug

help:
	@echo ""
	@echo "Usage: make <Target> [APP=app] [Parameter=n]"
	@echo ""
	@echo "    Target "
	@echo "        app    : execute app which is one of the application name of uapp"
	@echo "                 "$(APPS)
	@echo "                 ex: make "$(word 1, $(APPS))" --> execute app "$(word 1, $(APPS))
	@echo "        compil : compiles all sources"
	@echo "        pdf    : generate sources.pdf with all source files"
	@echo "        clean  : clean all compiled files"
	@echo "        exec   : executes the prototype (defaults $(APP) on $(SOC))"
	@echo "        debug  : Executes and generates logs (trace[cpu].s & label[cpu].s)"
	@echo ""
	@echo "    Parameters (default values are defined in the Makefile)"
	@echo "        APP    : application name (default $(APP) thus code is in uapp/$(APP))"
	@echo "                 "$(APPS)
	@echo "        FROM   : first cycle from which the trace is made in debug (default $(FROM))"
	@echo "        LAST   : last cycle to execute (default $(LAST))"
	@echo "        NTTYS  : number of TTY to create (default $(NTTYS))"
	@echo "        NCPUS  : number of CPU to create (default $(NCPUS))"
	@echo "        VERBOSE: verbose mode for (see common/debug_*.h) (default $(VERBOSE))"
	@echo ""

compil:
	make -C $(SWDIR) $(MAKOPT) MAKOPT=$(MAKOPT) compil SOC=$(SOC) VERBOSE=$(VERBOSE)

pdf:
	make -C $(SWDIR) $(MAKOPT) pdf SOC=$(SOC)

exec: compil
	make -C $(SOCDIR) exec NTTYS=$(NTTYS) NCPUS=$(NCPUS) \
		VERBOSE=$(VERBOSE) FROM=$(FROM) LAST=$(LAST)

debug: compil
	make -C $(SOCDIR) debug NTTYS=$(NTTYS) NCPUS=$(NCPUS) \
		VERBOSE=$(VERBOSE) FROM=$(FROM) LAST=$(LAST)

doxygen:
	doxygen doxygen.cfg

clean:
	make -C $(SWDIR) $(MAKOPT) MAKOPT=$(MAKOPT) clean
	@echo "- clean logs execution files"
	@-killall xterm soclib-fb 2> /dev/null || true
	@-rm -f /tmp/fbf.* $(DLOG) xterm* label*.s trace*.s 2> /dev/null || true
	@-rm -rf $(BLDDIR) doxygen 2> /dev/null || true
	@find . -name *~ | xargs rm -f

# Generate as many rules as app in uapp directory
# if there an application named "test" then "make test" execute "make exec APP=test"
# --------------------------------------------------------------------------------------------------
$(foreach a,$(APPS), $(eval $(a):;make exec APP=$(a)))
