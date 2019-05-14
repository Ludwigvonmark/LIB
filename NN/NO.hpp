#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

//Neuroal objects lib JLMF 2016 Oviedo V1.2
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream> //cout,cin

class Ne{//Input neuron type
    double D;//Input data
public:
    double NFRW(double d){
        D=d;
        return D;
    }
};

class Ns{//Outup neuron type
    std::vector<double> D;//Datos que entran por las sinapsis
	std::vector<double> W;//Peso de las sinapsis entrantes
	
    double SMTR_I_W = 0;//Sumatorio del producto de datos de entrada por sus respectivos pesos    
    double ActivFunc = 0;//Resultado de la función de activación
    
    void INs(std::vector<double> w, std::vector<double> d) {//Actualiza los datos y los pesos de entrada a la neurona

		//D.clear();
		//W.clear();
        D=d;
        W=w;

		/*for (unsigned int i = 0; i < INid.size(); i++) {
			D.push_back(d[INid[i]]);
			W.push_back(w[INid[i]]);
		}*/
	}
	
	/*void OUTs() {
        SMTR_I_W = 0;
        for (unsigned int i = 0; i < D.size(); i++) {
            //SMTR_I_W += D[i] * W[i];
            SMTR_I_W += D[i];
            //debug
            //std::cout << "SMTR_I_W:" << SMTR_I_W << ", ";
            //debug
        }
        SMTR_I_W = SMTR_I_W/D.size();
       
	}*/
        void OUTs() {
        SMTR_I_W = 0;
        for (unsigned int i = 0; i < D.size(); i++) {
            SMTR_I_W += D[i] * W[i];
            //debug
            //std::cout << "SMTR_I_W:" << SMTR_I_W << ", ";
            //debug
        }
        ActivFunc = (double)1 / (double)(1 + exp(-SMTR_I_W));//Una vez obtenida la salida de la neurona se a de traspasar al vector de datos de la red para ser obetnidos por las siguientes neuronas
		    //debug
			//std::cout << "ActivFunc:" << ActivFunc << ", ";
			//debug
	}
        
	
	public:
        
            double NFRW(std::vector<double> w, std::vector<double> d) {
		INs(w,d);
		OUTs();
            return SMTR_I_W;
}
};

class NiNs {//Neurona interna numérica estandar.

    std::vector<double> D;//Datos que entran por las sinapsis
	std::vector<double> W;//Peso de las sinapsis entrantes
    
    double SMTR_I_W = 0;//Sumatorio del producto de datos de entrada por sus respectivos pesos    
    double ActivFunc = 0;//Resultado de la función de activación

    void INs(std::vector<double> w, std::vector<double> d) {//Actualiza los datos y los pesos de entrada a la neurona
        D=d;
        W=w;
		/*D.clear();
		W.clear();

		for (unsigned int i = 0; i < INid.size(); i++) {
			D.push_back(d[INid[i]]);
			W.push_back(w[INid[i]]);
		}*/
	}

    void OUTs() {
        SMTR_I_W = 0;
        for (unsigned int i = 0; i < D.size(); i++) {
            SMTR_I_W += D[i] * W[i];
            //debug
            //std::cout << "SMTR_I_W:" << SMTR_I_W << ", ";
            //debug
        }
        ActivFunc = (double)1 / (double)(1 + exp(-SMTR_I_W));//Una vez obtenida la salida de la neurona se a de traspasar al vector de datos de la red para ser obetnidos por las siguientes neuronas
		    //debug
			//std::cout << "ActivFunc:" << ActivFunc << ", ";
			//debug
	}
	
public:
    
	double NFRW(std::vector<double> w, std::vector<double> d) {
		INs(w,d);
		OUTs();
        return ActivFunc;
	}

	/*NiNs() {//Constructor de la neurona

	}

	~NiNs() {//Desctructor de la neurona
		D.clear();//Datos que entran por las sinapsis
		W.clear();//Peso de las sinapsis entrantes
	}*/
};

class NbNs{//Neurona de tipo baipas numérica estandar
    
};

class NN {//Red Neural
public:
	//Datos de la red neural
	std::vector<int> T;//Topologia de la red, siendo (0)el numero de entradas y (end) el numero de salidas.
	std::vector<double> W;//Uniones entre neuronas,//el numero de weights es igual a las conexiones entre neuronas, es decir://sinapsis de entradas y salidas mas sumatorio(desde i=3 a i=numero de elementos en el vector topolog-1) de i*(i-1)
	std::vector<double> D;//Datos de las sinapsis, los n primeros corrsponden a las n entradas y los m Ãºltimos a las m salidas	//Las demas sinapsis estan ordenadas de forma de primera neurona del grupo anterior a la primera del siguiente,	//la primera del grupo anterior a la segunda del siguiente,etc...

