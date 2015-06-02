#include <flext.h>
#include <string>

#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;


// check for appropriate flext version
#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 400)
#error You need at least flext version 0.4.0
#endif



class arduinoPack:
	public flext_base
{
	// obligatory flext header (class name,base class name)
	FLEXT_HEADER(arduinoPack,flext_base)
 
public:
	// constructor
	arduinoPack()
	{ 

		sep= ';';
		
		// define inlets:
		AddInAnything();  // add one inlet for values

		// define outlets:
		AddOutInt(); 
		
		FLEXT_ADDMETHOD(0,m_pack);
		FLEXT_ADDMETHOD(0, m_nothing);
	}

protected:

	
	// retourne un symbol avec le code ascii + sep (en code ascii)
	void m_pack(const t_symbol * input_Sym)	
	{
		string s=GetString(input_Sym);
		const char* tab= new char[s.length()+1];
		tab=s.c_str();

		ostringstream ss;
		for(int i=0; i<s.length(); i++){
			ss << (int) tab[i];
			ss << " ";
		}
		ss << (int) sep;
		string out= ss.str();
		ToOutString(0, out.c_str()); 
	}

	// pour tous les autres types que les symbols
	void m_nothing(const t_symbol *s,int argc,const t_atom *argv){
		ToOutBang(0);
	}

private:
	char sep;

	//callback pour symbol
	FLEXT_CALLBACK_S(m_pack)
	//callback pour le reste  
	FLEXT_CALLBACK_A(m_nothing)
};

// instantiate the class
FLEXT_NEW("arduinoPack", arduinoPack)

