//
//  RenderingEngine1.cpp
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/14/11.
//  Copyright 2011 ofx. All rights reserved.
//

#include "RenderingEngine.hpp"
#include "GamestateManager.hpp"
#include "FontManager.hpp"
#include "ParticleSystem.hpp"

RenderingEngine *RenderingEngine::s_RenderingEngine = 0;

RenderingEngine::RenderingEngine( void )
{
    glGenRenderbuffersOES( 1, &m_Renderbuffer );
    glBindRenderbufferOES( GL_RENDERBUFFER_OES, m_Renderbuffer );
    
    m_Angle = 270;
    
    m_Swipe = false;
    
    m_SelectedDrawable = 0;
}

RenderingEngine::~RenderingEngine( void )
{
    delete m_GamestateManager;
    delete m_ResourceManager;
    delete m_FontManager;
    
    delete m_ParticleSystem;
    
    m_Drawables.clear();
}

void RenderingEngine::RegisterDrawable( IDrawable *drawable )
{
    m_Drawables.push_back( drawable );
}

void RenderingEngine::UnregisterDrawable( IDrawable *drawable )
{
    std::vector<IDrawable*>::iterator it;
    
    for( it = m_Drawables.begin() ; it < m_Drawables.end() ; ++it )
    {
        if( *it == drawable )
        {
            m_Drawables.erase( it );
            delete drawable;
        }
    }
}

//
// Little note on the coordinate system that is being initialized, since everything in this
// game is worked from the centre out to the sides (circular) I set up the coordinates system
// to be centred at the center of the screen. This might seem weird at first, but imagine that
// whenever you need to draw in a circle, you will only need to define a cubical quad from the centre
// out, so no need to work with viewport-dependent offsets of any kind.
//
//  ______________________
// |                      |
// |  10 <--> | <--> 10   |
// |      _________       |
// |   5 |         | 5    |
// |     |   0,0   |      |
// |   5  _________  5    |
// |                      |
// |  10 <--> | <--> 10   |
// |______________________|
//
// One other note on the coordinate system, please bear in mind that the x and y axis are flipped,
// because the game will always be played (with the current implementation) in landscape modus, the
// y axis will be the x axis and other way round. This does not only work so for the accelerometer,
// but also for the coordinates as passed by the iOS wrapper for touch coordinates.
//
void RenderingEngine::Initialize( const int width, const int height )
{
    m_Width = width; m_Height = height;
    
    // Create managers
    m_ResourceManager  = new ResourceManager();
    m_GamestateManager = new GamestateManager();
    m_FontManager      = new FontManager();
    //m_AudioManager     = new AudioManager();
    
    // Always load the no texture texture as the first texture and set every default texture handle for drawables to this texture
    m_ResourceManager->LoadPngTexture( std::string( "Notexture.png" ) );
    
    // Initialize the gamestate manager
    m_GamestateManager->Initialize( m_ResourceManager );
    
    // Initialize the particle system
    Texture *t = m_ResourceManager->LoadPngTexture( std::string( "StarParticle.png" ) );
    m_ParticleSystem = new ParticleSystem( Vector2( 0.0f, 0.0f ), 100.0f, 22, t );
    
    m_ParticleSystem->SetActive( false );
    
    // Load default font
    m_FontManager->LoadFont( "SoupOfJustice.ttf" );
    
    // Create the framebuffer object and attach the color buffer
    glGenFramebuffersOES( 1, &m_Framebuffer );
    glBindFramebufferOES( GL_FRAMEBUFFER_OES, m_Framebuffer );
    glFramebufferRenderbufferOES( GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, m_Renderbuffer );
    
    glViewport( 0, 0, width, height );
    
    glMatrixMode( GL_PROJECTION );
    
    // Initialize the projection matrix
    const float maxX = width * 0.5f;
    const float maxY = height * 0.5f;
    glOrthof( -maxX, +maxX, -maxY, +maxY, -1, 2 );
    
    glMatrixMode( GL_MODELVIEW );
    
    // Enable texturing and blending
    glEnable( GL_TEXTURE_2D );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    
    m_RotationAxis = Vector2( width * 0.5f, height * 0.5f );
    
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
    
    glRotatef( m_Angle, 0.0f, 0.0f, 1.0f );
}

void RenderingEngine::Reset( void )
{
    m_GamestateManager->Reset();
}

RenderingEngine *RenderingEngine::GetRenderingEngine( void )
{
    return (s_RenderingEngine == 0 ? (s_RenderingEngine = new RenderingEngine()) : s_RenderingEngine);
}

ResourceManager *RenderingEngine::GetResourceManager( void )
{
    return m_ResourceManager;
}

