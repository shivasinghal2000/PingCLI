#include "util.h"



int main(int argc, char*argv[]) {
    int ttl = 255;  // ttl defaults to 255

    // input error handling
    if (argc != 2 && argc != 3) {
        cout << "please follow the correct input format.\n" << 
        "correct format: ./pingCLI hostname/IP [ttl]\n";
        return 0;
    }

    // check to see if a ttl was passed in
    if (argc == 3) {
        if (isNumber(argv[2])) {
            ttl = atoi(argv[2]);
            if (debug) {
                printf("ttl: %d\n", ttl);
            }
        } else {
            // if the ttl parameter is not a number, terminate the program
            printf("invalid ttl entered. terminating.\n");
            return 0;
        }
    }

    string destination(argv[1]);  // set the destination (hostname/ip) to the first parameter passed in

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
    
    string command = "ping -D -t " + to_string(ttl) + " " + destination;  // the ping command to pipe

    if (debug) {
        printf("the command to be run: %s\n", command.c_str());
    }

    FILE *p;
    char *pLine = NULL;  // line array
    size_t bufferSize = BUFFER_SIZE;  // getLine allocates buffer size automatically
    int tokenBufferSize = TOKEN_BUFFER_SIZE;
    char **pToks = (char**) malloc(tokenBufferSize * sizeof(char*));  // token array
    int msgNum = 0;
    signal(SIGINT, signal_handler);
    // pipe the command
    if ((p = popen(command.c_str(), "r")) == NULL) {
        // error in opening the pipe
        printf("pipe could not be opened\n");
    } else {
        // pipe successful, continue.
        printf("starting to send echo requests\n");
        int lineCount = 0;
        // while lines are available to be read...
        while (getline(&pLine, &bufferSize, p)) {
            lineCount++;
            // ignore the first line
            if (lineCount == 1) {
                continue;
            }
            pToks = splitLine(pLine);  // split the line by the delimiters, saving the tokens
            string msgTime(pToks[7]);  // get the message rtt

            // if there was a "Time to live exceeded" message, print a custom message
            if (msgTime.size() == 4) {
                printf("message # %d\t Time to live exceeded\t100%% packet loss\n", msgNum++);
            } else {
                msgTime = msgTime.substr(5);  // get the time (in ms)
                printf("request # %d:\tRTT time = %.3f ms\t0%% packet loss\n", msgNum++, stof(msgTime));
            }
            continue;
        }
        // close the pipe
        if (pclose(p)) {
            // error closing the pipe
            printf("pipe could not close\n");
        }
    }
    return 0;
}
