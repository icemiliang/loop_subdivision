#ifndef _MESHLIB_ARRAY_
#define _MESHLIB_ARRAY_

#include <string.h>

namespace MeshLib{


#ifndef max
//!  Get max value function.
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
//!  Get min value function.
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

//Array Contains pointers of T

//!  Array class. 
/*!
  This class contains pointers of template T.
*/
template<typename T>
class Array
{

// Implementation
private:
	//!  The actual array of data.
	T** m_pData;     // the actual array of data
	//!  # of elements (upperBound - 1).
	int m_nSize;     // # of elements (upperBound - 1)
	//!  Max allocated.
	int m_nMaxSize;  // max allocated
	//!  Grow amount.
	int m_nGrowBy;   // grow amount

public:

	// Construction
	//!  Constructor.
	Array()
	{
		m_pData = NULL;
		m_nSize = 0;
		m_nMaxSize = 0;
		m_nGrowBy = 0;
	}

	// Destruction
	//!  Destructor.
	~Array()
		{
			delete [] (unsigned char*)m_pData;
		}

	// Attributes
	//!  Get the # of elements.
    /*!
      \return the # of elements (upperBound - 1).
    */
	int GetSize() { return m_nSize; }
	//!  Get the upper bound of the array.
    /*!
      \return the upper bound of the array.
    */
	int GetUpperBound() { return m_nSize-1; }

	// Operations

	// Really clean up
	//!  Really clean up.
	void Free()
	{
		for(int i=0;i<m_nSize;i++)
			if(m_pData[i] != NULL)
			{
				delete m_pData[i];
			  m_pData[i] = NULL;
			}
		RemoveAll();
	}

	// Clean up pointers array
	//!  Clean up pointers array.
	void FreeExtra()
	{

		if (m_nSize != m_nMaxSize)
		{
			// shrink to desired size

			T** pNewData = NULL;
			if (m_nSize != 0)
			{
				pNewData = (T**) new unsigned char[m_nSize * sizeof(T*)];
				// copy new data from old
				memcpy(pNewData, m_pData, m_nSize * sizeof(T*));
			}

			// get rid of old stuff (note: no destructors called)
			delete[] (unsigned char *)m_pData;
			m_pData = pNewData;
			m_nMaxSize = m_nSize;
		}

	}

	// Clean up pointers array
	//!  Clean up pointers array.
	void RemoveAll() { SetSize(0); }

	// Accessing elements
	//! Accessing elements.
    /*!
	  \param nIdex an int to indicate the position of the object to be picked up.
      \return template.
    */
	T* GetAt(int nIndex)
	{ 
		if(nIndex < 0 || nIndex >= m_nSize) throw std::out_of_range("invalid index");
		return m_pData[nIndex]; 
	}

	// SetAt
	//! SetAt.
    /*!
	  \param nIdex an int to indicate the position of the object to be set.
	  \param newElement a template to be set in this array.
    */
	void SetAt(int nIndex, T* newElement)
	{ 
		if(nIndex < 0 || nIndex >= m_nSize) throw std::out_of_range("invalid index");
		m_pData[nIndex] = newElement; 
	}

	// Has
	//! Has.
    /*!
	  to get to know the given element is in this array or not.
	  \param pElement a template to be test it is in this array or not.
      \return int to indicate yes or no. (1 for yes and 0 for no).
    */
	int Has(T* pElement)
	{
		int size = GetSize();
		for(int i=0;i<size;i++)
			if(GetAt(i) == pElement)
				return 1;
		return 0;
	}
	
	// Direct Access to the element data (may return NULL)
	//! Direct Access to the element data (may return NULL).
    /*!
      \return template pointer which is the actual array of data.
    */
	T** GetData()	{ return m_pData; }

	// Add
	//! Add.
    /*!
	  add a new element at the end of this array.
	  \param newElement a template to be added.
      \return int which is the new # of element of this array.
    */
	int Add(T* newElement)
	{ 
		int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; 
	}

	// overloaded operator helpers
	//! Overloaded operator helpers.
    /*!
	  \param nIdex the # of element.
      \return template which is the last element of this array.
    */
	T* operator[](int nIndex) { return GetAt(nIndex); }

	// Potentially growing the array
	//! Potentially growing the array.
    /*!
	  \param nIdex the # of element.
	  \param newElement the new element that need to be added.
    */
	void SetAtGrow(int nIndex, T* newElement)
	{
		if(nIndex < 0) throw std::out_of_range("invalid index==>index must be >=0");

		if (nIndex >= m_nSize)
			SetSize(nIndex+1);
		m_pData[nIndex] = newElement;
	}

