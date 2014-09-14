//
//  AppDelegate.h
//  Myouse
//
//  Created by Thomas Finch on 9/14/14.
//  Copyright (c) 2014 Thomas Finch. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
@property (weak, nonatomic) NSStatusItem *statusItem;
@property (weak) IBOutlet NSMenu *statusMenu;


@end

