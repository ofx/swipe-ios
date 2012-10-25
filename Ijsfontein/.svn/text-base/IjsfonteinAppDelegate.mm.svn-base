//
//  IjsfonteinAppDelegate.m
//  Ijsfontein
//
//  Created by Marlon Etheredge on 4/14/11.
//  Copyright 2011 ofx. All rights reserved.
//

#import "IjsfonteinAppDelegate.h"


@implementation IjsfonteinAppDelegate


- (BOOL) application: (UIApplication*) application didFinishLaunchingWithOptions: (NSDictionary*) launchOptions
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    
    m_Window = [[UIWindow alloc] initWithFrame: screenBounds];
    m_View   = [[GLView alloc] initWithFrame: screenBounds];
    
    [m_Window addSubview: m_View];
    [m_Window makeKeyAndVisible];
    
    return YES;
}

- (void) dealloc
{
    [m_View release]; 
    [m_Window release]; 
    
    [super dealloc];
}

@end
