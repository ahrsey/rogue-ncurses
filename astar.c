#include <ncurses.h>

typedef struct {
  uint8_t x;
  uint8_t y;
} Vector2;

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

  // Get adjacent nodes
  Vector2 nodes[4];
  nodes[0] = (Vector2){v1.x - 1, v1.y};
  nodes[1] = (Vector2){v1.x, v1.y + 1};
  nodes[2] = (Vector2){v1.x + 1, v1.y};
  nodes[3] = (Vector2){v1.x, v1.y - 1};

  // Weigh nodes
  for (size_t i = 0; i < 4; i++) {
    uint8_t g = 10;
    uint8_t h = (v2.y - nodes[i].y) * (v2.y - nodes[i].y) +
                (v2.x - nodes[i].x) * (v2.x - nodes[i].x);
    uint8_t f = h + g;

    printf("%zu{%d,%d}\n", i, nodes[i].x, nodes[i].y);
    printf("f %hhu\n", f);
  }
}
