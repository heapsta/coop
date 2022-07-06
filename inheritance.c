#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Base{
    char *name;
    char* (*get_name)(struct Base* base);
};

char* get_name(struct Base* base) {
    return base->name;
}

struct Base* create_base(char* name) {
   struct Base* base = malloc(sizeof(struct Base));
   assert(base != NULL);
   base->name = name;
   base->get_name = get_name;
   return base;
}

struct Derived {
    struct Base* base;
    char* (*retrive_name)(struct Derived* derived);
};

// Namespaces solve this!
char* retrieve_name(struct Derived* derived){
   return derived->base->get_name(derived->base);
}

struct Derived* create_derived(char* name) {
   struct Derived* derived = malloc(sizeof(struct Derived));
   assert(derived != NULL);
   derived->base = create_base(name);
   derived->retrive_name = retrieve_name;
   return derived;
}

int main() {
    struct Derived* derived = create_derived("Samsung");
    puts(derived->retrive_name(derived));
    puts("Using Polymorphims");
    struct Base* derived2 = (struct Base*) create_derived("Apple");
    puts(derived2->get_name(derived2));
    return 0;
}
