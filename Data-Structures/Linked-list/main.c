#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  int size_of_list;
  struct node *next;
};

struct node *init_head(int value) {
  struct node *Head = malloc(sizeof(*Head));

  Head->value = value;
  Head->size_of_list = 1;
  Head->next = NULL;

  return Head;
}

void push_front(struct node **head, int value) {
  struct node *newHead = malloc(sizeof *newHead);
  newHead->value = value;
  newHead->size_of_list = (*head)->size_of_list + 1;

  newHead->next = *head;
  *head = newHead;
}

void print_list(struct node *head) {
  struct node *last_node = head;
  for (int i = 0; i <= head->size_of_list - 1; i++) {
    printf("%d\n", last_node->value);
    last_node = last_node->next;
  }
}

void free_list(struct node *head) {
  struct node *last_node = head;
  struct node *next_node = head;
  for (int i = 0; i <= head->size_of_list - 1; i++) {
    next_node = last_node->next;

    free(last_node);

    last_node = next_node;
  }
}

int main(int argc, char *argv[]) {
  struct node *HEAD = init_head(0);

  push_front(&HEAD, 1);
  push_front(&HEAD, 2);
  push_front(&HEAD, 3);
  push_front(&HEAD, 4);

  print_list(HEAD);

  free_list(HEAD);

  return 0;
}
