#include "dict.h"

int writedict(const char *dictname, struct dict_elem *elist){

	int j;
	FILE *outf;

	if ((outf = fopen(dictname, "w")) == NULL){
		return ERROR;
	}

	//calculate length of the aray
	for (j = 0; elist[j].d_length != 0; j++)
		;

	//write out list of dict_elem structures
	if (fwrite((void*) elist,sizeof(struct dict_elem), j, outf)<j){
		fclose(outf);
		return ERROR;
	}


	fclose(outf);
	return SUCCESS;
}

//**************************************************************************


struct dict_elem *readdict(const char *dictname, struct dict_elem *inlist, int maxlength) {

	int i;
	FILE *inf;

	if ((inf = fopen(dictname, "r")) == NULL){
		return NULL;
	}
	//read in dict_elem structures from file
	for (i = 0; i < maxlength - 1; i++)
	{
		if (fread((void*)&inlist[i], sizeof(struct dict_elem), 1, inf)<1)
		{
			break;
		}
	}


	fclose(inf);

      //mark end of list
	inlist[i].d_length = 0;
	return inlist;
}


// your main function goes here.
int main(void) {
 struct dict_elem array[3] ={ {"water",9,2,5}, {"vanilla",7,2,3},{"english",3,2,1}, };
 struct dict_elem arr[3];
 writedict("file1.txt",array);
readdict("file1.txt",arr,4);

for(int i=0; i<3; i++){
    printf("%s,%d,%d,%d\n", arr[i].d_name,arr[i].d_start,arr[i].d_length,arr[i].d_type);
}
}