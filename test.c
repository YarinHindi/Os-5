//
// Created by orian on 28/04/2022.
//
#include <stdio.h>
#include<stdlib.h>

#include <unistd.h>
#define MAX 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

pid_t popen2(const char *command, int *infp, int *outfp)
{
    int p_stdin[2], p_stdout[2];
    pid_t pid;

    if (pipe(p_stdin) != 0 || pipe(p_stdout) != 0)
        return -1;

    pid = fork();
    if (pid < 0)
        return pid;
    else if (pid == 0)
    {
        close(p_stdin[WRITE]);
        dup2(p_stdin[READ], READ);
        close(p_stdout[READ]);
        dup2(p_stdout[WRITE], WRITE);
        char * const * param ={"Orian"};
        execvp("./client", param);
        exit(1);
    }

    if (infp == NULL)
        close(p_stdin[WRITE]);
    else
        *infp = p_stdin[WRITE];
    if (outfp == NULL)
        close(p_stdout[READ]);
    else
        *outfp = p_stdout[READ];
    return pid;
}

/*
* now in main... infp will be the stdin (in file descriptor)
* and outfp will be the stdout (out file descriptor)
* have fun
*/

int main(int argc, char **argv)
{
    int infp, outfp;
    char buf[128];

    if (popen2("your-program-B", &infp, &outfp) <= 0)
    {
        printf("Unable to exec your-program-B\n");
        exit(1);
    }

    memset (buf, 0x0, sizeof(buf));

    write(infp, "Z\n", 2);
    write(infp, "D\n", 2);
    write(infp, "A\n", 2);
    write(infp, "C\n", 2);
    close(infp);
    read(outfp, buf, 128);
    printf("buf = '%s'\n", buf);
    return 0;
}



