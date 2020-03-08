#gcc version
CC  = gcc
CXX = g++

GCCVER := $(shell $(CC) -dumpversion | awk -F. '{ print $$1"."$$2}' )

OBJ_DIR = ../build
LIB_DIR = ../lib

CFLAGS  = -g -Werror -Wall -O2 -pipe -fno-ident -D_GNU_SOURCE -D_REENTRANT -DNDEBUG 

CXXFLAGS += $(CFLAGS)

SUBDIRS := $(wildcard */)
OBJ_SUBDIRS := $(addprefix $(OBJ_DIR)/, $(SUBDIRS))
INCLUDE_SUBDIRS := $(addprefix -I./, $(SUBDIRS))

INCLUDES += -I./ 

LIBS = -lstdc++

CPP_SRC = $(wildcard *.cpp) $(wildcard */*.cpp)
C_SRC = $(wildcard *.c) $(wildcard */*.c)

CPP_OBJS = $(CPP_SRC:%.cpp=$(OBJ_DIR)/%.o)
C_OBJS   = $(C_SRC:%.c=$(OBJ_DIR)/%.o)

OBJ = DispatchBaseCoHash
all: $(OBJ)

prepare:
	@-mkdir -p $(OBJ_DIR)
	@-mkdir -p $(OBJ_SUBDIRS)


$(TARGET): $(CPP_OBJS) $(C_OBJS)
	$(CXX) $^ $(CXXFLAGS) $(LIBS) -o $@
	@echo


$(CPP_OBJS): $(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(INCLUDES) $(CXXFLAGS) -c $< -o $@
	@echo


$(C_OBJS): $(OBJ_DIR)/%.o: %.c
	$(CC) $(INCLUDES) $(CXXFLAGS)  -c $< -o $@
	@echo


distclean:
	@echo -e "cleaning...\n" 
	rm -rf $(OBJ)


clean:
	@echo -e "cleaning...\n" 
	rm -rf $(OBJ)

