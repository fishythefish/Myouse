//
//  Movement.cpp
//  Myouse
//
//  Created by Andrew Rochman on 9/13/14.
//  Copyright (c) 2014 Andrew Rochman. All rights reserved.
//

#include "Movement.h"
#import <ApplicationServices/ApplicationServices.h>
#import <Foundation/Foundation.h>

void moveToPoint(int xpos, int ypos) {
    CGWarpMouseCursorPosition(CGPointMake(xpos, ypos));
}

void clickAtPoint() {
    NSPoint mouseLoc = [NSEvent mouseLocation];
    
    CGEventRef click1_down = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseDown,
        CGPointMake(mouseLoc.xpos, mouseLoc.ypos),
        kCGMouseButtonLeft);
    
    CGEventPost(kCGHIDEventTap, click1_down);
    CFRelease(click1_down);
}

void unClickAtPoint() {
    
    
    CGEventRef click1_up = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseUp,
        CGPointMake(250, 250),
        kCGMouseButtonLeft);
    
    CGEventPost(kCGHIDEventTap, click1_up);
    CFRelease(click1_up);
}