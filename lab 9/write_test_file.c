#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void write_test_file(char * filename){
	FILE *fp;
	int error;
	fp = fopen(filename, "wb");
	int numbers[100];
	if(fp == NULL){
		fprintf(stderr,"couldn't open file\n");
	}
	for(int i=0;i<100;i++){
		numbers[i] = random() % 100;
		
	}
	error = fwrite(numbers,sizeof(int),100,fp);
	if(error != 100){
	fprintf(stderr,"fail to write\n");
	}	
	error = fclose(fp);
	if(error != 0){
		fprintf(stderr,"fail to close file\n");
	}
}

int main(int argc, char **argv){
	if(argc>=2){	
		char * filename = argv[1];
		write_test_file(filename);
		return 0;
	}
	else{
		printf("wrong use");
	}
}

