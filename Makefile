C_SRC=$(wildcard *.c)
O_SRC=$(patsubst %.c,%.o,$(C_SRC))
CC=gcc

all: clean pathTest

pathTest:
	$(CC) -o $@ $(C_SRC)

%.o:%.c
	$(CC) -c $<

.PHONY: all

clean:
	rm -rf *.o pathTest