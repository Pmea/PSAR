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


		// define inlets:
		AddInAnything();  // add one inlet for values

		// define outlets:
		AddOutInt(); 
		
		FLEXT_ADDMETHOD(0,m_unpack);
		FLEXT_ADDMETHOD(0, m_nothing);
	}

protected:

	
	// quand retourne ton la sequence quand il y en a une ou quand on envoi un bang ?
	void m_unpack(const t_symbol * input_Sym)	
	{
		string s=GetString(input_Sym);

		/*
			On recupere une list char on fait un strtok avec " " et on fait un struc de atoi  
		*/
		char* tmp= strtok((char*) s.c_str(), " ");

		ostringstream ss;
		while(tmp != NULL){
			ss << (char) atoi(tmp);
			
			tmp= strtok(NULL, " ");
		}
		string out= ss.str();
		ToOutString(0, out.c_str());
	
	}

	void m_nothing(const t_symbol *s,int argc,const t_atom *argv){
		ToOutBang(0);
	}

private:


	FLEXT_CALLBACK_S(m_unpack)  
	FLEXT_CALLBACK_A(m_nothing)
};

// instantiate the class
FLEXT_NEW("arduinoUnPack", arduinoUnPack)

