//
//  ResourceManager.h
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/15/11.
//  Copyright 2011 ofx. All rights reserved.
//

#pragma once

#include "lodepng.h"
#include "Common.hpp"

#include <string>
#include <vector>

typedef struct Texture
{
    GLuint handle;
    GLuint width, height;
} Texture;

class ResourceManager 
{
public:
    ResourceManager( void );
    ~ResourceManager( void );
    
    static std::string GetResourcePath( void );
    
    // Load a png texture with name specified, relative to resourcepath
    Texture *LoadPngTexture( std::string name );
private:
    LodePNG::Decoder m_Decoder;
    
    Texture *m_Textures[MAX_TEXTURES];
    
    std::string m_RelativePath;
};