#include "OBJFileReader.h"
#include "StringTokenizer.h"
#include "SolidDelegate.h"
#include <list>		//list of std

using namespace MeshLib;


OBJFileReader::OBJFileReader ()
{
	vID = 0;
	fID = 0;
}
		

OBJFileReader::~OBJFileReader()
{
	for(int i = 0; i< tArray.GetSize(); i++)
	{
		Point * p = tArray.GetAt(i);
		if( p != NULL)
			delete p;
	}

	for(int k = 0; k< nArray.GetSize(); k++)
	{
		Point * p = nArray.GetAt(k);
		if( p != NULL)
			delete p;
	}

}
		
//!	read input file, handle different contents
void 
OBJFileReader::readToSolid( Solid *mesh, std::istream &in)
{
	SolidDelegate delegate;
	char strLine [1024]  = {0};
	
	while (in && !in.eof() && in.getline(strLine, 1024)) 
	{

		if( strlen( strLine ) == 0 ) continue;

		StringTokenizer tokenizer( strLine, " \r\n\t" );

		List<char> & tokens = tokenizer.tokens();
		ListNode<char> * node = tokens.head();

		char * token = node->data();


		//!read vertex coordinates, generate vertex
		if( strcmp( token, "v" ) == 0 )
		{
			Point p;

			//read coordinates
			for(int i=0; i<3; i++)
			{
				node = node->next();
				if( strlen(node->data()) != 0)
				{
					p[i] = atof( node->data() );
				}
				else i--;
			}
		
			//generate vertex
			Vertex * v = delegate.createVertex(mesh,  ++vID);
			v->point() = p;
			v->id()    = vID;
		}
		
		//!read face information, generate faces
		else if ( strcmp( token, "f" ) == 0 )
		{
			char * subToken;
			int id =0;
			std::list<int> polygonVertex;

			node =node ->next();

			while( node != NULL )
			{
				if( strlen(node->data()) != 0)	//filt empty node
				{
					subToken = node ->data();
	
					id = modifyVertexInf(mesh, subToken);
					polygonVertex.push_back(id);
				}
				node = node->next();
			}

			int ids[3] = {0};
			ids[0] = polygonVertex.front();
			polygonVertex.pop_front();
			ids[2] = polygonVertex.front();
			polygonVertex.pop_front();

			while(!polygonVertex.empty())
			{
				ids[1] = ids[2];
				ids[2] = polygonVertex.front();
				polygonVertex.pop_front();
				delegate.createFace(mesh, ids, ++ fID);

			}
		}
		

		//!read vertex texture information, put it into texture array
		else if( strcmp (token , "vt" ) == 0 )
		{
			Point p;
			for(int i=0; i<2; i++)
			{
				node = node->next();
				if( strlen(node->data()) != 0)
				{
					p[i] = atof( node->data() );
				}
				else i--;
			}

			Point *pp = new Point();
			*pp = p;
	
			tArray.Add(pp);							//put texture inf to tArray
		}

		//!read vertex normal information, put it into normal array
		else if( strcmp (token , "vn" ) == 0)
		{
			Point p;
			for(int i=0; i<3; i++)
			{
				node = node->next();
				if( strlen(node->data()) != 0)
				{
					p[i] = atof( node->data() );
				}
				else i--;
			}

			Point *pp = new Point();
			*pp = p;
	
			nArray.Add(pp);							//put normal inf to nArray
		}

		else
		{
		}
	}//end of while

	mesh->labelBoundaryEdges();
	mesh->removeDanglingVertices();
}



//! update vertex by append texture, normal inf
int
OBJFileReader:: modifyVertexInf(Solid *sol, char * str)
{
	int vid = 0;
	int tid = 0;
	int nid = 0;

	StringTokenizer subTokenizer( str, "/" );
	List<char> & subTokens	= subTokenizer.tokens();
	ListNode<char>  *node	= subTokens.head();

	if( subTokens.size() == 1)			// 6 case
		vid = atoi(node->data());
	else if( subTokens.size() == 2)		// 6/8 case
	{
		vid = atoi (node->data() );
		node = node->next();
		tid = atoi (node->data() );
	}
	else if( subTokens.size() ==3)		// 6/8/4 case, 6//4 case
	{
		vid = atoi (node->data());
		node = node->next();
		if( strlen(node->data()) !=0 )
		{
			tid = atoi( node ->data());
		}

		{
			node = node ->next();
			nid = atoi(node->data());
		}
	}
	if( vid <0 )
		vid = vID + vid +1;
	if( nid <0 )
		nid = nArray.GetSize() + nid +1;
	if( tid <0 )
		tid = tArray.GetSize() + tid +1;

	modifyNormalInf(sol, vid, nid);
	modifyTextureInf(sol, vid, tid);		
	return vid;

}
	
//! modify normal information
/*!
	read information from file, append to vertex string.
*/
void
OBJFileReader:: modifyNormalInf(Solid * sol, int vid, int nid)
{
	/******************
	std::string temp="";
	if( nid != 0)
	{
		Point p = * nArray[nid-1];
		double nx = p(0);
		double ny = p(1);
		double nz = p(2);
	
		temp.append(" normal=(");
		temp.append(d2String(nx));
		temp.append(d2String(ny));
		temp.append(d2String(nz));
		temp.append(")");
	}

	Vertex *v = sol->idVertex(vid);
	v->string() = v->string() + temp;

  ***********************/

}

//! modify texture information
/*!
	read texture information from file, append to vertex string
*/
void 
OBJFileReader::modifyTextureInf(Solid *sol, int vid, int tid)
{
	std::string temp = "";
	if( tid != 0)
	{
		temp.append("uv=(");
		Point p	= *tArray[tid-1];
		double u = p(0);
		double v = p(1);
		// double w = p(2);

		temp.append( d2String(u));
		temp.append(" ");
		temp.append( d2String(v));
		temp.append(")");
	}

	Vertex *v = sol->idVertex(vid);
	v->string() = "";
	v->string() = temp+ v->string();
}



//how about w value, the format?
////////////////////////////////
//...............................

//! double to string convertor
std::string 
OBJFileReader::d2String( double value)
{
	char buffer [20];
	sprintf(buffer, "%g", value);
//	_gcvt (value,6,buffer);
	return buffer;
}

