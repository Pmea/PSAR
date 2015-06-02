#include <flext.h>
#include <string>
#include <vector>

#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;


// check for appropriate flext version
#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif



class arduinoUnPack:
	public flext_base
{
	// obligatory flext header (class name,base class name)
	FLEXT_HEADER(arduinoUnPack,flext_base)
 
public:
	// constructor
	arduinoUnPack()
	{ 

		sep= ';';

		// define inlets:
		AddInAnything();  // add one inlet for values

		// define outlets:
		AddOutInt(); 
		
		FLEXT_ADDMETHOD(0,m_unpack);
		FLEXT_ADDMETHOD(0, m_nothing);
	}

protected:

	
	// on stock les identifiants jusqu'a avoir un separateur, et on renvoi
	// on peut donc envoyer caractere par caractere ou une chaine entiere
	void m_unpack(const t_symbol * input_Sym)	
	{
		string s=GetString(input_Sym);

		/*
			On recupere une list char on fait un strtok avec " " et on fait un struc de atoi  
		*/
		char* tmp= strtok((char*) s.c_str(), " ");

		while(tmp != NULL){

			if((char) atoi(tmp) == sep){
				ostringstream ss;
				for(int i=0; i<msg.size(); i++){
					ss << msg.at(i);
				}
				string out= ss.str();
				ToOutString(0, out.c_str());
				msg.clear();
			}
			else{
				msg.push_back((char) atoi(tmp));
			}
			tmp= strtok(NULL, " ");
		}
	}

	void m_nothing(const t_symbol *s,int argc,const t_atom *argv){
		ToOutBang(0);
	}

private:

	// le message en cours
	vector<char> msg;

	char sep;

	//si on recoi un symbol
	FLEXT_CALLBACK_S(m_unpack)
	//si on recoi un autre symbol  
	FLEXT_CALLBACK_A(m_nothing)
};

// instantiate the class
FLEXT_NEW("arduinoUnPack", arduinoUnPack)

