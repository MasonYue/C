#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Read a user id and password from standard input, 
   - create a new process to run the validate program
   - send 'validate' the user id and password on a pipe, 
   - print a message 
        "Password verified" if the user id and password matched, 
        "Invalid password", or 
        "No such user"
     depending on the return value of 'validate'.
*/


int main(void) {
    char userid[10];
    char password[10];

    /* Read a user id and password from stdin */
    printf("User id:\n");
    scanf("%s", userid);
    printf("Password:\n");
    scanf("%s", password);

    /*Your code here*/
	int fd[2];
	if(pipe(fd) == -1){
		perror("pipe");
	}
	
	int r = fork();
	
	if(r>0){
		close(fd[0]);
		if(write(fd[1], userid, 11)==-1){
			perror("write userid to pipe");
		}
		if(write(fd[1], password, 11)==-1){
			perror("write password to pipe");
		}
		close(fd[1]);
		
		int status;
		if(wait(&status) != -1) {
			if(WIFEXITED(status)){
				if(WEXITSTATUS(status)==0){
					printf("Password verified");
				}
				if(WEXITSTATUS(status)==2){
					printf("Invalid password");
				}
				if(WEXITSTATUS(status)==3){
					printf("No such user");
				}
			}
			else{
				printf("Child exited abnormally");
			}
		}
	}
	
	else if(r==0){
		close(fd[1]);
		execvp("validate",fd[0]);
	}
    
    return 0;
}