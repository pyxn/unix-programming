#include <stdio.h>
#include <unistd.h>

int main() {

     //	printf("Hello world!");
	//printf("Hello world!\n");
      //  sleep(5);

	
	printf("To man the world is twofold,");
	write(STDOUT_FILENO, "in accordance with his twofold attitude.\n", 41);

}
