#include <flext.h>
#include <string>

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;


// check for appropriate flext version
#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif



class analyserythme:
	public flext_base
{
	// obligatory flext header (class name,base class name)
	FLEXT_HEADER(analyserythme,flext_base)
 
public:
	// constructor
	analyserythme()
	{ 

		tuple t={0,0};
		tuple_max= t;

		//seq.push_back(t);

		min_size_seq= 3; 

		p=0;


		// define inlets:
		AddInAnything();  // add one inlet for values
		AddInAnything();  // for parameter

		// define outlets:
		AddOutFloat(); 
		
		FLEXT_ADDMETHOD(0,m_analyse);  // register method (for float messages) "m_float" for inlet 0
		FLEXT_ADDMETHOD(0,m_bang);
		FLEXT_ADDBANG(0,m_bang);	

		FLEXT_ADDMETHOD(1, m_nothing);
		FLEXT_ADDMETHOD_(1, "min_size_seq", m_size_seq);
	}

protected:

	struct tuple{
		int start;
		int end;
	};
	

	vector<float> buff;

	vector<struct tuple> seq;
	int min_size_seq; 
	
	struct tuple tuple_max;

	int p;


// L'algorithme fonctionne, a base de tublee (indice debut, indice fin)
// il n'y a pas de recopie memoire, la seule place prise est celui du buffer des données recues.
void m_analyse(const t_symbol * input_Sym){

		if(tuple_max.end - tuple_max.start + 1 < min_size_seq){

			string s=GetString(input_Sym);

			char* elem= strtok((char*) s.c_str(), " ");
			
			if(tuple_max.end - tuple_max.start + 1 < min_size_seq ){
				while(elem != NULL){
					buff.push_back(atof(elem));

						for(int i=0; i<seq.size(); i++){
							if(buff.at(p) == buff.at(seq.at(i).end + 1)){	
								seq.at(i).end ++;
							}
							if( (seq.at(i).end - seq.at(i).start) > (tuple_max.end - tuple_max.start)){
								tuple_max= seq.at(i);
							}
						}
						for(int i=0; i< p; i++){
							if(buff.at(i) == buff.at(p)){
								tuple t={i, i};
								seq.push_back(t);
							}
						}

						p++;
					
					elem= strtok(NULL, " ");

					/*
					si on veut un message strictement de taille min_size_seq
					if(tuple_max.end - tuple_max.start >= min_size_seq -1)
						break;
					*/
				}
			}

			// output value to outlet
			if(tuple_max.end - tuple_max.start + 1 >= min_size_seq){

				ostringstream ss;
				for(int i=tuple_max.start; i< tuple_max.start + min_size_seq ; i++){
					ss << buff.at(i);
					ss << " ";
				}

				string patern_found= ss.str();
				ToOutString(0, patern_found.c_str()); 
			}
	}
}
	
	// si on recoi un bang a droite on vide les buffers, on reinitialiser la recherche
	void m_bang(const t_symbol *s,int argc,const t_atom *argv){
		//reset all 
		buff.clear();
		seq.clear();

		tuple t={0,0};
		tuple_max= t;

		p=0;
	}

	void m_nothing(const t_symbol *s,int argc,const t_atom *argv){
		ToOutBang(0);
	}

	// si on recoi un nombre a droite, on change la timme min du motif a detecter
	// on ne vide pas les buffers
	// ATTENTION: si on diminue la taille de la sequence. Le programme peut deja avoir trouvé
	// un sequence de la nouvelle taille (il l'envera la prochaine fois que l'on fera appel a m_analyse)
	void m_size_seq(int input_size){
		if(input_size <= 1){
			ToOutString(0, "Error: sequence must have 2 minimun");
			return;
		}

		m_bang(NULL, 0, NULL);

		if( input_size > 0){
			min_size_seq= input_size;
		}
		ToOutInt(0, min_size_seq);
	}


private:

	FLEXT_CALLBACK_S(m_analyse)  
	FLEXT_CALLBACK_A(m_bang)
	FLEXT_CALLBACK_A(m_nothing)
	FLEXT_CALLBACK_I(m_size_seq) 

};

// instantiate the class
FLEXT_NEW("analyserythme", analyserythme)