	// Operations that move elements around
	//! Insert element at specified position.
    /*!
	  \param nIdex the position for insert the element.
	  \param newElement the element that need to be inserted.
	  \param nCount the growing size (default = 1).
    */
	void InsertAt(int nIndex, T* newElement, int nCount = 1)
	{
		if(nIndex < 0) throw std::out_of_range("invalid index==>index must be >=0");    // will expand to meet need
		assert(nCount > 0);     // zero or negative size not allowed

		if (nIndex >= m_nSize)
		{
			// adding after the end of the array
			SetSize(nIndex + nCount);  // grow so nIndex is valid
		}
		else
		{
			// inserting in the middle of the array
			int nOldSize = m_nSize;
			SetSize(m_nSize + nCount);  // grow it to new size
			// shift old data up to fill gap
			memmove(&m_pData[nIndex+nCount], &m_pData[nIndex],
				(nOldSize-nIndex) * sizeof(T*));

			// re-init slots we copied from

			memset(&m_pData[nIndex], 0, nCount * sizeof(T*));

		}

		// insert new value in the gap
		if(nIndex + nCount > m_nSize) throw std::out_of_range("invalis index");
		while (nCount--)
			m_pData[nIndex++] = newElement;
	}

	//! Remove element at specified position.
    /*!
	  \param nIdex the position for remove the element.
	  \param nCount the reducing size (default = 1).
    */
	void RemoveAt(int nIndex, int nCount = 1)
	{
		if(nIndex <0 || nCount <0 || (nIndex + nCount > m_nSize)) throw std::out_of_range("invalid index");

		// just remove a range
		int nMoveCount = m_nSize - (nIndex + nCount);

		if (nMoveCount)
			memcpy(&m_pData[nIndex], &m_pData[nIndex + nCount],
				nMoveCount * sizeof(T*));
		m_nSize -= nCount;
	}

	// IndexFrom
	//! IndexFrom.
    /*!
	  \param pElement the element that need to get its index.
      \return int which is the index of the element.
    */
	int IndexFrom(T* pElement)
	{
		for(int i=0;i<m_nSize;i++)
			if(m_pData[i] == pElement)
				return i;
		return -1;
	}

	// SetSize
	//! SetSize.
    /*!
	  dynamically set array size. 
	  1. Shringk to nothing;
	  2. Create one with exact size;
	  3. Fitting size setting.
	  4. Growing array setting.
	  \param nNewSize the new size for this array.
      \param nGrowBy the growing size (default = -1).
    */
	void SetSize(int nNewSize, int nGrowBy = -1)
	{
		if(nNewSize < 0) throw std::out_of_range("size must be >=0");

		if(nGrowBy != -1)
			m_nGrowBy = nGrowBy;  // set new size
		
		// shrink to nothing
		if(nNewSize == 0)
		{
			delete[] (unsigned char*)m_pData;
			m_pData = NULL;
			m_nSize = 0;
			m_nMaxSize = 0;
		}
		else 
			// create one with exact size
			if(m_pData == NULL)
			{
				m_pData = (T**) new char[nNewSize * sizeof(T*)];
				memset(m_pData, 0, nNewSize * sizeof(T*));  // zero fill
				m_nSize = nNewSize;
				m_nMaxSize = nNewSize;
			}
			else 
				if(nNewSize <= m_nMaxSize)
				{
					// it fits
					if (nNewSize > m_nSize)
					{
						// initialize the new elements
						memset(&m_pData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(T*));
					}
					m_nSize = nNewSize;
				}
				else
				{
					// otherwise, grow array
					int nGrowBy = m_nGrowBy;
					if (nGrowBy == 0)
					{
						// heuristically determine growth when nGrowBy == 0
						//  (this avoids heap fragmentation in many situations)
						nGrowBy = min(1024, max(4, m_nSize / 8));
					}
					int nNewMax;
					if (nNewSize < m_nMaxSize + nGrowBy)
						nNewMax = m_nMaxSize + nGrowBy;  // granularity
					else
						nNewMax = nNewSize;  // no slush
					
					if(nNewMax < m_nMaxSize) throw std::out_of_range("array extend exception");  // no wrap around

					T** pNewData = (T**) new char[nNewMax * sizeof(T*)];
					
					// copy new data from old
					memcpy(pNewData, m_pData, m_nSize * sizeof(T*));
					
					// construct remaining elements
					if(nNewSize <= m_nSize) throw std::out_of_range("array extend exception");
					
					memset(&pNewData[m_nSize], 0, (nNewSize-m_nSize) * sizeof(T*));
					
					// get rid of old stuff (note: no destructors called)
					delete[] (char*)m_pData;
					m_pData = pNewData;
					m_nSize = nNewSize;
					m_nMaxSize = nNewMax;
				}
	}

};

}

#endif // _ARRAY_3D_
