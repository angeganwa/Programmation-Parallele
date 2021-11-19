#include <stdio.h>
#include <mpi.h>
#include <time.h>
  
// Ce code effectue la somme des elements d'un vecteur de maniere parallel
	int main(int argc,char* argv[]){
         double t1, t2; 
        t1 = MPI_Wtime(); 

        t2 = MPI_Wtime();

	    int rank, size, start, end;
	    int tab[] = {1, 2, 3, 4, 5, 6, 7};
	    size_t tabSize = sizeof(tab)/sizeof(tab[0]);
	    int som = 0;
	    int somTotal = 0;

	    MPI_Init(NULL, NULL);
	    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	    MPI_Comm_size(MPI_COMM_WORLD, &size);
       
	    start = rank * (tabSize/size);
	    if(rank == size - 1){
		end = tabSize - 1;
	    }else{
		end = start + (tabSize/size) -1;
	    }
	    for(int i = start; i <= end; i++){
		som = som + tab[i];
	    }
	    MPI_Reduce(&som ,&somTotal ,1 ,MPI_INT ,MPI_SUM ,0 , MPI_COMM_WORLD);
      printf( "Elapsed time is %f\n", t2 - t1 ); 

	    printf("\n rank: %d, som: %d,somTotal: %d\n", rank, som, somTotal);
	     
	    MPI_Finalize();
	    return 0;
	}
