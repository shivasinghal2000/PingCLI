#include "util.h"

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

int main(int argc, char*argv[]) {
    int ttl = 255;
    // input error handling
    if (argc != 2 && argc != 3) {
        cout << "please follow the correct input format.\n" << 
        "correct format: ./pingCLI hostname/IP [ttl]\n";
        return 0;
    }

    if (argc == 3) {
        if (isNumber(argv[2])) {
            ttl = atoi(argv[2]);
            if (debug) {
                printf("ttl: %d\n", ttl);
            }
        }
    }



    // int portNum = atoi(argv[1]);  // set the port number
    string destination(argv[1]);

    if (debug) {
        cout << "input read in: '" << destination << "'" << endl;
    }

    if (validateIP(destination)) {
        if (debug) {
            printf("valid IP address entered: '%s'\n", destination.c_str());
        }
    } else {
        if (debug) {
            printf("hostname entered: '%s'\n", destination.c_str());
        }
    }
    
    string command = "ping -D -t " + to_string(ttl) + " " + destination;

    if (debug) {
        printf("the command to be run: %s\n", command.c_str());
    }

    FILE *p;
    char *psLine = NULL;
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    char **pToks = (char**) malloc(tokenBufferSize * sizeof(char*));  // token array
 
    // pipe the ps command
    float prevTime = 0.000;
    int msgNum = 0;
    if ((p = popen(command.c_str(), "r")) == NULL) {
        // error in opening the pipe
        printf("pipe could not be opened\n");
    } else {
        // pipe successful, continue.
        printf("starting to send echo requests\n");
        int lineCount = 0;
        // while lines are available to be read...
        while (getline(&psLine, &bufferSize, p)) {
           lineCount++;
           // ignore the first line
           if (lineCount == 1) {
               continue;
           }
           pToks = splitLine(psLine);  // split the line by the delimiters, saving the tokens
           string msgTime(pToks[7]);

            if (msgTime.size() == 4) {
                printf("message # %d\t Time to live exceeded\t100%% packet loss\n", msgNum++);
            } else {


                msgTime = msgTime.substr(5);

                float newTime = abs(stof(msgTime) - prevTime);
                prevTime = stof(msgTime);

                    // if the pid is found
                    // if (!strcmp(pid, psToks[0])) {
                    //     return true;
                    // } else {
                    //     // pid is not a match, continue to the next line
                    //     continue;
                    // }

                    printf("request # %d:\tRTT time = %.3f ms\t0%% packet loss\n", msgNum++, newTime);
                    
                    // printf("%s\n", msgTime.c_str());
            }
            continue;
        }
        if (pclose(p)) {
            // error closing the pipe
            printf("pipe could not close\n");
        }
    }
    return 0;
}
