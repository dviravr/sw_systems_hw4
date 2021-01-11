#include "trie.h"

#include <stdio.h>
#include <stdlib.h>

Node* newNode(char ch) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->letter = ch;
    node->count = 0;
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        node->children[i] = NULL;
    }
    return node;
}

Node* insertChar(Node* node, char ch) {
    if (node->children[ch - 'a'] == NULL) {
        node->children[ch - 'a'] = newNode(ch);
    } else {
        node->children[ch - 'a']->letter = ch;
    }
    return node->children[ch - 'a'];
}

int getWord() {
// int getWord(Node* node) {
    char ch;
    printf("enter loop\n");
    while (scanf("%c", &ch) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            // node = insertChar(node, ch);
            printf("%c\n", ch);
        } else if (ch >= 'A' && ch <= 'z') {
            // ch += 'a' - 'A';
            // node = insertChar(node, ch);
            printf("%c\n", ch);
        } else if (ch == ' ') {
            // node->count++;
            printf("%c\n", ch);
            // printf("exit loop\n");
            // return TRUE;
        }
    }
    return FALSE;
}

// void printTrie(Node *node) {
//     // Node* node = head;
//     while (node != NULL) {
//         printf("%c, %lu\n", node->letter, node->count);
//         for (size_t i = 0; i < NUM_LETTERS; i++)
//         {
//             printTrie(node->children[0]);
//         }
//     }
// }

int main() {
    // Node* head = newNode('\0');
    // while (getWord());
    getWord();
    // insertChar(head, 'g');
    // printf("%c\n", head->children['g' - 'a']->letter);
    return 0;
}
