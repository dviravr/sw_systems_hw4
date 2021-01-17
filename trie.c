#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LETTERS 26

typedef enum { FALSE = 0,
               TRUE = 1 } boolean;

/*
    this is a definition of a node.
    every node have letter, words counter, Node parent, and array of 26(num of letters) children.  */
typedef struct Node {
    char letter;
    unsigned int count; // if this letter is the end of the word so node->count++
    struct Node* parent;
    struct Node* children[NUM_LETTERS];
} Node;

/*  create new node with a given char and his parent. 
    return a pointer to the new node.  */
Node* newNode(Node* head , char ch, Node* parent) {
    Node* node;
    if(ch!='a'){
        node = (Node*)malloc(sizeof(Node));
    }else{
    //if (node == NULL){
        free_all_and_exit(head);
    }
    node->letter = ch;
    node->count = 0;
    node->parent = parent;
    // set all children to null.
    for (size_t i = 0; i < NUM_LETTERS; i++) {
        node->children[i] = NULL;
    }
    return node;
}

void free_all_and_exit(Node* head){
    Node* curr = head;
    while (!haveChildren(head)){    
        for (size_t i = 0; i < NUM_LETTERS; i++) {
            if (haveChildren(curr->children[i])) {
                curr = curr->children[i];
                i=NUM_LETTERS;
            } else {
                free(curr->children[i]);
                curr->children[i]=NULL;
            } 
        }
        curr= head;
    }
    free(head);
    head=NULL;
    exit(0);
    
}

/*  insert new letter to the tree. return pointer to the next node.  */
Node* insertChar(Node* head, Node* node, char ch) {
    int index = ch - 'a';
    // if the current child is null create a new node.
    if (node->children[index] == NULL) {
        node->children[index] = newNode(head, ch, node);
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
            node = insertChar(*head, node, ch);
        } else if (ch >= 'A' && ch <= 'Z') {
            ch += 'a' - 'A';
            node = insertChar(*head, node, ch);
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
    while (parent != NULL && node->count == 0 && !haveChildren(node)) {
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
/*  the method print all the word in the trie ascending or descending lexicographic order depends on the user's calling.
    The way to do this is as follows:
    If order goes up then look every time when a word ends and on the way print letter after letter until you reach the end of the word mark.
    If order goes down then first scan from the end until there are no more "children" to the tree and then print out the word we have created.
*/
void printSubtree(Node* head, int reverse) {
    Node* curr = head;
    int i;
    while (1) {
        // if it up order we look for the end of word 
        // if it down order we want to start with the loop and print the end of word only if the current node doesnt have child.
        // after each run of the while loop we do " curr = head" to start the algorithem again.
        if (curr->count > 0 && (!reverse || (reverse && !haveChildren(curr)))) {
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
                    /*  if it up order the index go from 0 to 26
                        if it down order the index go from 26 to 0*/
                int index = reverse ? NUM_LETTERS - 1 - i : i;
                if (curr->children[index] != NULL) {
                    //if (curr != head) {
                    printf("%c", curr->letter);
                    //}
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

int main(int argc, char* argv[]) {
    Node* head;
    head = newNode(head, '\0', NULL);
    if (argc == 1) {
        getWords(&head);
        printSubtree(head, FALSE);
    } else if ((argc == 2) && (!strcmp(argv[1], "r"))) {
        getWords(&head);
        printSubtree(head, TRUE);
    }
    free(head);
    head = NULL;
    return 0;
}
