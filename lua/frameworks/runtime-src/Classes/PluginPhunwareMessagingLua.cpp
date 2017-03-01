#include "PluginPhunwareMessagingLua.hpp"
#include "PluginPhunwareMessaging/PluginPhunwareMessaging.h"
#include "SDKBoxLuaHelper.h"
#include "sdkbox/Sdkbox.h"



int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_version(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginPhunwareMessaging",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_version'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::PluginPhunwareMessaging::version();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging:version",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_version'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_read(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginPhunwareMessaging",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginPhunwareMessaging:read");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_read'", nullptr);
            return 0;
        }
        sdkbox::PluginPhunwareMessaging::read(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging:read",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_read'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_stop(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginPhunwareMessaging",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_stop'", nullptr);
            return 0;
        }
        sdkbox::PluginPhunwareMessaging::stop();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging:stop",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_stop'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_remove(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginPhunwareMessaging",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "sdkbox.PluginPhunwareMessaging:remove");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_remove'", nullptr);
            return 0;
        }
        sdkbox::PluginPhunwareMessaging::remove(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging:remove",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_remove'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_init(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginPhunwareMessaging",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_init'", nullptr);
            return 0;
        }
        bool ret = sdkbox::PluginPhunwareMessaging::init();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging:init",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_init'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_deviceId(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginPhunwareMessaging",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_deviceId'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::PluginPhunwareMessaging::deviceId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging:deviceId",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_deviceId'.",&tolua_err);
#endif
    return 0;
}
int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_serviceName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginPhunwareMessaging",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_serviceName'", nullptr);
            return 0;
        }
        std::string ret = sdkbox::PluginPhunwareMessaging::serviceName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging:serviceName",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_serviceName'.",&tolua_err);
#endif
    return 0;
}
static int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PluginPhunwareMessaging)");
    return 0;
}

int lua_register_PluginPhunwareMessagingLua_PluginPhunwareMessaging(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"sdkbox.PluginPhunwareMessaging");
    tolua_cclass(tolua_S,"PluginPhunwareMessaging","sdkbox.PluginPhunwareMessaging","",nullptr);

    tolua_beginmodule(tolua_S,"PluginPhunwareMessaging");
        tolua_function(tolua_S,"version", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_version);
        tolua_function(tolua_S,"read", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_read);
        tolua_function(tolua_S,"stop", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_stop);
        tolua_function(tolua_S,"remove", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_remove);
        tolua_function(tolua_S,"init", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_init);
        tolua_function(tolua_S,"deviceId", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_deviceId);
        tolua_function(tolua_S,"serviceName", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_serviceName);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(sdkbox::PluginPhunwareMessaging).name();
    g_luaType[typeName] = "sdkbox.PluginPhunwareMessaging";
    g_typeCast["PluginPhunwareMessaging"] = "sdkbox.PluginPhunwareMessaging";
    return 1;
}
TOLUA_API int register_all_PluginPhunwareMessagingLua(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"sdkbox",0);
	tolua_beginmodule(tolua_S,"sdkbox");

	lua_register_PluginPhunwareMessagingLua_PluginPhunwareMessaging(tolua_S);

	tolua_endmodule(tolua_S);

	sdkbox::setProjectType("lua");
	return 1;
}

