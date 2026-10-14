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

int count_nodes(struct Node *head) {
    int nodes = 0;
    while(head != NULL) {
        nodes++;
        head = head->next;
    }

    return nodes;
}

struct Node *get_first_node(struct Node *head) {
    return head;
}

struct Node *get_position_node(struct Node *head, int position) {
    int counter = 0;
    struct Node *current = NULL;
    while(counter < position) { 
        head = head->next;
        counter++;
    }

    current = head;

    return current;
}

struct Node *get_last_node(struct Node *head) {
    struct Node *last = NULL;

    if (head->next == NULL) return head;

    while(head->next != NULL) {
        if (head->next == NULL) {
            last = head->next;
        }

        head = head->next;
    }

    if (last == NULL) return head;

    return last;
}

struct Node *insert_position(struct Node *head, int index, int data) {
    struct Node *node = create_node(data);
    int nodes = count_nodes(head);

    if (head == NULL) {
        return node;
    }

    if (index == 0) {
        node->next = head;
        if (head->next == NULL) {
            head->next = NULL;
        }

        return node;
    }

    if (head->next == NULL) {
        head->next = node;
        return head;
    }

    if (index >= nodes) {
        struct Node *last_inserted_node = get_last_node(head);

        last_inserted_node->next = node;
        node->next = NULL;

        return head;
    }

    struct Node *position_node = get_position_node(head, index - 1);

    node->next = position_node->next;
    position_node->next = node;

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
    n1->next = create_node(4);
    n1->next->next = create_node(5);

    n1 = insert_position(n1, 3, 6);

    print_list(n1);
}