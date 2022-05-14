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
#include <sys/mman.h>

int main(){
    int *shared = (int*)mmap(NULL,sizeof(int),PROT_READ |PROT_WRITE, MAP_ANONYMOUS|MAP_SHARED ,-1,0);
    int not_shared = 0;
    *shared =0;
    if(fork()==0){
        *shared = 1;
        not_shared=1;
        exit(0);
    }else if(fork()==0){
        *shared = 2;
        not_shared=2;
        exit(0);
    }else{
//        wait(NULL);
    }
    sleep(1);
    printf("%d\n",*shared);
    printf("%d\n",not_shared);


}