	std::vector<std::vector<int>>IidS;//vector que contiene los ids de las sinapsis de entrada de cada neurona... [idNeurona][idsI]
	std::vector<std::vector<int>>OidS;//vector que contiene los ids de las sinapsis de salida de cada neurona... [idNeurona][idsO]

	int nN = 0;//NÃºmero total de neuronas
	int nS = 0;//NÃºmero total de sinapsis

	int nINs = 0;//Número de entradas
	int nOUTs = 0;//Número de salidas

	NiNs IC;//Neurons of the internal cortex
    Ne EIC;//Neurons of the external input cortex
    Ns EOC;//Neurons of the external output cortex

	std::vector<double> NNOUT;//Vector con las salidas ordenadas de la red neural
	
	std::vector<Ne> NeV;
        std::vector<Ns> NsV;
        std::vector<NiNs> NiNsV;
        std::vector<NbNs> NbNsV;
        
        bool errF=false;
        

	void SIDs() {//crea los datos de ids necesarios apartir de la topologÃ­a

            std::vector<int>t;
            IidS.clear();
            OidS.clear();

            nS = T[0] + T[T.size() - 1];//calcula el nÃºmero de sinapsis,
            nN = T[0];// cacluar el nÃºmero de neuronas,
            for (unsigned int i = 1; i < T.size(); i++) {
                    nS += T[i] * T[i - 1];
                    nN += T[i];
            }//fin del calculo del numero de sinapsis y nÃºmero de neuronas

            for (int y = 0; y < nS; y++) {//inicializa los vectores de ids
                    IidS.push_back(t);
                    OidS.push_back(t);
            }

            for (int neur = 0; neur < nN; neur++) {//Iterador que se repite el numero de neuronas, ofreciendo ids de 0 a n-1 neuronas
                    //int nte = nN - (neur + 1);//Calcula el numero de neuronas despues de la neurona actual
                    int topolID = 0;//Componente del vector de topologia donse se encuentra la neurona
                    int InterTopID = 0;//nÃºmero de neuronas despues de la actual dentro del mismo nivel de topologia.

                    int NsI = 0;//numero de sinapsis de entrada de la neurona actual
                    int NsO = 0;//numero de sinapsis de salida de la neurona actual

                    for (unsigned int i = 0; i < T.size(); i++) {//Buscar en que componente de la topologia se encuentra la neurona actual e insertarlo en topolID "0=>n"
                            topolID += T[i];
                            if (topolID - 1 >= neur) {
                                    topolID = i;
                                    break;
                            }
                    }




                    for (int i = 0; i < topolID; i++) {//Calcula el InterTopID, el ID de la neurona dentro de la capa de la topologia actual "arriba a abajo, de 0 a n-1"
                            InterTopID += T[i];
                    }
                    InterTopID = std::abs(InterTopID - neur);





                    if (topolID == 0) {//CÃ¡lculo del numero de salidas y entradas
                            NsI = 1;
                            NsO = T[topolID + 1];
                    }
                    else if (topolID == T.size() - 1) {
                            NsI = T[topolID - 1];
                            NsO = 1;
                    }
                    else {
                            NsI = T[topolID - 1];
                            NsO = T[topolID + 1];
                    }

                    IidS[neur].assign(NsI, 0);
                    OidS[neur].assign(NsO, 0);




                    for (int i = 0; i < topolID; i++) {//calcula el id de la primera sinapsis de entrada
                            if (i == 0) { IidS[neur][0] += T[i]; }
                            else if (i == T.size() - 1) { IidS[neur][0] += T[i]; }
                            else { IidS[neur][0] += T[i] * T[i - 1]; }
                    }
                    IidS[neur][0] += (InterTopID);

                    if (topolID == T.size() - 1) {

                            OidS[neur][0] = nS - (T[T.size() - 1] - InterTopID);

                    }


                    else {
                            for (int i = 0; i <= topolID; i++) {//calcula el id de la primera sinapsis de entrada
                                    if (i == 0) { OidS[neur][0] += T[i]; }
                                    else if (i == T.size() - 1) { OidS[neur][0] += T[i]; }
                                    else { OidS[neur][0] += T[i] * T[i - 1]; }
                            }
                            OidS[neur][0] += (InterTopID*T[topolID + 1]);
                    }




                    if (topolID != 0) {
                            for (int i = 1; i < NsI; i++) {
                                    IidS[neur][i] = (IidS[neur][0] + (i*T[topolID]));
                            }
                    }



                    if (topolID != T.size() - 1) {
                            for (int i = 1; i < NsO; i++) {
                                    OidS[neur][i] = (OidS[neur][0] + i);
                            }
                    }


                   /* //debugg//Parte correcta
                    std::cout << "ID Neurona : " << neur << " ";
                    for (int de = 0; de < IidS[neur].size(); de++){ std::cout << "ID Sinapsis entrada : " << IidS[neur][de] << " ";}
                    for (int de = 0; de < OidS[neur].size(); de++) { std::cout << "ID Sinapsis salida : " << OidS[neur][de] << " "; }
                    std::cout << std::endl;
                    //debugg*/
            }

            NNOUT.clear();
            NNOUT.assign(T[T.size()-1], 0);
	}

