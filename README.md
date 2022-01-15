# Introduction
This is my first readme file for any program that I have written.  This file at this point, only specifies things like exit codes, and documents the protocol by which messages are transmitted from monitor to agent.

# Protocol specs							 
After being corrected on my use of TCP, I've developed the 	 
following protocol specification for this program.		 
The agent program must represent 4 different stages, or run-	 
time conditions, at this time.  More may follow as future 	 
versions of the program are coded.				 


# Return Codes
```
 	0	Successful execution of program				 
 	1	Incorrect command line usage, currently only 		 
 		implemented in the monitor portion			 
 	2	Memory allocation errors, malloc()			 
 	3	Socket allocation errors, socket()			 
 	4	Error in bind()						 
 	5	Error in connect()					 
 	6	Error in accept()					 
 	7	Error in fork()						 
```
