//
//  Myouse.cpp
//  Test
//
//  Created by Thomas Finch on 9/13/14.
//  Copyright (c) 2014 Thomas Finch. All rights reserved.
//

#include <stdio.h>
#include <ApplicationServices/ApplicationServices.h>

void moveMouse() {
    CGWarpMouseCursorPosition(CGPointMake(100, 100));
}
