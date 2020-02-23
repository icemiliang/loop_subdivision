#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

//
// AVL Tree Implementation
//
//
// The template class AVL::Node (used in AVL::Tree) requires the following:
//
//   T::T ( T &);
//   T::~T ();
//   bool T::operator < ( T & rhs) ;
//   bool T::operator == ( T & rhs) ;
// 
// For printing purposes one must declare:
//
//   ostream & operator << ( ostream &,  T &);
//

//
// iostream is required for printing only.
//

#include <iostream>

//
// Use "namespace" to make sure the class names don't conflict with other code.
//

namespace AVL {

#ifndef TREE_MAX_HEIGHT
#define	TREE_MAX_HEIGHT 32
#endif

//
// The basic unit of currency in a tree are the nodes that comprise it.
//
template <class T>
class Node
{
public :

// This is were we keep the data we want to store in each node.
// It is  because if you change it while it is in the tree structure
// you compromise the integrity of the tree.
// It is public because the Tree class must have access to it in order
// to return it after being found with the found_node function.

     T * data;



// Each node has two children: left and right.  If they are both NULL then
// the node is a leaf node.  Otherwise, it's an interior node.

    Node<T> * left, * right;

private :

// The height is computed to be: 0 if NULL, 1 for leaf nodes, and the maximum
// height of the two children plus 1 for interior nodes.
// This is used to keep the tree balanced.

    int height;

    void compute_height ()
    {
        height = 0;
        if (left != NULL && left -> height > height)
            height = left -> height;
        if (right != NULL && right -> height > height)
            height = right -> height;
        height += 1;
    }

// The ructor is private because the nodes are self allocating.

    Node (T *  inData)
        : data (inData), left (NULL), right (NULL), height (1)
    {
    }

public :

// Recursively delete the children if this node is being nuked.

    ~Node ()
    {
        delete left;
        delete right;
    }

// Recursively insert some data into the tree then balance it on the way up.

    Node<T> * insert_node (T  *  inData)
    {
        if (this == NULL)
            return new Node<T> (inData);

        if ( *inData < *data)
            left = left -> insert_node (inData);
        else
            right = right -> insert_node (inData);
        return balance ();
    }

// Recursively find some data in the tree and if found return a pointer
// to the node containing the data.  If not found then return NULL.

    Node<T> * find_node (T * inData) 
    {
        if (this == NULL)
            return NULL;

        if ( *inData == *data)
            return this;

        if (*inData < *data)
            return left -> find_node (inData);
        else
            return right -> find_node (inData);
    }

// Recursively search the tree for some data and if found remove (delete) it.
// When you remove an interior node the right child must be place right of
// the right most child in the left sub-tree.
// Remember to balance the tree on the way up after removing a node.

    Node<T> * remove_node (T * inData)
    {
        if (this == NULL)
            return NULL;

        // we found the data we were looking for

        if ( *inData == *data)
        {
            // save the children

            Node<T> * tmp = left -> move_down_righthand_side (right);

            // by setting the children to NULL, we delete exactly one node.

            left = NULL;
            right = NULL;
            delete this;

            // return the reorganized children

            return tmp;
        }

        if ( *inData < *data)
            left = left -> remove_node (inData);
        else
            right = right -> remove_node (inData);
        return balance ();
    }

// Recursively print out all nodes in order (left to right).

    void print_node (std::ostream & co) 
    {
        if (this == NULL)
            return;

        left -> print_node (co);

        co << *data << " ";

        right -> print_node (co);
    }

private :


// move_down_righthand_side is the remove_node helper function:
//
// Recursively find the right most child in a sub-tree and put
// the "rhs" sub-tree there.
// Re-balance the tree on the way up.

    Node<T> * move_down_righthand_side (Node<T> * rhs)
    {
        if (this == NULL)
            return rhs;

        right = right -> move_down_righthand_side (rhs);
        return balance ();
    }

//
// Balancing a tree (or sub-tree) requires the AVL algorithm.
//
// If the tree is out of balance left-left, we rotate the node to the right.
// If the tree is out of balance left-right, we rotate the left child to the
// left and then rotate the current node right.
// If the tree is out of balance right-left, we rotate the right child to the
// right and then rotate the current node left.
// if the tree is out of balance right-right, we rotate the node to the left.
//

    Node<T> * balance ()
    {
        int d = difference_in_height ();

        // only rotate if out of balance
        if (d < -1 || d > 1)
        {
            // too heavy on the right
            if (d < 0)
            {
                // if right child is too heavy on the left,
                // rotate right child to the right
                if (right -> difference_in_height () > 0)
                    right = right -> rotate_right ();

                // rotate current node to the left
                return rotate_left ();
            }
            // too heavy on the left
            else
            {
                // if left child is too heavy on the right,
                // rotate left child to the left
                if (left -> difference_in_height () < 0)
                    left = left -> rotate_left ();

                // rotate current node to the right
                return rotate_right ();
            }
        }

        // recompute the height of each node on the way up
        compute_height ();

        // otherwise, the node is balanced and we simply return it
        return this;
    }

// ** balancing helper functions **

