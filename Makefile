
## Compilation flags
##comment out one or the other 
##debugging 
#CFLAGS = -g 

##release
CFLAGS = -O3 -DNDEBUG

CFLAGS+= -Wall



CC = g++ $(CFLAGS)


PROGS = viewshed

default: $(PROGS)

viewshed: main_viewshed.cpp
	$(CC) main_viewshed.cpp -o viewshed

clean::	
	rm *.o
	rm viewshed