CC=gcc
AR=ar
FLAGS= -Wall
OBJECTS_TRIE=trie.o

all: frequency

frequency: $(OBJECTS_TRIE) trie.a
	$(CC) $(FLAGS) -o trie $(OBJECTS_TRIE) trie.a

trie.a: $(OBJECTS_TRIE)
	$(AR) -rcs trie.a $(OBJECTS_TRIE)

trie.o: trie.c trie.h
	$(CC) $(FLAGS) -c trie.c

clean:
	rm -f *.o *.a frequency

.PHONY: clean all