image.out :	image.o driver.o stack.o queue.o
	g++ -o image.out image.o driver.o stack.o queue.o

image.o :	image.cpp image.h
	g++ -c image.cpp

driver.o :	driver.cpp image.cpp image.h
	g++ -c driver.cpp
	
stack.o :	stack.cpp stack.h
	g++ -c stack.cpp
	
queue.o :	queue.cpp queue.h
	g++ -c queue.cpp



clean :
	rm *.o 
