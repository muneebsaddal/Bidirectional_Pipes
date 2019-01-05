#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>
  
int main() {
    
    int fd1[2];
    int fd2[2];
    char child_str[] = "Hi Child Process";
    char parent_str[] = "Hello Parent Process";
    
    pid_t p;    //process creation

    if (pipe(fd1)==-1) {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd2)==-1) {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
   
    p = fork();     //process forked
  
    if (p < 0) {
        fprintf(stderr, "fork Failed" );
        return 1;
    } else if (p > 0) {
        char temp_str[100];
        close(fd1[0]);
        write(fd1[1], parent_str, strlen(parent_str)+1);
        close(fd1[1]);
        wait(NULL);
        close(fd2[1]);
        read(fd2[0], temp_str, 100);
        printf("Parent Message--> %s\n", temp_str);
        close(fd2[0]);
    } else {
        close(fd1[1]);
        char temp_str[100];
        read(fd1[0], temp_str, 100);
        close(fd1[0]);
        close(fd2[0]);
        write(fd2[1], child_str, strlen(child_str)+1);
        printf("Child Message--> %s\n", temp_str);
        close(fd2[1]);
        exit(0);
    }
}
