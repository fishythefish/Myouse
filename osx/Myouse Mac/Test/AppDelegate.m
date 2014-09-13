//
//  AppDelegate.m
//  Test
//
//  Created by Thomas Finch on 9/12/14.
//  Copyright (c) 2014 Thomas Finch. All rights reserved.
//

#import "AppDelegate.h"
//#import <ApplicationServices/ApplicationServices.h>
#import "Myouse-test.cpp"

void moveMouse();

@interface AppDelegate ()

@property (weak) IBOutlet NSWindow *window;
@property (strong, nonatomic) NSStatusItem *statusBar;
@property (weak) IBOutlet NSMenu *menu;
@end

@implementation AppDelegate

@synthesize statusBar = _statusBar;

- (void) awakeFromNib {
    self.statusBar = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
    
    self.statusBar.title = @"Myouse";
    
    // you can also set an image
    //self.statusBar.image =
    
    self.statusBar.menu = self.menu;
    self.statusBar.highlightMode = YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    // Insert code here to initialize your application
    moveMouse();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
