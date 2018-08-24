##1. What is a ring queue
--------------

* the data is "first in first out".
* prev data of queue head is the queue tail.
* the data of ring can reuse.


##2. The advantages of ring queue
--------------

* Guaranteed elements are first-in, first-out

* Element space can be reused

* Provides an efficient mechanism for multithread data transfer.


##3. Ring queue of work example
--------------

* Linux between kernel and system to transfor network data( PACKET_RX_RING and PACKET_TX_RING )


##4. Actual test results
--------------

* In CentOS 5.5 (cpu per core frequency 1200MHz) . 
* ring queue length is 10000, one element data size is 4 bytes
* [ring_test] the element writted and then to read is about 25 million per second.
* [notify_ring_test] the element writted and then to read is about 20 million per second.
