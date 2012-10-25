//
//  Disc.cpp
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/16/11.
//  Copyright 2011 ofx. All rights reserved.
//

#include "Disc.hpp"
#include "ResourceManager.h"
#include "RenderingEngine.hpp"

#include <math.h>

Texture *Disc::Handles[20] = {0};

Disc::Disc( Vector2 center, float r1, float r2, int index, bool ra )  : Quad( center ) 
{ 
    m_Radius1 = r1; 
    m_Radius2 = r2; 
    m_RotationEnabled = ra; 
    m_Index = index;
}

Disc::~Disc( void )
{
    for( int i = 0 ; i < GEMS_PER_DISC ; ++i )
    {
        delete Gems[i];
    }
}

void Disc::Initialize( ResourceManager *resourcemanager )
{
    RenderingEngine *r = RenderingEngine::GetRenderingEngine();
    
    for( int i = 0 ; i < GEMS_PER_DISC ; ++i )
    {
        srand( i );
        
        float a = (360 / GEMS_PER_DISC) * i + GetAngle();
        float f = DegreeToRadian( a );
        
        unsigned int t = rand() % 6;
        
        Gems[i] = new Gem( Vector2( (cosf( f ) * (105 * m_Index)), (sinf( f ) * (105 * m_Index)) ), this, a );
        Gems[i]->SetTexture( Disc::Handles[GLOW] );
        Gems[i]->SetType( t );
        Gems[i]->SetScale( Vector2( 50.0f, 50.0f ) );
        
        r->RegisterDrawable( Gems[i] );
    }
}

void Gem::Render( void )
{
    // We want to update the position here to reduce method calls upon finger events
    SetCenter( Vector2( (cosf( DegreeToRadian( GetAngle() ) ) * (105 * m_Parent->GetIndex())), (sinf( DegreeToRadian( GetAngle() ) ) * (105 * m_Parent->GetIndex())) ) );
    
    Quad::Render();
}