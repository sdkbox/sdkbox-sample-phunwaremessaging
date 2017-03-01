#include "PluginPhunwareMessagingJSHelper.h"
#include "PluginPhunwareMessaging/PluginPhunwareMessaging.h"
#include "SDKBoxJSHelper.h"

using namespace sdkbox;

extern JSObject* jsb_sdkbox_PluginPhunwareMessaging_prototype;
static JSContext* s_cx = nullptr;

JSOBJECT* PWMessageToJS(JSContext* cx, const PWZoneMessage& msg) {
    JS_INIT_CONTEXT_FOR_UPDATE(s_cx);

    JSOBJECT* jsobj= JS_NEW_OBJECT(s_cx);

    addProperty( s_cx, jsobj, "isRead", msg.isRead ? "true" : "false");
    addProperty( s_cx, jsobj, "alertTitle", msg.alertTitle);
    addProperty( s_cx, jsobj, "alertBody", msg.alertBody);
    addProperty( s_cx, jsobj, "promotionTitle", msg.promotionTitle);
    addProperty( s_cx, jsobj, "promotionBody", msg.promotionBody);
    addProperty( s_cx, jsobj, "identifier", msg.identifier);
    addProperty( s_cx, jsobj, "campaignType", msg.campaignType);

    return jsobj;
}

JSOBJECT* PWGeoZoneToJS(JSContext* cx, const PWGeozone& zone) {
    JS_INIT_CONTEXT_FOR_UPDATE(s_cx);

    JSOBJECT* jsobj= JS_NEW_OBJECT(s_cx);

    addProperty( s_cx, jsobj, "identifier", zone.identifier);
    addProperty( s_cx, jsobj, "name", zone.name);
    addProperty( s_cx, jsobj, "code", zone.code);
    addProperty( s_cx, jsobj, "zoneDescription", zone.zoneDescription);
    addProperty( s_cx, jsobj, "inside", zone.inside);
    addProperty( s_cx, jsobj, "monitored", zone.monitored);

    return jsobj;
}

class PhunwareMessaging_CallbackJS: public
#if COCOS2D_VERSION >= 0x00030000
cocos2d::Ref {
#else
    cocos2d::CCObject {
#endif
public:
    PhunwareMessaging_CallbackJS();
    void schedule();
    void notityJs(float dt);

    std::string _name;

    jsval _paramVal[2];
    int _paramLen;
};

class PhunwareMessagingListenerJS : public sdkbox::PhunwareMessagingListener {
private:
    JSObject* _JSDelegate;
public:
    void setJSDelegate(JSObject* delegate) {
        _JSDelegate = delegate;
    }

    JSObject* getJSDelegate() {
        return _JSDelegate;
    }

    virtual void init(bool success, const std::string& message)   {
        PhunwareMessaging_CallbackJS* cb = new PhunwareMessaging_CallbackJS();
        cb->_name = __FUNCTION__;
        cb->_paramVal[0] = BOOLEAN_TO_JSVAL(success);
        cb->_paramVal[1] = std_string_to_jsval(s_cx, message);
        cb->_paramLen = 2;
        cb->schedule();
    }
    virtual void error(const std::string& message)  {
        PhunwareMessaging_CallbackJS* cb = new PhunwareMessaging_CallbackJS();
        cb->_name = __FUNCTION__;
        cb->_paramVal[0] = std_string_to_jsval(s_cx, message);
        cb->_paramLen = 1;
        cb->schedule();
    }

    void invokeJS(const char* func, jsval* pVals, int valueSize) {
        if (!s_cx) {
            return;
        }
        JSContext* cx = s_cx;
        const char* func_name = func;
        JS::RootedObject obj(cx, _JSDelegate);
        JSAutoCompartment ac(cx, obj);

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
        bool hasAction;
        JS::RootedValue retval(cx);
        JS::RootedValue func_handle(cx);
#else
        bool hasAction;
        jsval retval;
        JS::RootedValue func_handle(cx);
#endif
#elif defined(JS_VERSION)
        JSBool hasAction;
        jsval retval;
        jsval func_handle;
#endif

        if (JS_HasProperty(cx, obj, func_name, &hasAction) && hasAction) {
            if(!JS_GetProperty(cx, obj, func_name, &func_handle)) {
                return;
            }
            if(func_handle == JSVAL_VOID) {
                return;
            }

#if MOZJS_MAJOR_VERSION >= 31
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::empty(), &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, JS::HandleValueArray::fromMarkedLocation(valueSize, pVals), &retval);
            }
#else
            if (0 == valueSize) {
                JS_CallFunctionName(cx, obj, func_name, 0, nullptr, &retval);
            } else {
                JS_CallFunctionName(cx, obj, func_name, valueSize, pVals, &retval);
            }
#endif
        }
    }

};


