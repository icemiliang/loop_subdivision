//TopologyException

#ifndef _TOPOLOGY_EXCEPTION_H_
#define _TOPOLOGY_EXCEPTION_H_


namespace MeshLib
{

class TopologyException 
{
 public:
	 TopologyException();
	 TopologyException(const char * strg);

	 ~TopologyException();

	 void what();
    
private:
 
	const char * msg;
};


}//end of namespace MeshLib
#endif //TopologyException

