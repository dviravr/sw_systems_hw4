CC=gcc
AR=ar
FLAGS= -Wall
OBJECTS_TRIE=trie.o

all: frequency

frequency: $(OBJECTS_TRIE)
	$(CC) $(FLAGS) -o frequency $(OBJECTS_TRIE)

trie.o: trie.c
	$(CC) $(FLAGS) -c trie.c

clean:
	rm -f *.o *.a frequency

.PHONY: clean all