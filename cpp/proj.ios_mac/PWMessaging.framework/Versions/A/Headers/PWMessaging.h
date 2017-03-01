//
//  PWMessaging.h
//  PWMessaging
//
//  Created by Xiangwei Wang on 1/29/16.
//  Copyright © 2016 Phunware Inc. All rights reserved.
//

@import UIKit;
@import Foundation;

#import <PWMessaging/PWMSGGeozone.h>
#import <PWMessaging/PWMSGZoneMessage.h>
#import <PWMessaging/PWMSGLocalNotification.h>
#import <PWMessaging/PWMSGAttributeManager.h>

/**
 The message identifier key which may be included in the notification's userInfo dictionary.
 */
extern NSString *const PWLMMessageIdentifierKey;

/**
 Post when there was new message arrived, and the identifer of the new message is included in the notification's userInfo dictionary. The message is included in the notification's userInfo dictionary with the `PWLMMessageIdentifierKey` key.
 */
extern NSString *const PWLMReceiveMessageNotificationKey;

/**
 Post when there was a message removed, and the identifer of the removed message is included in the notification's userInfo dictionary. The message is included in the notification's userInfo dictionary with the `PWLMMessageIdentifierKey` key.
 */
extern NSString *const PWLMDeleteMessageNotificationKey;

/**
 Post when there was a message modified, and the identifer of the modified message is included in the notification's userInfo dictionary. The message is included in the notification's userInfo dictionary with the `PWLMMessageIdentifierKey` key.
 */
extern NSString *const PWLMModifyMessageNotificationKey;

/**
 Post when there was a message read, and the identifer of the read message is included in the notification's userInfo dictionary. The message is included in the notification's userInfo dictionary with the `PWLMMessageIdentifierKey` key.
 */
extern NSString *const PWLMReadMessageNotificationKey;

/**
 The error key which may be included in the notification's userInfo dictionary.
 */
extern NSString *const PWLMNotificationErrorKey;

/**
 The geo zone identifier key which may be included in the notification's userInfo dictionary.
 */
extern NSString *const PWLMGeoZoneIdentifierKey;

/**
 The geo zone identifier array key which may be included in the notification's userInfo dictionary.
 */
extern NSString *const PWLMGeoZoneIdentifierArrayKey;

/**
 * Posted when determines that the device enters a geo zone. The zone identifer is included in the notification's userInfo dictionary with the `PWLMGeoZoneIdentifierKey` key.
 */
extern NSString *const PWLMEnterGeoZoneNotificationKey;

/**
 * Posted when the zone manager determines that the device exits a geo zone. The zone identifer is included in the notification's userInfo dictionary with the `PWLMGeoZoneIdentifierKey` key.
 */
extern NSString *const PWLMExitGeoZoneNotificationKey;

/**
 * Posted when new zones are added to the zone manager's list of available geo zones. The identifers of the new zones are included in the notification's userInfo dictionary with the 'PWLMGeoZoneIdentifierArrayKey' key.
 */
extern NSString *const PWLMAddGeoZonesNotificationKey;

/**
 * Posted when zones are removed from the zone manager's list of available geo zones. The identifers of the removed zones are included in the notification's userInfo dictionary with the 'PWLMGeoZoneIdentifierArrayKey' key.
 */
extern NSString *const PWLMDeleteGeoZonesNotificationKey;

/**
 * Posted when the information about one or more geo zones is modified. The identifers of the modified zones are included in the notification's userInfo dictionary with the 'PWLMGeoZoneIdentifierArrayKey' key.
 */
extern NSString *const PWLMModifyGeoZonesNotificationKey;

/**
 * Posted when location messaging service is ready.
 */
extern NSString *const PWLMLocationServiceReadyNotificationKey;

/**
 * Posted when determines that the monitored geo zone changes. 
 */
extern NSString *const PWLMMonitoredGeoZoneChangesNotificationKey;

