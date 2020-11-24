Jacob Pledger
001136676

I decided to use a vector for the processes, 
since it would be resizable to however many 
processes were required and the array index 
could serve as the process ID.

I did the same for the wait queues, allowing 
for a variable number of events.
 
As would make sense, I used the preexisting 
queue class in C++ to represent the queues.

I created a class for processes, which contain
all the necessary information for managing the
process, such as PID, state, which event the 
process is waiting for, etc.

All the processes are indexed by the processlist,
which gives each process their PID. When running,
all processes are put into the ready queue, and 
then "run". The process at the front of the ready 
queue is the running process. When blocked, the
process is either moved to the back of the queue
if it's not waiting for an event (event0) and was 
just taking too long, or is sent to the 
appropriate wait queue. When the corresponding
event occurs, the process is popped out of the wait
queue and pushed into the end of the ready queue.

When a process completes, it is simply popped off
the ready queue.

The vector of events is the list of events in the
order they occur. It is read in from a file that 
should just be a list of numbers. For example:
1 4 6 3 9 5 0 12 36 ...etc.
The index of each event it the time it occurs, or
rather, the loop iteration where it occurs. 0 means
no event. 

This is the same for whenEvents and whosEvents.
whenEvents is the vector for when a process requests
its event. whenEvents[pid] = time to request my event
whosEvents is the vector for which process is associated
with which event. whosEvents[pid] = event #

After the process requests its event, it continues to
run until it completes, or is blocked. 

The loop continues until all processes have completed.