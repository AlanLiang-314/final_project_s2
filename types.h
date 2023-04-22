#ifndef TYPES_H_
#define TYPES_H_
#include "header.h"

// pair<float,float>
// used for recording dynamically changing coordinate
typedef struct {
  float first, second;
} FloatPair;

FloatPair make_FloatPair(float f1, float f2) { return (FloatPair){f1, f2}; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// pair<int,int>
// used for saving coordinates
typedef struct {
  int first, second;
} IntPair;

IntPair make_IntPair(int i1, int i2) { return (IntPair){i1, i2}; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct __INT_PAIR_NODE__ {
  IntPair data;
  struct __INT_PAIR_NODE__ *next;
} IntPairNode;

// list<pair<int,int>>
// used for saving coordinates
/// @todo remove it and rewrite it in a better way
typedef struct {
  IntPairNode *head, *rear;
  unsigned size;
} IntPairList;

IntPairList *new_IntPairList() {
  IntPairList *l = malloc(sizeof(IntPairList));
  *l = (IntPairList){NULL, NULL, 0};
  return l;
}

void IntPairList_push(IntPairList *l, IntPair p) {
  if (!l->size)
    l->head = malloc(sizeof(IntPairNode)), l->rear = l->head;
  else
    l->rear->next = malloc(sizeof(IntPairNode)), l->rear = l->rear->next;
  *(l->rear) = (IntPairNode){p, NULL}, l->size++;
}

void IntPairList_clear(IntPairList *l) {
  IntPairNode *ptr = l->head, *tmp;
  while (ptr != NULL) {
    tmp = ptr;
    ptr = ptr->next;
    free(tmp);
  }
  free(l);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// triple<int,int,int>
typedef struct {
  int first, second, third;
} IntTriple;

IntTriple make_IntTriple(int i1, int i2, int i3) { return (IntTriple){i1, i2, i3}; }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct __INT_TRIPLE_NODE__ {
  IntTriple data;
  struct __INT_TRIPLE_NODE__ *next;
} IntTripleNode;

// stack<triple<int, int, int>>
typedef struct {
  IntTripleNode *top;
  unsigned size;
} IntTripleStack;

IntTripleStack *new_IntTripleStack() {
  IntTripleStack *s = malloc(sizeof(IntTripleStack));
  *s = (IntTripleStack){NULL, 0};
  return s;
}

IntTriple IntTripleStack_top(IntTripleStack *s) { return s->size > 0 ? s->top->data : make_IntTriple(-1, -1, -1); }

void IntTripleStack_push(IntTripleStack *s, IntTriple t) {
  IntTripleNode *tmp = malloc(sizeof(IntTripleNode));
  *tmp = (IntTripleNode){t, s->top};
  s->top = tmp, s->size++;
}

void IntTripleStack_pop(IntTripleStack *s) {
  if (s->size <= 0) return;
  IntTripleNode *tmp = s->top;
  s->top = s->top->next;
  free(tmp);
  s->size--;
}

void IntTripleStack_clear(IntTripleStack *s) {
  IntTripleNode *ptr = s->top, *tmp;
  while (ptr != NULL) {
    tmp = ptr;
    ptr = ptr->next;
    free(tmp);
  }
  free(s);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct {
  char **data;  // @: wall, ' ': path
  IntPairList *path, *walked_path;
  unsigned row, col, walked;
} Map;

Map *new_Map(unsigned r, unsigned c) {
  Map *m = malloc(sizeof(Map));
  char **tmp = malloc(r * sizeof(char *));
  for (unsigned i = 0; i < r; i++) tmp[i] = memset(malloc((c + 1) * sizeof(char)), '@', c);
  *m = (Map){tmp, new_IntPairList(), new_IntPairList(), r, c, 0};
  return m;
}

void Map_clear(Map *m) {
  for (unsigned i = 0; i < m->row; i++) free(m->data[i]);
  free(m->data);
  IntPairNode *ptr = m->path->head, *tmp;
  while (ptr != NULL) {
    tmp = ptr, ptr = ptr->next;
    free(tmp);
  }
  free(m->path);
  ptr = m->walked_path->head;
  while (ptr != NULL) {
    tmp = ptr, ptr = ptr->next;
    free(tmp);
  }
  free(m->walked_path);
  free(m);
}

#endif