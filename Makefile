################################################################################
#-------------------------------------------------------------------------------
# MakefileTargetRule for the seyeon make file template.
#-------------------------------------------------------------------------------
# Author: GJ Yang <gjyang@seyeon.co.kr>
#-------------------------------------------------------------------------------

################################################################################
# Include & Library Directorys
# EX: INC_DIRS += -I../IncDir 
# EX: LIB_DIRS += -L../LibDir 
#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
LIB_DIRS += -L/usr/lib

################################################################################
# Executable Target name : Executable File Target
# If you want to build multiple targets, then you can use EXC_TARGETS
# At this time, the ".c" file name must be the same as the targets name
#EXC_TARGETS = ExcTarget1 ExcTarget2
#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
EXC_TARGET = autoftp

################################################################################
# Source Files
#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
SRCS = autoftp.c

################################################################################
# LIBS Definitions : libXxxxYyyy.a --> -lXxxxYyyy
#vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
LIBS += -lpthread -lrt -lm

################################################################################
#-------------------------------------------------------------------------------
# Common Definitions
#-------------------------------------------------------------------------------
#CROSS = 
CC = $(CROSS)gcc
LD = $(CROSS)ld
AR = $(CROSS)ar
STRIP = $(CROSS)strip --strip-all
RANLIB = $(CROSS)ranlib
LN = ln

#-------------------------------------------------------------------------------
# Include & Library Directorys
#-------------------------------------------------------------------------------
INC_DIRS += -I. -I./include

#-------------------------------------------------------------------------------
# FLAGS Definitions
#-------------------------------------------------------------------------------
CFLAGS = -Wall $(INC_DIRS) $(DEFINES) $(DEBFLAGS)
ARFLAGS = crv

#-------------------------------------------------------------------------------
# Object Files
#-------------------------------------------------------------------------------
OBJS = ${SRCS:.c=.o}
LIB_OBJS = ${LIB_SRCS:.c=.o}


################################################################################
#-------------------------------------------------------------------------------
# Target Commands
#-------------------------------------------------------------------------------
all : $(EXC_TARGET)
	@echo "============================================================"
	@echo "= MAKE BUILD COMPLETED !! "
	@echo "============================================================"

#-------------------------------------------------------------------------------
release:
	make clean
	make all "DEBFLAGS=-O2 -DNDEBUG"
	
#-------------------------------------------------------------------------------
clean:
	rm -rf *.o *~ *.bak $(OBJS) $(LIB_OBJS)	$(LIB_TARGET) $(EXC_TARGET) $(EXC_TARGETS) $(SO_NAME) core*

################################################################################
#-------------------------------------------------------------------------------
# 1.Build for Executable File Target[$^ == $(OBJS) : Prerequest List]
#-------------------------------------------------------------------------------
$(EXC_TARGET): $(OBJS)
	@echo "============================================================"
	@echo "=  Build EXC: $@ for CROSS=$(CROSS)"
	@echo "============================================================"
	$(CC) $(CFLAGS) -o $@ $^ $(LIB_DIRS) $(LIBS)

