
#include "PluginPhunwareMessagingLuaHelper.h"
#include "PluginPhunwareMessaging/PluginPhunwareMessaging.h"
#include "CCLuaEngine.h"
#include "tolua_fix.h"
#include "SDKBoxLuaHelper.h"

static LuaValue PWMessageToLua( const sdkbox::PWZoneMessage& msg ) {
    LuaValueDict d;

    d.insert(std::make_pair("isRead", LuaValue::booleanValue(msg.isRead)));
    d.insert(std::make_pair("alertTitle", LuaValue::stringValue(msg.alertTitle)));
    d.insert(std::make_pair("alertBody", LuaValue::stringValue(msg.alertBody)));
    d.insert(std::make_pair("promotionTitle", LuaValue::stringValue(msg.promotionTitle)));
    d.insert(std::make_pair("promotionBody", LuaValue::stringValue(msg.promotionBody)));
    d.insert(std::make_pair("identifier", LuaValue::stringValue(msg.identifier)));
    d.insert(std::make_pair("campaignType", LuaValue::stringValue(msg.campaignType)));

    return LuaValue::dictValue(d);
}

static LuaValue PWGeoZoneToLua(const sdkbox::PWGeozone& zone) {
    LuaValueDict d;

    d.insert(std::make_pair("identifier", LuaValue::stringValue(zone.identifier)));
    d.insert(std::make_pair("name", LuaValue::stringValue(zone.name)));
    d.insert(std::make_pair("code", LuaValue::stringValue(zone.code)));
    d.insert(std::make_pair("zoneDescription", LuaValue::stringValue(zone.zoneDescription)));
    d.insert(std::make_pair("inside", LuaValue::booleanValue(zone.inside)));
    d.insert(std::make_pair("monitored", LuaValue::booleanValue(zone.monitored)));

    return LuaValue::dictValue(d);
}

class PhunwareMessagingListenerLua : public sdkbox::PhunwareMessagingListener {
public:
    PhunwareMessagingListenerLua(): mLuaHandler(0) {
    }

    ~PhunwareMessagingListenerLua() {
        resetHandler();
    }

    void setHandler(int luaHandler) {
        if (mLuaHandler == luaHandler) {
            return;
        }
        resetHandler();
        mLuaHandler = luaHandler;
    }

    void resetHandler() {
        if (0 == mLuaHandler) {
            return;
        }

        LUAENGINE->removeScriptHandler(mLuaHandler);
        mLuaHandler = 0;
    }

    virtual void init(bool success, const std::string& message)   {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue(__FUNCTION__)));
        dict.insert(std::make_pair("success", LuaValue::booleanValue(success)));
        dict.insert(std::make_pair("message", LuaValue::stringValue(message)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }
    virtual void error(const std::string& message)  {
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueDict dict;

        dict.insert(std::make_pair("event", LuaValue::stringValue(__FUNCTION__)));
        dict.insert(std::make_pair("message", LuaValue::stringValue(message)));

        stack->pushLuaValueDict(dict);
        stack->executeFunctionByHandler(mLuaHandler, 1);
    }

private:
    int mLuaHandler;
};

int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_setListener(lua_State* tolua_S) {
    int argc = 0;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"sdkbox.PluginPhunwareMessaging",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S, 2 , "LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
        PhunwareMessagingListenerLua* lis = static_cast<PhunwareMessagingListenerLua*> (sdkbox::PluginPhunwareMessaging::getListener());
        if (NULL == lis) {
            lis = new PhunwareMessagingListenerLua();
        }
        lis->setHandler(handler);
        sdkbox::PluginPhunwareMessaging::setListener(lis);

        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging::setListener",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_setListener'.",&tolua_err);
#endif
    return 0;
}

static int lua_createTable(lua_State* L, const std::map<std::string, int>& map) {
    lua_newtable(L);

    std::map<std::string, int>::const_iterator it = map.begin();
    while (it != map.end()) {
        lua_pushstring(L, it->first.c_str());
        lua_pushinteger(L, it->second);
        lua_settable(L, -3);
        it++;
    }

    return 1;
}

static int lua_setTable(lua_State* L, int table, const std::string& name, const std::map<std::string, int>& map) {
    if (table < 0) {
        table = lua_gettop(L) + table + 1;
    }
    lua_pushstring(L, name.c_str());
    lua_createTable(L, map);
    lua_rawset(L, table);

    return 0;
}

int lua_PluginPhunwareMessagingLua_constants(lua_State* L) {
    if (NULL == L) {
        return 0;
    }

    lua_pushstring(L, "sdkbox.PluginPhunwareMessaging");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1)) {

        std::map<std::string, int> enums;
        enums.clear();
        enums.insert(std::make_pair("AdOrientation_AutoDetect", 0));
        enums.insert(std::make_pair("AdOrientation_Landscape", 1));
        enums.insert(std::make_pair("AdOrientation_Portrait", 2));
        lua_setTable(L, -1, "AdOrientation", enums);
    }
    lua_pop(L, 1);

    return 1;
}

int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_messages(lua_State* tolua_S)
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
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_messages'", nullptr);
            return 0;
        }
        std::vector<sdkbox::PWZoneMessage> ret = sdkbox::PluginPhunwareMessaging::messages();
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueArray array;
        for (std::vector<sdkbox::PWZoneMessage>::iterator it = ret.begin(); it != ret.end(); it++) {
            array.push_back(PWMessageToLua((*it)));
        }
        stack->pushLuaValueArray(array);

        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging:messages",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_messages'.",&tolua_err);
#endif
    return 0;
}

int lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_geozones(lua_State* tolua_S)
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
            tolua_error(tolua_S,"invalid arguments in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_geozones'", nullptr);
            return 0;
        }
        std::vector<sdkbox::PWGeozone> ret = sdkbox::PluginPhunwareMessaging::geozones();
        LuaStack* stack = LUAENGINE->getLuaStack();
        LuaValueArray array;
        for (std::vector<sdkbox::PWGeozone>::iterator it = ret.begin(); it != ret.end(); it++) {
            array.push_back(PWGeoZoneToLua((*it)));
        }
        stack->pushLuaValueArray(array);

        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "sdkbox.PluginPhunwareMessaging:geozones",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_geozones'.",&tolua_err);
#endif
    return 0;
}


int extern_PluginPhunwareMessaging(lua_State* L) {
    if (NULL == L) {
        return 0;
    }

    lua_pushstring(L, "sdkbox.PluginPhunwareMessaging");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L,"setListener", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_setListener);

        tolua_function(L,"messages", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_messages);
        tolua_function(L,"geozones", lua_PluginPhunwareMessagingLua_PluginPhunwareMessaging_geozones);

    }
     lua_pop(L, 1);

//    lua_PluginPhunwareMessagingLua_constants(L);

    return 1;
}

TOLUA_API int register_all_PluginPhunwareMessagingLua_helper(lua_State* L) {
    tolua_module(L,"sdkbox",0);
    tolua_beginmodule(L,"sdkbox");

    extern_PluginPhunwareMessaging(L);

    tolua_endmodule(L);
    return 1;
}


