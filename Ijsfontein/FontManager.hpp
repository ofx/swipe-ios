//
//  FontManager.hpp
//  Ijsfontein
//
//  Created by Marlon Etheredge on 6/1/11.
//  Copyright 2011 ofx. All rights reserved.
//

#include "FTGL/ftgles.h"
#include "ResourceManager.h"

typedef int FontHandle;

typedef struct ExplodingText
{
    Vector2 scale;
    Vector2 position;
    
    FontHandle handle;
    Color color;
    
    char* string;
    
    float step, max;
} ExplodingText;

class FontManager
{
private:
    FTFont *m_Fonts[MAX_FONTS];
    
    std::vector<ExplodingText*> m_ExplodingText;
public:
    FontManager( void );
    ~FontManager( void );
    
    FontHandle LoadFont( std::string name );
    
    void SetFaceSize( FontHandle handle, const unsigned int size );
    
    void Render( const char* string, FontHandle handle, Color c, Vector2 position = Vector2(), Vector2 scale = Vector2( 1.0f, 1.0f ) );
    
    void AddExplodingText( char* string, FontHandle handle, Color c, Vector2 position, float step, float max );
    void RenderExplodingTexts( void );
};