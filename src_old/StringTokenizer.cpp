#include <string.h>
#include "StringTokenizer.h"

using namespace MeshLib;

StringTokenizer::StringTokenizer( char * buffer, const char * seperator )
{

	char * pStr = NULL;

	int str_len = (int)strlen( buffer    );

	if( str_len == 0 ) return;

	pStr = buffer;

	for( int i = 0; i < str_len; i ++ )
	{
		char c = buffer[i];

		if( strchr( seperator, c ) )
		{
			buffer[i] = 0;
			m_tokens.Append( pStr );
			pStr = buffer+i+1;
		}
	
	}

	m_tokens.Append( pStr );
}

StringTokenizer::~StringTokenizer(){}

List<char> & 
StringTokenizer::tokens()
{
	return m_tokens;
}