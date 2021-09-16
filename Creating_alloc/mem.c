#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>


int Mem_Init(int sizeOfRegion);
void *TEDU_alloc(int size);
int TEDU_Free(void *ptr);
int Mem_IsValid(void *ptr);
int Mem_GetSize(void *ptr);
int TEDU_GetStats();


// Block start
typedef struct Block
{
    int sizeOfregion;
    int* check;
    int** memory;
    int* part_of_block_size;
    
}Block;
static int total_block_size;
static Block block;
static int part=1;
static int index=0;
// Block end




//Functions start

int Mem_Init(int sizeOfRegion){
    total_block_size=sizeOfRegion;
    block.sizeOfregion=sizeOfRegion;
    block.memory=(int**)malloc(sizeof(int*)*part);
    block.part_of_block_size=(int*)malloc(sizeof(int)*part);  
    if(block.memory==NULL){
        return 0;
    } 
}
void *TEDU_alloc(int size){
    int fixedSize;
    int* tempptr;
    if(size<block.sizeOfregion){
        if(size>4){
            block.memory=realloc(block.memory,sizeof(int*)*(++part));
            block.part_of_block_size=realloc(block.part_of_block_size,sizeof(int)*(part));
            
            if(block.memory==NULL){
                return 0;
            }
            fixedSize=size-(size%4);
            block.memory[index]=(int*)calloc((fixedSize/sizeof(int)),sizeof(int));
            block.part_of_block_size[index]=fixedSize;
            tempptr=block.memory[index];
            index++;
            block.sizeOfregion-=fixedSize;

        }
        
    }else{
        if(size==block.sizeOfregion){
            fixedSize=size-(size%4);
            block.memory[index]=(int*)calloc((fixedSize/sizeof(int)),sizeof(int));
            block.part_of_block_size[index]=fixedSize;
            tempptr=block.memory[index];
            block.sizeOfregion-=fixedSize;
        }else{
            printf("Memory is invalid.\n");
            return 0;
        }
    }
    return tempptr;
}
int TEDU_Free(void *ptr){
    int block_index=0;
    int loopsize;
    int block_size=0;
    if(ptr==NULL){
        return 0;
    }else{
        if(block.sizeOfregion==0){
            loopsize=index;
        }else{
            loopsize=index-1;
        }
        for(int i=0;i<=loopsize;i++){
            if(block.memory[i]==ptr){
                block_index=i;
                block_size=block.part_of_block_size[i];
            }
        }
        
        if(block_index==loopsize){
            block.memory=realloc(block.memory,sizeof(int*)*(--part));
            block.part_of_block_size=realloc(block.part_of_block_size,sizeof(int)*(part));
            block.part_of_block_size[loopsize]=-1;
            
            
        }else{
            for(int i=block_index;i<loopsize;i++){
                block.memory[i]=block.memory[i+1];
                block.part_of_block_size[i]=block.part_of_block_size[i+1];
            }
            //free(block.memory[loopsize]);
            block.part_of_block_size[loopsize]=-1;
            free(ptr);
            block.memory=realloc(block.memory,sizeof(int*)*(--part));
            block.part_of_block_size=realloc(block.part_of_block_size,sizeof(int)*(part));
        }
        block.sizeOfregion+=block_size;
        index--;
        
    }
    return -1;
}
int Mem_IsValid(void *ptr){
    int loopsize;
    int isValid=0;
    if(block.sizeOfregion==0 || block.sizeOfregion<4){
        loopsize=index;
    }else{
        loopsize=index-1;
    }
    for(int i=0;i<=loopsize;i++){
            if(block.memory[i]==ptr){
                isValid=1;
                break;
            }
    }
    return isValid;
}
int Mem_GetSize(void *ptr){
    
    if(Mem_IsValid(ptr)){
        int loopsize;
        int isValid=0;
        int block_index;
        if(block.sizeOfregion==0){
            loopsize=index;
        }else{
        loopsize=index-1;
        }
        for(int i=0;i<=loopsize;i++){
            if(block.memory[i]==ptr){
                block_index=i;
            }
        }
        return block.part_of_block_size[block_index];
    }else{
        return -1;
    }
    
}
int TEDU_GetStats(){
    double percentage_of_mem_usage=0;
    int num_of_empty_fragment=0;
    double avg_frag_size=0;
    int largest_empty_fragment_size=0;
    /////
    int loopsize;
    if(block.sizeOfregion==0){
        loopsize=index;
    }else{
        loopsize=index-1;
    }
    for(int i=0;i<=loopsize;i++){
        percentage_of_mem_usage+=(double)block.part_of_block_size[i];
    }
    for(int i=0;i<=loopsize;i++){
        if(i==0){
            largest_empty_fragment_size=block.part_of_block_size[i];
        }
        if(block.part_of_block_size[i]>largest_empty_fragment_size){
            largest_empty_fragment_size=block.part_of_block_size[i];
        }
    }
    avg_frag_size=percentage_of_mem_usage/(loopsize+1);
    num_of_empty_fragment=loopsize+1;    
    if(block.memory==NULL){
        return 0;
    }else{
        if(total_block_size==0){
            printf("\nThe percent of used memory: %%%.2f\n",(percentage_of_mem_usage));
        }else{
            printf("\nThe percent of used memory: %%%.2f\n",(percentage_of_mem_usage/total_block_size)*100);
        }
        printf("Number of empty fragments: %d\n",num_of_empty_fragment);
        if((loopsize+1)==0){
            avg_frag_size=0;
            printf("Average of fragment size: %.2f\n",avg_frag_size);
        }else{
            printf("Average of fragment size: %.2f\n",avg_frag_size);
        }
        
        printf("The largest empty fragment size: %d\n\n",largest_empty_fragment_size);
        return 1;
    }
    
    

}

//Functions end

