#include <ncurses.h>
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
  Vector2 v2 = {1, 5};

  astar(v1, v2);

  return 0;
}

// V{1,1}, V{1,2}, V{1,3}, V{1,4}, V{1,5}
void astar(Vector2 v1, Vector2 v2) {
  // Add the lowest weight to a queue
  // Update with lowest value node
  // Repeat

  // while(1)

  // Get adjacent nodes
  Vector2 nodes[4];
  nodes[0] = (Vector2){v1.x - 1, v1.y};
  nodes[1] = (Vector2){v1.x, v1.y + 1};
  nodes[2] = (Vector2){v1.x + 1, v1.y};
  nodes[3] = (Vector2){v1.x, v1.y - 1};

  uint8_t previous_f = 0;
  Vector2 result = {0};
  Stack *s = stack__init();

  // Weigh nodes
  for (size_t i = 0; i < 4; i++) {
    uint8_t g = 10;
    uint8_t h = (v2.y - nodes[i].y) * (v2.y - nodes[i].y) +
                (v2.x - nodes[i].x) * (v2.x - nodes[i].x);
    uint8_t f = h + g;

    if (f < previous_f) {
      result = nodes[i];
    }

    previous_f = f;

    printf("%zu{%d,%d}\n", i, nodes[i].x, nodes[i].y);
    printf("f %hhu\n", f);
  }

  stack__push(s, &result);

  printf("result {%d,%d}\n", result.x, result.y);

  Vector2 *sv2 = stack__pop(s);

  printf("result {%d,%d}\n", sv2->x, sv2->y);
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
