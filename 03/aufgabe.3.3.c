#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main (int argc, char * args[])
{
    int32_t myRank    = 0;
    int32_t worldsize = 0;
    
    MPI_Init(&argc,&args);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank); 
    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);
    
    int32_t stride = ((argc-1+(worldsize-1)) / worldsize);
    int32_t * numbers   = malloc(stride     * worldsize * sizeof(int32_t)); 
    int32_t * buffer    = malloc(stride     * sizeof(int32_t));
    int32_t * scount    = malloc(worldsize  * sizeof(int32_t));
    int32_t * dispis    = malloc(worldsize  * sizeof(int32_t));

    memset(numbers,     0, worldsize*stride*sizeof(int32_t));
    memset(scount,      0, worldsize*sizeof(int32_t));
    memset(buffer,      0, stride);
    memset(dispis,      0, worldsize*sizeof(int32_t));
    
    for(int i = 0; i < argc-1 ; i++)
        numbers[i] = atoi(args[i+1]);

    
    for(int i = 0; i < worldsize; i++)
    {
        scount[i] = stride;
        dispis[i] = stride*i;
    }
    MPI_Scatterv(numbers,scount,dispis,MPI_INT32_T,buffer,stride,MPI_INT32_T,0,MPI_COMM_WORLD);
    
    int32_t myResult = 0;
    for(int i = 0; i < scount[myRank];i++)
        myResult += buffer[i];
    int endResult = 0;
    printf("%2d - %4d\n",myRank,myResult);
    MPI_Reduce(&myResult, &endResult,1 , MPI_INT32_T, MPI_SUM ,0,MPI_COMM_WORLD);

    MPI_Finalize();


    return endResult;
}
