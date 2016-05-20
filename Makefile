# Anne Chen
#

CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: 1dca_array 1dca_pointer

1dca_array: 1dca_array.o memcheck.o
	$(CC) 1dca_array.o memcheck.o -o 1dca_array
	
1dca_pointer: 1dca_pointer.o memcheck.o
	$(CC) 1dca_pointer.o memcheck.o -o 1dca_pointer

1dca_array.o: 1dca_array.c
	$(CC) $(CFLAGS) -c 1dca_array.c
	
1dca_pointer.o: 1dca_pointer.c
	$(CC) $(CFLAGS) -c 1dca_pointer.c
	
memcheck.o: memcheck.c 
	$(CC) $(CFLAGS) -c memcheck.c

check:
	c_style_check 1dca_array.c 1dca_pointer.c 

clean:
	rm -f 1dca_array 1dca_pointer *.o
