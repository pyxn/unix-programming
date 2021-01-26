// Description: Finds a file in current directory and identifies it as either a file or a directory

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findFile(char *basePath, char fileName[]);

int main(int argc, char *argv[]) {

	char fileName[100];

	if (argc == 1) {
		printf("This command requires one (1) argument.\n");
		exit(1);
	} else if (argc > 1) {
		strcpy(fileName, argv[1]);
		printf("Search results for \"%s\": \n", fileName);
		findFile("./", fileName);
	} else {
		printf("Too many arguments.\n");
		return 0;
	}
}

void findFile(char *basePath, char fileName[]) {

	DIR *dp;
	struct dirent *dirp;

	dp = opendir("./");
	int foundFlag = 0;

	while ( (dirp = readdir(dp)) != NULL)  {
		if (strcmp(dirp->d_name, fileName) == 0) {
			if (dirp->d_type == DT_DIR) {
				printf("%s\t\tThis is a directory.\n", dirp->d_name);
			} else if (dirp->d_type == DT_REG) {
				printf("%s\t\tThis is a file.\n", dirp->d_name);
			}
			foundFlag = 1;
		}
	}

	if (foundFlag == 0) {
		printf("File not found.\n");
	}

	closedir(dp);
}
