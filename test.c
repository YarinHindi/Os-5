//
//
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
char * golb = "a";
void write_to_client(char to_do){
    int des_p[2];
    char buffer[6];
    if(pipe(des_p)) {
        perror("Pipe failed");
        exit(1);
    }
    char * args[] = {"./client","Yarin",NULL};
    int pid=fork();
    if(pid==0){
        close(STDIN_FILENO);  //closing stdout
        close(des_p[1]); //close cause parent will write to this end of pipe
        dup2(des_p[0],0);//replacing Stdin with pipe read so when parnt will write it will show on stdin
        close(des_p[0]);       //closing pipe read
        execvp("./client",args);
        exit(1);
    }else {
        memset(buffer, '0', 6);
        close(des_p[0]);
        char * command  = "PUSH HELLO\n";

        if (to_do == 'w'){
            write(des_p[1], "PUSH HELLO\n", 11);
            write(des_p[1], "TOP\n", 4);
        }else{
            write(des_p[1],"POP\n",4);
            write(des_p[1], "TOP\n", 4);
        }
        sleep(1);
        close(des_p[1]);
        wait(NULL);
    };
}

int main(int argc, char **argv) {
    int pid = fork();
    if (pid == 0) {
        write_to_client('w');
        exit(1);
    } else {
        int pid2 = fork();
        if (pid2 == 0) {
            write_to_client('w');
            exit(1);
        } else {
            int pid3 = fork();
            if (pid3 == 0) {
                write_to_client('r');
                exit(1);
            } else {
                wait(NULL);
            }
        }
    }
}



