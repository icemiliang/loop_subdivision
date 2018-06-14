#ifndef _DLIST_H_
#define _DLIST_H_


namespace MeshLib
{
#include "avltree.h"


template<typename T>
class DListNode
{
	public:
		DListNode( T * data ) { m_data =  data; m_prev = NULL; m_next = NULL; };
		T * & data()       { return m_data; };

		DListNode<T> * & prev() { return m_prev; };
		DListNode<T> * & next() { return m_next; };
 
		bool operator<( DListNode<T> & node ) 
		{
			return m_data < node.data();
		};

		bool operator==( DListNode<T> & node ) 
		{
			return m_data == node.data();
		};

	private:
		T * m_data;
		DListNode * m_prev;
		DListNode * m_next;
};

template<typename T>
class DList
{
public:
	DList(){ m_head = NULL; };
	~DList();

	void Append( T * t );
	bool Delete( T * t );

	bool empty(){ return m_head == NULL; };

	T *  first(){ if( m_head ) return m_head->data(); else return NULL; };

	DListNode<T> * head() { return m_head; };

	bool           contains( T * t );

	void			clear();
	bool			Insert( T * front, T * t );
	void			sethead(T * t);
	DList<T> *		reverse();

	DListNode<T> * find( T * t );

	bool Update( T * ot, T * nt );
	int Size(){return m_tree.getSize();};
    void           insertBefore(T * reference, T * t);

private:

	AVL::Tree<DListNode<T> > m_tree;

