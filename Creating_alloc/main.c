#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int Mem_Init(int sizeOfRegion);
void *TEDU_alloc(int size);
int TEDU_Free(void *ptr);
int Mem_IsValid(void *ptr);
int Mem_GetSize(void *ptr);
int TEDU_GetStats();

int main(){

//The workloads vary the order of allocates and frees in two different ways:

    //Order A: The user allocates N objects and then frees all N of them; the user then allocates N more objects and frees all N of them.
    Mem_Init(100);
    int *ptr1 = TEDU_alloc(20);
    int *ptr2 = TEDU_alloc(20);
    int *ptr3 = TEDU_alloc(40);
    int *ptr4 = TEDU_alloc(10);
    TEDU_GetStats();
    TEDU_Free(ptr1);
    TEDU_Free(ptr2);
    TEDU_Free(ptr3);
    TEDU_Free(ptr4);
    TEDU_GetStats();
    ptr1 = TEDU_alloc(20);
    ptr2 = TEDU_alloc(20);
    ptr3 = TEDU_alloc(40);
    ptr4 = TEDU_alloc(10);
    TEDU_GetStats();
    TEDU_Free(ptr1);
    TEDU_Free(ptr2);
    TEDU_Free(ptr3);
    TEDU_Free(ptr4);
    TEDU_GetStats();
    //Order B: The user repeatedly allocates N objects and then frees N/2 of the objects until the end at which point it frees all remaining objects.
    ptr1 = TEDU_alloc(20);
    ptr2 = TEDU_alloc(20);
    ptr3 = TEDU_alloc(40);
    ptr4 = TEDU_alloc(10);
    TEDU_Free(ptr1);
    TEDU_Free(ptr2);
    TEDU_GetStats();
return 0;
}