    Node<T> * exchange_left (Node<T> * & r, Node<T> * node)
    {
        r = left;
        left = node -> balance ();
        return balance ();
    }

    Node<T> * exchange_right (Node<T> * & l, Node<T> * node)
    {
        l = right;
        right = node -> balance ();
        return balance ();
    }

    int difference_in_height ()
    {
        int left_height = (left != NULL) ? left -> height : 0;
        int right_height = (right != NULL) ? right -> height : 0;
        return left_height - right_height;
    }

    Node<T> * rotate_left ()
    {
        return right -> exchange_left (right, this);
    }

    Node<T> * rotate_right ()
    {
        return left -> exchange_right (left, this);
    }

};

//
// Cover class for maintaining the tree.
//
// Since Node<T> is self allocating and self deleting, the Tree<T> class
// ensures that only qualified calls are made.
//
// Tree<T> is the public interface to the AVL Tree code.
// Node<T> is not meant to be used by the public.
//
// This code makes use of the somewhat dubious practice of calling a member
// function with a NULL "this" pointer.  We will not run into problems since
// we have no virtual member functions in Node<T>.
//

template <class T> class TreeIterator;

template <class T>
class Tree
{
private :

    Node<T> * root;
	int size;

public :

    Tree ()
    {
        root = NULL;
		size = 0;
    }

    ~Tree ()
    {
        delete root;
		size =0;
    }

    void insert (T * inData)
    {
        root = root -> insert_node (inData);
		size++;
    }

    T * find (T * inData) 
    {
        Node<T> * found = root -> find_node (inData);
        if (found != NULL)
            return  found -> data;
        else
            return NULL;
    }

    void remove (T * inData)
    {
        root = root -> remove_node (inData);
		if(root != NULL)
			size --;
    }

    void print (std::ostream & co) 
    {
        root -> print_node (co);
    }

	bool isEmpty()
	{
		return root == NULL;
	}

	T * rootData() { return root->data;}

	Node<T> * Root() { return root; };	

	int getSize()
	{
		return size;
	}
};


// Used for traversing an AVL tree. 
template <class T> 
class TreeIterator
{
	public:
		TreeIterator( Tree<T> & tree );
		~TreeIterator(){};
		void operator++();
		T *  operator*();
		bool end() { return m_finished; };
		void reset();

	private:
		bool m_finished;                    //finished ?
		bool m_initialized;					//initialized ?
		int  m_top;							//top of stack
		Node<T> * m_pointer;				//current Node
		Node<T> * m_stack[TREE_MAX_HEIGHT];	// Descended trees. 
		Node<T> * m_root;                   // root of the tree
};

template<class T>
TreeIterator<T>::TreeIterator( Tree<T> & tree )
{
	m_initialized = true;
	m_finished    = false;

	m_top  = 0;
	m_root = tree.Root();
	m_pointer = m_root;
	

	for (;;)
    {
		/* T2. */
		while (m_pointer != NULL)
		{
			/* T3. */
			m_stack[m_top ++ ] = m_pointer;
			m_pointer = m_pointer->left;
		}
		
		/* T4. */
		if (m_top == 0)
		{
			m_finished = true;
			m_initialized = false;
			return;
		}

		m_pointer = m_stack[--m_top];
		return;
    }

}

template<class T>
void TreeIterator<T>::reset()
{
	m_initialized = true;
	m_finished    = false;

	m_top = 0;
	m_pointer = m_root;
	

	for (;;)
    {
		/* T2. */
		while (m_pointer != NULL)
		{
			/* T3. */
			m_stack[m_top ++ ] = m_pointer;
			m_pointer = m_pointer->left;
		}
		
		/* T4. */
		if (m_top == 0)
		{
			m_finished = true;
			m_initialized = false;
			return;
		}

		m_pointer = m_stack[--m_top];
		return;
    }

}


template <class T> 
T * TreeIterator<T>::operator *()
{
	return m_pointer->data;
}

template<class T>
void TreeIterator<T>::operator++()
{	
	/* Uses Knuth's algorithm 2.3.1T (inorder Traverserersal). */
	/* T5. */
	m_pointer = m_pointer->right;
	
	for (;;)
    {
		/* T2. */
		while ( m_pointer != NULL)
		{
			/* T3. */
			m_stack[m_top ++ ] = m_pointer;
			m_pointer = m_pointer->left;
		}
		
		/* T4. */
		if (m_top == 0)
		{
			m_initialized = false;
			m_finished = true;
			return;
		}

		m_pointer = m_stack[--m_top];
		
		/* T5. */
		return;
    }
}





//
// Declare a useful extention to the output stream convention for
// the Tree<T> class.
//

template <class T>
std::ostream & operator << (std::ostream & co, Tree<T> & tree)
{
    tree.print (co);
    return co;
}

// end of namespace AVL

}

#endif
