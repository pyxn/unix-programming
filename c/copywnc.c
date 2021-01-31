/**
 * ------------------------------------------------------------------
 * Copy With No Comments - copywnc.c
 * Creates a non-commented copy of a commented file.
 * ------------------------------------------------------------------
*/

#include <stdio.h>

int copyfile(const char *filename1, const char *filename2);
void remove_line_comment(FILE *inputFile, int *c, int *next);
void remove_block_comment(FILE *inputFile, int *c, int *next);

int main(int argc, char *argv[]) {

    if (argc != 3) {
        printf("Usage: %s <filename1> <filename 2>\n", argv[0]);
    }
	copyfile(argv[1], argv[2]);
	
}

int copyfile(const char *filename1, const char *filename2) {

	FILE *inputFile;
    FILE *outputFile;

	int c;
	int next;

	if ((inputFile = fopen(filename1, "r")) == NULL) {
		printf("Error: %s not found.\n", filename1);
		return -1;
	}

	if ((outputFile = fopen(filename2, "w")) == NULL) {
		printf("Error: unable to write to %s.\n", filename2);
		fclose(inputFile);
		return -2;
	}

	while ((c = getc(inputFile)) != EOF) {

		remove_line_comment(inputFile, &c, &next);
		remove_block_comment(inputFile, &c, &next);
		
		if (c != EOF) {
			putc(c, outputFile);
		}
	}

	fclose(inputFile);
	fclose(outputFile);

	printf("\n\nSuccessfully created the non-commented file: %s.\n\n", filename2);

    return 0;
}

void remove_line_comment(FILE *inputFile, int *c, int *next) {
	if (*c == '/') {
		if ((*next = getc(inputFile)) == '/') {
		while ((*c = getc(inputFile)) != '\n') {
			// Ignore characters before the newline.
		}
		} else {
			*next = ungetc(*next, inputFile);
		}
	}
}

void remove_block_comment(FILE *inputFile, int *c, int *next) {
	if (*c == '/') {
		if ((*next = getc(inputFile)) == '*') {
			while (((*c = getc(inputFile)) != EOF)) {
				int temp;
				if (*c == '*') {
					temp = getc(inputFile);
					if (temp == '/') {
						*c = getc(inputFile);
						return;
					} else {
						temp = ungetc(temp, inputFile);
					}
				}
			}
		} else {
			*next = ungetc(*next, inputFile);
		}
	}
}
