#include <stdio.h>
#include <stdlib.h>
#define NUM_LETTERS 26

typedef enum { FALSE = 0,
               TRUE = 1 } boolean;

/*
    this is a definition of a node.
    every node have letter, words counter, Node parent, and array of 26(num of letters) children.  */
typedef struct Node {
    char letter;
    unsigned int count;
    struct Node* parent;
    struct Node* children[NUM_LETTERS];
} Node;

/*  create new node with a given char and his parent. 
    return a pointer to the new node.  */
Node* newNode(char ch, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->letter = ch;
    node->count = 0;
    node->parent = parent;
    // set all children to null.
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        node->children[i] = NULL;
    }
    return node;
}

/*  insert new letter to the tree. return pointer to the next node.  */
Node* insertChar(Node* node, char ch) {
    int index = ch - 'a';
    // if the current child is null create a new node.
    if (node->children[index] == NULL) {
        node->children[index] = newNode(ch, node);
    } else {
        node->children[index]->letter = ch;
    }
    return node->children[index];
}

/*  get all the words from the user.  */
void getWords(Node** head) {
    Node* node = *head;
    char ch;
    while (!feof(stdin)) {
        // get letter by letter whlie there is an input.
        ch = fgetc(stdin);
        // insert the letter to the tree in lowercase.
        if (ch >= 'a' && ch <= 'z') {
            node = insertChar(node, ch);
        } else if (ch >= 'A' && ch <= 'Z') {
            ch += 'a' - 'A';
            node = insertChar(node, ch);
        } else if ((ch == ' ' || ch == '\t' || ch == '\n' || ch == EOF) && node != *head) {
            // if the word was ended count the word and return to the head of the tree to get more words.
            node->count++;
            node = *head;
        }
    }
}

/*  returns TRUE if given node has any children.  */
int haveChildren(Node* curr) {
    for (int i = 0; i < NUM_LETTERS; i++)
        if (curr->children[i] != NULL)
            return TRUE;
    return FALSE;
}

/*  free the node and all his parents that dont hava children.  */
void freeNodes(Node* node) {
    // save the parent of he node
    Node* parent = node->parent;
    int index;
    while (parent != NULL && !haveChildren(node)) {
        // save the index of the current node in his parent array of children.
        index = node->letter - 'a';
        free(node);
        // set the child to null after free him.
        parent->children[index] = NULL;
        // go up one level.
        node = parent;
        parent = parent->parent;
    }
}

void printSubtree(Node* head, int reverse) {
    Node* curr = head;
    int i;
    while (head != NULL) {
        if (curr->count > 0) {
            printf("%c %d\n", curr->letter, curr->count);
            curr->count = 0;
            if (!haveChildren(curr)) {
                freeNodes(curr);
            }
            curr = head;
        } else if (!haveChildren(curr)) {
            freeNodes(curr);
            curr = head;
        } else {
            for (i = 0; i < NUM_LETTERS; ++i) {
                int index = reverse ? NUM_LETTERS - 1 - i : i;
                if (curr->children[index] != NULL) {
                    if (curr != head) {
                        printf("%c", curr->letter);
                    }
                    curr = curr->children[index];
                    i = NUM_LETTERS;
                }
            }
        }
        if (!haveChildren(head)) {
            // finish print all the words
            break;
        }
    }
}

int main() {
    Node* head = newNode('\0', NULL);
    getWords(&head);
    printSubtree(head, TRUE);
    printSubtree(head, FALSE);
    free(head);
    head = NULL;
    return 0;
}
