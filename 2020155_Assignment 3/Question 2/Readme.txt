FIFOs:
In order to run the program based on FIFOs, run './p1Fifo' and then './p2Fifo' in 2 separate terminals after running the 'make' command.

Logic:
First 50 random strings are generated each of length 9 and are stored in a 2D char array. After that, we create 2 fifos with read, write and execute permissions. These FIFOs are named memory locations in the kernel's memory used for Inter Process Communicaton.
2 FIFOs are made because both the processes need to read and write simultaeously.
Both the FIFOs are opened, one in write-only mode and the other in read-only mode. Now we write the data from the first FIFO P1-P2Fifo from P1 program to P2 program. We use a struct called 'data' to send the index and the random string to send the data from P1 to P2.

5 instances of such a structure are sent to P2 a which are then printed. Then using the other FIFO, P2 sends the highest index as the acknowledgement which is reflected in P1. After receiving the acknowledgement, P1 then sends the next 5 strings to P2. This thing continues until 50 strings are sent. 
Note that the index of the strings follow 0 based indexing.

Finally the FIFOs are closed and removed, i.e. deleted from the kernel's memory

MESSAGE QUEUEs
After the make command run './P1MsgQueue' and then './P2MsgQueue' in 2 separate terminals.

Logic:
Again 50 random strings are generated and then using ftok, a unique identifier to a message queue is generated for 2 queues as we have to send and receive data simultaeously from P1 and P2.

After making the unique identifier, we get the message queue identifier using the msgget function with IPC|CREAT flag to ensure a new queue is made.
A struct named msg_struct is used to send data from one process to another. It has 2 values: long type to determine the order in ehich the queues will be sent or recived and the other is a string to send the message across the processes.

Since we are able to only send the string as message, the index is converted to string using sprintf and appended to the corresponding string before sending from P1 to P2.

We set the type as 1 as we do not wish to follow any particular hierarchy of sending and receiving messages.

The message using struct is sent using the msgsnd function and received on the other end using the msgrcv function. After sending the batch of 5 strings, P1 would wait for acknowledgement sent by P2 as string, converted to int using atoi(). This continues for 10 batches of 5 strings each. The messages sent to both processes are printed to stdout.


UNIX DOMAIN SOCKETS:
For evaluation of this part kindly run the './p2Socket' first and then './p1Socket' rather than the othr way around as in above 2 cases. Also ensure before running 'make' that there is no pre-existing socket with the name "p1-p2Socket". In case it is there use the command 'rm p1-p2Socket'

Logic:
Firstly, 50 random strings are generated and a struct to determine the UNIX domain socket address is declared. There are 2 values in this struct, sa_family_t sun_family that just contains the information that it is a unix domain socket by mentioning AF_UNIX and the other value is a string of 108 characters which contains the path of the unix socket.

Next we use the socke() syscall to create the socket which is returns the file descriptor to be actually used for communication. Its 1st parameter declares that the socket is a local UNIX socket and 2nd parameter declares that it is 2 way connection that supports byte streams using read and write syscalls.

The connection to the socket is created using the connect() function and this is the point where p1 and p2 get to know each other as client and server respectively and can share data bith ways using only one socket using read() and write. P2 gets connected using the bind syscall and marks the start of accepting the incoming strings using the listen system call.

Communication in batch of 5 strings is done and after completion the socket is closed.





References:
https://medium.com/swlh/getting-started-with-unix-domain-sockets-4472c0db4eb1
https://man7.org/linux/man-pages/man7/unix.7.html
Tutorial 9