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
#define BUFFER_SIZE 1024
#define TOKEN_BUFFER_SIZE 64

using namespace std;

bool debug = true;

/*The next three function are referenced from the following address: https://www.techiedelight.com/validate-ip-address/ */

// check if given string is a numeric string or not
bool isNumber(const string& str)
{
	// std::find_first_not_of searches the string for the first character 
	// that does not match any of the characters specified in its arguments
	return !str.empty() && 
		(str.find_first_not_of("[0123456789]") == std::string::npos);
}

// Function to split string str using given delimiter
vector<string> split(const string& str, char delim)
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

// Function to validate an IP address
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
#endif
