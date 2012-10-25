//
//  GLView.h
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/14/11.
//  Copyright 2011 ofx. All rights reserved.
//

#import "RenderingEngine.hpp"
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>

@interface GLView : UIView 
{
@private
    EAGLContext *m_Context;
    
    RenderingEngine *m_RenderingEngine;
    
    float m_Timestamp;
}

- (void) drawView: (CADisplayLink*) displayLink;
- (void) didRotate: (NSNotification*) notification;

@end
