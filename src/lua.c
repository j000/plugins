#include "plugin.h"
#include <stdio.h>
#include <stdlib.h>

#include <luajit-2.0/lauxlib.h>
#include <luajit-2.0/lua.h>
#include <luajit-2.0/lualib.h>

#define INCSTRING(name, file) \
    __asm__(".section .rodata\n" \
            ".global incbin_" #name "_start\n" \
            ".balign 16\n" \
            "incbin_" #name "_start:\n" \
            ".incbin \"" file "\"\n" \
            ".global incbin_" #name "_end\n" \
            ".balign 1\n" \
            "incbin_" #name "_end:\n" \
            ".byte 0\n" \
    ); \
    extern const __attribute__((aligned(16))) void* incbin_ ## name ## _start; \
    extern const void* incbin_ ## name ## _end; \
	const char* script = (char*)&incbin_ ## name ## _start;

INCSTRING(script, "plugin.lua")

struct Plugin_t {
	char* name;
	lua_State* lua;
};

Plugin_t* plugin_create(void)
{
	Plugin_t* tmp = malloc(sizeof(Plugin_t));
	tmp->name = "lua";
	tmp->lua = luaL_newstate();
	luaL_openlibs(tmp->lua);

	if (luaL_loadstring(tmp->lua, script))
		goto lua_fail;

	if (lua_pcall(tmp->lua, 0, 0, 0)) // prime
		goto lua_fail;

	lua_getglobal(tmp->lua, "plugin_destroy");
	if (!lua_isfunction(tmp->lua, -1))
		goto lua_fail;

	lua_getglobal(tmp->lua, "plugin_name");
	if (!lua_isfunction(tmp->lua, -1))
		goto lua_fail;

	lua_getglobal(tmp->lua, "plugin_test");
	if (!lua_isfunction(tmp->lua, -1))
		goto lua_fail;

	lua_getglobal(tmp->lua, "plugin_create");
	if (!lua_isfunction(tmp->lua, -1))
		goto lua_fail;

	if (lua_pcall(tmp->lua, 0, 0, 0)) // run function
		goto lua_fail;

	return tmp;
lua_fail:
	free(tmp);
	return NULL;
}

void plugin_destroy(Plugin_t* plug)
{
	lua_getglobal(plug->lua, "plugin_destroy");
	lua_pcall(plug->lua, 0, 0, 0);
	lua_close(plug->lua);
	free(plug);
}

void plugin_test(Plugin_t* plug)
{
	lua_getglobal(plug->lua, "plugin_test");
	if (lua_pcall(plug->lua, 0, 0, 0)) { // run function
	}
}

const char* plugin_name(Plugin_t* plug)
{
	lua_getglobal(plug->lua, "plugin_name");
	if (lua_pcall(plug->lua, 0, 1, 0)) { // run function
		return "FAIL";
	}
	const char* name = lua_tostring(plug->lua, -1);
	return name;
}
