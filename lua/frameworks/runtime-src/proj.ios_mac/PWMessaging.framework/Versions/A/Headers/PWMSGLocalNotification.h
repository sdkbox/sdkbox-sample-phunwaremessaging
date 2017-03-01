//
//  PWLPLocalNotification.h
//  PWMessaging
//
//  Copyright (c) 2015 Phunware, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <PWMessaging/PWMSGZoneMessage.h>

extern NSString *const PWMSGLocalNotificationSendNotification;

// UserInfo dictionary keys
extern NSString *const PWMSGLocalNotificationUserInfoMessageIdentifierKey;
extern NSString *const PWMSGLocalNotificationUserInfoCampaignTypeKey;
extern NSString *const PWMSGLocalNotificationUserInfoAlertTitleKey;
extern NSString *const PWMSGLocalNotificationUserInfoAlertBodyKey;

/**
 * A PWLPLocalNotification object holds the information related to a local notification that will be shown to the user. The PWLPLocalNotification object allows the alert title and alert body to be modified if needed.
 */
@interface PWMSGLocalNotification : NSObject

/**
 Returns the title of the local notification.
 @discussion This method should never return `nil`.
 @return The title of this local notification.
 */
@property (copy) NSString *alertTitle;

/**
 Returns the alert body of the local notification.
 @discussion This method should never return `nil`.
 @return The message of this local notification.
 */
@property (copy) NSString *alertBody;

/**
 The zone message associated with the local notification.
 @return The zone message associated with the local notification.
 */
@property (readonly) PWMSGZoneMessage *message;

@end
