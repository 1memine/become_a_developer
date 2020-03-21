# Makefile
# Become a developer test
# March 2019


# Compiler
CC = clang

# Flags for compiler
CFLAGS = -ggdb3 -O0 -Qunused-arguments -std=c11 -Wall -Werror

# Executable
EXE = main

# Header files
HDRS = functions.h

LIBS =

# Sources
SRCS = main.c functions.c

OBJS = $(SRCS:.c=.o)

# default target
$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

# Dependencies
$(OBJS): $(HDRS) Makefile

clean:
	rm -f core $(EXE) *.o
