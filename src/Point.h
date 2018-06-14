#ifndef _MESHLIB_POINT_H_

#define _MESHLIB_POINT_H_



#include <iostream>
#include <stdexcept>

#include <math.h>



namespace MeshLib{



class Point{



public:
	Point rotate(double theta, Point vector);

	Point( double x, double y, double z ){ v[0] = x; v[1] = y; v[2] = z;};

	Point() { v[0] = v[1] = v[2] = 0; };

	~Point(){};



	double & operator[]( int i)		  

	{ 

		if( 0>i || i>=3 ) throw std::out_of_range("invalid index for point coordinates"); 

		return v[i]; 

	};

	double   operator()( int i) const

	{ 

		if( 0>i || i>=3 ) throw std::out_of_range("invalid index for point coordinates");

		return v[i]; 

	};

	double   operator[]( int i) const 

	{

		if( 0>i || i>=3 ) throw std::out_of_range("invalid index for point coordinates");

		return v[i]; 

	};

	double norm() const { return sqrt( fabs( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] ) ); };

	double norm2() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2];};

	Point  & operator += ( const Point & p) { v[0] += p(0); v[1] += p(1); v[2] += p(2); return *this; }; 

	Point  & operator -= ( const Point & p) { v[0] -= p(0); v[1] -= p(1); v[2] -= p(2); return *this; };

	Point  & operator *= ( const double  s) { v[0] *= s   ; v[1] *=    s; v[2] *=    s; return *this; };

	Point  & operator /= ( const double  s) { v[0] /= s   ; v[1] /=    s; v[2] /=    s; return *this; };



	double   operator*( const Point & p ) const 

	{

		return v[0] * p[0] + v[1] * p[1] + v[2] * p[2]; 

	};



	Point   operator+( const Point & p  ) const

	{

		Point r( v[0] + p[0], v[1] + p[1], v[2] + p[2] );

		return r;

	};

	Point   operator-( const Point & p  ) const

	{

		Point r( v[0] - p[0], v[1] - p[1], v[2] - p[2] );

		return r;

	};

	Point   operator*( const double s  ) const

	{

		Point r( v[0] * s, v[1] * s, v[2] * s );

		return r;

	};

	Point   operator/( const double s  ) const

	{

		Point r( v[0] / s, v[1] / s, v[2] / s );

		return r;

	};



	Point operator^( const Point & p2) const

	{

		Point r( v[1] * p2[2] - v[2] * p2[1],

			     v[2] * p2[0] - v[0] * p2[2],

		         v[0] * p2[1] - v[1] * p2[0]);

		return r;

	};



	Point operator-() const

	{

		Point p(-v[0],-v[1],-v[2]);

		return p;

	};



	bool operator == (const Point & p)									

	{												

		return (v[0] == p(0) && v[1] == p(1) && v[2] == p(2));

	};



	bool operator< (const Point & p) 

	{

		bool returnValue = false;



		if( v[0] < p(0) ) returnValue = true;

		else if( v[0] == p[0])

		{

			if( v[1] < p(1) ) returnValue = true;

			else if( v[1] == p(1))

			{

				if( v[2] < p(2)) returnValue = true;

				else returnValue = false;

			}

			else returnValue = false;

		}

		else returnValue = false;



		return returnValue;

	};

		//Use this when treating the points as vectors
	double angleBetween(Point &p2)
	{
		return acos( (*this) * p2 / norm() * p2.norm() );
	}

protected:

	double v[3];

};



std::ostream & operator<<( std::ostream & os, const Point & p);


}//name space MeshLib



#endif //_MESHLIB_POINT_H_ defiined
