.SUFFIXES: .cpp .hpp

#VERSION
VERSION	= 1.2

# Programs
SHELL 	= bash
CC     	= g++
LIB		= ar
MKDIR	= mkdir
RM 		= rm
CP		= cp
ECHO	= /bin/echo
DOXYGEN = doxygen
CAT		= cat
PRINTF	= printf
######################################
# Project Name (generate executable with this name)
TARGET_LIB = libsre.a
TARGET_ZIP = sre-lib-v$(VERSION).tgz

# Project Paths
PROJECT_ROOT=.
SRCDIR = $(PROJECT_ROOT)/src
SREDIR = $(SRCDIR)/sre
OBJDIR = $(PROJECT_ROOT)/obj
BINDIR = $(PROJECT_ROOT)/bin
DOCDIR = $(PROJECT_ROOT)/doc
LIBDIR = $(PROJECT_ROOT)/lib
BUNDIR = $(PROJECT_ROOT)/sre-lib
EXMDIR = $(PROJECT_ROOT)/examples

INCLUDE_PATH = /usr/include
INCLUDE_PATH_SRE = $(INCLUDE_PATH)/sre
INSTALL_PATH = /usr/lib

# Library Paths
BDD_ROOT=/usr

#Libraries
LIBS = -lbdd 

# Compiler and Linker flags
CPPFLAGS =-g -O3 
CPPFLAGS+=-I $(BDD_ROOT)/include
LDFLAGS+=-L $(BDD_ROOT)/lib

######################################

NO_COLOR=\e[0m
OK_COLOR=\e[1;32m
ERR_COLOR=\e[1;31m
WARN_COLOR=\e[1;33m
MESG_COLOR=\e[1;34m
FILE_COLOR=\e[1;37m

OK_STRING="[OK]"
ERR_STRING="[ERRORS]"
WARN_STRING="[WARNINGS]"
OK_FMT="${OK_COLOR}%30s\n${NO_COLOR}"
ERR_FMT="${ERR_COLOR}%30s\n${NO_COLOR}"
WARN_FMT="${WARN_COLOR}%30s\n${NO_COLOR}"
######################################

SRCS := $(wildcard $(SREDIR)/*.cpp)
INCS := $(wildcard $(SREDIR)/*.hpp)
OBJS := $(SRCS:$(SREDIR)/%.cpp=$(OBJDIR)/%.o)

EXAMPLES := $(wildcard $(EXMDIR)/*.cpp)
EXOBJS := $(EXAMPLES:$(EXMDIR)/%.cpp=$(OBJDIR)/%.o)
EXBINS := $(EXAMPLES:$(EXMDIR)/%.cpp=$(BINDIR)/%.out)

.PHONY: all setup compsetup doc clean distclean

all: setup $(LIBDIR)/$(TARGET_LIB)

setup:
	@$(ECHO) "Setting up compilation..."
	@mkdir -p $(LIBDIR)
	@mkdir -p $(DOCDIR)
	@mkdir -p $(OBJDIR)
	
compsetup: setup 
	@mkdir -p $(EXMDIR)
	@mkdir -p $(BINDIR)
	
$(OBJS): $(OBJDIR)/%.o : $(SREDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

$(LIBDIR)/$(TARGET_LIB): $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building: $(NO_COLOR) $(FILE_COLOR) %26s$(NO_COLOR)" "$(notdir $@)"
	@$(AR) -cr $@ $(OBJS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err
	@$(PRINTF) "${OK_COLOR}%50s\n${NO_COLOR}" "[DONE]"

########################################################################
## Installation

install: setup $(LIBDIR)/$(TARGET_LIB)
	@$(ECHO) "Installing Library Files ...  "
	@$(CP) $(LIBDIR)/$(TARGET_LIB) $(INSTALL_PATH)
	@$(ECHO) "Copying class files ...  "
	@$(RM) -rf $(INCLUDE_PATH_SRE)
	@$(MKDIR) -p $(INCLUDE_PATH_SRE)
	$(CP) $(INCS) $(INCLUDE_PATH_SRE)
	@$(ECHO) "Copying header files ...  "
	@$(CP) $(SRCDIR)/sre.h $(INCLUDE_PATH)
	@$(PRINTF) "${OK_COLOR}%50s\n${NO_COLOR}" "[DONE]"

########################################################################
## Uninstallation

uninstall: distclean
	@$(ECHO) "Uninstalling Library Files ...  "
	@$(RM) -rf $(INSTALL_PATH)/$(TARGET_LIB)
	@$(RM) -rf $(INCLUDE_PATH_SRE)
	@$(ECHO) "Deleting header files ...  "
	@$(RM) -rf $(INCLUDE_PATH)/sre.h
	@$(PRINTF) "${OK_COLOR}%50s\n${NO_COLOR}" "[DONE]"


########################################################################
## Examples

examples: compsetup $(EXBINS)

$(EXOBJS): $(OBJDIR)/%.o : $(EXMDIR)/%.cpp
	@$(PRINTF) "$(MESG_COLOR)Compiling: $(NO_COLOR) $(FILE_COLOR) %25s$(NO_COLOR)" "$(notdir $<)"
	@$(CC) $(CPPFLAGS) -c $< -o $@ -MD 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else printf "${OK_COLOR}%30s\n${NO_COLOR}" "[OK]"; \
	fi;
	@$(RM) -f temp.log temp.err

$(EXBINS): $(BINDIR)/%.out : $(OBJDIR)/%.o $(OBJS)
	@$(PRINTF) "$(MESG_COLOR)Building executable:$(NO_COLOR) $(FILE_COLOR) %16s$(NO_COLOR)" "$(notdir $@)"
	@$(CC) -o $@ $(LDFLAGS) $< $(OBJS) $(LIBS) 2> temp.log || touch temp.err
	@if test -e temp.err; \
	then $(PRINTF) $(ERR_FMT) $(ERR_STRING) && $(CAT) temp.log; \
	elif test -s temp.log; \
	then $(PRINTF) $(WARN_FMT) $(WARN_STRING) && $(CAT) temp.log; \
	else $(PRINTF) $(OK_FMT) $(OK_STRING); \
	fi;
	@$(RM) -f temp.log temp.err

########################################################################
## Documentation and CleanUp

doc:
	@$(ECHO) "Generating Doxygen Documentation ...  "
	@$(RM) -rf doc/html
	@$(DOXYGEN) $(DOCDIR)/Doxyfile 2 > /dev/null
	@$(PRINTF) "${OK_COLOR}%50s\n${NO_COLOR}" "[DONE]"

clean:
	@$(PRINTF) "Cleaning up... "
	@$(RM) -rf $(OBJDIR) *~ $(SRCDIR)/*~
	@$(PRINTF) "${OK_COLOR}%53s\n${NO_COLOR}" "[OK]"
	 
distclean: clean
	@$(PRINTF) "Removing compiled files ... "
	@$(RM) -rf $(BINDIR) $(DOCDIR)/html $(LIBDIR) *.tgz
	@$(PRINTF) "${OK_COLOR}%40s\n${NO_COLOR}" "[OK]"
	
bundle: distclean
	@$(ECHO) "Bundling to compressed folder ... "
	@$(MKDIR) -p $(BUNDIR)
	@$(CP) -r $(SRCDIR) $(DOCDIR) $(EXMDIR) Makefile README* $(BUNDIR)
	@tar -zcvf $(TARGET_ZIP) $(BUNDIR)
	@$(RM) -rf $(BUNDIR)
	@$(PRINTF) "${OK_COLOR}%50s\n${NO_COLOR}" "[DONE]"
	
	
