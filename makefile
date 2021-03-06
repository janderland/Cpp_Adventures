##       ##  ########  ##   ##   #######  ######
####   ####  ##    ##  ##  ##    ##       ##   ##
###########  ########  ######    #####    ######
##  ###  ##  ##    ##  ##   ##   ##       ##   ##
##       ##  ##    ##  ##    ##  #######  ##    ##

##################################################
# https://github.com/janderland/Maker



# GLOBAL CONFIG
###############

# Path(s) to configuration file(s).
configFiles=config.mkr


# Directory where all files generated by
# the build go.
buildDir=_build


# C++ Compiler Executable
# This executable is used to convert C++ source files into
# C++ object files.
cxx=g++


# C++ Compiler Flags
# cxxFlags     : used in every invocation of the compiler.
# cxxFlagsComp : used only during compilation.
# cxxFlagsLink : used only during linking.
cxxFlags=
cxxFlagsComp=
cxxFlagsLink=


# Flags passed to the ar utility.
arFlags=rcs


# File extensions for the input files
sourceExt=cpp
headerExt=hpp


# File extensions for the generated executables and
# static libraries.
execExt=out
slibExt=lib


# Set this variable to a non-empty string to turn off
# verbose output.
verbose=



# GLOBAL PROCESSING
###################

# Ensure all required global variables are defined.
requiredVars=buildDir cxx execExt slibExt
$(foreach v,$(requiredVars),$(if $($v),,$(error $v is required but not defined)))


# Empty the .SUFFIXES variable to turn off
# almost all the builtin rules.
.SUFFIXES:


# If "verbose" is empty, then don't print the
# command being invoked by make.
ifeq ($(verbose),)
.SILENT:
endif



# RULE MACROS
#############

# Define Static Lib Rule
# 1 - Output file
# 2 - Input files
# 3 - Compile Flags
# 4 - Package Flags
slibRule=$(eval $(call slibRuleTempl,$1,$2,$3,$4))
define slibRuleTempl
$1: cxxFlagsCompExtra = $3
$1: $2
	@echo "Packaging $$@"
	mkdir -p $$(dir $$@)
	ar $$(arFlags) $4 $$@ $$^
endef


# Define Executable Rule
# 1 - Output file
# 2 - Input files
# 3 - Compile Flags
# 4 - Link Flags
execRule=$(eval $(call execRuleTempl,$1,$2,$3,$4))
define execRuleTempl
$1: cxxFlagsCompExtra = $3
$1: $2
	@echo "Linking $$@"
	mkdir -p $$(dir $$@)
	$$(cxx) $$(cxxFlags) $$(cxxFlagsLink) $4 $$^ -o $$@
endef


# Define Alias Rule
# 1 - Alias Name
# 2 - Real Name
aliasRule=$(eval $(call aliasRuleTempl,$1,$2))
define aliasRuleTempl
.PHONY: $1
$1: $2
endef


# Define Run Rule
# 1 - Rule Name
# 2 - Executable
# 3 - Depedencies
runRule=$(eval $(call runRuleTempl,$1,$2,$3))
define runRuleTempl
.PHONY: $1
$1: $2 $3
	@echo "Running $$<"
	$$<
endef



# LOGGING MACROS
################

# Log - Normal
# 1 - Message
log=$(info $1)


# Log - Debug
# 1 - Message
debug=$(if $(verbose),$(info $1))



# METADATA MACROS
#################

