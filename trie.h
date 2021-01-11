#ifndef _TRIE_H_
#define _TRIE_H_
#define NUM_LETTERS 26

typedef enum { FALSE = 0,
               TRUE = 1 } boolean;

typedef struct Node {
    char letter;
    long unsigned int count;
    struct Node* children[NUM_LETTERS];
} Node;

Node* newNode(char ch);

// insertChar(Node** node, char ch);

#endif


