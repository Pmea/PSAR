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



class simple:
	public flext_base
{
	// obligatory flext header (class name,base class name)
	FLEXT_HEADER(simple,flext_base)
 
public:
	// constructor
	simple()
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
		FLEXT_ADDMETHOD_(1, "size_seq", m_size_seq);
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

	//useless
	bool present_tuple(int indi){
		for(int i=0; i<seq.size(); i++){
			if(seq.at(i).start == indi && seq.at(i).end == seq.at(i).start ){
				return true;
			}
		}

		return false;
	}
	// quand retourne ton la sequence quand il y en a une ou quand on envoi un bang ?
	void m_analyse(const t_symbol * input_Sym)	
	{
		string s=GetString(input_Sym);

		buff.push_back(atof(s.c_str()));
		
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

		// output value to outlet
		if(tuple_max.end - tuple_max.start >= min_size_seq -1){
			
			ostringstream ss;
			for(int i=tuple_max.start; i< min_size_seq + tuple_max.start; i++){
				ss << buff.at(i);
				ss << " ";
			}
			string patern_found= ss.str();
			ToOutString(0, patern_found.c_str()); 
		}
	}

	void m_bang(const t_symbol *s,int argc,const t_atom *argv){
		//reset all 
		buff.clear();
		seq.clear();

		tuple t={0,0};
		tuple_max= t;

		p=0;
	}
//*

	void m_nothing(const t_symbol *s,int argc,const t_atom *argv){
		ToOutBang(0);
	}


	void m_size_seq(int input_size){
		if( input_size > 0){
			min_size_seq= input_size;
		}
		ToOutInt(0, min_size_seq);
	}
	//*/


private:


	FLEXT_CALLBACK_S(m_analyse)  
	FLEXT_CALLBACK_A(m_bang)
	FLEXT_CALLBACK_A(m_nothing)
	FLEXT_CALLBACK_I(m_size_seq) 

};

// instantiate the class
FLEXT_NEW("simple", simple)

