#ifndef __PluginPhunwareMessagingJS_h__
#define __PluginPhunwareMessagingJS_h__

#include "jsapi.h"
#include "jsfriendapi.h"


#if MOZJS_MAJOR_VERSION >= 33
void js_register_PluginPhunwareMessagingJS_PluginPhunwareMessaging(JSContext *cx, JS::HandleObject global);
void register_all_PluginPhunwareMessagingJS(JSContext* cx, JS::HandleObject obj);
#else
void js_register_PluginPhunwareMessagingJS_PluginPhunwareMessaging(JSContext *cx, JSObject* global);
void register_all_PluginPhunwareMessagingJS(JSContext* cx, JSObject* obj);
#endif
#endif

