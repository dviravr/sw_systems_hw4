#include <stdio.h>
#include <stdlib.h>
#define NUM_LETTERS 26

typedef enum { FALSE = 0,
               TRUE = 1 } boolean;

typedef struct Node {
    char letter;
    unsigned int count;
    struct Node* children[NUM_LETTERS];
} Node;

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
        } else if (ch >= 'A' && ch <= 'Z') {
            ch += 'a' - 'A';
            node = insertChar(node, ch);
        } else if (ch == ' ' || ch == '\t' || ch == EOF) {
            node->count++;
            node = *head;
        }
    }
}

// returns TRUE if given node has any children
int haveChildren(Node* curr)
{
    for (int i = 0; i < NUM_LETTERS; i++)
        if (curr->children[i])
            return TRUE;
 
    return FALSE;
}
/*
void printTrie(Node** head, Node** curr){
    Node* curr = *curr;
    printf("%c", node->letter);
    if(node->count != 0){
        printf(" %d", node->count);
        node->count = 0;
        printTrie(head,head);
    }
    for(int i= 0; i<NUM_LETTERS; i++){
        if(node->count != 0)
        
        if(node->children[i] != NULL){
            printTrie()
        }
    }

void printTrie(Node** head){
        Node* curr = *head;
        while( !haveChildren(*head)){
            curr->
        }

}
*/

void printSubtree(Node* head) {
    Node* curr = head;
    while (head != NULL)
    {
        if(haveChildren(curr)){
             for (int i = 0; i < NUM_LETTERS; i++)
            {
                if (curr->count>0)
                {
                    printf( "%c %d\n ",curr->letter, curr->count);
                    curr-> count =0;
                    curr = head;
                    break;
                }
                else if (curr->children[i] != NULL)
                {
                    printf("%c", curr->letter);
                    curr= curr->children[i];
                    i=0;
                }
            }
        }
        else 
        {
            if (curr->count>0)
            {
                printf( "%c %d\n ",curr->letter, curr->count);
                curr-> count =0;
            }
            free(curr);
            curr=NULL;
            curr = head;
        }
    }
}   
/*
void printSubtree1(Node* head ,Node* curr, int index) {

    if (curr == NULL){
        return;
        }

    printf("%c", curr->letter);

    if (curr->count != 0) {     
        printf( " %d\n ", curr->count);
        curr = head;
        }

    for (int i = 0; i<26;i++) {    
        if (curr->children[i]!= NULL) {   
            printSubtree( head ,curr->children[i], index +1);
            curr->children[i]= NULL;
           // free(curr->children[i]);
        }           
    }

               
 }
*/
// }
    
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
    printf("checkkkkk");
    printSubtree( head);
    printf("aa: %u\n", head->children[0]->children[0]->count);
    printf("aaa: %u\n", head->children[0]->children[0]->children[0]->count);
    printf("aba: %u\n", head->children[0]->children[1]->children[0]->count);
    // insertChar(head, 'g');
    // printf("%c\n", head->children['g' - 'a']->letter);
    return 0;
}
