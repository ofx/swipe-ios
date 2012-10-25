//
//  LevelManager.cpp
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/16/11.
//  Copyright 2011 ofx. All rights reserved.
//
//  Added CheckField( void ) by Mark Bouwman
//

#include "GamestateManager.hpp"
#include "FontManager.hpp"

inline float MultiplierHeuristic( float a )
{
    if( a < 0 )
    {
        return 0;
    }
    
    return a * a * 0.25f + 1;
}

GamestateManager::GamestateManager( void )
{
    m_Discs = new Disc*[3];
    
    m_Pause = false;
    m_Multiplier = 1;
    m_Score = 0;
    m_ScorePerTimeframe = 0;
}

GamestateManager::~GamestateManager ( void )
{
    delete m_Discs[0];
    delete m_Discs[1];
    delete m_Discs[2];
    
    delete m_Discs;
}

void GamestateManager::Initialize ( ResourceManager *resourcemanager )
{
    RenderingEngine *r = RenderingEngine::GetRenderingEngine();
    
    // Stub: Initializes level with 3 discs and thus generates and binds 3 textures
    Texture *t1 = resourcemanager->LoadPngTexture( std::string( "Inner.png" ) );
    Texture *t2 = resourcemanager->LoadPngTexture( std::string( "Middle.png" ) );
    Texture *t3 = resourcemanager->LoadPngTexture( std::string( "Outer.png" ) );
    
    Texture *b = resourcemanager->LoadPngTexture( std::string( "Background.png" ) );
    
    // Initialize gem textures
    Disc::Handles[BLUE]     = resourcemanager->LoadPngTexture( std::string( "GemBlue.png" ) );
    Disc::Handles[GREEN]    = resourcemanager->LoadPngTexture( std::string( "GemGreen.png" ) );
    Disc::Handles[ORANGE]   = resourcemanager->LoadPngTexture( std::string( "GemOrange.png" ) );
    Disc::Handles[PURPLE]   = resourcemanager->LoadPngTexture( std::string( "GemPurple.png" ) );
    Disc::Handles[RED]      = resourcemanager->LoadPngTexture( std::string( "GemRed.png" ) );
    Disc::Handles[TURQOISE] = resourcemanager->LoadPngTexture( std::string( "GemTurqoise.png" ) );
    Disc::Handles[GLOW]     = resourcemanager->LoadPngTexture( std::string( "GemGlow.png" ) );
    
    // Init the background plane
    Quad *backgroundPane = new Quad( Vector2( 0.0f, 0.0f ) );
    backgroundPane->SetTexture( b );
    backgroundPane->SetScale( Vector2( 512.0f, 384.0f ) );
    
    r->RegisterDrawable( backgroundPane );
    
    // Init discs
    m_Discs[2] = new Disc( Vector2( 0.0f, 0.0f ), 0, 143, 1 );
    m_Discs[2]->SetTexture( t1 );
    m_Discs[2]->SetScale( Vector2( 384.0f, 384.0f ) );
    
    m_Discs[1] = new Disc( Vector2(0.0f, 0.0f), 143, 206, 2 );
    m_Discs[1]->SetTexture( t2 );
    m_Discs[1]->SetScale( Vector2( 384.0f, 384.0f ) );
    
    m_Discs[0] = new Disc( Vector2( 0.0f, 0.0f ), 206, 406, 3 );
    m_Discs[0]->SetTexture( t3 );
    m_Discs[0]->SetScale( Vector2( 384.0f, 384.0f ) );
    
    // Register drawables
    for( int i = 0 ; i < 3 ; ++i )
    {
        r->RegisterDrawable( m_Discs[i] );
    }
    
    // Initialize in separate loop because of render priorities
    for( int i = 0 ; i < 3 ; ++i )
    {
        m_Discs[i]->Initialize( resourcemanager );
    }
}

