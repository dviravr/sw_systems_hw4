#include <stdio.h>
#include <stdlib.h>
#define NUM_LETTERS 26

typedef enum { FALSE = 0,
               TRUE = 1 } boolean;

typedef struct Node {
    char letter;
    unsigned int count;
    struct Node* father;
    struct Node* children[NUM_LETTERS];
} Node;

Node* newNode(char ch, Node* father) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->letter = ch;
    node->count = 0;
    node->father = father;
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        node->children[i] = NULL;
    }
    return node;
}

Node* insertChar(Node* node, char ch) {
    if (node->children[ch - 'a'] == NULL) {
        node->children[ch - 'a'] = newNode(ch, node);
    } else {
        node->children[ch - 'a']->letter = ch;
    }
    return node->children[ch - 'a'];
}

void getWords(Node** head) {
    Node* node = *head;
    char ch;
    while (!feof(stdin)) {
        ch = fgetc(stdin);
        if (ch >= 'a' && ch <= 'z') {
            node = insertChar(node, ch);
        } else if (ch >= 'A' && ch <= 'Z') {
            ch += 'a' - 'A';
            node = insertChar(node, ch);
        } else if ((ch == ' ' || ch == '\t' || ch == '\n' || ch == EOF) && node != *head) {
            node->count++;
            node = *head;
        }
    }
}

// returns TRUE if given node has any children
int haveChildren(Node* curr) {
    for (int i = 0; i < NUM_LETTERS; i++)
        if (curr->children[i] != NULL)
            return TRUE;
    return FALSE;
}

// free the node and all his fathers that dont hava children
void freeNodes(Node* node) {
    Node* father = node->father;
    int index = -1;
    while (father != NULL && !haveChildren(node)) {
        index = node->letter - 'a';
        free(node);
        father->children[index] = NULL;
        node = father;
        father = father->father;
    }
}

void printSubtree(Node* head) {
    Node* curr = head;
    int i;
    while (head != NULL) {
        if (curr->count > 0) {
            if (curr == head) 
                puts("shouldn't be here");
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
            for (i = 0; i < NUM_LETTERS; i++) {
                if (curr->children[i] != NULL) {
                    if (curr != head) {
                        printf("%c", curr->letter);
                    }
                    curr = curr->children[i];
                    i = NUM_LETTERS;
                }
            }
        }
        if (!haveChildren(head)) {
            break;
        }
    }
}

int main() {
    Node* head = newNode('\0', NULL);
    getWords(&head);
    printSubtree(head);
    free(head);
    head = NULL;
    return 0;
}
