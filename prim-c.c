#include <stdio.h>
#include <stdlib.h>

enum { Number, String, Symbol, Vector, Cons };

struct Number
{
};

struct String
{
  int   length;
  char *contents;
};

struct Symbol
{
  struct String *string;
};

struct Vector
{
  int            length;
  struct Object *contents;
};

struct Cons
{
  struct Object *car;
  struct Object *cdr;
};

typedef struct Object
{
  int		tag;
  union {
    struct Number number;
    struct String string;
    struct Symbol symbol;
    struct Vector vector;
    struct Cons   cons;
  } payload;
} *oop;

static inline int length(struct Object *object)
{
  switch (object->tag)
    {
    case Number:
      fprintf(stderr, "Number has no length\n");
      exit(-1);
      
    case String:
      return object->payload.string.length;

    case Symbol:
      return object->payload.symbol.string->length;

    case Vector:
      return object->payload.vector.length;

    case Cons:
      return object->payload.cons.cdr
	? 1 + length(object->payload.cons.cdr)
	: 0;

    default:
      fprintf(stderr, "illegal tag %d\n", object->tag);
      exit(-1);
    }
}

int main()
{
  int i, j;
  struct Object *a= calloc(1, sizeof(struct Object));
  struct Object *b= calloc(1, sizeof(struct Object));
  struct Object *c= calloc(1, sizeof(struct Object));
  struct Object *d= calloc(1, sizeof(struct Object));

  a->tag= String;  a->payload.string.length= 1;
  b->tag= Symbol;  b->payload.symbol.string= (struct String *)a;
  c->tag= Vector;  c->payload.vector.length= 3;
  d->tag= Cons;    c->payload.cons.cdr= 0;

  for (i= 0, j= 0;  i < 2000000;  ++i)
    {
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
      j += length(a) + length(b) + length(c) + length(d);
    }

  printf("total %d\n", j);

  return 0;
}
