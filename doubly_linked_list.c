#include <stdio.h>
#include <stdlib.h>

#define EMPTY_LIST -1

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

enum VerboseType {
    On,
    Off
};

enum PrintType {
    Normal,
    Reverse
};

struct Node *create_node(int data, struct Node *pNext, struct Node *pPrev) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL)
        return NULL;

    node->data = data;
    node->next = NULL;
    node->prev = NULL;

    if (pNext != NULL) node->next = pNext;

    if (pPrev != NULL) node->prev = pPrev;

    return node;
}

struct Node *get_first_node(struct Node *pNode) {
    struct Node* current = pNode;

    if (current->prev != NULL) {
        current = get_first_node(current->prev);
    }

    return current;
}

struct Node *get_last_node(struct Node *pNode) {
    struct Node* current = pNode;
    if (current->next != NULL) {
        current = get_last_node(current->next);
    }

    return current;
}

int count_nodes(struct Node *pNode) {
    int counter = 0;
    struct Node *node = get_first_node(pNode);
    while(node != NULL) {
        counter++;
        node = node->next;
    }

    return counter;
}

struct Node *get_position_node(struct Node *pNode, int position) {
    int nodes = count_nodes(pNode);
    if (nodes == 0) return NULL;

    struct Node *temp_node = get_first_node(pNode);
    if (position > nodes) {
        temp_node = get_last_node(pNode);    
        if (temp_node == NULL) {
            return NULL;
        }

        return temp_node;
    }
    

    int counter = 0;
    while (counter < position) {
        if (temp_node->next != NULL) {
            temp_node = temp_node->next;
        }
        counter++;
    }

    return temp_node;
}

void normal_printing(struct Node *pNode, enum VerboseType verbose) {
    while(pNode != NULL) {
        if (verbose == On) {
            printf("Node Addrs: %p\n Node data: %d\n Node prev: %p\n Node next: %p\n", pNode, pNode->data, pNode->prev, pNode->next);
            printf("\n");
        } else {
            if (pNode->next != NULL) {
                printf("%d <-> ", pNode->data);
            } else {
                printf("%d\n", pNode->data);
            }
        }
        pNode = pNode->next;
    }
}

void reverse_printing(struct Node *pNode, enum VerboseType verbose) {
    while(pNode != NULL) {
        if (verbose == On) {
            printf("Node Addrs: %p\n Node data: %d\n Node prev: %p\n Node next: %p\n", pNode, pNode->data, pNode->prev, pNode->next);
            printf("\n");
        } else {
            if (pNode->prev != NULL) {
                printf("%d <-> ", pNode->data);
            } else {
                printf("%d\n", pNode->data);
            }
        }
        pNode = pNode->prev;
    }
}

void print_nodes(struct Node* pNode, enum VerboseType verbose, enum PrintType printType) {
    struct Node *current = get_first_node(pNode);
    switch(printType) {
        case Normal:
            normal_printing(current, verbose);
            break;
        case Reverse:
            reverse_printing(current, verbose);
            break;    
        default:
            normal_printing(current, verbose);
    }
}

void print_nodes_reverse(struct Node* pNode, enum VerboseType verbose) {
    struct Node *current = get_last_node(pNode);
    while(current != NULL) {
        if (verbose == On) {
            printf("Node Addrs: %p\n Node data: %d\n Node prev: %p\n Node next: %p\n", current, current->data, current->prev, current->next);
            printf("\n");
        } else {
            if (current->prev != NULL) {
                printf("%d <-> ", current->data);
            } else {
                printf("%d\n", current->data);
            }
        }
        current = current->prev;
    }
}

void print_node(struct Node* pNode, enum VerboseType verbose) {
    if (pNode == NULL) {
        printf("Can't print null node.");
        return;
    }

    if (verbose == On) {
        printf("Node Addrs: %p | Data: %d | Previous: %p | Next: %p\n", pNode, pNode->data, pNode->prev, pNode->next);
    } else {
        printf("%d\n", pNode->data);
    }
}

