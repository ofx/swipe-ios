//
//  Common.h
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/14/11.
//  Copyright 2011 ofx. All rights reserved.
//

#pragma once

#include <math.h>
#include <time.h>

#define MAX_FONTS          20
#define MAX_TEXTURES       20

#define BLUE     0
#define GREEN    1
#define ORANGE   2
#define PURPLE   3
#define RED      4
#define TURQOISE 5
#define GLOW     6

#define GEM      0 
#define DISC     1
#define QUAD     2
#define DRAWABLE 3

#define GEMS_PER_DISC 7
#define SWIPE_ANGLE_OFFSET 20

#define IS_POWER_OF_2( a ) (a < 1 ? 0 : ((a & (a - 1)) == 0))
#define POW( a ) (a * a)
#define MULTIPLIER_HEURISTIC(  )

#define PI 3.1415926535897
#define EPSILON 0.0001

typedef struct Color
{
    float r, g, b, a;
    
    Color( void )
    {
        g = a = b = r = 1.0f;
    }
    
    Color( float _r, float _g, float _b, float _a )
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }
} Color;

class Vector2
{
public:
    float x, y;
    
    Vector2( void ) 
    {
        y = x = 0.0f;
    }
    
    Vector2( float a, float b )
    {
        x = a;
        y = b;
    }
    
    Vector2 &operator +=( const Vector2 &v ) { x += v.x; y += v.y; return (*this); }
    Vector2 &operator -=( const Vector2 &v ) { x -= v.x; y -= v.y; return (*this); }
    Vector2 &operator *=( float t )          { x *= t; y *= t; return (*this); }
    Vector2 &operator /=( float t )          { float f = 1.0f / t; x *= f; y *= f; return (*this); }
    
    Vector2 operator -( void )             const { return (Vector2( -x, -y )); }
    Vector2 operator +( const Vector2 &v ) const { return (Vector2( x + v.x, y + v.y )); }
    Vector2 operator -( const Vector2 &v ) const { return (Vector2( x - v.x, y - v.y )); }
    Vector2 operator *( float t )          const { return (Vector2( x * t, y * t )); }
    Vector2 operator /( float t )          const { float f = 1.0f / t; return (Vector2( x * f, y * f )); }
    Vector2 operator &( const Vector2 &v ) const { return (Vector2( x * v.x, y * v.y )); }
    
    float operator *( const Vector2 &v ) const { return (x * v.x + y * v.y); }
    
    bool operator ==( const Vector2 &v ) const { return ((x == v.x) && (y == v.y)); }
    bool operator !=( const Vector2 &v ) const { return ((x != v.x) || (y != v.y)); }
    
    Vector2 &Normalize( void ) { return (*this /= sqrtf( x * x + y * y )); } // Beware: Square root is slow
    
    Vector2 &Rotate( float angle ) { float s = sinf( angle ); float c = cosf( angle ); float nx = c * x - s * y; float ny = s * x + c * y; x = nx; y = ny; return (*this); }
    
    Vector2 &Swap( void ) { float yy = y; y = x; x = yy; return (*this); }
    
    // Static routines
    static inline float Dot( const Vector2 &v1, const Vector2 &v2 ) { return (v1 * v2); }
    
    static inline float Magnitude( const Vector2 &v )                { return (sqrtf( v.x * v.x + v.y * v.y )); }
    static inline float InverseMag( const Vector2 &v )               { return (1.0f / sqrtf( v.x * v.x + v.y * v.y )); }
    static inline float SquaredMag( const Vector2 &v )               { return (v.x * v.x + v.y * v.y); }
};

class Line2
{
private:
    Vector2 m_Start, m_End;
public:
    Line2( void ) {}
    Line2( Vector2 start, Vector2 end ) { m_Start = start; m_End = end; }
    ~Line2( void ) {}
    
    Vector2 GetStart( void ) const { return m_Start; }
    Vector2 GetEnd( void ) const   { return m_End; }
    
    void Set( Vector2 start, Vector2 end ) { m_Start = start; m_End = end; }
    
    bool Intersect( const Line2 &r );
};

typedef Line2 Ray;
typedef Line2 Swipe;

typedef struct Point3 
{
    float x, y, z;
} Point3;

inline bool IntersectPointAnnulus( Vector2 a, Vector2 c, float r1, float r2 )
{
    double b = POW( (a.x - c.x) ) + POW( (a.y - c.y) );
    
    return (b > POW( r1 )) && (b < POW( r2 ));
}

inline double DegreeToRadian( double d )
{
    return d * (PI / 180);
}

extern void reverse( char s[] );
extern void itoa( int n, char s[] );