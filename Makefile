SRC = $(wildcard *.c)
OBJ = $($(SRC):.c=.o)
HDRS = $(wildcard *.h)


main:$(SRC) $(HDRS)
	$(CC) -o $@ $^