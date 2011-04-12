#include "obj.c"

/*----------------------------------------------------------------*/

struct object *s_new= 0;
struct object *s_length= 0;

struct Number
{
  struct vtable *_vt[0];
};

struct vtable *Number_vt = 0;
struct object *Number = 0;

struct object *Number_new(struct closure *closure, struct Number *self)
{
  fprintf(stderr, "Number_new\n");
  exit(1);
  return 0;
}

int Number_length(struct closure *closure, struct Number *self)
{
  fprintf(stderr, "Number has no length\n");
  exit(1);
  return 0;
}

struct String
{
  struct vtable *_vt[0];
  int            length;
  char          *chars;
};

struct vtable *String_vt = 0;
struct object *String = 0;

struct object *String_new(struct closure *closure, struct String *self, int size)
{
  struct String *clone = (struct String *)send(self->_vt[-1], s_allocate, sizeof(struct String));
  clone->length = size;
  clone->chars  = (char *)malloc(size);
  return (struct object *)clone;
}

int String_length(struct closure *closure, struct String *self)
{
  return self->length;
}

struct Symbol
{
  struct vtable *_vt[0];
  struct String *string;
};

struct vtable *Symbol_vt = 0;
struct object *Symbol = 0;

struct object *Symbol_new(struct closure *closure, struct Symbol *self, struct String *string)
{
  struct Symbol *clone = (struct Symbol *)send(self->_vt[-1], s_allocate, sizeof(struct Symbol));
  clone->string = string;
  return (struct object *)clone;
}

int Symbol_length(struct closure *closure, struct Symbol *self)
{
  return self->string->length;
}

struct Vector
{
  struct vtable *_vt[0];
  int            length;
  struct object *contents;
};

struct vtable *Vector_vt = 0;
struct object *Vector = 0;

struct object *Vector_new(struct closure *closure, struct Vector *self, int size)
{
  struct Vector *clone = (struct Vector *)send(self->_vt[-1], s_allocate, sizeof(struct Vector));
  clone->length   = size;
  clone->contents = (struct object *)calloc(size, sizeof(struct object *));
  return (struct object *)clone;
}

int Vector_length(struct closure *closure, struct Vector *self)
{
  return self->length;
}

struct Cons
{
  struct vtable *_vt[0];
  struct object *car;
  struct object *cdr;
};

struct vtable *Cons_vt = 0;
struct object *Cons = 0;

struct object *Cons_new(struct closure *closure, struct Cons *self, struct object *car, struct object *cdr)
{
  struct Cons *clone = (struct Cons *)send(self->_vt[-1], s_allocate, sizeof(struct Cons));
  clone->car = car;
  clone->cdr = cdr;
  return (struct object *)clone;
}

int Cons_length(struct closure *closure, struct Cons *self)
{
  return self->cdr
    ? 1 + (int)send(self->cdr, s_length)
    : 0;
}

void init2(void)
{
  s_new    = symbol_intern(0, 0, "new");
  s_length = symbol_intern(0, 0, "length");

  Number_vt = (struct vtable *)send(object_vt, s_delegated);
  String_vt = (struct vtable *)send(object_vt, s_delegated);
  Symbol_vt = (struct vtable *)send(object_vt, s_delegated);
  Vector_vt = (struct vtable *)send(object_vt, s_delegated);
  Cons_vt   = (struct vtable *)send(object_vt, s_delegated);

  send(Number_vt, s_addMethod, s_new, Number_new);
  send(String_vt, s_addMethod, s_new, String_new);
  send(Symbol_vt, s_addMethod, s_new, Symbol_new);
  send(Vector_vt, s_addMethod, s_new, Vector_new);
  send(Cons_vt,   s_addMethod, s_new,   Cons_new);

  send(Number_vt, s_addMethod, s_length, Number_length);
  send(String_vt, s_addMethod, s_length, String_length);
  send(Symbol_vt, s_addMethod, s_length, Symbol_length);
  send(Vector_vt, s_addMethod, s_length, Vector_length);
  send(Cons_vt,   s_addMethod, s_length,   Cons_length);

  Number = send(Number_vt, s_allocate, 0);
  String = send(String_vt, s_allocate, 0);
  Symbol = send(Symbol_vt, s_allocate, 0);
  Vector = send(Vector_vt, s_allocate, 0);
  Cons   = send(Cons_vt,   s_allocate, 0);
}

/*----------------------------------------------------------------*/

void doit(void)
{
  int i, j;

  struct object *a = send(String, s_new, 1);
  struct object *b = send(Symbol, s_new, a);
  struct object *c = send(Vector, s_new, 3);
  struct object *d = send(Cons,   s_new, 0, 0);

  for (i = 0, j = 0;  i < 2000000;  ++i)
    {
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
      j += (int)send(a, s_length) + (int)send(b, s_length) + (int)send(c, s_length) + (int)send(d, s_length);
    }

  printf("total %d\n", j);
}

int main()
{
  init();
  init2();
  doit();
  return 0;
}