/**
 * The Location Messaging framework is a location and notification based system.
 *
 * The recommended way to start Location Messaging in your application is to place a call
 * to `+startWithmaasAppId:accessKey:signatureKey:encryptionKey:completion:` in your `-application:didFinishLaunchingWithOptions:` method.
 *
 * This delay defaults to 1 second in order to generally give the application time to
 * fully finish launching.
 *
 * The framework needs you to forward the following methods from your application delegate:
 *
 * - 'didFinishLaunchingWithOptions:withCompletionHandler:'
 * - 'didRegisterForRemoteNotificationsWithDeviceToken:withNotificationHandler:'
 * - 'didFailToRegisterForRemoteNotificationsWithError:withNotificationHandler:'
 * - 'didReceiveRemoteNotification:withNotificationHandler:'
 *
 * You can optionally add a delegate to be informed about errors while initalizing the location marketing service and to control the display of local notifications to the user.
 **/
@interface PWMessaging : NSObject

/**
 * Starts the Location Messaging service with environment.
 * @param maasAppId You can find your Application ID in the MaaS portal.
 * @param accessKey A unique key that identifies the client making the request. You can find your Access Key in the MaaS portal.
 * @param signatureKey A unique key that is used to sign requests. The signature is used to both check request authorization as well as data integrity. You can find your Signature Key in the MaaS portal.
 * @param encryptionKey The key used to encrypt and decrypt data that is exchanged between the client and the server. You can find your Encryption Key in the MaaS portal.
 * @param completion A block that notify location messaging service is successfully started or failed to start with reason.
 *      - *param1* error It's nil when it's started successfully, or an error object containing information about a problem that indicates location messaging service failed to start.
 * @return A singleton class of `LocationMessaging`
 */
+ (void)startWithMaasAppId:(NSString *)maasAppId
				   accessKey:(NSString *)accessKey
				signatureKey:(NSString *)signatureKey
			   encryptionKey:(NSString *)encryptionKey
				  completion:(void(^)(NSError *error))completion;


/**
 * Stop location messaging service.
 * @param completion A block that notify location messaging service is successfully stopped or failed to stop with reason.
 *
 *      - *error* It's nil when it's stopped successfully, or an error object containing information about a problem that indicates location messaging service failed to stop.
 */
+ (void)stopWithCompletion:(void(^)(NSError *error))completion;

/**
 * All the available `PWLPGeozone` list.
 */
+ (NSArray *)geozones;

/**
 * All the available `PWLPZoneMessage` list.
 */
+ (NSArray *)messages;

/**
 * Return the device identifier which the location messaging service uses.
 */
+ (NSString *)deviceId;

/**
 * Return the current SDK version of location messaging.
 */
+ (NSString *)version;

/**
 * The name of the location messaging service.
 */
+ (NSString *)serviceName;

/**
 * Set the block to handle the error when it occurs.
 *
 * @param handler A block that caused location messaging service failed.
 *
 *      - *error* An error object containing information about a problem that indicates location messaging service failed if the results are retrieved successfully.
 */
+ (void)setErrorHandler:(void(^)(NSError *error))handler;

/**
 * Set the block to handle the local notification which is about to display.
 * @discussion The local notification will be displayed if the block returns `YES`, otherwise, it will not be displayed.
 * @param handler A block that notifies the local notification is about to display, you can control the local notification display and customize the display content.
 *
 *      - *notification* The `PWLPLocalNotification` object which contains notification information to display.
 *      - @return The local notification will be displayed if returns `YES`, otherwise, it will not be displayed.
 */
+ (void)setLocalNotificationHandler:(BOOL(^)(PWMSGLocalNotification *notification))handler;