struct Node *in_begin(struct Node *pNode, int data) {
    struct Node *first_node = get_first_node(pNode);
    if (first_node == NULL) return NULL;
    
    struct Node *node = create_node(data, first_node, NULL);
    first_node->prev = node;

    return node;
}

struct Node *in_last(struct Node *pNode, int data) {
    struct Node *last_node = get_last_node(pNode);
    struct Node *first_node = get_first_node(pNode);
    
    if (first_node == NULL) return NULL;
    if (last_node == NULL) return NULL;

    struct Node *node = create_node(data, NULL, last_node);
    last_node->next = node;

    return first_node;
}

struct Node *in_position(struct Node *pNode, int data, int position) {

    struct Node *temp_node = get_first_node(pNode);
    if (temp_node == NULL) {
        struct Node *new_node = create_node(data, NULL, NULL);
        return new_node;
    }

    struct Node *head = get_first_node(pNode);
    if (head == NULL) {
        struct Node *new_node = create_node(data, NULL, NULL);
        return new_node;
    }

    int nodes = count_nodes(pNode);
    if (nodes <= 0) {
        return NULL;
    }

    if (position <= 0) {
        struct Node *node = create_node(data, temp_node, NULL);
        temp_node->prev = node;

        return node;
    }

    if (position > nodes) {
        temp_node = get_last_node(pNode);
        struct Node *node = create_node(data, NULL, temp_node);
        temp_node->next = node;

        return head;
    }

    struct Node *pos_node = get_position_node(pNode, position);
    if (pos_node == NULL) {
        return NULL;
    }

    struct Node *new_node = create_node(data, pos_node->next, pos_node);
    if (new_node == NULL) {
        return NULL;
    }

    pos_node->next = new_node;
    new_node->prev = pos_node;

    free(temp_node);
    temp_node = NULL;

    return head;
}

struct Node *del_begin(struct Node *pNode) {
    struct Node *first_node = get_first_node(pNode);
    if (first_node == NULL) return NULL;

    struct Node *next_node = first_node->next;
    if (next_node == NULL) {
        first_node->data = EMPTY_LIST;
        first_node->next = NULL;
        first_node->prev = NULL;

        return first_node;
    }

    first_node->next = NULL;
    first_node->prev = NULL;

    next_node->prev = NULL;

    free(first_node);
    first_node = NULL;
    
    return next_node;
}

struct Node *del_last(struct Node *pNode) {
    struct Node *last_node = get_last_node(pNode);
    if (last_node == NULL) return NULL;

    struct Node *head = get_first_node(pNode);
    if (head == NULL) return NULL;

    struct Node *prev_node = last_node->prev;
    if (prev_node == NULL) return NULL;

    last_node->next = NULL;
    last_node->prev = NULL;

    prev_node->next = NULL;

    free(last_node);
    last_node = NULL;

    return head;
}

struct Node *del_position(struct Node *pNode, int pos) {
    int nodes = count_nodes(pNode);
    
    struct Node *head = get_first_node(pNode);
    if (head == NULL) return NULL;

    if (pos <= 0) {
        head = del_begin(head);
        return head;
    }

    if (pos > nodes) {
        head = del_last(pNode);
        return head;
    }

    struct Node *pos_node = get_position_node(pNode, pos);
    if (pos_node == NULL) return NULL;

    struct Node *prev_node = pos_node->prev;
    struct Node *next_node = pos_node->next;

    pos_node->next = NULL;
    pos_node->prev = NULL;

    next_node->prev = prev_node;
    prev_node->next = next_node;

    free(pos_node);
    pos_node = NULL;

    return head;
}

int panic(char *message) {
    printf("%s\n", message);
    return -1;
}


int main(void) {
    
    struct Node *node = create_node(1, NULL, NULL);

    print_nodes(node, Off, Normal);

    void *temp_ptr;
    while(node) {
        temp_ptr = node;
        node = node->next;
        free(temp_ptr);
    }

    return 0;
}