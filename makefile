image.out :	image.o driver.o stack.o queue.o nodetype.o sorted.o unsorted.o 
	g++ -o image.out image.o driver.o stack.o queue.o nodetype.o sorted.o unsorted.o

image.o :	image.cpp image.h
	g++ -c image.cpp

driver.o :	driver.cpp image.cpp image.h
	g++ -c driver.cpp
	
stack.o :	stack.cpp stack.h
	g++ -c stack.cpp
	
queue.o :	queue.cpp queue.h
	g++ -c queue.cpp

nodetype.o :	nodetype.cpp nodetype.h
	g++ -c nodetype.cpp

unsorted.o :	unsorted.cpp unsorted.h
	g++ -c unsorted.cpp
	
sorted.o :	sorted.cpp sorted.h
	g++ -c sorted.cpp

clean :
	rm *.o 
