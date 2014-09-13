//
//  AppDelegate.h
//  Myo_Mouse
//
//  Created by Andrew Rochman on 9/13/14.
//  Copyright (c) 2014 Andrew Rochman. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (weak) IBOutlet NSMenu *menu;
@property (strong, nonatomic) NSStatusItem *statusItem;

@property (assign) IBOutlet NSWindow *window;

@end
