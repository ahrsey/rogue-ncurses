#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  uint8_t x;
  uint8_t y;
} Vector2;

bool vector2__eq(Vector2 *v1, Vector2 *v2);
uint8_t vector2__distance(Vector2 *v1, Vector2 *v2);
void vector2__print(Vector2 *v2Array, uint8_t length);

Vector2 *astar(Vector2 v1, Vector2 v2);

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
// int main(void) {
//   Vector2 v1 = {5, 1};
//   Vector2 v2 = {1, 5};
//
//   // printf("%d", vector2__eq(&v1, &v2));
//   astar(v1, v2);
//
//   return 0;
// }

// Instead of using stack I can use an array with lenght of distance
// V{1,1}, V{1,2}, V{1,3}, V{1,4}, V{1,5}
Vector2 *astar(Vector2 v1, Vector2 v2) {
  // Add the lowest weight to a queue
  // Update with lowest value node
  // Repeat

  // Instead of this let's just do whichever is highest minus the lowest one
  // and then add them together
  // uint8_t distance = (uint8_t)(sqrt((v2.y - v1.y) * (v2.y - v1.y) -
  // (v2.x - v1.x) * (v2.x - v1.x)));
  uint8_t distance = vector2__distance(&v1, &v2);
  // printf("distance: %hhu\n", distance);
  Vector2 result = v1;
  Vector2 *vector_array = {0};
  vector_array = (Vector2 *)malloc(sizeof(Vector2) * distance);
  uint8_t vector_array_index = 0;

  uint8_t count = 1;

  // printf("result {%d,%d}\n", v1.x, v1.y);
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
    for (size_t i = 4; i > 0; i--) {
      uint8_t g = 5; // bug: calculate the distance backwards as well
      uint8_t h = vector2__distance(&v2, &nodes[i]);
      uint8_t f = h + g;

      if (f < previous_f || previous_f == 0) {
        temp = nodes[i];
      }

      previous_f = f;
    }

    result = temp;
    vector_array[vector_array_index++] = result;
    ++count;
  }

  return vector_array;
}

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

void vector2__print(Vector2 *v2Array, uint8_t length) {
  for (size_t i = 0; i < length; ++i) {
    mvprintw(LINES - (1 * (i + 1)), 0, "%zu: {%d,%d}, ", i + 1, v2Array[i].x,
             v2Array[i].y);
  }
  printf("\n");
}
