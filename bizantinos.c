#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv)
{
    int size, rank;

    MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size); // numero de procesos de nuestro proyecto
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Identificador de nuestro proyecto

 
  

    

    int action;
    if(rank == 0){
        
        action = 0;
        /*accion que  distinta*/
        int action2 = 1;
        // Enviamos el mensasje de la primer ronda  
        MPI_Send(&action,1, MPI_INT,1,1,MPI_COMM_WORLD);
        MPI_Send(&action2,1, MPI_INT,2,1,MPI_COMM_WORLD);
        int n1;
        // Recibimos el mensaje del nodo 1 
        MPI_Recv(&n1,1,MPI_INT,1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int n2;
        // Recibimos el mensaje del nodo 2
        MPI_Recv(&n2,1,MPI_INT,2,1, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
       // printf("Primera ronda: %i ,%i ",n1,n2);

        //  SEGUNDA RONDA
        // Reportamos a el nodo 1 lo que nos dijo el nodo 2
        MPI_Send(&n2,1, MPI_INT,1,2,MPI_COMM_WORLD);
        // Reportamos al nodo 2 lo que dijo el nodo 1
        MPI_Send(&n2,1, MPI_INT, 2,2, MPI_COMM_WORLD);


        // Recibimos las informacion que nos envio el nodo 2 del nodo 1.
        int n1_1;
        MPI_Recv(&n1_1,1, MPI_INT,2,2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        // Recibimos la informacion que nos envío el nodo 1 del nodo 2
        int n2_1;
        MPI_Recv(&n2_1,1, MPI_INT,1,2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        /*ACCION FINAL DEL NODO O*/
        int action_node0;

        if ((n1 == 1 && n2 == 1) || (n2_1 == 1 && n1_1 ==1)){
            action_node0 = 1;
        }else if ( (n2_1 == 1 && n1 == 1) || (n2 == 1 && n1_1 == 1)){
            action_node0 = 1;
        }else if ((n2 == 1 && n2_1 == 1) || (n1_1 == 1 && n1 == 1)){
            action_node0 = 1;
        }else{  
            action_node0 = 0;
        }

        printf("action node 0 : %i", action_node0);
 

    } else if (rank == 1){
        action = 1;

        // Enviamos el mensasje de la primer ronda primer ronda 
        for(int i = 0; i <= 2; i++){
            if (i != 1){
                 MPI_Send(&action,1, MPI_INT,i,1,MPI_COMM_WORLD);
            }
        }

        int n0 ;
        //Recibimos el mensaje del nodo 0
        MPI_Recv(&n0,1,MPI_INT,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int n2;
        // Recibimos el mensaje del nodo 2
        MPI_Recv(&n2,2,MPI_INT,2,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

        // SEGUNDA RONDA
       
        //Reportamos lo que nos dijo el nodo 0 del nodo 2
        MPI_Send(&n0,1, MPI_INT,2,2,MPI_COMM_WORLD);

        //REPORTAMOS a 0 o lo que nos dijo el nodo 2
        MPI_Send(&n2,1, MPI_INT,0,2,MPI_COMM_WORLD);


        int n2_1;     
        //REcibimos las informacion que nos envio el nodo 0 del nodo 2
        MPI_Recv(&n2_1,1, MPI_INT,0,2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int n0_1;
        //RECIBIMOS la informacion que nos envio el nodo 2 del nodo 0
        MPI_Recv(&n2_1,1, MPI_INT,2,2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        /*ACCION FINAL DEL NODO 1*/
        int action_node1;
        if((n0 == 1 && n2 == 1) || (n2_1 == 1 && n0_1 == 1)){
            action_node1 = 1;
        }else if((n0 == 1 && n2_1 == 1) || (n2 == 1 && n0_1 == 1)){
            action_node1 = 1;
        }else if ((n0 == 1 && n0_1 == 1) || (n2 ==1 && n2_1 == 1)){
            action_node1 = 1;
        }else {
            action_node1 = 0;
        }
    
         printf("action node 1 : %i", action_node1);
      
    
    } else if (rank == 2){
        action =1;
         // Enviamos el mensasje de la primer ronda primer ronda 
        for(int i = 0; i <= 2; i++){
            if (i != 2){
                MPI_Send(&action,1, MPI_INT,i,1,MPI_COMM_WORLD);
            }
        }

        int n0;
        // Recibimos el mensaje del nodo 0
        MPI_Recv(&n0,1,MPI_INT,0,1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int n1;
        // Recibimos el mensaje del nodo 1
        MPI_Recv(&n1,1, MPI_INT,1,1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       // printf("Primera ronda: %i, %i", n0, n1 );

        // SEGUNDA RONDA 
        // reportamos lo que dijo el nodo 0 al nodo 1.
        MPI_Send(&n1,1, MPI_INT,0,2,MPI_COMM_WORLD);
        // REPORTAMOS la información al nodo 1  lo que nos dijo el nodo 0
        MPI_Send(&n0,1, MPI_INT,1,2,MPI_COMM_WORLD);
        
        int n0_1;
        // recibimos lo que nos dijo el nodo 1 del nodo 0
        MPI_Recv(&n0_1,1, MPI_INT,1,2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        int n1_1;
        // Recibimos del nodo 0 lo que dijo el nodo 1 
         MPI_Recv(&n1_1,1, MPI_INT,0,2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       
       // ACCION FINAL DEL NODO 2
        int action_node2; 
        if((n0 ==1  && n1 == 1) || (n0_1 == 1 && n1_1 == 1)){
            action_node2 = 1;
        } else if ((n0 == 1 && n1_1 == 1) || (n1 == 1 && n0_1 == 1)){
            action_node2 = 1;
        } else if ((n0 == 1 && n0_1 == 1) || (n1 == 1 && n1_1)){
            action_node2 = 1;
        }else{
            action_node2 = 0;
        }

         printf("action node 2 : %i", action_node2);
  
    }
    
    // calculamos el resultado 
    MPI_Finalize();
    return 0;
}

