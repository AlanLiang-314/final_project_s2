// #include "3d_renderer.c"
#include "header.h"
#include "types.h"
// #include "print.c"

CharArray *events_shuffle(unsigned size) {
  CharArray *events = new_CharArray(size - 1);
  for (unsigned i = 0; i < sizeof(events_ratio) / sizeof(float); i++)
    for (int j = 0; j < round(events_ratio[i] * (float)size) - (i == 9); j++) CharArray_push_back(events, (char)('0' + i));
  return events;
}

void gen_maze(Map *map) {  // generate the maze
  CharArray *events = events_shuffle(map->path);

  /// @todo fix initial direction wrongly decided when map size is small
  IntTriple pos = make_IntTriple(rand_between(0, (int)map->col - 2) | 1, rand_between(0, (int)map->row - 2) | 1, rand_between(0, 3));  // gen_center (x, y, from_dir)
  IntTripleStack *pos_st = new_IntTripleStack();                                                                                       // from_dir is saved as well
  IntTripleStack_push(pos_st, pos);
  map->data[pos.second][pos.first] = 'M';  // not sure whether it is necessary

  int dir;
  bool grow;

  while (pos_st->size) {
    pos = IntTripleStack_top(pos_st);
    dir = rand_between(pos.third + 3, pos.third + 5) % 4, grow = 0;  // choose a new direction randomly from 0 to 3, but avoid choosing the opposite direction
    for (int i = 0; i < 3; i++) {                                    // try at most three directions
      if (pos.first + 2 * direction[dir][0] >= 0 && pos.first + 2 * direction[dir][0] < (int)map->col && pos.second + 2 * direction[dir][1] >= 0 && pos.second + 2 * direction[dir][1] < (int)map->row && map->data[pos.second + direction[dir][1]][pos.first + direction[dir][0]] == '@' && map->data[pos.second + 2 * direction[dir][1]][pos.first + 2 * direction[dir][0]] == '@') {
        // the direction's next two coordinates are both @ (wall), choose this direction as the new direction
        // change the two positions to path
        map->data[pos.second + direction[dir][1]][pos.first + direction[dir][0]] = CharArray_pop_front(events), map->data[pos.second + 2 * direction[dir][1]][pos.first + 2 * direction[dir][0]] = CharArray_pop_front(events);
        pos.first += 2 * direction[dir][0], pos.second += 2 * direction[dir][1], pos.third = dir, grow = 1;
        IntTripleStack_push(pos_st, pos);  // push the current position into the position stack
        break;                             // stop attempting other directions
      }

      /// @todo make it real random
      dir = (dir + 1) % 4;                              // try next direction
      if ((dir ^ 2) == pos.third) dir = (dir + 1) % 4;  // fix when choosing the opposite direction
    }
    if (!grow) IntTripleStack_pop(pos_st);  // can't go into any direction (dead end), pop out the top-most element
  }

  CharArray_clear(events);
  IntTripleStack_clear(pos_st);
  return;
}
