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

void getWords(Node** head) {
    Node* node = *head;
    char ch;
    printf("enter loop\n");
    while (!feof(stdin)) {
        ch = fgetc(stdin);
        if (ch >= 'a' && ch <= 'z') {
            node = insertChar(node, ch);
        } else if (ch >= 'A' && ch <= 'z') {
            ch += 'a' - 'A';
            node = insertChar(node, ch);
        } else if (ch == ' ' || ch == EOF) {
            node->count++;
            node = *head;
        }
    }
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
    Node* head = newNode('\0');
    // while (getWord());
    getWords(&head);
    printf("aa: %lu\n", head->children[0]->children[0]->count);
    printf("aaa: %lu\n", head->children[0]->children[0]->children[0]->count);
    printf("aba: %lu\n", head->children[0]->children[1]->children[0]->count);
    // insertChar(head, 'g');
    // printf("%c\n", head->children['g' - 'a']->letter);
    return 0;
}
