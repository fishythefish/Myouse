//
//  MyouseController.m
//  Myouse
//
//  Created by Thomas Finch on 9/14/14.
//  Copyright (c) 2014 Thomas Finch. All rights reserved.
//

#import "MyouseController.h"
#import <ApplicationServices/ApplicationServices.h>

@implementation MyouseController

CGPoint lastMouseCoord;

+(void)moveMouseToXCoord:(long)x andYCoord:(long)y {
    lastMouseCoord = CGPointMake(x, y);
    CGWarpMouseCursorPosition(lastMouseCoord);
}

+(void)leftClickDown {
    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseDown, lastMouseCoord, kCGMouseButtonLeft);
    CGEventSetType(theEvent, kCGEventLeftMouseDown);
    CGEventPost(kCGHIDEventTap, theEvent);
    CFRelease(theEvent);
}

+(void)leftClickUp {
    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventLeftMouseUp, lastMouseCoord, kCGMouseButtonLeft);
    CGEventSetType(theEvent, kCGEventLeftMouseUp);
    CGEventPost(kCGHIDEventTap, theEvent);
    CFRelease(theEvent);
}

+(void)rightClickDown {
    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventRightMouseDown, lastMouseCoord, kCGMouseButtonRight);
    CGEventSetType(theEvent, kCGEventRightMouseDown);
    CGEventPost(kCGHIDEventTap, theEvent);
    CFRelease(theEvent);
}

+(void)rightClickUp {
    CGEventRef theEvent = CGEventCreateMouseEvent(NULL, kCGEventRightMouseUp, lastMouseCoord, kCGMouseButtonRight);
    CGEventSetType(theEvent, kCGEventRightMouseUp);
    CGEventPost(kCGHIDEventTap, theEvent);
    CFRelease(theEvent);
}

+(void)scrollMouse:(int)speed {
    CGEventRef event = CGEventCreateScrollWheelEvent(NULL, kCGScrollEventUnitPixel, 1, speed);
    CGEventSetType(event, kCGEventScrollWheel);
    CGEventPost(kCGHIDEventTap, event);
    CFRelease(event);
}

@end