void GamestateManager::Reset( void )
{
    for( int i = 0 ; i < 3 ; ++i )
    {
        for( int n = 0 ; n < GEMS_PER_DISC ; ++n )
        {
            srand( n );
            
            m_Discs[i]->Gems[n]->SetType( rand() % 6 );
        }
    }
    
    m_Multiplier        = 1;
    m_Score             = 0;
    m_ScorePerTimeframe = 0;
}

void GamestateManager::Update( void )
{
    time_t now;
    time( &now );
    
    if( difftime( now, m_LastScore ) > 6 )
    {
        m_Multiplier = 1;
    }
}

void GamestateManager::Score( Vector2 scoreposition )
{
    time_t now;
    time( &now );
    
    // See if we should increase the scores per timeframe to determine if we should
    // increase the multiplier
    if( difftime( now, m_LastScore ) < 5 )
    {
        ++m_ScorePerTimeframe;
    }
    else
    {
        m_ScorePerTimeframe = 1;
    }
    
    // Determine the multiplier
    m_Multiplier = MultiplierHeuristic( m_ScorePerTimeframe );
    
    // Update the score
    int score = 100 * m_Multiplier;
    m_Score += score;
    
    // Add a cool exploding text
    RenderingEngine::GetRenderingEngine()->GetFontManager()->AddExplodingText( "100", 0, Color(), scoreposition, 0.1f, 5.0f );
    
    if( m_ScorePerTimeframe > 1 )
    {
        RenderingEngine::GetRenderingEngine()->GetFontManager()->AddExplodingText( "Combo", 0, Color(), scoreposition + Vector2( 0.0f, 100.0f ), 0.1f, 5.0f );
    }
    
    m_LastScore = now;
}

void GamestateManager::CheckField( void )
{
    bool types[6][3];
    int coveredlines[6];
    
    // Iterate through the gems for each type
    for( int type = 0 ; type < 6 ; ++type )
    {
        coveredlines[type] = 0;
        
        for( int y = 0; y < 3; ++y ) 
        {
            Gem **gems = m_Discs[y]->Gems;
            
            bool hastype = false;
            
            // Check if the current type appears in the disc
            for( int x = 0 ; x < GEMS_PER_DISC ; ++x ) 
            {
                if( gems[x]->GetGemType() == type && gems[x]->GetActive() ) 
                {
                    hastype        = true;
                    types[type][y] = true;
                }
            }
            
            if( hastype == true )
            {
                ++coveredlines[type];
            }
            else 
            {
                types[type][y] = false;
            }
        }
    }
    
    // Choose a random colour to spawn
    int colourspawn = rand() % 6;
    
    
    // Check if the chosen colour is active on the screen
    bool missingcolour = false;
    int missingtype = 10;
    
    while (coveredlines[colourspawn] == 0)
    {
        missingtype = colourspawn;
        missingcolour = true;
        
        
        int t = colourspawn;
        while( t == colourspawn )
        {
            t = rand() % 6;
        }
        
        colourspawn = t;
    }
    
    // Iterate through all gems to see if they're active
    for( int y = 0 ; y < 3 ; ++y )
    {
        Gem **gems = m_Discs[y]->Gems;
        
        for( int x = 0 ; x < GEMS_PER_DISC ; ++x ) 
        {
            if( gems[x]->GetActive() == false ) 
            {
                // Check to see if the disc needs a gem with the colourspawn type and the required amount
                // of gems needed to create a set isn't 3 (meaning there isn't any of that colour)
                if( types[colourspawn][y] == false)
                {
                    gems[x]->SetType(colourspawn);
                }
                
                // Spawn the missing colour
                else if ( missingtype == true )
                {   
                    gems[x]->SetType( missingtype );
                }
                
                // Give the gem a random type different than colourspawn (so that it isn't possible to spawn
                // a complete set
                else
                {
                    int t = colourspawn;
                    while( t == colourspawn || t == missingtype )
                    {
                        t = rand() % 6;
                    }
                    
                    gems[x]->SetType( t );
                }
            }
        }
    }
}