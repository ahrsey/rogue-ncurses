#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Vector2 {
  uint8_t x;
  uint8_t y;
} Vector2;

typedef struct Room {
  Vector2 position;
  uint8_t height;
  uint8_t width;
  Vector2 doors[4];
} Room;

typedef struct Player {
  Vector2 position;
} Player;

Room **map__init(void);

Player *player__init(void);
uint8_t player__handle_input(Player *p, uint8_t ch);
uint8_t player__move(Player *p, uint8_t x, uint8_t y);
uint8_t player__check_position(Player *p, uint8_t x, uint8_t y);

Room *room__init(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
uint8_t room__draw(Room *r);
uint8_t room__connect(Vector2 door1, Vector2 door2);

int main(void) {
  initscr();
  noecho();
  refresh();
  srand(time(NULL));

  map__init();

  Player *p = player__init();
  uint8_t ch;

  while ((ch = getch()) != 'q') {
    player__handle_input(p, ch);
  }

  endwin();
  return 0;
}

Room **map__init(void) {
  Room **rooms = {0};

  rooms = (Room **)malloc(sizeof(Room) * 6);

  rooms[0] = room__init(13, 13, 8, 6);
  rooms[1] = room__init(40, 2, 8, 6);
  rooms[2] = room__init(40, 10, 14, 6);

  room__draw(rooms[0]);
  room__draw(rooms[1]);
  room__draw(rooms[2]);

  room__connect(rooms[0]->doors[3], rooms[2]->doors[2]);

  return rooms;
}

Player *player__init(void) {
  Player *p = {0};
  p = (Player *)malloc(sizeof(p));

  p->position.y = 14;
  p->position.x = 14;

  mvprintw(p->position.y, p->position.x, ".");
  player__move(p, 14, 14);

  return p;
}

uint8_t player__handle_input(Player *p, uint8_t input) {
  uint8_t newX = 0;
  uint8_t newY = 0;
  switch (input) {
  case 'w':
  case 'W':
    newX = p->position.x;
    newY = p->position.y - 1;
    break;
  case 's':
  case 'S':
    newX = p->position.x;
    newY = p->position.y + 1;
    break;
  case 'a':
  case 'A':
    newX = p->position.x - 1;
    newY = p->position.y;
    break;
  case 'd':
  case 'D':
    newX = p->position.x + 1;
    newY = p->position.y;
    break;
  default:
    break;
  }

  player__check_position(p, newX, newY);
  return 1;
}

uint8_t player__move(Player *p, uint8_t x, uint8_t y) {
  mvprintw(p->position.y, p->position.x, ".");
  p->position.x = x;
  p->position.y = y;

  mvprintw(p->position.y, p->position.x, "@");
  move(p->position.y, p->position.x);

  return 1;
}

uint8_t player__check_position(Player *p, uint8_t x, uint8_t y) {
  // uint8_t space;
  switch (mvinch(y, x)) {
  case '.':
  case '+':
  case '#':
    player__move(p, x, y);
    break;
  default:
    move(p->position.y, p->position.x);
    break;
  }
  return 1;
}

Room *room__init(uint8_t x, uint8_t y, uint8_t width, uint8_t height) {
  Room *r = {0};
  r = (Room *)malloc(sizeof(Room));
  r->position.x = x;
  r->position.y = y;
  r->height = height;
  r->width = width;

  // Top door
  r->doors[0].x = rand() % (width - 2) + x + 1;
  r->doors[0].y = y;

  // Bottom doors
  r->doors[1].x = rand() % (width - 2) + x + 1;
  r->doors[1].y = y + height - 1;

  // Left doors
  r->doors[2].x = x;
  r->doors[2].y = rand() % (height - 2) + y + 1;

  // Right doors
  r->doors[3].x = x + width - 1;
  r->doors[3].y = rand() % (height - 2) + y + 1;

  return r;
}

uint8_t room__draw(Room *r) {
  uint8_t x = 0;
  uint8_t y = 0;

  // Draw top and bottom wall
  for (x = r->position.x; x < (r->position.x + r->width); ++x) {
    mvprintw(r->position.y, x, "-");
    mvprintw(r->position.y + r->height - 1, x, "-");
  }

  for (y = r->position.y + 1; y < (r->position.y + r->height - 1); ++y) {
    // Draw side walls
    mvprintw(y, r->position.x, "|");
    mvprintw(y, r->position.x + r->width - 1, "|");

    // Draw floor
    for (x = r->position.x + 1; x < (r->position.x + r->width - 1); ++x) {
      mvprintw(y, x, ".");
    }
  }

  // Draw doors
  mvprintw(r->doors[0].y, r->doors[0].x, "+");
  mvprintw(r->doors[1].y, r->doors[1].x, "+");
  mvprintw(r->doors[2].y, r->doors[2].x, "+");
  mvprintw(r->doors[3].y, r->doors[3].x, "+");

  return 1;
}

// TODO Update to use a star
// https://medium.com/@nicholas.w.swift/easy-a-star-pathfinding-7e6689c7f7b2
uint8_t room__connect(Vector2 door1, Vector2 door2) {
  Vector2 temp;
  Vector2 previous;
  uint8_t count = 0;

  temp.x = door1.x;
  temp.y = door1.y;

  previous = temp;

  while (1) {
    // Left
    if ((abs((temp.x - 1) - door2.x) < abs(temp.x - door2.x)) &&
        (mvinch(temp.y, temp.x - 1) == ' ')) {
      previous.x = temp.x;
      temp.x = temp.x - 1;
      // Right
    } else if ((abs((temp.x + 1) - door2.x) < abs(temp.x - door2.x)) &&
               (mvinch(temp.y, temp.x + 1) == ' ')) {
      previous.x = temp.x;
      temp.x = temp.x + 1;
      // Up
    } else if ((abs((temp.y - 1) - door2.y) < abs(temp.y - door2.y)) &&
               (mvinch(temp.y - 1, temp.x) == ' ')) {
      previous.y = temp.y;
      temp.y = temp.y - 1;
      // Down
    } else if ((abs((temp.y + 1) - door2.y) < abs(temp.y - door2.y)) &&
               (mvinch(temp.y + 1, temp.x) == ' ')) {
      previous.y = temp.y;
      temp.y = temp.y + 1;
    } else {
      if (count == 0) {
        temp = previous;
        count++;
        continue;
      } else {
        return 0;
      }
    }

    mvprintw(temp.y, temp.x, "#");
    // getch();
  }

  return 1;
}
