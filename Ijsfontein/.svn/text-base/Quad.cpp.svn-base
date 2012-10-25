//
//  Quad.cpp
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/14/11.
//  Copyright 2011 ofx. All rights reserved.
//

#include "Quad.hpp"

// Defining vertices
static const GLfloat vertices[4][3] = 
{
    {-1.0f, -1.0f, 0.0f},
    { 1.0f, -1.0f, 0.0f},
    {-1.0f,  1.0f, 0.0f},
    { 1.0f,  1.0f, 0.0f}
};

// Defining normals
static const GLfloat normals[4][3] = 
{
    {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f},
    {0.0f, 0.0f, -1.0f}
};

// Defining texture coordinates
static const GLfloat texCoords[8] = 
{
    0.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
};

Quad::Quad( void ) : IDrawable()
{
    
}

Quad::Quad( Vector2 center ) : IDrawable( center )
{
    
}

Quad::~Quad( void )
{
    // Nothing to free (I do hope so)
}

// Render the quad
void Quad::Render( void )
{
    glPushMatrix();
        glBindTexture( GL_TEXTURE_2D, m_Texture->handle );
    
        // Might want to select a colour later on, not needed at this time
        glColor4f( m_Color.r, m_Color.g, m_Color.b, m_Color.a );
    
        glTranslatef( m_Center.x, m_Center.y, 0.0f );
        glRotatef( Angle, 0.0f, 0.0f, 1.0f );
        glScalef( m_Scale.x, m_Scale.y, 1.0f );
    
        // Pass pointers to quad-specific arrays
        glVertexPointer( 3, GL_FLOAT, 0, vertices );
        glNormalPointer( GL_FLOAT, 0, normals );
        glTexCoordPointer( 2, GL_FLOAT, 0, texCoords );
        
        // Render as a triangle strip
        glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
    glPopMatrix();
}

void Quad::GetBounds( Line2 *bounds, float offset )
{
    float halfW = m_Scale.x * 0.5f * offset;
    float halfH = m_Scale.y * 0.5f * offset;
    
    bounds[0].Set( Vector2( m_Center.x - halfW, m_Center.y - halfH ), Vector2( m_Center.x - halfW, m_Center.y + halfH ) );
    bounds[1].Set( Vector2( m_Center.x - halfW, m_Center.y + halfH ), Vector2( m_Center.x + halfW, m_Center.y + halfH ) );
    bounds[2].Set( Vector2( m_Center.x + halfW, m_Center.y + halfH ), Vector2( m_Center.x + halfW, m_Center.y - halfH ) );
    bounds[3].Set( Vector2( m_Center.x + halfW, m_Center.y - halfH ), Vector2( m_Center.x - halfW, m_Center.y - halfH ) );
}