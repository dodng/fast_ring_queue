ALL: ring_example notify_ring_example
ring_example:
	g++ -g -o ring_test main.c -lpthread -fpermissive
notify_ring_example:
	g++ -g -o notify_ring_test notify_main.c -lpthread -fpermissive
clean:
	rm -f ring_test notify_ring_test
