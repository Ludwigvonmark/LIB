//LIB DEBUGGER
#include <math.h>
#include <unistd.h>
#include "vector"
#include <limits>
#include <sys/wait.h>

#include "LINUX/DPR.h"
#include "NET/CLD.hpp"
#include "LINUX/MPR.hpp"
#include "FDR.hpp"
#include "PARSR/CSV.hpp"
#include "DBGU.hpp"

int main (int argc, char* argv[]){
   std::vector<std::string> comandos;
   std::vector<bool>MODE={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
if (argc > 1) {//Existen argumentos

for (int i = 1; i < argc; ++i){//Pasa los arguemtnos a la memoria compartida mediante el string INST
  // INST+=std::string()+argv[i]+" ";
    comandos.push_back(argv[i]);
    if((comandos[i-1]==("-S"))||(comandos[i-1]==("-s"))){
                MODE[0]=1;
                //Server mode
    }
    else if((comandos[i-1]==("-C"))||(comandos[i-1]==("-c"))){
                MODE[1]=1;
                //Server mode
    }
}    
}
/*DATE TIME;
DATE CT;*/

/*CRN CR;
CR.STRT();*/

MPR MPSIS;
CSV CSV_PARS;

/*CT.ST(0);
CT.GT();
long timelapse=86400;
long ctt=(long)ceil((CT.RTE()/timelapse));
CT.ST(CT.RTE());*/
//std::cout<<"HI"<<std::endl;
std::cout<<GCC_VERSION<<std::endl;

//std::cout<<" Current day: "<<ctt<<"Current time:"<<TIME.RTS()<<std::endl;

if(MODE[0]){//Server mode
   
   // CDO CLOUD(true);
   // CLOUD.SERV();
    FDR CLOU_S(true,true);
    std::cout<<"SERVER "<<std::endl;

}

else if (MODE[1]){//Client mode
    FDR CLOU_C(true,false);
    std::string fts="NEW FILE CREATED \nFOR TEST PORPOSES.";
    CLOU_C.SF("TEST_FILE.test",fts);
    CLOU_C.LF("TEST_FILE.test");
    std::cout<<"The recived file contains:"<<std::endl<<CLOU_C.DATA<<std::endl;
    CLOU_C.PH(".");//Closes the conection
    std::cout<<"The recived PATH contains:"<<std::endl<<CLOU_C.DATA<<std::endl;
    CSV_PARS.DEC(CLOU_C.DATA);
    DBG_STD(CSV_PARS.ADATA);
    CLOU_C.DL("TEST_FILE.test");//Closes the conection

/*NET SRV(NET_TYPE::TCP_CLT);
    SRV.TCP_CLT("192.168.1.142","Data that the client sends");
    std::cout<<"DATA FROM Server: "<<SRV.DR<<std::endl;*/
}

   /* if(MPSIS.PRN()==1){    
        return 1;
    }

std::cout<<TIME.RTS();
TIME.ST("2030-11-10");
std::cout<<TIME.RTS();
std::cout<<TIME.RTE();
std::cout<<std::endl;

CR.STP();
std::cout<<CR.LPS();
std::cout<<std::endl;
*/
    /*std::string fts="LOCAL FILE \nTEST PORPOSES.";
    LOCAA.SF("TESTLOCAL_FILE.test",fts);
    LOCAA.LF("TESTLOCAL_FILE.test");
    std::cout<<"file contains:"<<std::endl<<LOCAA.DATA<<std::endl;
    LOCAA.PH(".");//Closes the conection
    std::cout<<"PATH contains:"<<std::endl<<LOCAA.DATA<<std::endl;
    LOCAA.DL("TESTLOCAL_FILE.test");//Closes the conection*/

  return 0;
}
