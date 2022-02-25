In order to evaluate this question, 5 files need to be updated with the provided patch files viz, 

    sys.c - update with sys.patch. Add the patch file in the directory and run the command: $patch sys.c < sys.patch
    (build > linux-//version// > kernel > sys.c)

    fair.c - update with fair.patch. Add the patch file in the directory and run the command: $patch fair.c < fair.patch
    (build > linux-//version// > kernel > sched > fair.c)

    core.c - update with core.patch. Add the patch file in the directory and run the command: $patch core.c < core.patch
    (build > linux-//version// > kernel > sched > core.c)

    syscall_64.tbl - update with table.patch. Add the patch file in the directory and run the command: $patch syscall_64.tbl < table.patch
    (build > linux-//version// > arch > x86 > entry > syscalls > syscall_64.tbl)

    sched.h - update with sched.patch. Add the patch file in the directory and run the command: $patch sched.h < sched.patch
    (build > linux-//version// > include > linux > sched.h)

All these changed and unchanged files are also in the folder

Example command for patching: patch syscall_64.tbl < table.patch
This will update the syscall_64.tbl file provided the table.patch is in the directory of the file


After updating all the files and then compiling the kernel, a folder named tester is given that contains the C programs for testing the updated scheduler. Go into the directory of that folder and run the 'make' command. after that 2 program pairs need to be tested, one can be run by './test' for nice value 0 and the other one by './test1.2' for nice value 19. Both the program pairs are used to find first 20k prime nos and then evaluate the running time of that function which is then printed on the screen first without calling the syscall and then after calling the syscall. Instead of fork, execl is used to maintain the same PID for both with and without syscall testing.

To evaluate the updated vruntimes, see the kernel log after running './test1' and after './test1.2' using '$ sudo dmesg | tail'. The printed lines are not very clear as to what they specify. This is because my kernel's memory was full and so I could not do another make to rectify these print statements however, they are clearly explained here.

First of all syscall is called in test1.c (correspondingly in tes1.2.c). With this syscall, 1st line would be "Inside syscall". The next 2 lines, contrary to what has been printed in kernel log, its numerical value, just shows the vruntime before it is updated and used in the process. Again the next line contrary to what is printed, its numerical value shows the delay in nanosecond that is stored in the delay vaiable of the sched_entity structure.

Then the print statements after the next "Inside syscall" line show the following: The numerical value of the next 2 lines is the updated vruntime of the process and again the last line shoes the value of the delay variable.

It ay be possible that the vruntim are same for the first execution of the programs. This happens because the Scheduler variables are not updated. If it is the case, kindly run the program again to see the differences.

Same as above is valid for './test1.2'.

LOGICAL EXPLANATION:
The syscall accesses the current process's task struct(whose PID is passed) and there updates the vruntime by increasing the vruntime by the delay specified as a parameter. Currently delay sent is 200ms.

Inside the kernel in sched.h file, the sched_entity struct that contains the details about the process such as the vruntime, execution time changes are made. A new variaible 'delay' is declared of type u64 i.e. unsigned long in the struct that specifies by how much the vruntime of the process must be delayed. Like all other variables, this delay is initialised in the fair.c to 0 file and in core.c of the Completely Fair Scheduler fo the linux, the vruntime is updated by adding the delay. After this the process is added to the RB tree by the scheduler and sent to the processor for processing when its turn comes.

All scheduler's variables are initialised in the fair.c to 0 before they are actually used and re-valued by the scheduler as we do in core.c file.

vruntime is changed so that as per the CFS, it is placed in the right of the RB tree and hence its selection for execution is delayed and not really its execution. This happens because everytime a process is given the processor, its real runtime obviously increases now depending on the nice values which determines the weighing factor of the real runtime adjusted for calculating vruntime.

Inside the syscall, 2 special structs are used: pid adn task_struct

pid struct is used to get store the process with the given PID using the find_get_pid function. This process' reference is now used to refer to scheduler variables in the syscall by getting the task_struct(structure that stores the process' information about the scheduler variables) using the pid_task(pid_struct,PIDTYPE_PID) method.

All these things above change the scheduler parameters for the process. 

Also the difference between the test1 and test1.2 is that test1.2 and test2.2 have a nice value of 19 and then do the above things only.

The effect of changing, although in some 1/10 th of a second is that this usually takes more time to execute as its priority is lowered to get picked by the processor. This is done by increasing the multiplication factor while calculating the vruntime.


Note that the effect of changes in real time is not always as expected as we it might be true that the processor state while executing even the different parts of a computation intensive program may be different and hence less concrete results.

Even the vruntime is not updated directly by the amount we increase because of 2 reasons:
    vruntime is not just processed by the processor as it is. The scheduler does some calculations on it.
    Secondly, the delay added by us may cause vruntime to be so large that there may not be sufficient processes in the RB tree that can run before actually the delay of the vruntime is actually reflected. 