    void INN(std::vector<int> t, std::vector<double> w) {//Constructor basado en datos ya generados
		T = t;
		W = w;
		D.assign(W.size()+T[0]+T[T.size()-1], 0);
		SIDs();

		//SNE = NEiNs();
	}
	
	NN() {
            IC = NiNs();
            EIC=Ne();
            EOC=Ns();
            
        }

	NN(std::vector<int> t, std::vector<double> w) {//Constructor basado en datos ya generados
        INN(t,w);
        
            IC = NiNs();
            EIC=Ne();
            EOC=Ns();
	}
	
	~NN() {//Destructor
		/*T.clear();
		W.clear();
		D.clear();*/
	}
		
	void UD(std::vector<double>d){//Updatea los datos de entrada
        for(int i=0;i<T[0];i++){
            D[i]=d[i];
        }
    }
	
	void FRW() {//Pasa datos por la red neuronal y acturaliza el vector de datos neuronales incluidas todas las sinapsis
        double tOd;//Temporal output data
                     
        std::vector<double> td;
        std::vector<double> tw;
        
		for (int i = 0; i < T[0]; i++) {//Tratamiento de datos de entrada
                tOd=EIC.NFRW(D[i]);
                for(int e=0;e<OidS[i].size();e++){
                    D[OidS[i][e]] = tOd;
                }
			}


		for (int j = T[0]; j < nN-T[T.size()-1]; j++) {//Tratamiento de datos de la corteza interna
            td.clear();
            tw.clear();
            
            for (unsigned int i = 0; i < IidS[j].size(); i++) {
                td.push_back(D[IidS[j][i]]);
                tw.push_back(W[IidS[j][i]-T[0]]);
                }
            
            tOd=IC.NFRW(tw, td);
			for (int i = 0; i < OidS[j].size(); i++) {
				D[OidS[j][i]] =tOd;
			}
		}
		
		
		for(int t=nN-T[T.size()-1];t<nN;t++){//Tratamiento de datos de salida
                        td.clear();
            tw.clear();
            
            for (unsigned int i = 0; i < IidS[t].size(); i++) {
                td.push_back(D[IidS[t][i]]);
                tw.push_back(W[IidS[t][i]-T[0]]);
                }
            tOd=IC.NFRW(tw, td);
           /* if(tOd>1){
                std::cout<<"Posible NN error: NNOUT>1"<<std::endl;
                errF=true;
                
            }
            else errF=false;*/
            D[OidS[t][0]] =tOd;
            NNOUT[t-(nN-T[T.size()-1])]=tOd;
        }
		
            
		/*//debug
		std::cout << "W: ";
		for (int ww = 0; ww < W.size(); ww++) {
			std::cout << W[ww] << ", ";
		}std::cout << std::endl;

		std::cout << "D: ";
		for (int dd = 0; dd < D.size(); dd++) {
			std::cout << D[dd] << ", ";
		}std::cout << std::endl << std::endl << std::endl << std::endl;
		//debug*/
	}
	
	std::vector<double>RNOD(){//Retuen neural output data
        return NNOUT;
    }
	

};

class NNN {//Red neural de redes neurales, especialmente eficaz en multiproceso,implementaciÃ³n en OpenCL ,implementaciÃ³s en FPGAs ..., Ãºltima parte a desarrollar.


};

#endif
