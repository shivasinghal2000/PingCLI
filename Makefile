# Rutvik Patel
# PingCLI

# This makefile allows the user to link, compile and clean the files
# necessary to run the project
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

CC = g++ # compiler of choice
OBJS = main.o # object files to be generated
FILES = main.cpp util.h Makefile
EXEC = pingCLI

# builds the project
pingCLI: $(OBJS)
	@$(CC) -o $(EXEC) $(OBJS) -w

# compiles main.cpp into its respective object (.o) file
main.o: main.cpp util.h
	@$(CC) -c -std=c++11 main.cpp -w

# removes the .o and executable files from the source directory
clean:
	@rm -f *.o $(EXEC)

# prints out the makefile target objectives
help:
	@echo 'make (pingCLI) : builds the project, creating the pingCLI executable'
	@echo 'make main.o    : compiles main.cpp into its respective object (.o) file'
	@echo 'make clean     : removes the .o and executable files from the source directory'
	@echo 'make help      : prints out further information about the makefile targets available to use'
