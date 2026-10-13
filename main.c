#include <stdio.h>

typedef struct {
    int data;
    void *next;
} Node;

int main() {

    Node head = {0};
    Node n1 = {0};
    Node n2 = {0};

    head.data = 10;
    head.next = (Node *)&n1;

    n1.data = 20;
    n1.next = (Node *)&n2;

    n2.data = 30;
    n2.next = NULL;

    Node *n1_data = (Node *)head.next;
    Node *n2_data = (Node *)n1.next;

    Node *temp = &head;
    printf("%d\n", temp->data);
    while(temp->next != NULL) {
        temp = (Node *)temp->next;
        printf("%d\n", temp->data);
    }

    return 0;   
}