/**
 * Lets the location messaging service know that launch process is almost done and the app is almost ready to run.(APNs).
 * @discussion The message deep linking could be fired from the `completionHandler` block. And if returns `YES` in the block, it will prompt an alert tells user how to enable push notification setting when it's disabled, and the prompted message could be configured in localized string file with key `RemindOfEnablePushNotificationSettings`.
 * @param launchOptions A dictionary indicating the reason the app was launched (if any). The contents of this dictionary may be empty in situations where the user launched the app directly. For information about the possible keys in this dictionary and how to handle them, see Launch Options Keys.
 * @param completionHandler A block that tells if user opens the app by tapping a notification.
 *
 *      - *notification* The notification object if user open the app by tapping a notification from notification tray, otherwise, it's nil.
 */
+ (void)didFinishLaunchingWithOptions:(NSDictionary *)launchOptions withCompletionHandler:(BOOL(^)(PWMSGLocalNotification *notification))completionHandler;

/**
 * Lets the location messaging service know that the app successfully registered with Apple Push Notification service (APNs).
 * @param deviceToken A token that identifies the device to APNs. The token is an opaque data type because that is the form that the provider needs to submit to the APNs servers when it sends a notification to a device. The APNs servers require a binary format for performance reasons. The size of a device token is 32 bytes. Note that the device token is different from the uniqueIdentifier property of UIDevice because, for security and privacy reasons, it must change when the device is wiped.
 */
+ (void)didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken;

/**
 * Lets the location messaging service know that the Apple Push Notification service cannot successfully complete the registration process.
 * @param error An NSError object that encapsulates information why registration did not succeed. The app can choose to display this information to the user.
 */
+ (void)didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;

/**
 * Lets the location messaging service know that the app receives a local notification, so that it can process it internally.
 * @discussion The message deep linking could be fired from the `completion` block.
 * @param notification A `UILocalNotification` object.
 * @param notificationHandler A block that tells the notification with message which was received.
 *
 *      - *notification* The notification object which was received.
 */
+ (void)didReceiveLocalNotification:(UILocalNotification *)notification withNotificationHandler:(void(^)(PWMSGLocalNotification *notification))notificationHandler;

/**
 * Lets the location messaging service know that the app receives a remote notification, so that it can process it internally.
 * @discussion The message deep linking could be fired from the `notificationHandler` block.
 * @param userInfo A dictionary that contains information related to the remote notification, potentially including a badge number for the app icon, an alert sound, an alert message to display to the user, a notification identifier, and custom data. The provider originates it as a JSON-defined dictionary that iOS converts to an NSDictionary object; the dictionary may contain only property-list objects plus NSNull.
 * @param notificationHandler A block that tells the notification with message which was received.
 *
 *      - *notification* The notification object which was received.
 */
+ (void)didReceiveRemoteNotification:(NSDictionary *)userInfo withNotificationHandler:(void(^)(PWMSGLocalNotification *notification))notificationHandler;

/**
 * Lets the location messaging service know that the app receives a remote notification, so that it can process it internally.
 * @discussion The message deep linking could be fired from the `notificationHandler` block.
 * @param userInfo A dictionary that contains information related to the remote notification, potentially including a badge number for the app icon, an alert sound, an alert message to display to the user, a notification identifier, and custom data. The provider originates it as a JSON-defined dictionary that iOS converts to an NSDictionary object; the dictionary may contain only property-list objects plus NSNull. 
 * @param completionHandler The block to execute when the download operation is complete. When calling this block, pass in the fetch result value that best describes the results of your download operation. You must call this handler and should do so as soon as possible. For a list of possible values, see the UIBackgroundFetchResult type.
 *
 *      - *userInfo* A dictionary that contains information related to the remote notification, potentially including a badge number for the app icon, an alert sound, an alert message to display to the user, a notification identifier, and custom data. The provider originates it as a JSON-defined dictionary that iOS converts to an NSDictionary object; the dictionary may contain only property-list objects plus NSNull.
 * @param notificationHandler A block that tells the notification with message which was received.
 *
 *      - *notification*: The notification object which was received.
 */
+ (void)didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler  withNotificationHandler:(void(^)(PWMSGLocalNotification *notification))notificationHandler;

@end
