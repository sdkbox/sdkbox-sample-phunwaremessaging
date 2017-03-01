

#ifndef __js__PluginPhunwareMessagingJSHelper_H_
#define __js__PluginPhunwareMessagingJSHelper_H_

#include "jsapi.h"
#include "jsfriendapi.h"

#if MOZJS_MAJOR_VERSION >= 31
void register_all_PluginPhunwareMessagingJS_helper(JSContext* cx, JS::HandleObject global);
#else
void register_all_PluginPhunwareMessagingJS_helper(JSContext* cx, JSObject* global);
#endif

#endif /* defined(__PluginPhunwareMessagingJSHelper_H_) */
