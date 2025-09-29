//All code for exercises 1 - 3
#include <stdio.h>
#include <stdlib.h>

void FizzBuzz(int n);

int descending(const void *a, const void *b);

int main(){
	printf("Hello, World!\r\n");


	// Dynamically allocate int array of size 20
	int *arr = malloc(20 * sizeof(int));
	// Fills the array with values 1 - 20
	for (int i = 0; i < 20; i++){
		arr[i] = i + 1;
	}

	printf("FizzBuzz on int array: \r\n");
	for (int i = 0; i < 20; i++){
		printf("%d: ", i + 1);
		FizzBuzz(arr[i]);
		printf("\r\n");
	}

	printf("FizzBuzz on 1 to 30: \r\n");
	for (int i = 1; i < 31; i++){
		printf("%d: ", i);
		FizzBuzz(i);
		printf("\r\n");
	}

	qsort(arr, 20, sizeof(int), descending);
	for (int i = 0; i < 20; i ++ ){
		printf("%d\r\n", arr[i]);
	}

	return 0;
}

void FizzBuzz(int n){

	if ((n % 3 == 0) && !(n % 5 == 0))
	{
		printf("Fizz");
	}
	else if ((n % 5 == 0) && !(n % 3 == 0))
	{
		printf("Buzz");
	}
	else if ((n % 3 == 0) && (n % 5 == 0))
	{
		printf("FizzBuzz");
	}

}

int descending(const void *a, const void *b){
	int x = *(const int *)a;
	int y = *(const int *)b;
	// Too many operations
	// if (x > y){
	// 	return -1;
	// }
	// else if (x < y){
	// 	return 1;
	// }
	// else{
	// 	return 0;
	// }
	int difference = y - x;
	return difference;
}