ALL:
	g++ -g -o ring_test main.c -lpthread -fpermissive
clean:
	rm -f ring_test
