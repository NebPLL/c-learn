#include <stdio.h>
#include <stdlib.h>

struct node {
  int value;
  struct node *next;
};

struct node *init_head(int value) {
  struct node *Head = malloc(sizeof(*Head));

  Head->value = value;
  Head->next = NULL;

  return Head;
}

void push_front(struct node **head, int value) {
  struct node *newHead = malloc(sizeof *newHead);
  newHead->value = value;
  newHead->next = *head;
  *head = newHead;
}

int sizeof_list(struct node *head) {
  int i = 1;
  for (struct node *current = head; current->next == NULL;
       current = current->next) {
    i++;
  }
  return i;
}

struct node *get_index(struct node *head, int index) {
  if (index < 0)
    return NULL;

  struct node *next_node = head;
  for (int i = 0; i < index && next_node != NULL; i++) {
    next_node = next_node->next;
  }

  return next_node;
}

void print_list(struct node *head) {
  struct node *last_node = head;
  for (int i = 0; i <= sizeof_list(head) - 1; i++) {
    printf("%d\n", last_node->value);
    last_node = last_node->next;
  }
}

void free_list(struct node *head) {
  struct node *last_node = head;
  struct node *next_node = head;
  for (int i = 0; i <= sizeof_list(head) - 1; i++) {
    next_node = last_node->next;

    free(last_node);

    last_node = next_node;
  }
}

int main(int argc, char *argv[]) {
  struct node *head = init_head(0);

  push_front(&head, 1);
  push_front(&head, 2);
  push_front(&head, 3);
  push_front(&head, 4);

  // printf("%i\n", sizeof_list(head));

  // print_list(head);
  printf("%d\n", get_index(head, 0)->value);

  free_list(head);

  return 0;
}
