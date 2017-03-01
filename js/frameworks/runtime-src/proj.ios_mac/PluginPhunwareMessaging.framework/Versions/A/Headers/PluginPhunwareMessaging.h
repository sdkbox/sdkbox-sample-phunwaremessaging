/****************************************************************************

 Copyright (c) 2014-2017 SDKBOX Inc

 ****************************************************************************/

#ifndef _PLUGIN_PHUNWAREMESSAGING_H_
#define _PLUGIN_PHUNWAREMESSAGING_H_

#include <string>
#include <vector>

namespace sdkbox {

    class PWZoneMessage {
    public:
        // A Boolean value indicating whether or not the entry is read.
        bool isRead;
        // Returns the alert title of this message. This property will never return a `nil` value.
        std::string alertTitle;
        // Returns the alert body of this message. This property will never return a `nil` value.
        std::string alertBody;
        // Returns the promotion title of this message. This property will never return a `nil` value.
        std::string promotionTitle;
        // Returns the promotion body of this message. The value returned by this method is usually HTML.
        // This property will never return a `nil` value.
        std::string promotionBody;
        // Returns the internal unique identifier of the message. This identifier also idenfities the campaign this message was sent for.
        std::string identifier;
        // A string containing the campaign type of the message.
        std::string campaignType;
    };

    class PWLocalNotification {
    public:
        // The title of this local notification.
        std::string alertTitle;
        // The message of this local notification.
        std::string alertBody;
        // The zone message associated with the local notification.
        PWZoneMessage message;
    };
    class PWGeozone {
    public:
        // The geozone identifier.
        std::string identifier;
        // The name given to the geozone object.
        std::string name;
        // The code assigned to the geozone object.
        std::string code;
        // The description assigned to the geozone object.
        std::string zoneDescription;
        // A flag that indicates if the user is currently inside the geozone.
        bool inside;
        // A flag that indicates if the zone is monitored. (read-only)
        bool monitored;
    };

    class PhunwareMessagingListener;
    class PluginPhunwareMessaging {
    public:

        /**
         *  initialize the plugin instance.
         */
        static bool init();

        /**
         * Set listener to listen for phunwaremessaging events
         */
        static void setListener(PhunwareMessagingListener* listener);

        /**
         * Get the listener
         */
        static PhunwareMessagingListener* getListener();

        /**
         * Remove the listener, and can't listen to events anymore
         */
        static void removeListener();

        static void read(const std::string& messageID);

        static void remove(const std::string& messageID);

        static std::vector<sdkbox::PWZoneMessage> messages();

        static std::vector<sdkbox::PWGeozone> geozones();

        static std::string deviceId();
        static std::string serviceName();
        static std::string version();

        static void stop();
        };

    class PhunwareMessagingListener {
    public:

        /**
         * Notifies the delegate that the module has finished loading
         */
        // virtual void onModuleLoaded(const std::string& placement) {};
        virtual void init(bool success, const std::string& message)   {}
        virtual void error(const std::string& message)  {}
        virtual void notification(sdkbox::PWLocalNotification notifi) {}

    };
}

#endif
