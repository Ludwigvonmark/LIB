#ifndef SML_H_INCLUDED
#define SML_H_INCLUDED

//Libreria de memoria compartida//LINUX_UNIX_POSIX

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


#define MAX_RETRIES 10

class SMLL{
    
    union semun {
    int val;               /* used for SETVAL only */
    struct semid_ds *buf;  /* used for IPC_STAT and IPC_SET */
    ushort *array;         /* used for GETALL and SETALL */
};



int AXSMIDd;
char *AXSHMd;
char *AXSMSd;

struct semid_ds buf;
union semun arg;
struct sembuf sb;

int idse;
int idsmd;

public:
int AXSMZd= 729;//Size in bites of the shared memory space

bool SB=false;//Bloqueo de seguridad, para aplicaciones en las que predomine la seguridad, y la integridad de los datos

//char AXSM [729];
    std::string AXSM;
    
key_t smkey; 
key_t semkey;

SMLL(){}
    
    SMLL(key_t smkeyi,int AXSMZdi){//Llave de la memoria y espacio de la memoria compartida
        
        smkey=smkeyi;
        AXSMZd=AXSMZdi;
        
        //Shared memori init
        AXSMIDd=shmget(smkey,AXSMZd,IPC_CREAT | 0666);
    if(AXSMIDd<0){
        std::cerr<<"semget1";
        exit(1);
        }



AXSHMd=(char*)shmat(AXSMIDd,0,0);
   if(AXSHMd==(char*)-1){
std::cerr<<"shmat1";
        exit(1);
}

idsmd=AXSMIDd;
        



//Semaphore init
semkey=smkeyi-2000;


int semid;
struct semid_ds buf;

union semun arg;
struct sembuf sb;

sb.sem_op = -1;
sb.sem_flg = /*SEM_UNDO;*/IPC_NOWAIT;

//sb.sem_flg = 0;
arg.val = 1;

semid = semget(semkey, 1, IPC_CREAT | IPC_EXCL | 0666);
 if (semid >= 0) { /* we got it first */
        sb.sem_op = 1; //sb.sem_flg = 0;
        arg.val = 1;

        for(sb.sem_num = 0; sb.sem_num < 1; sb.sem_num++) {
            //do a semop() to "free" the semaphores.
            // this sets the sem_otime field, as needed below.
            if (semop(semid, &sb, 1) == -1) {
                int e = errno;
                semctl(semid, 0, IPC_RMID); // clean up
                errno = e;
                //return -1; // error, check errno
            }
        }

} else if (errno == EEXIST) { /* someone else got it first */
        int ready = 0;

        semid = semget(semkey, 1, 0); /* get the id */
        //if (semid < 0) return semid; /* error, check errno */

        /* wait for other process to initialize the semaphore: */
        arg.buf = &buf;
        for(int i = 0; i < MAX_RETRIES && !ready; i++) {
            semctl(semid, 1, IPC_STAT, arg);
            if (arg.buf->sem_otime != 0) {
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

idse=semid;


    }
    
    
    void R(){
int sen=0;
int AXSMi=0;
AXSM.clear();

if(SB){ sb.sem_flg = SEM_UNDO;}//Espera para acceder
else{sb.sem_flg = IPC_NOWAIT;}//No espera para acceder

sb.sem_op = -1;//BLOCK SHM IN
sb.sem_num = sen;
    if (semop(idse, &sb, 1) == -1) {
            // std::cout<<"SEM NO AVALIABLE\n";
        //return 1;
        }//END BLOCK SHM IN

else{

//READ SHARED INPUT
for(AXSMSd=AXSHMd;*AXSMSd!=0;AXSMSd++){
AXSM+=*AXSMSd;
}


//if(SB){ sb.sem_flg = SEM_UNDO;}//Espera para acceder
//else{sb.sem_flg = IPC_NOWAIT;}//No espera para acceder

  sb.sem_op = 1;//FREE SHM IN
sb.sem_num =sen;
    if (semop(idse, &sb, 1) == -1) {
        perror("semop");
        exit(1);
    }//END FREE SHM IN

}

        
    }
    
    void W(std::string data){
       // void WSMD(char data[729],int sdid, int seid){
//AXIS SHARED WRITE
int sen=0;
union semun arg;
struct sembuf sb;

if(SB){ sb.sem_flg = SEM_UNDO;}//Espera para acceder
else{sb.sem_flg = IPC_NOWAIT;}//No espera para acceder

sb.sem_op = -1;
sb.sem_num = sen;
    if (semop(idse, &sb, 1) == -1) {
        //std::cout<<"SEM NO AVALIABLE\n";

        }
        else{

//std::memcpy(AXSHMd,data,AXSMZd);
            strncpy(AXSHMd,data.c_str(),AXSMZd);
 AXSMSd=AXSHMd;
 AXSMSd+=AXSMZd;
  *AXSMSd=0;
  
  //if(SB){ sb.sem_flg = SEM_UNDO;}//Espera para acceder
//else{sb.sem_flg = IPC_NOWAIT;}//No espera para acceder

sb.sem_op = 1;//FREE SHM OUT
sb.sem_num = sen;

    if (semop(idse, &sb, 1) == -1) {
         //std::cout<<"SEM NO AVALIABLE\n";
        //return 1;
        }//END FREE SHM OUT

        }

//END AXIS SHARED  WRITE
}
        
    
    
    
};




#endif // SML_H_INCLUDED