	DListNode<T> * m_head;
	void append( DListNode<T> * tn );
	void insert( DListNode<T> * fn, DListNode<T> * cn );
	void remove( DListNode<T> * tn );
};


template<typename T>
void DList<T>::insert( DListNode<T> * fn, DListNode<T> * cn )
{
	cn->next() = fn->next();
	cn->prev() = fn;

	fn->next()->prev() = cn;
	fn->next() = cn;

	m_tree.insert( cn );
}


template<typename T>
bool DList<T>::Insert( T * front, T * t )
{
	DListNode<T> * fn = find( front );
	if( fn == NULL ) throw std::invalid_argument("can't get specified node");

	DListNode<T> * tn = find( t );

	if( tn != NULL ) throw std::invalid_argument("duplicate node");

	DListNode<T> * node = new DListNode<T>(t);

	insert( fn, node );
	return true;
}

template<typename T>
void DList<T>::insertBefore( T * front, T * t )
{
    DListNode<T> * fn = find( front );
    if( fn == NULL ) throw std::invalid_argument("can't get specified node");

    DListNode<T> * tn = find( t );

    if( tn != NULL ) throw std::invalid_argument("duplicate node");

    DListNode<T> * node = new DListNode<T>(t);

    insert( fn->prev(), node );
    if (fn == m_head) {
        m_head = node;  //new head
    }
};

template<typename T>
DListNode<T> * DList<T>::find( T * t )
{
	if( empty() ) return NULL;

	DListNode<T> tn(t);
	DListNode<T> * node = m_tree.find( &tn );

/*
	DListNode<T> * node = m_head;
	do{
		if( node->data() == t )
		{
			return node;
		}
		node = node->next();
	}while( node != m_head );

	return NULL;
*/

	return node;
}


template<typename T>
void DList<T>::sethead (T * t)
{
	if(m_head == NULL) return;
	DListNode<T> * tn = find(t);
	if(tn == NULL) return;
	m_head = tn;
}


template<typename T>
DList<T> * DList<T>::reverse()
{
	if(this == NULL)
		return NULL;
	if(empty())
		return new DList<T>;
	DList<T> * list = new DList<T>;
	list->Append (m_head->data());
	if(m_head->next() == m_head) return list;
	DListNode<T> * cur = m_head->next();
	while(cur != m_head)
	{
		list->insertBefore(list->first (),cur->data());
		cur = cur->next();
	}
	return list;

}

template<typename T>
DList<T>::~DList()
{
	while( m_head )
	{
		remove( m_head );
	}
}

template<typename T>
void DList<T>::clear()
{
	while( m_head )
	{
		remove( m_head );
	}
}


template<typename T>
void DList<T>::append( DListNode<T> * tn )	//insert to the tail
{
	if( m_head == NULL )
	{
		m_head = tn;
		m_head->next() = m_head;
		m_head->prev() = m_head;
	}
	else
	{
		tn->next() = m_head;
		tn->prev() = m_head->prev();
		m_head->prev()->next() = tn;
		m_head->prev() = tn;
	}

	m_tree.insert( tn );
};

template<typename T>
void DList<T>::remove( DListNode<T> * tn )
{
	if( tn != m_head )
	{
		tn->next()->prev() = tn->prev();
		tn->prev()->next() = tn->next();
		m_tree.remove( tn );
		delete tn;
		return;
	}

	if( m_head->next() == m_head )
	{
		m_tree.remove( m_head );
		delete m_head;
		m_head = NULL;
		return;
	}

	m_head->next()->prev() = m_head->prev();
	m_head->prev()->next() = m_head->next();

	DListNode<T> * h = m_head;
	m_head = m_head->next();
	m_tree.remove( h );
	delete h;
};

template<typename T>
bool DList<T>::Update( T * ot, T * nt )
{

	DListNode<T> * tn = find( ot );

	if( tn == NULL ) return false;

	m_tree.remove( tn );

	tn->data() = nt;

	m_tree.insert( tn );

	return true;
}


template<typename T>
void DList<T>::Append( T * t )
{
	
	DListNode<T> * h = new DListNode<T>(t);
	
	append( h );

};

template<typename T>
bool DList<T>::contains( T * t )
{
	DListNode<T> * h = m_head;

	if( !h )
	{
		return false;
	}
	
	do{
		if( h->data() == t ) return true;
		h = h->next();
	}while( h != m_head );

	return false;

};


template<typename T>
bool DList<T>::Delete( T * t )
{

	if( empty() )
	{
		return false;
	}

	DListNode<T> * h = find(t);
	
	if( h )
	{
		remove( h );
		return true;
	}

	return false;

};

template<typename T>
class DListIterator
{
public:
	DListIterator( DList<T> & list );
	~DListIterator(){};
	void operator++();
    void operator--();
	T * operator*();
	bool end();
	void reset();
    bool setStart(DListNode<T> *pNode);
    bool setStart(T *pT) ;/*{
        if (m_initialized) throw std::invalid_argument("Interation in progress");
        if (m_list->empty()) throw std::invalid_argument("No elements in the list");

        DListNode<T> *pNode = m_list->find(pT);
        if (pNode == NULL) throw std::invalid_argument("No such element in the list");

        m_pointer = m_start = pNode;
        return true;
    };*/


private:
	bool		   m_initialized;
	DListNode<T> * m_pointer;
    DListNode<T> * m_start;
	DList<T>     * m_list;
};

template<typename T>
void DListIterator<T>::reset()
{
	m_pointer = m_start;
	m_initialized = false;
};

template<typename T>
DListIterator<T>::DListIterator( DList<T> & list )
{
	m_list = & list;
	m_pointer = m_start = m_list->head();
	m_initialized = false;
};

template<typename T>
void DListIterator<T>::operator++()
{
    if (m_pointer == NULL) throw std::out_of_range("List is empty");
	if( m_initialized == false )
	{
		m_initialized = true;
	}
	m_pointer = m_pointer->next();
};

template<typename T>
void DListIterator<T>::operator--()
{
    if (m_pointer == NULL) throw std::out_of_range("List is empty");
	if( m_initialized == false )
	{
		m_initialized = true;
	}
	m_pointer = m_pointer->prev();
};

template<typename T>
T* DListIterator<T>::operator*()
{
	return m_pointer->data();
};

template<typename T>
bool DListIterator<T>::end()
{
	if( m_list->empty() ) return true;
	return ( m_initialized && m_pointer == m_start );
};

template<typename T>
bool DListIterator<T>::setStart(DListNode<T> *pNode)
{
    if (m_initialized) throw std::invalid_argument("Iteration in progress");
    if (m_list->empty()) throw std::invalid_argument("No elements in the list");

    if (pNode == m_start) return true;

    do {
        if (m_pointer == pNode) break;
        m_pointer = m_pointer->next();
    } while (m_pointer != m_start);

    if (m_pointer == m_start) { //reach the end
        throw std::invalid_argument("No such element in the list");
    }

    m_start = pNode;    //set the start point
    return true;
};

template<typename T>
bool DListIterator<T>::setStart(T *pT)
{
    if (m_initialized) throw std::invalid_argument("Interation in progress");
    if (m_list->empty()) throw std::invalid_argument("No elements in the list");

    DListNode<T> *pNode = m_list->find(pT);
    if (pNode == NULL) throw std::invalid_argument("No such element in the list");

    m_pointer = m_start = pNode;
    return true;
};
}
#endif
