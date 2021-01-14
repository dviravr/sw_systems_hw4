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
        } else if (ch == ' ' || ch == '\t' || ch == EOF) {
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

void freeNodes(Node** node) {
    Node** temp = node;
    Node* father = (*node)->father;
    while (father != NULL) {
        // printf("temp: %c %d\n", *(temp)->letter, *(temp)->count);
        printf("father: %c %d\n", father->letter, father->count);
        free(*temp);
        *temp = NULL;
        if (haveChildren(father)) {
            puts("TRUE");
        } else {
            puts("FALSE");
        }
        temp = &father;
        // temp = father;
        father = father->father;
    }
}

void printSubtree(Node* head) {
    Node* curr = head;
    int i;
    while (head != NULL) {
        if (curr->count > 0) {
            printf("%c %d\n", curr->letter, curr->count);
            curr->count = 0;
            if (!haveChildren(curr)) {
                freeNodes(&curr);
            }
            curr = head;
        } else if (!haveChildren(curr)) {
            freeNodes(&curr);
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
        /*
            for (i = 0; i < NUM_LETTERS; i++)
            {
                if (curr->count>0)
                {
                    printf( "%c %d\n ",curr->letter, curr->count);
                    curr-> count =0;
                    curr = head;
                    i=NUM_LETTERS;
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
        }*/
    }
}
/*
void printSubtree1(Node* head ,Node* curr, int index) {

    if (curr == NULL){
        return;
        }

    if (curr->count != 0) {     
        printf( "%c %d\n", curr->letter ,curr->count);
        curr-> count =0;
        printSubtree1(head,head,0);
    }
     
    if(!haveChildren(curr))
    {
        curr 
    }

    printf("%c", curr->letter);

    if (curr -> count != 0) {     
        printf(" %d\n", curr->count);
        curr = head;
        }

    for (int i = 0; i<26;i++) {    
        if (curr->children[i]!= NULL) {   
            printSubtree1( head , curr->children[i], index +1);
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
    Node* head = newNode('\0', NULL);

    getWords(&head);
    head->children[0]->count = 1;
    head->children[0]->children[1]->children[2]->count = 0;
    Node** n = &(head->children[0]->children[1]->children[2]);
    freeNodes(n);
    if (head->children[0] != NULL) {
        puts("shouldn't be null");
    }
    // // head->children[0]->children[1]->children[2] = NULL;
    // *n = NULL;
    if (head->children[0]->children[1] == NULL) {
        puts("should be null 1");
    }

    if (head->children[0]->children[1]->children[2] == NULL) {
        puts("should be null 2");
    }

    // putc(n->letter, stdout);
    // while (n != NULL) {
    //     putc(n->letter, stdout);
    //     n = n->father;
    // }

    // printSubtree(head);
    // printf("aa: %u\n", head->children[0]->children[0]->count);
    // printf("aaa: %u\n", head->children[0]->children[0]->children[0]->count);
    // printf("aba: %u\n", head->children[0]->children[1]->children[0]->count);
    // insertChar(head, 'g');
    // printf("%c\n", head->children['g' - 'a']->letter);
    return 0;
}
