#define N 10

int glob = 44; 


int f(int a[][N], int len) {
    int sum = 0; 
    int k; 
    for(k=0; k< len; k++) {
        sum += a[k][0];
    }
    return sum;
}


int main() {
}

/*

void test_f() {

    int arr_size = pick_random(); 
    int* arr = (int*)malloc(sizeof(int)*arr_size); 
    int k; 
    for(k=0; k< arr_size; k++) {
        arr[k] = symb_int();  
    }

    int len = symb_int(); 

    f(arr, len);
}


void test_g() {
    // construir os inputs simbolicos

    // chamar a funcao 

}


*/