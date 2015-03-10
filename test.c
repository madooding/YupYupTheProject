#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randint(int);
void perchar(char text[]);

int main(){
    char text[30];
    gets(text);
    perchar(text);
    printf("%s\n", text);
	return 0;
}

int randint(int size){
	int num;	
    time_t t;
	srand((unsigned) time(&t));
	return rand() % size;
}
void perchar(char text[]){
     int i, ranNumber;
     char temp;
     for(i = 0; i < strlen(text); i++){
           ranNumber = randint(strlen(text));
           temp = text[i];
           text[i] = text[ranNumber];
           text[ranNumber] = temp;
           }
     }
