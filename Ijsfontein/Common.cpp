//
//  Common.c
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/14/11.
//  Copyright 2011 ofx. All rights reserved.
//

#include "Common.hpp"

bool Line2::Intersect( const Line2 &r )
{	
    Vector2 u = m_End - m_Start;	
    Vector2 v = r.GetEnd() - r.GetStart();	
    
    float D = u.x * v.y - u.y * v.x;	
    
    if( fabs( D ) < EPSILON )
    {
        return false;
    }
        
    Vector2 w = m_Start - r.GetStart();	
    
    float s = v.x * w.y - v.y * w.x;	
    
    if( s < 0 || s > D ) 
    {
        return false;	
    }
        
    float t = u.x * w.y - u.y * w.x;	
    
    if( t < 0 || t > D ) 
    {
        return false;
    }
        
    return true;
}

void reverse( char s[] )
{
    int i, j;
    char c;
    
    for( i = 0, j = strlen( s ) - 1 ; i < j ; ++i, --j) 
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa( int n, char s[] )
{
    int i, sign;
    
    if( (sign = n) < 0 )
    {
        n = -n;
    }
    
    i = 0;
    
    do 
    {
        s[i++] = n % 10 + '0';
    } while( (n /= 10) > 0 );
    
    if( sign < 0 )
    {
        s[i++] = '-';
    }
    
    reverse( s );
}