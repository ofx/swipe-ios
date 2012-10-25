//
//  Particle.h
//  Ijsfontein
//
//  Created by Marlon Etheredge on 5/30/11.
//  Copyright 2011 ofx. All rights reserved.
//

#pragma once

#include "RenderingEngine.hpp"
#include "Quad.hpp"

class ParticleSystem;

class Particle : public Quad
{
private:
    ParticleSystem *m_Parent;
public:
    Particle( Vector2 center );
    ~Particle( void );
    
    void SetParent( ParticleSystem *parent ) { m_Parent = parent; }
    
    void Render( void );
};

class ParticleSystem
{
private:
    unsigned int m_CountParticles;
    
    Particle **m_Particles;

    Vector2 m_Center;
    
    bool m_Active;
public:
    ParticleSystem( Vector2 center, int radius, unsigned int particles, Texture *texture );
    ~ParticleSystem( void );
    
    Vector2 GetCenter( void ) { return m_Center; }
    
    bool IsActive( void ) { return m_Active; }
    
    void SetActive( bool active )    { m_Active = active; }
    void SetCenter( Vector2 center ) { m_Center = center; }
};