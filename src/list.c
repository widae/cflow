#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    struct node* next;
    void* data;
} node;

typedef struct list {
    node* head;
    node* last;
    int size;
    int data_size;
} list;

void init_list(list* mylist, int data_size);
void push_back(list* mylist, void* data);
void* get_idx(list* mylist, int idx);
void clear_list(list* mylist, int data_size);
void free_node(node* current_node);

void init_list(list* mylist, int data_size) {
    mylist->head = (node*)malloc(sizeof(node));
    mylist->head->next = NULL;
    mylist->last = mylist->head;
    mylist->size = 0;
    mylist->data_size = data_size;
}

void push_back(list* mylist, void * data) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = malloc(mylist->data_size);
    memcpy(new_node->data, data, mylist->data_size);
    new_node->next = NULL;
    mylist->last->next = new_node;
    mylist->last = new_node;
    mylist->size++;
}

void* get_idx(list* mylist, int idx) {
    node* pre_node = mylist->head;
    while(idx--) {
        pre_node = pre_node->next;
    }
    return pre_node->next->data;
}

