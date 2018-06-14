#ifndef _MESHLIB_STRING_TOKENIZER_H_
#define _MESHLIB_STRING_TOKENIZER_H_

#include <stdlib.h>
#include "SList.h"

namespace MeshLib
{
	
	class StringTokenizer
	{
	public:
		StringTokenizer( char * buffer, const char * seperator );
		~StringTokenizer();
		
		List<char> & tokens();
	private:
		List<char>   m_tokens;
	};
	
} //end name space
#endif
