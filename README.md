##1. What is a ring queue

Queue is a common data structure, this structure ensures that the data is "first in first out". Ring queue is a special queue structure , To ensure the data are FIFO, but the difference with queue is that they are ring, that is, the prev data of queue head is the queue tail,the data of ring can reuse.


##2. The advantages of ring queue

###2.1. Guaranteed elements are first-in, first-out

###2.2. Element space can be reused

###2.3. Provides an efficient mechanism for multithread data transfer.


##3. Ring queue of work scenes

(Linux system for PACKET_RX_RING and PACKET_TX_RING support in essence is a kernel to achieve a ring queue), such as the use of multi-threaded data transfer data.


##4. Actual test results

In CentOS 5.5 (cpu per core frequency 1200MHz) on the device simply test a bit. The size of the ring queue is 10000, the size of the element data is 4 bytes, and the element that can be written and read per second is about 2.5 million, or 250 pps.
