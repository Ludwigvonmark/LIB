#ifndef DA_H_INCLUDED
#define DA_H_INCLUDED

//Neuroal objects lib

#include <fstream>
#include <string>

#include <algorithm>

#include <iostream> //cout,cin


class DA {//Data administrator
public:

	std::vector<double> ALLTD;
	std::vector<double> TIN;
	std::vector<double> TOUT;

	std::fstream TData;

	std::vector<int> topologia;
	std::vector<double> pesos;

	std::ofstream SConf;

	std::vector<int> ReceoveredTopologie;
	std::vector<double> ReceoveredWeights;

	std::fstream OConf;

	int deb = 0;


	DA(int i) {
		deb = i;
	}

	DA() {
	}

	void Destr() {//No puedo usar el destructor predefinido porque da error en la clase de entrenamiento al definirlo
		ALLTD.clear();
		TIN.clear();
		TOUT.clear();

		topologia.clear();
		pesos.clear();

		ReceoveredTopologie.clear();
		ReceoveredWeights.clear();
	}

	void SW(std::vector<int> topolog, std::vector<double> weights) {//Guarda en un archivo la configuración actual de la red neural

		SConf.open("NND.nnd");
		if (SConf.is_open()) {
			//myfile << "Writing this to a file.\n";
			for (unsigned int i = 0; i< topolog.size(); i++) {

				SConf << topolog[i] << ",";
			}
			SConf << std::endl;

			for (unsigned int i = 0; i< weights.size(); i++) {
				SConf << weights[i] << ",";
			}
			SConf << std::endl;
		}
		SConf.close();
	}

	void LW() {//Carga la configuración de una red neural en el programa


		int lineID = 0;

		OConf.open("NND.nnd", std::ios::in);
		if (OConf.is_open())
		{
			std::cout << "Found previous Config." << std::endl;
			std::string line = "";

			//read data
			while (!OConf.eof())
			{
				getline(OConf, line);

				std::string delimiter = ",";

				size_t pos = 0;
				std::string token;
				while ((pos = line.find(delimiter)) != std::string::npos) {
					token = line.substr(0, pos);
					if (lineID == 0) { ReceoveredTopologie.push_back(std::stod(token)); }
					else if (lineID == 1) { ReceoveredWeights.push_back(std::stod(token)); }
					//std::cout << token << std::endl;

					line.erase(0, pos + delimiter.length());
				}
				//std::cout << line << std::endl;
				lineID += 1;
			}

		}

		SConf.close();

		std::cout << "RecoveredTopolog=";
		for (unsigned int i = 0; i < ReceoveredTopologie.size(); i++) { std::cout << ReceoveredTopologie[i] << ": "; }std::cout << ReceoveredTopologie.size() << std::endl;

		std::cout << "RecoveredWeights=";
		for (unsigned int i = 0; i < ReceoveredWeights.size(); i++) { std::cout << ReceoveredWeights[i] << ": "; }std::cout << ReceoveredWeights.size() << std::endl;
	}

	void LTD() {
		TData.open("TRD.ntd", std::ios::in);
		if (TData.is_open())
		{
			std::string line = "";

			//read data
			while (!TData.eof()) {
				getline(TData, line);
				std::string delimiter = ",";

				size_t pos = 0;
				std::string token;
				while ((pos = line.find(delimiter)) != std::string::npos) {
					token = line.substr(0, pos);
					ALLTD.push_back(std::stod(token));
					//std::cout << token << std::endl;
					line.erase(0, pos + delimiter.length());
				}
				//std::cout << line << std::endl;
			}
		}
		TData.close();

		//std::cout << "Training data=";
		//for (int i = 0; i < ALLTD.size(); i++) { std::cout << ALLTD[i] << ": "; }std::cout << ALLTD.size() << std::endl;
	}
};

#endif
