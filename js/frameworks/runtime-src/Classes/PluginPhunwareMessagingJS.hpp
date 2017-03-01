#ifndef __PluginPhunwareMessagingJS_h__
#define __PluginPhunwareMessagingJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_sdkbox_PluginPhunwareMessaging_class;
extern JSObject *jsb_sdkbox_PluginPhunwareMessaging_prototype;

#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginPhunwareMessagingJS_PluginPhunwareMessaging(JSContext *cx, JS::HandleObject global);
void register_all_PluginPhunwareMessagingJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginPhunwareMessagingJS_PluginPhunwareMessaging(JSContext *cx, JSObject* global);
void register_all_PluginPhunwareMessagingJS(JSContext* cx, JSObject* obj);
#endif

bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_finalize(JSContext *cx, JSObject *obj);
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_version(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_version(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_read(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_read(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_stop(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_stop(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_remove(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_remove(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_init(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_init(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_deviceId(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_deviceId(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#if defined(MOZJS_MAJOR_VERSION)
bool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_serviceName(JSContext *cx, uint32_t argc, jsval *vp);
#elif defined(JS_VERSION)
JSBool js_PluginPhunwareMessagingJS_PluginPhunwareMessaging_serviceName(JSContext *cx, uint32_t argc, jsval *vp);
#endif
#endif

