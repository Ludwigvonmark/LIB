#ifndef SNC_H_INCLUDED
#define SNC_H_INCLUDED

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <errno.h>
#include <iostream>



#define MAX_RETRIESS 50

//El semaforo de sincronización se bloquea si no está en 0, el valor del semaforo ha de estar siempre por encima de 0, positivos para bloquear, este es un uso especial del semaforo para sincronización.



class SNC{
    
    union semuns {
    int vals;               /* used for SETVAL only */
    struct semid_ds *bufs;  /* used for IPC_STAT and IPC_SET */
    ushort *arrays;         /* used for GETALL and SETALL */
};

struct semid_ds bufs;
union semuns args;
struct sembuf sbs;

key_t semkey=5800;
int semid;

int nsm;

public:
    SNC(){}
    
SNC(key_t semkeyi,int nsems){
        
        semkey=semkeyi;
//int semid;
struct semid_ds bufs;

union semuns args;
struct sembuf sbs;

sbs.sem_op = -1;
sbs.sem_flg = SEM_UNDO;//

//int nsems=(2);//Numero de semaforos

//sbs.sem_flg = 0;
args.vals = 1;

semid = semget(semkey, nsems, IPC_CREAT | IPC_EXCL | 0666);
 if (semid >= 0) { /* we got it first */
        sbs.sem_op = 1; //sbs.sem_flg = 0;
        args.vals = 1;

        for(sbs.sem_num = 0; sbs.sem_num <nsems; sbs.sem_num++) {
            //do a semop() to "free" the semaphores.
            // this sets the sem_otime field, as needed below.
            if (semop(semid, &sbs, 1) == -1) {
                int e = errno;
                semctl(semid, 0, IPC_RMID); // clean up
                errno = e;
                //return -1; // error, check errno
            }
        }

} else if (errno == EEXIST) { /* someone else got it first */
        int ready = 0;

        semid = semget(semkey, nsems, 0); /* get the id */
        //if (semid < 0) return semid; /* error, check errno */

        /* wait for other process to initialize the semaphore: */
        args.bufs = &bufs;
        for(int i = 0; i < MAX_RETRIESS && !ready; i++) {
            semctl(semid,nsems, IPC_STAT, args);
            if (args.bufs->sem_otime != 0) {
                ready = 1;
            } else {
                sleep(1);
            }
        }
        if (!ready) {
            errno = ETIME;
            //return -1;
        }
    }

//return semid;
        
        
    }

    
void SNCR(int nsm){ //Lee el semaforo dejamdo el proceso bloqueado hasta que se libera el semaforo, se libera cuando su valor es 0
    sbs.sem_flg = SEM_UNDO;//Pausa hasta que se libera el proceso
    //int sen=0;
    sbs.sem_op = 0;//read
sbs.sem_num = nsm;
    if (semop(semid, &sbs, 1) == -1) {
             std::cout<<"SEM READ ERROR"<<std::endl;
        //return 1;
        }//END BLOCK SHM IN
    
}

void SNCB(int nsm){//Bloquea el semaforo de sincronización nsm es el numero del semaforo con el que interacutar
    //int sen=0;
    sbs.sem_flg =IPC_NOWAIT;//No bloquea el proceso    
    sbs.sem_op = 1;//BLOCK SHM IN
    sbs.sem_num = nsm;
    if (semop(semid, &sbs, 1) == -1) {
             std::cout<<"SEM ERROR BLOK"<<std::endl;
        //return 1;
        }//END BLOCK SHM IN
    
}


void SNCF(int nsm){//Libera el semaforo de sincronización 
    
    //EXPERIM son instrucciones para liberar el semaforo,ponerlo a 0, se encuentre donde se encuentre, puede que no sea muy eficiente, pero funciona.
    
    bool fr=false;//EXPERIM
    
        sbs.sem_flg =IPC_NOWAIT; //No bloquea el proceso         
        sbs.sem_op = -1;//FREE SHM IN
        sbs.sem_num =nsm;//Semaforo a liberar
        while(!fr){//EXPERIM
        
    if (semop(semid, &sbs, 1) == -1) {
        //std::cout<<"SEM ERROR FREE"<<std::endl;
        fr=true;//EXPERIM
 
    }
            
        }//EXPERIM
            
}

    
};


#endif // SNC_H_INCLUDED