# Check Path Exists
# 1 - Input path
checkPathExists=$(if $(shell test -d $1 && echo true),,$(error $1 isn't a directory))


# Check Path For 'At' Symbol ('@' isn't allowed in Maker paths)
# 1 - Input path
checkPathForAt=$(if $(findstring @,$1),$(error $1 contains the @ symbol))


# Runner Name
# 1 - Input path
rname=run@$1


# Input Source Files
# 1 - Input path
sources=$(shell find $1 -iname *.$(sourceExt))


# Output Object Files
# 1 - Input path
objects=$(addprefix $(buildDir)/,$(patsubst %.cpp,%.obj,$(call sources,$1)))


# Output File Path
# 1 - Input path
# 2 - Type
file=$(buildDir)/$1.$(call fileExt,$2)


# Output File Extension
# 1 - Type
fileExt=$(strip \
$(if $(filter exec,$1),$(execExt),\
$(if $(filter slib,$1),$(slibExt),\
$$$(error No file extension defined for type $1)\
))\
)


# File Rule Macro Name
# 1 - Type
fileRuleName=$(strip \
$(if $(filter exec,$1),execRule,\
$(if $(filter slib,$1),slibRule,\
$$$(error No file rule defined for type $1)\
))\
)


# Metadata Print Template
# 1 - Input Path
# 2 - Type
# 3 - Dependencies
# 4 - Compile Flags
# 5 - Link/Package Flags
define formatMetadata
Type          : $2
Dependencies  : $3
Compile Flags : $4
Linker Flags  : $5
Source Files  : $(call sources,$1)
Object Files  : $(call objects,$1)
Output File   : $(call file,$1,$2)
endef


# Define Module Metadata
# 1 - Input Path
# 2 - Type
# 3 - Dependencies
# 4 - Compile Flags
# 5 - Link/Package Flags
# 6 - Run Dependencies
module=$(eval $(call moduleTempl,$(strip $1),$(strip $2),$(strip $3),$(strip $4),$(strip $5),$(strip $6)))
define moduleTempl
$(call debug,Defining module for $1)
$(call checkPathExists,$1)
$(call checkPathForAt,$1)

$(call debug,$(call formatMetadata,$1,$2,$3,$4,$5))
$(call debug,)

$(1)Type=$2
$(1)Deps=$3
$(1)CFlags=$4
$(1)LFlags=$5
$(1)RunDeps=$6
targets+=$1
endef


# Dependency Files
# 1 - Dependency input paths
depFiles=$(foreach v,$1,$(call file,$v,$($(v)Type)))


# Define Module Rules
# 1 - Input Path
rules=$(eval $(call rulesTempl,$1,$($(1)Type),$($(1)Deps),$($(1)CFlags),$($(1)LFlags),$($(1)RunDeps)))
define rulesTempl
# Define the file rule
$(call $(call fileRuleName,$2),$(call file,$1,$2),$(call objects,$1) $(call depFiles,$3),$4,$5)

# Define the alias rule
$(call aliasRule,$1,$(call file,$1,$2))

# Define the run rule (only for executables)
$(if $(filter exec,$2),$(call runRule,$(call rname,$1),$(call file,$1,$2),$6))
endef



# HEADER DEP MACROS
###################

headerDepFlags=-MMD -MF $(basename $@).dep

headerDepFiles=$(shell if [ -d $(buildDir) ]; then find $(buildDir) -iname *.dep; fi)



# PUBLIC MACROS
###############

# Declare Module
# 0 - Type
# 1 - Input path
# 2 - Dependencies
# 3 - Compile Flags
# 4 - Link/Package Flags
moduleTypes=exec slib
$(foreach v,$(moduleTypes),$(eval $v=$$(call module,$$1,$$0,$$2,$$3,$$4)))



# LOAD METADATA
###############

# Parse Config File
# 1 - Config file path
parseConfig=$(call debug,Parsing $1)$(call debug,)\
            $(eval tempFile=$(shell mktemp))\
            $(shell perl -pe '$(parserCode)' < $1 > $(tempFile))\
            $(eval include $(tempFile))
define parserCode
s/(?<!\\)#.*\n/\n/g;
s/(?<!;)\s*\n//g;
s/;\s*\n/\n/g;
endef


$(call debug,Configuration)
$(call debug,=============)

$(foreach f,$(configFiles),$(call parseConfig,$f))



# STATIC RULES
##############

.PHONY: all clean

all: $(targets)

$(buildDir)/%.obj: %.cpp
	$(call log,Compiling $<)
	mkdir -p $(dir $@)
	$(cxx) -c $(headerDepFlags) $(cxxFlags) $(cxxFlagsComp) $(cxxFlagsCompExtra) $< -o $@

clean:
	$(call log,Cleaning)
	rm -rf $(buildDir)



# DYNAMIC RULES
###############

ifndef targets
$(error No module definitions found)
else
$(call debug,Targets: $(targets))
$(call debug,)

$(foreach t,$(targets),$(eval $(call rules,$t)))

include $(headerDepFiles)

$(call debug,Compilation)
$(call debug,===========)
endif
