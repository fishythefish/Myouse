//
//  MyouseController.h
//  Myouse
//
//  Created by Thomas Finch on 9/14/14.
//  Copyright (c) 2014 Thomas Finch. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MyouseController : NSObject

+(void)moveMouseToXCoord:(long)x andYCoord:(long)y;
+(void)leftClickDown;
+(void)leftClickUp;
+(void)rightClickDown;
+(void)rightClickUp;
+(void)scrollMouse:(int)speed;

@end
