#include <stdio.h>
#include <stdlib.h>

/*
TypeTag enum containing the following operations:
ADD: Addition
MUL: Multiplication
SUB: Subtraction
DIV: Division
FIB: Fibonacci

An extra type NUM is also added for Integer Nodes that contain
numbers and not a specific function
*/
typedef enum TypeTag { ADD, MUL, SUB, DIV, FIB, NUM } TypeTag;

/*
The Node struct consists of:
- type: The type of this node operation
- val: The value of this node in case of a NUM type tag
- left: A node representing the left argument of the operation
- right: A node representing the right argument of the operation
*/
typedef struct Node {
  TypeTag type;
  int val;
  struct Node *left;
  struct Node *right;
} Node;

/*
Defining the structure of the makeFunc function
*/
typedef Node *(*FuncPtr)(void *, void *);

/*
Fibonacci series implemented using the popular (DP) bottom-up approach:
- We first create our fib array which will store the fibonacci values
at each index. Its size will be depending on the input.
- Define fib[0] and fib[1] as 0 & 1 respectively
- Loop from 2 to n & assign the current fib value as the sum of the previous
two (The main idea of the fibonacci series)
- Return the result and deallocate the fib array from memory
*/
int fibonacci(int n) {
  int *fib = (int *)malloc((n + 1) * sizeof(int));

  fib[0] = 0;
  fib[1] = 1;
  for (int i = 2; i <= n; i++) {
    fib[i] = fib[i - 1] + fib[i - 2];
  }

  int result = fib[n];
  free(fib);

  return result;
}

/*
This function creates a new node based on the type tag given
and the value in case we want to create an integer node
*/
Node *createNode(TypeTag tag, int value) {
  Node *node = (Node *)malloc(sizeof(Node));

  node->type = tag;
  node->val = value;
  node->left = NULL;
  node->right = NULL;

  return node;
}

/*
Our generic function used for each operation: We first create a node
using the above createNode function & then set the left and right nodes
to the incoming arguments a & b.
*/
Node *solve(void *a, void *b, TypeTag type) {
  Node *node = createNode(type, 0);

  node->left = a;
  node->right = b;

  return node;
}

/*
Specific operation functions which just calls the solve function
given the type tag of this operation. The purpose of these function is to just
be returned by makeFunc as functions depending on the type
*/
Node *Add(void *a, void *b) { return solve(a, b, ADD); }
Node *Mul(void *a, void *b) { return solve(a, b, MUL); }
Node *Div(void *a, void *b) { return solve(a, b, DIV); }
Node *Sub(void *a, void *b) { return solve(a, b, SUB); }
Node *Fib(void *a, void *b) { return solve(a, b, FIB); }

/*
This function returns one of the above functions as pointers according to the
type
*/
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

/*
The calc function is implemented recursively to traverse over each node branch
left & right until it reaches an integer node where the type is NUM, then this
value is returned to be used in one of the operations we have defined.
*/
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

  // Delete function nodes in the correct order
  free(add);
  free(mul);
  free(div);
  free(sub);
  free(fib);
}