PhunwareMessaging_CallbackJS::PhunwareMessaging_CallbackJS():
_paramLen(0) {
}

void PhunwareMessaging_CallbackJS::schedule() {
    retain();
#if COCOS2D_VERSION >= 0x00030000
    cocos2d::Director::getInstance()->getScheduler()->schedule(schedule_selector(PhunwareMessaging_CallbackJS::notityJs), this, 0.1, false);
#else
    cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(PhunwareMessaging_CallbackJS::notityJs), this, 0.1, false);
#endif
    autorelease();
}

void PhunwareMessaging_CallbackJS::notityJs(float dt) {
    sdkbox::PhunwareMessagingListener* lis = sdkbox::PluginPhunwareMessaging::getListener();
    PhunwareMessagingListenerJS* l = dynamic_cast<PhunwareMessagingListenerJS*>(lis);
    if (l) {
        l->invokeJS(_name.c_str(), _paramVal, _paramLen);
    }

#if COCOS2D_VERSION >= 0x00030000
    cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
#else
    cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllForTarget(this);
#endif
    release();
}

#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#else
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_setListener(JSContext *cx, uint32_t argc, jsval *vp)
#endif
{
    s_cx = cx;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    if (argc == 1) {

        if (!args.get(0).isObject())
        {
            ok = false;
        }
        JSObject *tmpObj = args.get(0).toObjectOrNull();

        JSB_PRECONDITION2(ok, cx, false, "js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_setIAPListener : Error processing arguments");
        PhunwareMessagingListenerJS* wrapper = new PhunwareMessagingListenerJS();
        wrapper->setJSDelegate(tmpObj);
        sdkbox::PluginPhunwareMessaging::setListener(wrapper);

        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_setIAPListener : wrong number of arguments");
    return false;
}

#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
void phunwaremessaging_set_constants(JSContext* cx, const JS::RootedObject& obj, const std::string& name, const std::map<std::string, int>& params)
#else
void phunwaremessaging_set_constants(JSContext* cx, JSObject* obj, const std::string& name, const std::map<std::string, int>& params)
#endif
{
    jsval val = sdkbox::std_map_string_int_to_jsval(cx, params);

    JS::RootedValue rv(cx);
    rv = val;
#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
    JS_SetProperty(cx, obj, name.c_str(), rv);
#else
    JS_SetProperty(cx, obj, name.c_str(), rv.address());
#endif
}

#if defined(MOZJS_MAJOR_VERSION) and MOZJS_MAJOR_VERSION >= 26
void phunwaremessaging_register_constants(JSContext* cx, const JS::RootedObject& obj)
#else
void phunwaremessaging_register_constants(JSContext* cx, JSObject* obj)
#endif
{
    std::map<std::string, int> enums;
    enums.clear();
    enums.insert(std::make_pair("AdOrientation_AutoDetect", 0));
    enums.insert(std::make_pair("AdOrientation_Landscape", 1));
    enums.insert(std::make_pair("AdOrientation_Portrait", 2));
    phunwaremessaging_set_constants(cx, obj, "AdOrientation", enums);
}


#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_messages(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::vector<sdkbox::PWZoneMessage> ret = sdkbox::PluginPhunwareMessaging::messages();

        JS_INIT_CONTEXT_FOR_UPDATE(cx);

        // collection of FBGraphUser
        sdkbox::JSOBJECT *jarr= sdkbox::JS_NEW_ARRAY(cx, ret.size());

        uint32_t index=0;
        for (int i = 0; i < ret.size(); i++) {
            JSOBJECT* gu = PWMessageToJS(cx, ret.at(i));
            JS_ARRAY_SET( cx, jarr, index, gu );
            index++;
        }

        jsval jsret = JSVAL_NULL;
        do {
            if (jarr) {
                jsret = OBJECT_TO_JSVAL(jarr);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_messages : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_messages(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::vector<sdkbox::PWZoneMessage> ret = sdkbox::PluginPhunwareMessaging::messages();

        JS_INIT_CONTEXT_FOR_UPDATE(cx);

        // collection of FBGraphUser
        sdkbox::JSOBJECT *jarr= sdkbox::JS_NEW_ARRAY(cx, ret.size());

        uint32_t index=0;
        for (int i = 0; i < ret.size(); i++) {
            JSOBJECT* gu = PWMessageToJS(cx, ret.at(i));
            JS_ARRAY_SET( cx, jarr, index, gu );
            index++;
        }

        jsval jsret = JSVAL_NULL;
        do {
            if (jarr) {
                jsret = OBJECT_TO_JSVAL(jarr);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_geozones(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        std::vector<sdkbox::PWGeozone> ret = sdkbox::PluginPhunwareMessaging::geozones();

        JS_INIT_CONTEXT_FOR_UPDATE(cx);

        // collection of FBGraphUser
        sdkbox::JSOBJECT *jarr= sdkbox::JS_NEW_ARRAY(cx, ret.size());

        uint32_t index=0;
        for (int i = 0; i < ret.size(); i++) {
            JSOBJECT* gu = PWGeoZoneToJS(cx, ret.at(i));
            JS_ARRAY_SET( cx, jarr, index, gu );
            index++;
        }

        jsval jsret = JSVAL_NULL;
        do {
            if (jarr) {
                jsret = OBJECT_TO_JSVAL(jarr);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_geozones : wrong number of arguments");
    return false;
}
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_geozones(JSContext *cx, uint32_t argc, jsval *vp)
{
    if (argc == 0) {
        std::vector<sdkbox::PWGeozone> ret = sdkbox::PluginPhunwareMessaging::geozones();

        JS_INIT_CONTEXT_FOR_UPDATE(cx);

        // collection of FBGraphUser
        sdkbox::JSOBJECT *jarr= sdkbox::JS_NEW_ARRAY(cx, ret.size());

        uint32_t index=0;
        for (int i = 0; i < ret.size(); i++) {
            JSOBJECT* gu = PWGeoZoneToJS(cx, ret.at(i));
            JS_ARRAY_SET( cx, jarr, index, gu );
            index++;
        }

        jsval jsret = JSVAL_NULL;
        do {
            if (jarr) {
                jsret = OBJECT_TO_JSVAL(jarr);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    JS_ReportError(cx, "wrong number of arguments");
    return JS_FALSE;
}
#endif


#if defined(MOZJS_MAJOR_VERSION)
#if MOZJS_MAJOR_VERSION >= 33
void register_all_PluginPhunwareMessagingJS_helper(JSContext* cx, JS::HandleObject global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginPhunwareMessaging", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, pluginObj, "geozones", js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_geozones, 1, JSPROP_READONLY | JSPROP_PERMANENT);


//    phunwaremessaging_register_constants(cx, pluginObj);
}
#else
void register_all_PluginPhunwareMessagingJS_helper(JSContext* cx, JSObject* global) {
    JS::RootedObject pluginObj(cx);
    sdkbox::getJsObjOrCreat(cx, JS::RootedObject(cx, global), "sdkbox.PluginPhunwareMessaging", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, pluginObj, "messages", js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_messages, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, pluginObj, "geozones", js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_geozones, 1, JSPROP_READONLY | JSPROP_PERMANENT);

//    phunwaremessaging_register_constants(cx, pluginObj);
}
#endif
#elif defined(JS_VERSION)
void register_all_PluginPhunwareMessagingJS_helper(JSContext* cx, JSObject* global) {
    jsval pluginVal;
    JSObject* pluginObj;
    pluginVal = sdkbox::getJsObjOrCreat(cx, global, "sdkbox.PluginPhunwareMessaging", &pluginObj);

    JS_DefineFunction(cx, pluginObj, "setListener", js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_setListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, pluginObj, "messages", js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_messages, 1, JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineFunction(cx, pluginObj, "geozones", js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_geozones, 1, JSPROP_READONLY | JSPROP_PERMANENT);

//    phunwaremessaging_register_constants(cx, pluginObj);
}
#endif
