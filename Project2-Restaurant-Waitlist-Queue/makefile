CC = g++
CPPFLAGS = -Wall -g -std=c++11

project2:		group.o queue.o stack.o group.h queue.h stack.h 

project2.o:		group.h

group.o:		queue.h

queue.o:		stack.h

stack.o:

.PHONY:	clean
clean:			# clean the directory
			$(info -- cleaning the directory --)
			rm -f *.o
			rm -f project2
