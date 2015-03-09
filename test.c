#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randint(int);

int main(){
    printf("Hello, world");
	return 0;
}

int randint(int size){
	int num;	
    time_t t;
	srand((unsigned) time(&t));
	return rand() % size;
}
