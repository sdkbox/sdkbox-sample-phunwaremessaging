
#include "HelloWorldScene.h"

#include "PluginPhunwareMessaging/PluginPhunwareMessaging.h"
using namespace sdkbox;

USING_NS_CC;


MenuItemFont *deviceIdMenuItem = 0;
class CustomListener : public sdkbox::PhunwareMessagingListener {
public:
    void init(bool success, const std::string& message) {
        CCLOG("success=%s, message=%s", success ? "yes" : "no", message.c_str());

        if (deviceIdMenuItem) {
            deviceIdMenuItem->setString("deviceID="+sdkbox::PluginPhunwareMessaging::deviceId());
        }
    }
    void error(const std::string& message) {
        CCLOG("error=%s", message.c_str());
    }
    
};

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    CCLOG("Sample Startup");

    // add logo
    auto winsize = Director::getInstance()->getWinSize();
    auto logo = Sprite::create("Logo.png");
    auto logoSize = logo->getContentSize();
    logo->setPosition(Vec2(logoSize.width / 2,
                           winsize.height - logoSize.height / 2));
    addChild(logo);

    // add quit button
    auto label = Label::createWithSystemFont("QUIT", "sans", 32);
    auto quit = MenuItemLabel::create(label, [](Ref*){
        exit(0);
    });
    auto labelSize = label->getContentSize();
    quit->setPosition(Vec2(winsize.width / 2 - labelSize.width / 2 - 16,
                           -winsize.height / 2 + labelSize.height / 2 + 16));
    addChild(Menu::create(quit, NULL));

    // add test menu
    createTestMenu();

    return true;
}

void HelloWorld::createTestMenu()
{
    MenuItemFont::setFontName("sans");
    MenuItemFont::setFontSize(16);

    sdkbox::PluginPhunwareMessaging::setListener(new CustomListener());
//    sdkbox::PluginPhunwareMessaging::init();

    deviceIdMenuItem = MenuItemFont::create("deviceID="+sdkbox::PluginPhunwareMessaging::deviceId());

    auto menu = Menu::create(
                             deviceIdMenuItem,
                             MenuItemFont::create("serviceName="+sdkbox::PluginPhunwareMessaging::serviceName()),
                             MenuItemFont::create("pw version="+sdkbox::PluginPhunwareMessaging::version()),
                             MenuItemFont::create("messages", [](Ref*){
        std::vector<sdkbox::PWZoneMessage> msgs = PluginPhunwareMessaging::messages();
        for (auto item : msgs) {
            CCLOG("isRead=%s", item.isRead ? "yes" : "no");
            CCLOG("alertTitle=%s", item.alertTitle.c_str());
            CCLOG("alertBody=%s", item.alertBody.c_str());
            CCLOG("promotionTitle=%s", item.promotionTitle.c_str());
            CCLOG("promotionBody=%s", item.promotionBody.c_str());
            CCLOG("identifier=%s", item.identifier.c_str());
            CCLOG("campaignType=%s", item.campaignType.c_str());
            CCLOG("\n");
        }
    }), NULL);
    menu->alignItemsVerticallyWithPadding(10);
    addChild(menu);
    

}

