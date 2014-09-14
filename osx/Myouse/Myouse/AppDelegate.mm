//
//  AppDelegate.m
//  Myouse
//
//  Created by Thomas Finch on 9/14/14.
//  Copyright (c) 2014 Thomas Finch. All rights reserved.
//

#import "AppDelegate.h"
#import "myouse.h"

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@end

@implementation AppDelegate

@synthesize statusItem = _statusItem;
@synthesize statusMenu = _statusMenu;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    self.statusItem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
    self.statusItem.title = @"Myouse";
    self.statusItem.menu = self.statusMenu;
    self.statusItem.highlightMode = YES;
    
    runMyouse();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
