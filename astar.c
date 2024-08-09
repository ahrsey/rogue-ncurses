#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint8_t x;
  uint8_t y;
} Vector2;

typedef struct Node {
  void *next;
  Vector2 *data;
} Node;

typedef struct {
  Node *head;
} Stack;

Stack *stack__init(void);
void stack__push(Stack *s, Vector2 *v);
Vector2 *stack__pop(Stack *s);

bool vector2__eq(Vector2 *v1, Vector2 *v2);
uint8_t vector2__distance(Vector2 *v1, Vector2 *v2);

void astar(Vector2 v1, Vector2 v2);

// f(n) = g(n) + h(n)
// n: node
// g: cost from start node
// h: cost to finish node

//     A   B   C   D   E
//   +---+---+---+---+---+
// 1 |   |   |   |   |   |
//   +---+---+---+---+---+
// 2 |   |   |   |   |   |
//   +---+---+---+---+---+
// 3 |   |   |   |   |   |
//   +---+---+---+---+---+
// 4 |   |   |   |   |   |
//   +---+---+---+---+---+
// 5 |   |   |   |   |   |
//   +---+---+---+---+---+

// A1 -> E1
int main(void) {
  Vector2 v1 = {1, 1};
  Vector2 v2 = {1, 2};

  // printf("%d", vector2__eq(&v1, &v2));
  astar(v1, v2);

  return 0;
}

// Instead of using stack I can use an array with lenght of distance
// V{1,1}, V{1,2}, V{1,3}, V{1,4}, V{1,5}
void astar(Vector2 v1, Vector2 v2) {
  // Add the lowest weight to a queue
  // Update with lowest value node
  // Repeat

  // Instead of this let's just do whichever is highest minus the lowest one
  // and then add them together
  // uint8_t distance = (uint8_t)(sqrt((v2.y - v1.y) * (v2.y - v1.y) -
  // (v2.x - v1.x) * (v2.x - v1.x)));
  uint8_t distance = vector2__distance(&v1, &v2);
  printf("distance: %hhu\n", distance);
  Vector2 result = v1;
  // Stack *s = stack__init();
  uint8_t count = 1;

  printf("result {%d,%d}\n", v1.x, v1.y);
  while (!vector2__eq(&result, &v2)) {
    if (distance < count)
      break;

    // Get adjacent nodes
    // Update this to only check nodes that should be checked
    Vector2 nodes[4];
    nodes[0] = (Vector2){result.x - 1, result.y};
    nodes[1] = (Vector2){result.x, result.y + 1};
    nodes[2] = (Vector2){result.x + 1, result.y};
    nodes[3] = (Vector2){result.x, result.y - 1};

    uint8_t previous_f = 0;
    Vector2 temp = {0};
    // Weigh nodes
    for (size_t i = 0; i < 4; i++) {
      uint8_t g = 5; // bug: calculate the distance backwards as well
      // uint8_t h = (uint8_t)sqrt((v2.y - nodes[i].y) * (v2.y - nodes[i].y) +
      //                           (v2.x - nodes[i].x) * (v2.x - nodes[i].x));
      uint8_t h = vector2__distance(&v2, &nodes[i]);
      uint8_t f = h + g;
      // printf("h: %hhu\n", h);
      // printf("f: %hhu\n", f);
      // printf("previous_f: %hhu\n", previous_f);

      if (f < previous_f || previous_f == 0) {
        temp = nodes[i];
      }

      previous_f = f;

      // printf("%zu{%d,%d}\n", i, nodes[i].x, nodes[i].y);
      // printf("f %hhu\n", f);
    }

    result = temp;
    printf("result {%d,%d}\n", result.x, result.y);
    ++count;
  }

  // stack__push(s, &result);
  // printf("result {%d,%d}\n", result.x, result.y);
  // Vector2 *sv2 = stack__pop(s);
  // printf("result {%d,%d}\n", sv2->x, sv2->y);
}

Stack *stack__init(void) {
  Stack *s = {0};
  s = (Stack *)malloc(sizeof(Stack));
  s->head = NULL;
  return s;
}

void stack__push(Stack *s, Vector2 *v) {
  Node *n = {0};
  n = (Node *)malloc(sizeof(Node));

  if (s->head == NULL) {
    n->next = NULL;
    n->data = v;
    s->head = n;
  } else {
    Node *cn = s->head;
    while (cn != NULL) {
      cn = cn->next;
    }
    cn->next = n;
  }
}

Vector2 *stack__pop(Stack *s) { return s->head->data; }

bool vector2__eq(Vector2 *v1, Vector2 *v2) {
  if (v1->x == v2->x && v1->y == v2->y)
    return TRUE;
  else
    return FALSE;
}

uint8_t vector2__distance(Vector2 *v1, Vector2 *v2) {
  return (v1->x > v2->x ? v1->x - v2->x : v2->x - v1->x) +
         (v1->y > v2->y ? v1->y - v2->y : v2->y - v1->y);
}
