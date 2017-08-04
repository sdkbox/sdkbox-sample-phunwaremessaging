
var HelloWorldLayer = cc.Layer.extend({
    sprite:null,
    ctor:function () {
        //////////////////////////////
        // 1. super init first
        this._super();

        cc.log("Sample Startup")

        this.createTestMenu();

        var winsize = cc.winSize;

        var logo = new cc.Sprite("res/Logo.png");
        var logoSize = logo.getContentSize();
        logo.x = logoSize.width / 2;
        logo.y = winsize.height - logoSize.height / 2;
        this.addChild(logo);

        // var quit = new cc.MenuItemLabel(new cc.LabelTTF("QUIT", "sans", 32), function() {
        //     cc.log("QUIT");
        // });
        // var menu = new cc.Menu(quit);
        // var size = quit.getContentSize();
        // menu.x = winsize.width - size.width / 2 - 16;
        // menu.y = size.height / 2 + 16;
        // this.addChild(menu);

        sdkbox.PluginPhunwareMessaging.init();
        sdkbox.PluginPhunwareMessaging.setListener({
            init : function(success, message) { cc.log("init:" + message)},
            error: function(message) { cc.og("error:"+message)},
        });

        return true;
    },

    createTestMenu:function() {
        var menu = new cc.Menu();

        var item1 = new cc.MenuItemLabel(new cc.LabelTTF(sdkbox.PluginPhunwareMessaging.deviceId(), "sans", 28), function() {
        });
        menu.addChild(item1);

        var item2 = new cc.MenuItemLabel(new cc.LabelTTF(sdkbox.PluginPhunwareMessaging.serviceName(), "sans", 28), function() {
        });
        menu.addChild(item2);

        var item3 = new cc.MenuItemLabel(new cc.LabelTTF(sdkbox.PluginPhunwareMessaging.version(), "sans", 28), function() {
            cc.log("Test Item 3");
        });
        menu.addChild(item3);

        var winsize = cc.winSize;
        menu.x = winsize.width / 2;
        menu.y = winsize.height / 2;
        menu.alignItemsVerticallyWithPadding(20);
        this.addChild(menu);
    }
});

var HelloWorldScene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new HelloWorldLayer();
        this.addChild(layer);
    }
});

