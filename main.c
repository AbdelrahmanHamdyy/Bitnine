#include <stdio.h>
#include <stdlib.h>

typedef enum TypeTag { ADD, MUL, SUB, DIV, FIB, NUM } TypeTag;

typedef struct Node {
  TypeTag type;
  int val;
  struct Node *left;
  struct Node *right;
} Node;

typedef Node *(*FuncPtr)(void *, void *);

int fibonacci(int n) {
  int *fib = (int *)malloc((n + 1) * sizeof(int));

  fib[0] = 0;
  fib[1] = 1;
  for (int i = 2; i <= n; i++) {
    fib[i] = fib[i - 1] + fib[i - 2];
  }

  int result = fib[n - 1];
  free(fib);

  return result;
}

Node *createNode(TypeTag tag, int value) {
  Node *node = (Node *)malloc(sizeof(Node));

  node->type = tag;
  node->val = value;
  node->left = NULL;
  node->right = NULL;

  return node;
}

Node *solve(void *a, void *b, TypeTag type) {
  Node *node = createNode(type, 0);

  node->left = a;
  node->right = b;

  return node;
}

Node *Add(void *a, void *b) { return solve(a, b, ADD); }

Node *Mul(void *a, void *b) { return solve(a, b, MUL); }

Node *Div(void *a, void *b) { return solve(a, b, DIV); }

Node *Sub(void *a, void *b) { return solve(a, b, SUB); }

Node *Fib(void *a, void *b) { return solve(a, b, FIB); }

Node *(*makeFunc(TypeTag type))(void *, void *) {
  switch (type) {
  case ADD:
    return &Add;
    break;
  case SUB:
    return &Sub;
    break;
  case MUL:
    return &Mul;
    break;
  case DIV:
    return &Div;
    break;
  case FIB:
    return &Fib;
    break;
  default:
    printf("Unknown TypeTag\n");
  }
  return NULL;
}

int calc(Node *node) {
  int result;

  if (node->type == ADD) {
    result = calc(node->left) + calc(node->right);
  } else if (node->type == SUB) {
    result = calc(node->left) - calc(node->right);
  } else if (node->type == MUL) {
    result = calc(node->left) * calc(node->right);
  } else if (node->type == DIV) {
    result = calc(node->left) / calc(node->right);
  } else if (node->type == FIB) {
    int n = calc(node->left);
    result = fibonacci(abs(n));
  } else if (node->type == NUM) {
    result = node->val;
  } else {
    printf("Unknown node type %d\n", node->type);
  }

  return result;
}

int main() {
  // Create Integer Nodes
  Node *n1 = createNode(NUM, 10);
  Node *n2 = createNode(NUM, 6);
  Node *n3 = createNode(NUM, 5);
  Node *n4 = createNode(NUM, 4);
  Node *n5 = createNode(NUM, 99);
  Node *n6 = createNode(NUM, 11);

  // Create function nodes
  Node *add = (*makeFunc(ADD))(n1, n2);
  Node *mul = (*makeFunc(MUL))(n3, n4);
  Node *div = (*makeFunc(DIV))(n5, n6);
  Node *sub = (*makeFunc(SUB))(add, mul);
  Node *fib = (*makeFunc(FIB))(sub, NULL);

  // Compute the above operations and print them
  printf("%d\n", calc(add));
  printf("%d\n", calc(mul));
  printf("%d\n", calc(div));
  printf("%d\n", calc(sub));
  printf("%d\n", calc(fib));

  // Delete integer nodes
  free(n1);
  free(n2);
  free(n3);
  free(n4);
  free(n5);
  free(n6);

  // Delete function nodes
  free(add);
  free(mul);
  free(div);
  free(sub);
  free(fib);
}