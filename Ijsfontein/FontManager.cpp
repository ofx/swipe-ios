//
//  FontManager.cpp
//  Ijsfontein
//
//  Created by Marlon Etheredge on 6/1/11.
//  Copyright 2011 ofx. All rights reserved.
//

#include "FontManager.hpp"

FontManager::FontManager( void )
{
    
}

FontManager::~FontManager( void )
{
    for( int i = 0 ; i < MAX_FONTS ; ++i )
    {
        delete m_Fonts[i];
    }
    
    m_ExplodingText.clear();
}

FontHandle FontManager::LoadFont( std::string name )
{
    name = ResourceManager::GetResourcePath() + "/Assets/" + name;
    
    FTFont *f = new FTTextureFont( name.c_str() );
    f->FaceSize( 50 );
    
    static int index = 0;
    
    m_Fonts[index++] = f;
    
    return index;
}

void FontManager::SetFaceSize( FontHandle handle, const unsigned int size )
{
    m_Fonts[handle]->FaceSize( size );
}

void FontManager::Render( const char* string, FontHandle handle, Color c, Vector2 position, Vector2 scale )
{
    glPushMatrix();
        glColor4f( c.r, c.g, c.b, c.a );
        
        // TODO: Could be neater
        // Translate the position back to the default coordinates system
        glTranslatef( -512.0f, -384.0f, 0.0f );
    
        glTranslatef( position.x, position.y, 1.0f );
    
        glScalef( scale.x, scale.y, 1.0f );
        
        m_Fonts[handle]->Render( string );
    glPopMatrix();
}

void FontManager::AddExplodingText( char *string, FontHandle handle, Color c, Vector2 position, float step, float max )
{
    ExplodingText *t = new ExplodingText();
    t->string   = string;
    t->position = position;
    t->handle   = handle;
    t->color    = c;
    t->step     = step;
    t->max      = max;
    t->scale    = Vector2();
    
    m_ExplodingText.push_back( t );
}

void FontManager::RenderExplodingTexts( void )
{
    std::vector<ExplodingText*>::iterator it;
    
    for( it = m_ExplodingText.begin() ; it < m_ExplodingText.end() ; ++it )
    {
        ExplodingText *t = *it;
        
        t->scale.x += t->step;
        t->scale.y += t->step;
        
        if( t->scale.x < t->max && t->scale.y < t->max )
        {
            Render( t->string, t->handle, t->color, t->position, t->scale );
        }
        else
        {
            m_ExplodingText.erase( it );
        }
    }
}