FontManager *RenderingEngine::GetFontManager( void )
{
    return m_FontManager;
}

void RenderingEngine::Update( void ) const
{
    m_GamestateManager->Update();
}

void RenderingEngine::Render( void ) const
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    glPushMatrix();
        glEnableClientState( GL_VERTEX_ARRAY );
        glEnableClientState( GL_NORMAL_ARRAY );
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
        
            for( std::vector<IDrawable*>::const_iterator it = m_Drawables.begin(), end = m_Drawables.end(); it != end; ++it )
            {
                (*it)->Render();
                (*it)->Update();
            }
        
        glDisableClientState( GL_VERTEX_ARRAY );
        glDisableClientState( GL_NORMAL_ARRAY );
        glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glPopMatrix();
    
    // Display text
    char b[50];
    
    m_FontManager->Render( "Swipe v0.1", 0, Color( 0.0f, 0.0f, 0.0f, 0.7f ) );
    
    sprintf( b, "Score: %i", m_GamestateManager->GetScore() );
    m_FontManager->Render( b, 0, Color( 0.0f, 0.0f, 0.0f, 0.7f ), Vector2( 0.0f, 732.0f ) );
    
    sprintf( b, "Multiplier: %ix", m_GamestateManager->GetMultiplier() );
    m_FontManager->Render( b, 0, Color( 0.0f, 0.0f, 0.0f, 0.7f ), Vector2( 720.0f, 732.0f ) );
    
    m_FontManager->Render( "Reset", 0, Color( 0.0f, 0.0f, 0.0f, 0.7f ), Vector2( 900.0f, 0.0f ) );
    
    m_FontManager->RenderExplodingTexts();
}

void RenderingEngine::OnRotate( DeviceOrientation orientation )
{
    // Rotation disabled
    return;
    
    switch( orientation ) 
    {
        case DeviceOrientationLandscapeLeft:
            m_Angle = 270;
            break;
        case DeviceOrientationPortraitUpsideDown:
            m_Angle = 180;
            break;
        case DeviceOrientationLandscapeRight:
            m_Angle = 90;
            break;
        default:;
    }
}

bool RenderingEngine::CheckCollision( Vector2 position, Disc *object )
{
    Vector2 c = object->GetCenter();
    float r1 = object->GetInnerRadius();
    float r2 = object->GetOuterRadius();
    
    return IntersectPointAnnulus( position, c, r1, r2 );
}

bool RenderingEngine::CheckCollision( Vector2 position, Gem *object )
{
    Vector2 c = object->GetCenter();
    Vector2 d = object->GetDimensions();
    
    bool a1 = position.x >= c.x - (d.x * 0.75f);
    bool a2 = position.x <= c.x + (d.x * 0.75f);
    bool a3 = position.y >= c.y - (d.y * 0.75f);
    bool a4 = position.y <= c.y + (d.y * 0.75f);
    
    return a1 && a2 && a3 && a4;
}

