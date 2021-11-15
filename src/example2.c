typedef struct A {
   int a_id;   
   char name[10];
   struct A a;
} Book;


struct B {
   int b_id;
   struct A a;
};


void f1(int* a, struct A c, struct B b) {

}
