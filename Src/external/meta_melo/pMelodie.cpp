/*
This object is write by Pierre Mahe (mahe.pierre@live.fr)
during the DASS projet.
For any information please contact him
*/
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>


#include <stdlib.h>
#include <string.h>

#include <flext.h>

#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif

using namespace std;

class pMelodie:

		int approx=10; 


	public flext_base{
		FLEXT_HEADER(pMelodie, flext_base)
	
	public: 
		pMelodie(){
			AddInAnything("Bang or List");
			AddInList();
			AddOutList();

			FLEXT_ADDMETHOD_(0, "list", m_process);
			FLEXT_ADDBANG(0, m_bang);

			FLEXT_ADDMETHOD_(0, "round", m_approx);


		}

	protected:
		void m_process(t_symbol *input){
		// la fonction de processing 
			// initialisation valeur
			char* listIn= (char *) GetString(input);
			vector<float> listValeur; 

			char* subArray= strtok(listIn, " ");
			int compt=0;
			float nbApprox;
			while(subArray != NULL){
				if(compt %2 != 0){
					nbApprox= atof(subArray) / approx;
					nbApprox= round(nbApprox);
					nbApprox= nbApprox * approx;
 				}
 				else
 					nbApprox= atof(subArray);

				listValeur.push_back(nbApprox);

				subArray= strtok(NULL, " ");
				compt ++;
			}

			// reecriture des valeurs

			// recherche du max des temps
			int max=0;
			for(int i=1; i<listValeur.size(); i=i+2){
				if(max< listValeur.at(i)){
					max= listValeur.at(i);
				}
			}

			for(int i=1; i<listValeur.size(); i=i+2){
				listValeur.at(i)= listValeur.at(i) / max;
			}

			// transformation char* des valeurs
			stringstream ss;
			for(int i=0; i<listValeur.size(); i++){
				ss << listValeur.at(i);
				ss << " ";
			}
			string result= ss.str();
			const char *c_result= result.c_str();

			ToOutString(0, c_result);
			//ToOutInt(0, max);
		}

		void m_bang(){
			// la fonction pour tester le bang 
			ToOutBang(0);
		}

		void m_approx(int input){
			approx=input;
			ToOutInt(0, approx);
		}

	private:
		FLEXT_CALLBACK_S(m_process);
		FLEXT_CALLBACK(m_bang);
		FLEXT_CALLBACK_I(m_approx);
	};


FLEXT_NEW("pMelodie", pMelodie);
