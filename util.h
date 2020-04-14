#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <queue>
#include <cstring>
#include <string>
#include <sstream>
#include <time.h>
#include <map>
#include <limits.h>
#include <string.h>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <signal.h>

/* defintion of constants */
#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64

using namespace std;

bool debug = false;  // set to true for debugging output to stdout, false otherwise

/*The next three functions are referenced from the following address: https://www.techiedelight.com/validate-ip-address/ */

/*
The isNumber function is responsible for checking to see if a string is a valid number
    Parameters:
        const string& str: The string to check
    Returns:
        bool : True if a number, false otherwise
*/
bool isNumber(const string& str)
{
	// std::find_first_not_of searches the string for the first character 
	// that does not match any of the characters specified in its arguments
	return !str.empty() && 
		(str.find_first_not_of("[0123456789]") == std::string::npos);
}

/*
The split function is responsible for splitting a string by a specified delimiter
    Parameters:
        const string& str: The string to split
        char delim : The delimiter to split by
    Returns:
        vector<string> : The resulting tokens of the split operation
*/vector<string> split(const string& str, char delim)
{
	auto i = 0;
	vector<string> list;

	auto pos = str.find(delim);
	
	while (pos != string::npos) 
	{
		list.push_back(str.substr(i, pos - i));
		i = ++pos;
		pos = str.find(delim, pos);
	}
	
	list.push_back(str.substr(i, str.length()));
	
	return list;
}

/*
The validateIP function is responsible for checking to see if a string is a valid IP address
    Parameters:
        const string& str: The string to check
    Returns:
        bool : True if a valid IP, false otherwise
*/
bool validateIP(string ip)
{
	// split the string into tokens
	vector<string> list = split(ip, '.');

	// if token size is not equal to four
	if (list.size() != 4)
		return false;

	// validate each token
	for (string str : list) 
	{
		// verify that string is number or not and the numbers 
		// are in the valid range
		if (!isNumber(str) || stoi(str) > 255 || stoi(str) < 0)
			return false;
	}
	return true;
}

/*
The readLine function is responsible for reading in a line from stdin
    Parameters:
    Returns:
        char *inputLine : the line read in from stdin
*/
char *readLine() {
    char *inputLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    getline(&inputLine, &bufferSize, stdin);
    return inputLine;
}

/*
The splitLine function is responsible for splitting the specified line by the delimiters
    Parameters:
        char *line: the line read in from stdin
    Returns:
        char **tokens: the tokens split by the delimiters
*/
char **splitLine(char *line) {
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    char *delims = " \t\r\n\a";  // delimiters of choices
    char **tokens = (char**)malloc(tokenBufferSize * sizeof(char*));
    char *tok = strtok(line, delims);
    int pos = 0;
    
    while (tok != NULL) {
        tokens[pos] = tok;
        pos++;
        if (pos >= tokenBufferSize) {
            tokenBufferSize += TOKEN_BUFFER_SIZE;
            tokens = (char**)realloc(tokens, tokenBufferSize * sizeof(char*));
        }
        tok = strtok(NULL, delims);
    }
    tokens[pos] = NULL;
    return tokens;    
}

/*
The signal_handler function is responsible for handling the SIGINT signal (ctrl+c), and printing out a message.
    Parameters:
        int signum: the signal classification number
    Returns: void
*/
void signal_handler(int signum) {
    printf("\ndone sending requests, goodbye.\n");
    exit(signum);
}

#endif
