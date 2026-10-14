#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *create_node(int data) {
    struct Node *node = malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

struct Node *insert_last(struct Node *head, int data) {
    struct Node* new_node = create_node(data);

    struct Node *last = head;
    while(last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;

    return head;
}

struct Node *insert_begin(struct Node *head, int data) {
    struct Node* new_node = create_node(data);
    new_node->next = head;
    return new_node;
}

struct Node *insert_position(struct Node *head, int index, int data) {
    struct Node* new_node = create_node(data);
    int need_link = 0;
    struct Node* temp_node = NULL;

    int counter = 0;
    struct Node* last = head;
    while(counter < index) {
        last = last->next;
        counter++;
    }

    if (last->next != NULL) {
        need_link = 1;
        temp_node = last;
    }

    last->next = new_node;

    if (need_link == 1) {
        new_node->next = temp_node;
    }

    return head;
}

void print_list(struct Node *head) {
    struct Node *current = head;
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
}


int main(void)  {
    struct Node *n1 = create_node(1);
    n1->next = create_node(2);
    n1->next->next = create_node(3);
    n1->next->next->next = create_node(4);

    n1 = insert_begin(n1, 0);
    insert_last(n1, 6);
    n1 = insert_position(n1, 5, 5);

    print_list(n1);
}