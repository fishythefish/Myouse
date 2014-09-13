//
//  AppDelegate.m
//  Myo_Mouse
//
//  Created by Andrew Rochman on 9/13/14.
//  Copyright (c) 2014 Andrew Rochman. All rights reserved.
//

#import "AppDelegate.h"
#import <ApplicationServices/ApplicationServices.h>

@implementation AppDelegate

@synthesize statusItem = _statusItem;

- (void)awakeFromNib {
    self.statusItem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
    self.statusItem.title = @"Myouse";
    self.statusItem.menu = self.menu;
    self.statusItem.highlightMode = YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    
    CGWarpMouseCursorPosition(CGPointMake(100, 100));
}

@end
