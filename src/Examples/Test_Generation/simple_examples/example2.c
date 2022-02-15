struct Car {
   char name[10];
   int id;
};


typedef struct Person {
   char name[10];
   int id;
   struct Car car;

   struct Person* other;
}* Type_Person;




void f1(int* a[], struct Car car, Type_Person array[]) {

}
