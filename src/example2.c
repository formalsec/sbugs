struct Car {
   char name[10];
   int id;
};


typedef struct Person {
   char name[10];
   int id;
   struct Car car;

   struct Person other[10];
} Book;




void f1(int a, struct Car car, struct Person person[10]) {

}
