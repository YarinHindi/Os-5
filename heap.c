/* Include the sbrk function */
#include <unistd.h>
//#include <stdio.h>
#ifndef HEAP
#define HEAP

typedef struct mem_block {
    int free;
    int size;
    struct mem_block *next;
}mem_block;

int initialized = 0;
struct mem_block * heap;

void init(ssize_t size){
    heap = (mem_block*)sbrk(0);
    void * req = sbrk(size);
    heap->free=0;
    heap->next = NULL;
    heap->size = size;
    initialized=1;
}
struct mem_block* requstMemorySpace(ssize_t bytes,struct mem_block **last){
    struct mem_block * newd;
    newd = (mem_block*)sbrk(0);
    void *request = (void*)sbrk(bytes + sizeof(struct mem_block));
    if (request == (void*) -1) {
        return NULL; // sbrk failed.
    }
    (*last)->next = newd;
    newd->size = bytes+sizeof(struct mem_block);
    newd->next = NULL;
    newd->free = 0;
    return newd+sizeof(struct mem_block);
}

void * Mymalloc(long bytes){
        if(!initialized){
            init(bytes+sizeof(struct mem_block));
            return heap+sizeof(struct mem_block);
        }
        void * req = (void *)bytes+(sizeof(struct mem_block));
        struct mem_block * temp = heap;
        while (temp!=NULL){
                if(temp->size>=sizeof(struct mem_block)+bytes&&temp->free){
                    return temp+sizeof(struct mem_block);

                }
                if(temp->next==NULL){
                    return requstMemorySpace(bytes,&temp);
                }
                temp = temp->next;

        }

}
void* Mycalloc(size_t num, size_t len) {
    void* ptr = malloc(num * len);

    /* Set the allocated array to 0's.*/
    if (ptr != NULL) {
        memset(ptr, 0, num * len);
    }

    return ptr;
}
void Myfree (void * adress){
    struct mem_block * temp = heap;
    while (temp!=NULL){
        if (temp+sizeof(struct mem_block)==adress){
            temp->free=1;
        }
        temp =temp->next;
    }
}
#endif

//
//int main(){
//    int * ma = (int *)Malloc(sizeof(int)*100);
//    ma[0]=3213;
//    int * text  = (int *)(Malloc(sizeof(int)*100));
//    int * text2  = (int *)(Malloc(sizeof(int)*50));
//    Free(text);
//    int * text3  = (int *)(Malloc(sizeof(int)*50));
//    printf("%p\n",ma);
//    printf("%p\n",text);
//    printf("%p\n",text2);
//    printf("%p\n",text3);
//    for (int i = 0;  i< 5; i++) {
//        text[i] = i;
//    }
//    for (int i = 0;  i<10 ; i++) {
//        text2[i] = 1000;
//    }
//    printf("%d\n",ma[0]);
//    printf("%d\n",text[3]);
//    printf("%d\n",text2[5]);
////    printf("%p - first\n",heap+sizeof(struct mem_block));
////    printf("%d - second\n",heap->next->free);
//    printf("%d - third\n",heap->next->next->free);
////    int i =0;
//}
