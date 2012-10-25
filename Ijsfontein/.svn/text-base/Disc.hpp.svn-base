//
//  Disc.h
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/16/11.
//  Copyright 2011 ofx. All rights reserved.
//

#pragma once

#include "Quad.hpp"

class Gem;

class Disc : public Quad 
{
private:
    float m_Radius1, m_Radius2;
    
    int m_Index;
    
    bool m_RotationEnabled;
public:  
    static Texture *Handles[20];
    
    Gem *Gems[GEMS_PER_DISC];
    
    Disc( Vector2 center, float r1, float r2, int index, bool ra = true );
    ~Disc( void );
    
    void Initialize( ResourceManager *resourcemanager );
    
    bool RotationEnabled( void ) { return m_RotationEnabled; }
    
    int GetIndex( void ) { return m_Index; }
    unsigned int GetType( void ) { return DISC; }
    float GetInnerRadius( void ) { return m_Radius1; }
    float GetOuterRadius( void ) { return m_Radius2; }
};

class Gem : public Quad
{
private:
    Disc *m_Parent;
    
    unsigned int m_Type;
    
    float m_InitialRotation;
    
    Gem *m_MatchingGem;
    
    bool active;
    
public:
    Gem( Vector2 center, Disc *parent, float initialRotation ) : Quad( center ) { m_MatchingGem = 0; m_Parent = parent; m_InitialRotation = initialRotation; }
    ~Gem( void ) {}
    
    unsigned int GetType( void ) { return GEM; }
    unsigned int GetGemType( void ) { return m_Type; }
    
    float GetAngle( void ) { return m_InitialRotation + m_Parent->GetAngle(); }
    Gem *GetMatchingGem( void ) { return m_MatchingGem; }
    bool HasMatchingGem( void ) { return m_MatchingGem != 0; }
    
    void SetType( unsigned int t ) 
    { 
        Texture *tex = Disc::Handles[t];
        
        m_Type = t; 
        SetTexture( tex ); 
        
        SetActive( true );
    }
    
    void SetActive( bool b )
    {
        active = b;
    }
    
    bool GetActive() { return active; }
    
    void SetMatchingGem( Gem *gem ) { m_MatchingGem = gem; }
    
    void Render( void );
};