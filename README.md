 # PingCLI
 This is a command line interface made for review by the Cloudflare team. This application runs on **Linux** sends repeated **ICMP echo requests** to the specified host/IP-address, while receiving proper *acknowledgement* (echo reply) messages.

 ## Running Instructions
 To build the project, simply navigate to the correct (source) directory in terminal, and run the following command:
 ```
 $ make
 ```
 After the project is successfully built, follow the following syntax to run the executable:
 ```
 $ ./pingCLI <hostname / IP-address> <ttl>?
 ```
 The input parameters are described in more detail below:
 
 `hostname/IP-address`: a valid hostname **or** IP-address

 `ttl` : The **time-to-live** for the ping. This field is **optional** and should be an integer value between **1** and **255**. If left empty, the ttl defaults to 255.

## Program Output
After starting the program, assuming all parameters are entered correctly, the program writes to stdout. The following format is followed:
```
request # <request number>:    RTT time = <time in ms>    <percentage> packet loss
```
The 3 output fields are described in further detail below:
* `request number`: An integer that simply increments and keeps a track of the number of requests sent
* `RTT time`: This represents the **round trip time**, which is the time it takes for the request to be sent and proper acknowledgement reception.
* `packet loss`: This is shown as a percentage, and represents the number of packets lost in the communication.

## Program Termination
This application is designed to send ICMP "echo requests" in an **infinite** loop. This means that termination requires the user to send the *SIGINT* signal (ctrl + c) to the program to stop sending requests.


## Miscellaneous
### Extra Credit
Addressing the extra credit points provided in the [challenge description](https://github.com/cloudflare-internship-2020/internship-application-systems/blob/master/README.md), this implementation allows for the **TTL** to be received as an argument and reports the resulting ICMP message. If given more time, and under better circumstances, the project would be fleshed out further and support would be provided to valuable features.

### Makefile Targets
The project includes its own Makefile, which is used to compile and link all the object (.o) files. The targets of the Makefile can be displayed in the command line by using the command
```
$ make help
```
Furthermore, the target descriptions can be found below:
* make (**pingCLI**) : builds the project, creating the pingCLI executable
* make **main.o**    : compiles main.cpp into its respective object (.o) file
* make **clean**     : removes the .o and executable files from the source directory
* make **help**      : prints out further information about the makefile targets available to use
