#ifndef _SLIST_H_
#define _SLIST_H_

#include <stdexcept>

namespace MeshLib
{

template<typename T>
class ListNode
{
	public:
		ListNode( T * data )   { m_data =  data; m_next = NULL; };
		T * & data()		   { return m_data; };

		ListNode<T> * & next() { return m_next; };

	private:

		T * m_data;
		ListNode * m_next;
};

template<typename T>
class List
{
public:
	List()  { m_head = NULL; m_size = 0; };
	~List();

	bool InsertAfter ( T * ft, T * t );	
	bool InsertBefore( T * ft, T * t );	

	bool Delete( T * t );

	void Append( T * t );

	bool empty(){ return m_head == NULL; };

	T *  first(){ if( m_head ) return m_head->data(); else return NULL; };

	T *  last() 
	{ 
		if( !m_head )  return NULL;
		ListNode<T> *n = m_head;
		for( ; n->next() != NULL; n = n->next() );
		return n->data(); 
	};

	ListNode<T> * head() { return m_head; };

	bool           contains( T * t );
	
	void           clear();

	friend class ListItertor;
	T * operator[](int i);
	int      size() { return m_size; }; 
	ListNode<T> *  find( T * t );

	void           Reverse();				//reverse the list

private:

	ListNode<T> * m_head;
	void append( ListNode<T> * tn );
	void remove( ListNode<T> * tn );
	void insert_before( ListNode<T> * fn, ListNode<T> * tn );
	void insert_after( ListNode<T> * fn,  ListNode<T> * tn );
	int  m_size;

};

template<typename T>
List<T>::~List()
{
	while( m_head )
	{
		remove( m_head );
	}
}

template<typename T>
ListNode<T> * List<T>::find( T * t)
{
	ListNode<T> * h = m_head;

	if( !h )
	{
		return NULL;
	}
	
	
	do{
		if( h->data() == t ) return h;
		h = h->next();
	}while( h != NULL );

	return NULL;
}

template<typename T>
void List<T>::clear()
{
	while( m_head )
	{
		remove( m_head );
	}
}

template<typename T>
void List<T>::insert_after( ListNode<T> * fn, ListNode<T> * tn )
{
	tn->next() = fn->next();
	fn->next() = tn;
	m_size ++;
}

template<typename T>
void List<T>::insert_before( ListNode<T> * fn, ListNode<T> * tn )
{
	if( m_head == fn )
	{
		tn->next() = m_head;
		m_head = tn;
	}
	else
	{
		ListNode<T> * n = m_head;
		while( n->next() != fn ) n = n->next();
		tn->next() = fn;
		n->next()  = tn;
	}
	m_size ++;
}

template<typename T>
void List<T>::append( ListNode<T> * tn )
{
	if( m_head == NULL )
	{
		m_head = tn;
		m_head->next() = NULL;
		m_size ++;
		return;
	}

	ListNode<T> * n = m_head;
	while( n->next() != NULL )
	{
		n = n->next();
	}

	n->next() = tn;
	tn->next() = NULL;
	m_size ++;
}

template<typename T>
void List<T>::remove( ListNode<T> * tn )
{

	if( tn == m_head )
	{
		m_head = m_head->next();
		delete tn;
		m_size --;
		return;
	}

	ListNode<T> * n;
	n = m_head;

	while( n->next() != tn )
	{
		n = n->next();
	}


	if( n != NULL )
	{
		n->next() = tn->next();
		m_size --;
		delete tn;
	}
}

template<typename T>
bool List<T>::InsertAfter( T * ft, T * t )
{
	ListNode<T> * fn = find( ft );
	if( fn == NULL ) throw std::invalid_argument("specified data is not in list");

	ListNode<T> * h = new ListNode<T>(t);
	
	insert_after( fn, h );
	return true;

}

template<typename T>
bool List<T>::InsertBefore( T * ft, T * t )
{
	if( ft == NULL )
	{
		ListNode<T> * h = new ListNode<T>(t);
		
		append(h);
		return true;
	}	

	ListNode<T> * fn = find( ft );
	if( fn == NULL ) throw std::invalid_argument("specified data is not in list");

	ListNode<T> * h = new ListNode<T>(t);
	
	insert_before( fn, h );
	return true;
}

template<typename T>
void List<T>::Reverse()		//reverse the list
{
	if( m_head == NULL ) return;

	ListNode<T> * reverse_head = NULL;

	ListNode<T> * n = m_head;
	
	m_head = m_head->next();

	while( m_head != NULL )
	{
		n->next() = reverse_head;
		reverse_head = n;
		n = m_head;
		m_head = m_head->next();
	}

	n->next() = reverse_head;
	reverse_head = n;
	m_head = reverse_head;
}


template<typename T>
void List<T>::Append( T * t )
{
	ListNode<T> * h = m_head;

	h = new ListNode<T>(t);
	
	append( h );
	return;

}

template<typename T>
bool List<T>::contains( T * t )
{
	ListNode<T> * h = m_head;

	if( !h )
	{
		return false;
	}
	
	do{
		if( h->data() == t ) return true;
		h = h->next();
	}while( h != NULL );

	return false;
}


template<typename T>
bool List<T>::Delete( T * t )
{
	ListNode<T> * h = m_head;

	if( !h )
	{
		return false;
	}
	
	do{
		if( h->data() == t ) 
		{
			remove( h );
			return true;
		}
		h = h->next();
	}while( h != NULL );

	return false;

}

template<typename T>
T * List<T>::operator[]( int idx )
{
	ListNode<T> * n = m_head;

	for( int i = 0; i < idx; i ++, n=n->next() );

	return n->data();
}


template<typename T>
class ListIterator
{
public:
	ListIterator();
	ListIterator( List<T> & list );
	~ListIterator(){};
	void operator++();
	T * operator*();
	bool end();
	void reset();
	void reset( List<T> & list );

private:
	ListNode<T> * m_pointer;
	List<T>     * m_list;
};

template<typename T>
ListIterator<T>::ListIterator( )
{
	m_list = NULL;
	m_pointer = NULL;
}

template<typename T>
ListIterator<T>::ListIterator( List<T> & list )
{
	m_list = & list;
	m_pointer = m_list->head();
}

template<typename T>
void ListIterator<T>::reset()
{
	m_pointer = m_list->head();
}

template<typename T>
void ListIterator<T>::reset( List<T> & list )
{
	m_list = & list;
	m_pointer = m_list->head();
}

template<typename T>
void ListIterator<T>::operator++()
{
	if( m_pointer )
	{
		m_pointer = m_pointer->next();
	}
}

template<typename T>
T* ListIterator<T>::operator*()
{
	return m_pointer->data();
}

template<typename T>
bool ListIterator<T>::end()
{
	return m_pointer == NULL;
}

} //end of namespace 

#endif
