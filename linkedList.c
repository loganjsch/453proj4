#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define the structure for the linked list itself
typedef struct LinkedList {
    Node* head;
} LinkedList;

// Function to create a new node with given data
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error allocating memory for new node\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to add a node to the end of the linked list
void appendNode(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to print all the elements in the linked list
void printList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// Function to initialize a new linked list
LinkedList* createLinkedList() {
    LinkedList* newList = (LinkedList*)malloc(sizeof(LinkedList));
    if (newList == NULL) {
        fprintf(stderr, "Error allocating memory for new linked list\n");
        exit(EXIT_FAILURE);
    }
    newList->head = NULL;
    return newList;
}

// Function to free all nodes in the linked list
void freeLinkedList(LinkedList* list) {
    Node* temp = list->head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    free(list);
}

int main() {
    LinkedList* myList = createLinkedList();
    appendNode(myList, 1);
    appendNode(myList, 2);
    appendNode(myList, 3);

    printList(myList);

    freeLinkedList(myList);
    printList(myList); // This should print "NULL" (segfault if it doesn't
    return 0;
}