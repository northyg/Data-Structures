CC = g++
CPPFLAGS = -Wall -g -std=c++11

proj1:		artist.o recordlabel.o artist.h recordlabel.h song.h

proj1.o:			artist.h

artist.o:		recordlabel.h

recordlabel.o:		song.h

song.o:

.PHONY:	clean
clean:			# clean the directory
			$(info -- cleaning the directory --)
			rm -f *.o
			rm -f proj1
