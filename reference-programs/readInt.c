#include <stdio.h>

int readInt(void){  
	char input[100];  
	int value;

	do{
		printf("Please enter an integer>");  
		scanf("%s", input);
	}while (sscanf(input, "%d", &value)!= 1);  
	return(value);
}

int main(int argc, char* argv[]){
//	int t=readInt();
	int t;
        scanf("%d", &t);

	printf("int=%d\n", t);
}
