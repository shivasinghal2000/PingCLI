# Rutvik Patel

# This makefile allows the user to link, compile and clean the files
# necessary to run the package
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

CC = g++ # compiler of choice
OBJS = main.o # object files to be generated
FILES = main.cpp util.h Makefile
EXEC = pingCLI

# builds the project
pingCLI: $(OBJS)
	$(CC) -o $(EXEC) $(OBJS) -w

# compiles main.cpp into its respective object (.o) file
main.o: main.cpp util.h
	$(CC) -c -std=c++11 main.cpp -w

# compresses and creates a tar file
tar:
	tar -cvf pingCLI.tar.gz $(FILES) pingCLI/

# removes the .o and executable files from the source directory
clean:
	@rm -f *.o $(EXEC)

# prints out the makefile target objectives
help:
	@echo 'make (all)     : builds the server and client executable, along with generating a pdf version of the man pages'
