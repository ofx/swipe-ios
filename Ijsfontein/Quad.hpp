//
//  Quad.h
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/14/11.
//  Copyright 2011 ofx. All rights reserved.
//

#pragma once

#include "IDrawable.hpp"
#include "Common.hpp"

class Quad : public IDrawable 
{
public:
    Quad( void );
    Quad( Vector2 center );
    ~Quad( void );
    
    unsigned int GetType( void ) { return QUAD; }
    void GetBounds( Line2 *bounds, float offset );
    
    void Render( void );
};