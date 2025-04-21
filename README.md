[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/T-oguugN)
# Master-Worker

In this project, you will implement a simple master and worker thread pool, a pattern that occurs
in many real life applications. The master threads produce numbers continuously and place them in
a buffer, and worker threads will consume them, i.e., print these numbers to the screen. This simple
program is an example of a master-worker thread pool pattern that is commonly found in several reallife
application servers. For example, in the commonly used multi-threaded architecture for web servers,
the server has one or more master threads and a pool of worker threads. When a new connection arrives
from a web client, the master accepts the request and hands it over to one of the workers. The worker
then reads the web request from the network socket and writes a response back to the client. Your simple
master-worker program is similar in structure to such applications, albeit with much simpler request
processing logic at the application layer.

You are given a skeleton program master-worker-skeleton.c. This program takes 4 command
line arguments: how many numbers to “produce” (M), the maximum size of the buffer in which
the produced numbers should be stored (N), the number of worker threads to consume these numbers
(C), and the number of master threads to produce numbers (P). The skeleton code spawns P master
threads, that produce the specified number of integers from 0 to M − 1 into a shared buffer array. The
main program waits for these threads to join, and then terminates. The skeleton code given to you does
not have any logic for synchronization.

You must write your solution in the file master-worker.c. You must modify this skeleton code
in the following ways. You must add code to spawn the required number of worker threads, and write the
function to be run by these threads. This function will remove/consume items from the shared buffer and
print them to screen. Further, you must add logic to correctly synchronize the producer and consumer
threads in such a way that every number is produced and consumed exactly once. Further, producers
must not try to produce when the buffer is full, and consumers should not consume from an empty
buffer. While you need to ensure that all C workers are involved in consuming the integers, it is not
necessary to ensure perfect load balancing between the workers. Once allM integers (from 0 toM −1)
have been produced and consumed, all threads must exit. The main thread must call pthread join
on the master and worker threads, and terminate itself once all threads have joined. Your solution must
only use pthreads condition variables for waiting and signaling: busy waiting is not allowed.
Your code can be compiled as shown below: <br>
`gcc master-worker.c -lpthread` <br>
To run your code: <br>
`./master-worker #total_items #max_buf_size #num_workers #masters` <br>
Example: <br>
`./master-worker 100 10 4 3`

If your code is written correctly, every integer from 0 to M −1 will be produced exactly once by the
master producer thread, and consumed exactly once by the worker consumer threads. And all master threads and worker threads should join as below <br>
<img width="223" alt="image" src="https://github.com/user-attachments/assets/55f7c557-1f8f-4c4a-b76e-938c00c67324" />

We have provided you with a simple testing script (test-master-worker.sh which invokes the script check.awk)
that checks this above invariant on the output produced by your program. The script relies on the two
print functions that must be invoked by the producer and consumer threads: the master thread must call
the function print produced when it produces an integer into the buffer, and the worker threads
must call the function print consumed when it removes an integer from the buffer to consume. You
must invoke these functions suitably in your solution. Please do not modify these print functions, as their
output will be parsed by the testing script. <br>
To run test script: <br>
`./test-master-worker.sh 100 10 4 3`

Please ensure that you test your case carefully, as tricky race conditions can pop up unexpectedly.
You must test with up to a few million items produced, and with a few hundreds of master/worker threads.
Test for various corner cases like a single master or a single worker thread or for a very small buffer size
as well. Also test for cases when the number of items produced is not a multiple of the buffer size or the
number of master/worker threads, as such cases can uncover some tricky bugs. Increasing the number
of threads to large values beyond a few hundred will cause your system to slow down considerably, so
exercise caution. 

If you pass all tess cases, the output should look like below <br>
<img width="486" alt="image" src="https://github.com/user-attachments/assets/30470731-9e78-424c-927e-6346eaa7d2eb" /> <br>
Test case with 1 and 3 million items produced <br>
<img width="478" alt="image" src="https://github.com/user-attachments/assets/97036f97-4f6a-4c23-ab1d-55142d7a02c5" />

Source https://www.cse.iitb.ac.in/~mythili/os/