void RenderingEngine::OnFingerUp( Vector2 location )
{
    // Reset the selected drawable
    m_SelectedDrawable = 0;
    
    Vector2 in = location;
    in.Swap();
    
    // TODO: Fix input coordinates
    
    // Convert to our own coordinate system
    location.x -= (m_Width * 0.5f); location.y -= (m_Height * 0.5f);
    location.Swap();
    
    if( m_Swipe )
    {
        // Detect direction of the vector
        {
            if( fabs( m_SwipeStart.x - location.x ) > 50.0f || fabs( m_SwipeStart.y - location.y ) > 50.0f )
            {
                Gem *b = m_SelectedGem->GetMatchingGem();
                
                float la = VectorToAngle( location );
                float ca = VectorToAngle( b->GetCenter() );
                
                // Use the center angle as the reference for the direction the location vector should be pointing to,
                // we use the halftime SWIPE_ANGLE_OFFSET to validate the location angle against
                if( la - (SWIPE_ANGLE_OFFSET * 0.5f) < ca && la + (SWIPE_ANGLE_OFFSET * 0.5f > ca) )
                {
                    m_GamestateManager->Score( in );
                }
                
                if( b != 0 && b->GetMatchingGem() != 0 )
                {
                    // TODO: Add logic to the newly set types
                    m_SelectedGem->SetActive( false );
                    b->SetActive( false );
                    b->GetMatchingGem()->SetActive( false );
                    
                    m_SelectedGem->SetMatchingGem( 0 );
                    b->SetMatchingGem( 0 );
                    
                    m_GamestateManager->CheckField();
                }
            }
        }
        
        m_ParticleSystem->SetActive( false );
    }
    
    // Reset the selected gem and indicate that we are not in an active swipe
    m_SelectedGem = 0;
    m_Swipe = false;
    
    // On finger up, cast a ray from the outer most gems to the centre to check for
    // collisions with other gems along the ray, if collision are found, check for their types
    // if the types equal the outer most gem, we got a swipe
    
    // TODO: This code is not optizimed and could possibly become slow
    
    // Inner disc at location 0
    Disc **discs = m_GamestateManager->GetDiscs(); 
    
    Gem **outerGems = discs[0]->Gems;
    
    Gem *intersectionGems[3];
    
    // Check outer gems
    for( int i = 0 ; i < GEMS_PER_DISC ; ++i )
    {
        Gem *a = outerGems[i];
        
        int k = 0;
        
        bool swipe = false;
        int gemType = -1;
        
        intersectionGems[k] = a;
        
        // Cast a ray from the outer gem position to the centre
        Ray r( intersectionGems[k]->GetCenter(), Vector2( 0.0f, 0.0f ) );
        
        ++k;
        
        // Check 2 more discs
        for( int n = 1 ; n < 3 ; ++n )
        {
            Gem **gems = discs[n]->Gems;
            
            if( n == 1 || gemType == a->GetGemType() )
            {
                gemType = -1;
                
                // Check gems in disc
                for( int j = 0 ; j < GEMS_PER_DISC ; ++j )
                {
                    Gem *b = gems[j];
                    
                    Line2 bounds[4];
                    b->GetBounds( bounds, 2.0f );
                    
                    bool intersection = false;
                    
                    intersection = intersection || r.Intersect( bounds[0] );
                    intersection = intersection || r.Intersect( bounds[1] );
                    intersection = intersection || r.Intersect( bounds[2] );
                    intersection = intersection || r.Intersect( bounds[3] );
                    
                    if( intersection )
                    {
                        gemType = b->GetGemType();
                        intersectionGems[k++] = b;
                        break;
                    }
                }
            }
        }
        
        // Whenever we have not broken out of our inner search loop, and the final gem type equals
        // the outer gem type, we can assume that every gem has the same type of the outer gem
        if( gemType == a->GetGemType() )
        {
            swipe = true;
        }
        
        // Link all gems to eachother
        if( swipe )
        {
            for( int i = 2 ; i >= 0 ; --i )
            {
                intersectionGems[i]->SetMatchingGem( i - 1 >= 0 ? intersectionGems[i - 1] : 0 );
            }
        }
    }
}

void RenderingEngine::OnFingerDown( Vector2 location )
{
    Vector2 in = location;
    in.Swap();
    
    if( in.x > 900.0f && in.y < 100.0f )
    {
        Reset();
    }
    
    // TODO: Fix input coordinates
    
    // Convert to our own coordinate system
    location.x -= (m_Width * 0.5f); location.y -= (m_Height * 0.5f);
    location.Swap();
    
    for( std::vector<IDrawable*>::const_iterator it = m_Drawables.begin(), end = m_Drawables.end(); it != end; ++it )
    {
        int type = (*it)->GetType();
        
        if( type == GEM )
        {
            if( CheckCollision( location, (Gem*) *it ) )
            {
                if( ((Gem*)*it)->HasMatchingGem() )
                {
                    m_SelectedGem = (Gem*) *it;
                    m_SwipeStart = location;
                    m_Swipe = true;
                    m_ParticleSystem->SetActive( true );
                }
            }
        }
        else if( type == DISC && ((Disc*)*it)->RotationEnabled() ) 
        {
            if( CheckCollision( location, (Disc*) *it ) ) 
            {
                m_SelectedDrawable = *it;
            }
        }
    }
}

void RenderingEngine::OnFingerMove( Vector2 previous, Vector2 location )
{
    if( m_Swipe == false )
    {
        if( m_SelectedDrawable != 0 ) 
        {
            float locationAngle = VectorToAngle( location );
            float previousAngle = VectorToAngle( previous );
            
            m_SelectedDrawable->Angle += (locationAngle - previousAngle);
        }
    }
    
    // Convert to our own coordinate system
    location.x -= (m_Width * 0.5f); location.y -= (m_Height * 0.5f);
    
    // Coordinates need to be flipped for non directional movement
    m_ParticleSystem->SetCenter( Vector2( location.y, location.x ) );
}

// TODO: Might want to put this one in Common
float RenderingEngine::VectorToAngle( Vector2 v )
{
    Vector2 direction = Vector2( v - m_RotationAxis ).Normalize();
    
    direction.y = -direction.y;
    
    float rotationAngle = acos( direction.y ) * 180.0f / PI;
    
    if( direction.x > 0 ) 
    {
        rotationAngle = -rotationAngle;
    }
    
    return rotationAngle;
}





