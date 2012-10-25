//
//  IDrawable.h
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/14/11.
//  Copyright 2011 ofx. All rights reserved.
//

#pragma once

#include "ResourceManager.h"
#include "Common.hpp"

class IDrawable 
{
protected:
    Texture *m_Texture;
    
    Vector2 m_Center, m_Scale;
    Color m_Color;
    
    bool m_Active;
    
    int m_Layers;
private:
    void Initialize( Vector2 position ) 
    {
        m_Center = position;
        m_Active = true;
        
        Angle = 0.0f;
    }
public:
    float Angle;
    
    IDrawable( Vector2 &position ) { Initialize( position ); }
    IDrawable( int layers = 0 ) { Initialize( Vector2( 0.0f, 0.0f ) ); }
    
    ~IDrawable( void )
    {
    }
    
    Vector2 GetCenter( void ) { return m_Center; }
    
    void SetColor  ( Color color )      { m_Color = color; }
    void SetScale  ( Vector2 scale )    { m_Scale = scale; }
    void SetCenter ( Vector2 center )   { m_Center = center; }
    void SetTexture( Texture *texture ) { m_Texture = texture; }
    void SetActive ( bool active )      { m_Active = true; }
    
    virtual float GetAngle( void ) { return Angle; }
    
    virtual unsigned int GetType( void ) { return DRAWABLE; }
    virtual Vector2 GetDimensions( void ) { return m_Scale; }
    
    // Should be overloaded
    virtual void Render( void ) = 0;
    
    virtual void Update( void )
    {
    }
};