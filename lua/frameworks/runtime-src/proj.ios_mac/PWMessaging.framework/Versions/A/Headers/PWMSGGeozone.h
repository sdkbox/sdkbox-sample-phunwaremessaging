//
//  PWMSGGeozone.h
//  PWMessaging
//
//  Copyright (c) 2015 Phunware, Inc. All rights reserved.
//

@import Foundation;
@import CoreLocation;

#import "PWMSGZoneProtocol.h"

/**
 * A PWMSGGeozone object represents a circular region in a map with some associated data
 * for that region.
 */
@interface PWMSGGeozone : NSObject <PWMSGZone, NSSecureCoding, NSCopying>

/**
 The circular region represented by the PWMSGGeozone object. (read-only)
 @discussion  When working with CLRegions, you should never perform pointer-level comparisons to determine equality. Instead, use the region’s identifier string to compare regions.
 */
@property (readonly, nonatomic) CLCircularRegion *region;

/**
 The geozone identifier. (read-only)
 */
@property (readonly, nonatomic) NSString * identifier;

/**
 The name given to the geozone object. (read-only)
 */
@property (readonly, nonatomic) NSString * name;

/**
 The code assigned to the geozone object. (read-only)
 */
@property (readonly, nonatomic) NSString * code;

/**
 The description assigned to the geozone object. (read-only)
 */
@property (readonly, nonatomic) NSString * zoneDescription;

/**
 A flag that indicates if the user is currently inside the geozone. (read-only)
 */
@property (readonly, nonatomic) BOOL inside;

/**
 * A flag that indicates if the zone is monitored. (read-only)
 */
@property (nonatomic, readonly) BOOL monitored;

/**
 A set of tags associated to the geozone. (read-only)
 */
@property (readonly, nonatomic) NSSet *tags;



/**
 * Unavailable initializer.
 * @return
 */
- (instancetype)init NS_UNAVAILABLE;

@end
