EECS 3221 CPU Scheduler 
Made by Nikhil Sabharwal 216240707

This project implements CPU scheduling algorithms such as: FCFS, SJF, RR, Priority and priority.

This projects consists of 17 files:
book.txt
CPU.c
cpu.h
driver.c
list.c
list.h
Makefile
pri-schedule.txt
README.txt
rr-schedule.txt
schedule_fcfs.c
schedule_prirority.c
schedule_rr.c
schedule_sjf.c
schedule.txt
schedulers.h
task.h

Implementation:

the Driver.c file will read in the task from the selected text file for testing. from here the driver passes the newly created linked list to the algorithm of choice.

to compile the selected algorithm first enter:
make algorithm_name_here.c
for example we will compile sjf below:
make sjf

then the user must execute the compiled object file with a tester file in the format below:
./algorithm_name_here tester_file_name_here.txt
all test files are in the format of .txt 
for example using schedule.txt and sjf
./sjf schedule.txt

all the alogrithm's have 3 calculations that are documented in the end Turn Around time, Response time, and Wait time. These calculations assume that all tasks arrive at time = 0;
