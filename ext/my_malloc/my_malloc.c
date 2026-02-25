#include <ruby.h>

/* to hold the allocated memory */
struct my_malloc {
  size_t size;
  void *ptr;
};

/* to free the allocated memory after garbage collection */
static void
my_malloc_free(void *p) {
  struct my_malloc *ptr = p;

  if (ptr->size > 0)
    free(ptr->ptr);
}

/* to create the ruby wrapper object */
static VALUE
my_malloc_alloc(VALUE klass) {
  VALUE obj;
  struct my_malloc *ptr;

  obj = Data_Make_Struct(klass, struct my_malloc, NULL, my_malloc_free, ptr);

  ptr->size = 0;
  ptr->ptr  = NULL;

  return obj;
}

/* to allocate memory from ruby */
static VALUE
my_malloc_init(VALUE self, VALUE size) {
  struct my_malloc *ptr;
  size_t requested = NUM2SIZET(size);

  if (0 == requested)
    rb_raise(rb_eArgError, "unable to allocate 0 bytes");

  Data_Get_Struct(self, struct my_malloc, ptr);

  ptr->ptr = malloc(requested);

  if (NULL == ptr->ptr)
    rb_raise(rb_eNoMemError, "unable to allocate %ld bytes", requested);

  ptr->size = requested;

  return self;
}

/* to free memory from ruby */
static VALUE
my_malloc_release(VALUE self) {
  struct my_malloc *ptr;

  Data_Get_Struct(self, struct my_malloc, ptr);

  if (0 == ptr->size)
    return self;

  ptr->size = 0;
  free(ptr->ptr);

  return self;
}

/* to register the functions in the MyMalloc class */
void
Init_my_malloc(void) {
  VALUE cMyMalloc;

//  cMyMalloc = rb_const_get(rb_cObject, rb_intern("MyMalloc"));
  cMyMalloc = rb_define_class("MyMalloc", rb_cObject);

  rb_define_alloc_func(cMyMalloc, my_malloc_alloc);
  rb_define_method(cMyMalloc, "initialize", my_malloc_init, 1);
  rb_define_method(cMyMalloc, "free", my_malloc_release, 0);
}
