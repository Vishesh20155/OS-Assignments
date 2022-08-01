In order to evaluate this question, 2 files need to be updated with the provided patch files viz, 

    sys.c - update with sys.patch. Add the patch file in the directory and run the command: $patch sys.c < sys.patch
    (build > linux-//version// > kernel > sys.c)

    syscall_64.tbl - update with table.patch. Add the patch file in the directory and run the command: $patch syscall_64.tbl < table.patch
    (build > linux-//version// > arch > x86 > entry > syscalls > syscall_64.tbl)


All these changed and unchanged files are also in the folder

Example command for patching: patch syscall_64.tbl < table.patch
This will update the syscall_64.tbl file provided the table.patch is in the directory of the file.

After that run the make command and run the processes ./producer and then ./consumer. 

See the data of the queue after running the producer process in the kernel log using the sudo dmesg command.

ALso added are the config file after make and the tar file

LOGIC of the program:

Random bytes are read from the /dev/urandom file and sent to the kernel space via syscalls. 
The data is read in char variables(to read it byte by byte) and sent the same way to the kernel space. Inside the kernel the queue is updated with the data using the enque function called from the writer syscall.

The reader syscall dequeues an element and sends the data back to user using the copy_to_user function. This data is printed on running the consumer code. 

A static queue was made inside the kernel in global scope. Its pointers, tail and head were also made in the global scope. 

As per the question, the 2 system calls: reader and writer are made which accept the data sent by the producer and consumer and these does the work as explained above.

The queue and its pointers are treated as a critical section and is used only within the mutex lock.
mutex lock is used within the kernel. It is defined statically using DEFINE_MUTEX function.

mutex_lock and mtex_unlock are used to lock and unlock the critical section
