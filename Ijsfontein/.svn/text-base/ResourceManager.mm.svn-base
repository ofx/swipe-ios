//
//  ResourceManager.cpp
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/15/11.
//  Copyright 2011 ofx. All rights reserved.
//

#include "ResourceManager.h"
#include "Common.hpp"

ResourceManager::ResourceManager( void )
{
}

ResourceManager::~ResourceManager( void )
{
    for( int i = 0 ; i < MAX_TEXTURES ; ++i )
    {
        delete m_Textures[i];
    }
}

std::string ResourceManager::GetResourcePath( void )
{
    NSString* bundlePath = [[NSBundle mainBundle] resourcePath];
    
    return [bundlePath UTF8String];
}

Texture *ResourceManager::LoadPngTexture( std::string name )
{
    // Initializing
    std::vector<unsigned char> raw;
    std::vector<unsigned char> image;
    
    unsigned char *pImage, *top = NULL, *bottom = NULL, temp = 0;
    
    int fractionHeight, width, height, byteWidth;
    
    name = GetResourcePath() + "/Assets/" + name;
    
    // Lode load
    LodePNG::loadFile( raw, name );
    
    m_Decoder.decode( image, raw.empty() ? 0 : &raw[0], (unsigned)raw.size() );
    
    // Swap the data
    pImage         = &image[0];
    fractionHeight = m_Decoder.getHeight() * 0.5f;
    height         = m_Decoder.getHeight();
    
    byteWidth = (width = m_Decoder.getWidth()) * 4;
    
    if( !IS_POWER_OF_2( width ) || !IS_POWER_OF_2( height ) )
    {
        printf( "Texture \"%s\", not a power of two\n", name.c_str() );
    }
    
    if( width <= 0 || height <= 0 || !pImage )
    {
        puts( "Error loading texture" );
    }
    
    for( int y = 0 ; y < fractionHeight ; ++y ) 
    {
        top    = pImage + y * byteWidth;
        bottom = pImage + (fractionHeight - y - 1) * byteWidth;
        
        for( int x = 0 ; x < byteWidth ; ++x ) 
        {
            temp = *top;
            *top = *bottom;
            *bottom = temp;
            
            ++top;
            ++bottom;
        }
    }
    
    static int index = 0;
    
    Texture *t = new Texture();
    t->width  = width;
    t->height = height;
    
    // Bind GL texture
    glGenTextures( 1, &t->handle );
    
    glBindTexture( GL_TEXTURE_2D, t->handle );
    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0] );
    
    if( !glIsTexture( t->handle ) )
    {
        puts( "Generated texture is no texture" );
        printf( "GL error: %i", glGetError() );
    }
    
    m_Textures[index++] = t;
    
    return t;
}