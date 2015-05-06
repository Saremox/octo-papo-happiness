#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
int main (int argc, char * args[])
{
    int32_t * numbers = malloc(argc * sizeof(int32_t));
    int32_t result    = 0;
    int32_t myRank    = 0;
    int32_t worldsize = 0;
    
    MPI_Init(&argc,&args);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank); 
    MPI_Comm_size(MPI_COMM_WORLD, &worldsize);


    worldsize--; // Master Node soll im round robin nciht einbezogen werden
    // Master node soll nur die nodes verwalten 

    int32_t maxQueneSize = (argc / worldsize) + 1;

    if(myRank == 0)
    {
        for(int i = 0; i < argc ; i++)
        {
            numbers[i] = atoi(args[i]);
            result += numbers[i];
        }
        int *  datablock = malloc(worldsize * maxQueneSize * sizeof(int32_t));
        int ** quene     = malloc(worldsize * sizeof(int32_t**));
        memset(datablock,0,worldsize * maxQueneSize * sizeof(int32_t));
        fprintf(stderr,"WorldSize: %4d\n",worldsize);

        for(int i = 0; i < worldsize; i++)
            quene[i] = datablock + (maxQueneSize * i);
        
        printf("Mache gleich groesse Quenes fuer die Welt mittels round robin");
        for(int i = 0; i < argc; i++)
            quene[i%worldsize][i/worldsize] = numbers[i];
        for(int i = 0; i < worldsize; i++)
            MPI_Send(quene[i],maxQueneSize,MPI_INT,i+1,1,MPI_COMM_WORLD);
        int result = 0;
        int answer = 0;
        for(int i = 0; i < worldsize; i++)
        {
            MPI_Recv(&answer,1,MPI_INT,i+1,2,MPI_COMM_WORLD,NULL);
            result += answer;
        }
        printf("MPI SAGT: %5d\n",result);
    }
    else
    {
        int * buffer = malloc(maxQueneSize * sizeof(int32_t));
        MPI_Recv(buffer,maxQueneSize,MPI_INT,0,1,MPI_COMM_WORLD,NULL);
        int result = 0;
        for(int i = 0; i < maxQueneSize; i++)
            result += buffer[i];
        MPI_Send(&result,1,MPI_INT,0,2,MPI_COMM_WORLD);
    }

    MPI_Finalize();


    return EXIT_SUCCESS;
}
