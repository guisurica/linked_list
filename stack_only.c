#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data;
    void *next;
} Node;

Node insert_start(int data, Node node) {
    Node new = {0};
    new.data = data;
    new.next = &node;
    return new;
}

Node insert_last(int data) {
    Node new = {0};
    new.data = data;
    new.next = NULL;

    return new;
}

Node insert_position(int data, Node *pNode) {
    Node new = {0};
    new.data = data;
    new.next = pNode;

    return new;
}

int main() {

    Node head = {0};
    Node n1 = {0};
    Node n2 = {0};

    head.data = 1;
    head.next = (Node *)&n1;

    n1.data = 2;
    n1.next = (Node *)&n2;

    n2.data = 3;
    n2.next = NULL;

    Node first = insert_start(0, head);
    Node last = insert_last(5);

    n2.next = (Node *)&last;

    Node position = insert_position(4, &last);

    n2.next = (Node *)&position;

    Node last2 = insert_last(7);

    last.next = (Node *)&last2;

    Node position2 = insert_position(6, &last2);

    last.next = (Node *)&position2;

    Node *temp = &first;
    printf("%d\n", temp->data);
    while(temp->next != NULL) {
        temp = (Node *)temp->next;
        printf("%d\n", temp->data);
    }

    return 0;   
}