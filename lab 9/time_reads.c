#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int number_reads = 0;
int time = 0;

void message(int sig){
	printf("Number of reads %d\nTime used: %d\n",number_reads, time);
	exit(1);
}

int catch_signal(int sig, void(*handler)(int)){
	number_reads ++;	
	struct sigaction action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	//sigaddset(&action.sa_mask,SIGALRM);
	action.sa_flags = 0;
	return sigaction(sig,&action,NULL);
}

int time_reads(char *filename){
	FILE *fp;
	int location = random() % 100;	
	fp = fopen(filename, "rb");
	int number;
	fseek(fp,sizeof(int)*location,SEEK_SET);
	fread(&number,sizeof(int),1,fp);
	fclose(fp);
	return number;
	

}

int main(int argc, char **argv){
	if(argc != 3){
		printf("wrong usage\n");
		exit(1);
	}
		
	time = (int) strtol(argv[1],NULL,10);
	struct itimerval timer;
	timer.it_value.tv_sec = time;
	timer.it_value.tv_usec = 0;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 0;
	if(setitimer(ITIMER_REAL,&timer,NULL)<0){
		perror("set time error");
		exit(1);
	}
	
	char * filename = argv[2];		
	while(1){		
	time_reads(filename);
	catch_signal(SIGALRM,message);
	}
	
	
	return 0;
	
}
