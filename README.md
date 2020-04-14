 # PingCLI
 This is a command line interface made for **linux**, and for review by the Cloudflare team. This application sends repeated **ICMP echo requests** to the specified host/IP-address, while receiving proper *acknowledgement* (echo reply) messages.

 ## Running Instructions
 To build the project, simply navigate to the correct (source) directory in terminal, and run the following command:
 ```
 $ make
 ```
 After the project is successfully built, follow the following syntax to run the executable:
 ```
 $ ./pingCLI <hostname / IP-address> <ttl>*
 ```
 The input parameters are described in more detail below:
 
 `hostname/IP-address`: a valid hostname **or** IP-address

 `ttl` : The **t**ime-**t**o-**l**ive for the ping. This field is **optional** and should be an integer value between **1** and **255**. If left empty, the ttl defaults to 255.

## Program Output
After starting the program, assuming all parameters are entered correctly, the program writes to stdout. The following format is followed:
```
request # <request number>:    RTT time = <time in ms>    <percentage> packet loss
```
The 3 output fields are described in further detail below:
* `request number`: An integer that simply increments and keeps a track of the number of requests sent
* `RTT time`: This represents the **round trip time**, which is the time it takes for the request to be sent and proper acknowledgement reception.
* `packet loss`: This is shown as a percentage, and represents the number of packets lost in the communication.
