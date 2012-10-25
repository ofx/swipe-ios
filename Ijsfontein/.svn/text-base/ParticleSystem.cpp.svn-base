//
//  Particle.cpp
//  Ijsfontein
//
//  Created by Marlon Etheredge on 5/30/11.
//  Copyright 2011 ofx. All rights reserved.
//

#include "ParticleSystem.hpp"
#include <QuartzCore/QuartzCore.h>
#include <time.h>

Particle::Particle( Vector2 center ) : Quad( center )
{
    m_Active = false;
}

Particle::~Particle( void )
{
    // Nothing to free (I do hope so)
}

void Particle::Render( void )
{
    if( m_Parent->IsActive() )
    {
        int t = (int) time( NULL );
        
        m_Center.x += cosf( t * rand() );
        m_Center.y += sinf( t * rand() );
        
        Vector2 c = m_Parent->GetCenter();
        
        glPushMatrix();
            glTranslatef( c.x, c.y, 0.0f );
            
            Quad::Render();
        glPopMatrix();
    }
}

ParticleSystem::ParticleSystem( Vector2 center, int radius, unsigned int particles, Texture *texturehandle )
{
    RenderingEngine *r = RenderingEngine::GetRenderingEngine();
    
    m_CountParticles = particles;
    m_Center = Vector2( 0.0f, 0.0f );
    
    m_Particles = (Particle**) malloc( sizeof( Particle* ) * particles );
    
    for( int i = 0 ; i < particles ; ++i )
    {
        Vector2 s;
        s.x = s.y = rand() % 22;
        
        float x = (rand() % radius) - (radius / 2);
        float y = (rand() % radius) - (radius / 2);
        
        m_Particles[i] = new Particle(  Vector2( x, y ) );
        m_Particles[i]->SetTexture( texturehandle );
        m_Particles[i]->SetScale( s );
        m_Particles[i]->SetParent( this );
        
        r->RegisterDrawable( m_Particles[i] );
    }
}

ParticleSystem::~ParticleSystem( void )
{
    for( int i = 0 ; i < m_CountParticles ; ++i )
    {
        delete m_Particles[i];
    }
    
    delete m_Particles;
}