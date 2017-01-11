##1. What is a circular queue

Queue is a common data structure, this structure ensures that the data is in accordance with the "first in first out" principle to operate, that is the first to go out of the elements is the first out of the element.Circular queue is a special queue structure , To ensure that the elements are FIFO, but the difference with the general queue is that they are circular, that is, queue head is the last element of the queue tail, usually a fixed number of elements to accommodate a closed loop.

##2. The advantages of circular queue

###2.1. Guaranteed elements are first-in, first-out

###2.2. Element space can be reused

###2.3. Provides an efficient mechanism for multithreaded data communication.

##3. Circumstantial queue of work scenes

(Linux system for PACKET_RX_RING and PACKET_TX_RING support in essence is a kernel to achieve a ring queue), such as the use of multi-threaded data transfer,

##4. Actual test results

In CentOS 5.5 (cpu per core frequency 1200MHz) on the device simply test a bit. The size of the ring queue is 10000, the size of the element data is 4 bytes, and the element that can be written and read per second is about 2.5 million, or 250 pps.
