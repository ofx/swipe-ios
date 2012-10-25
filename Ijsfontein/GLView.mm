//
//  GLView.m
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/14/11.
//  Copyright 2011 ofx. All rights reserved.
//

#import <OpenGLES/EAGLDrawable.h>
#import "GLView.h"
#import "mach/mach_time.h"
#import <OpenGLES/ES2/gl.h>

@implementation GLView

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (id) initWithFrame: (CGRect) frame
{
    if ((self = [super initWithFrame:frame])) 
    {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
        eaglLayer.opaque = YES;
        
        m_Context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        
        if (!m_Context || ![EAGLContext setCurrentContext:m_Context]) 
        {
            [self release];
            
            return nil;
        }
        
        m_RenderingEngine = RenderingEngine::GetRenderingEngine();        
        
        [m_Context
         renderbufferStorage:GL_RENDERBUFFER
         fromDrawable: eaglLayer];
        
        m_RenderingEngine->Initialize( CGRectGetWidth( frame ), CGRectGetHeight( frame ) );
        
        [self drawView: nil];
        m_Timestamp = CACurrentMediaTime();
        
        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self
                                                  selector:@selector(drawView:)];
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop]
                          forMode:NSDefaultRunLoopMode];
        
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        
        [[NSNotificationCenter defaultCenter]
         addObserver:self
         selector:@selector(didRotate:)
         name:UIDeviceOrientationDidChangeNotification
         object:nil];
    }
    
    return self;
}

- (void) touchesBegan: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint location  = [touch locationInView: self];
    m_RenderingEngine->OnFingerDown( Vector2( location.x, location.y ) );
}

- (void) touchesEnded: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint location  = [touch locationInView: self];
    m_RenderingEngine->OnFingerUp( Vector2( location.x, location.y ) );
}

- (void) touchesMoved: (NSSet*) touches withEvent: (UIEvent*) event
{
    UITouch* touch = [touches anyObject];
    CGPoint previous  = [touch previousLocationInView: self];
    CGPoint current = [touch locationInView: self];
    m_RenderingEngine->OnFingerMove( Vector2( previous.x, previous.y ), Vector2( current.x, current.y ) );
}

- (void) didRotate: (NSNotification*) notification
{
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    m_RenderingEngine->OnRotate( (DeviceOrientation) orientation );
    [self drawView: nil];
}

- (void) drawView: (CADisplayLink*) displayLink
{
    if( displayLink != nil ) 
    {
        float elapsedSeconds = displayLink.timestamp - m_Timestamp;
        m_Timestamp = displayLink.timestamp;
        m_RenderingEngine->UpdateAnimation( elapsedSeconds );
    }
    
    m_RenderingEngine->Update();
    m_RenderingEngine->Render();
    [m_Context presentRenderbuffer:GL_RENDERBUFFER];
}

@end
