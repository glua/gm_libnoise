#ifndef MODULE_H
#define MODULE_H


#include <Windows.h>
#include <string>

#include "GarrysMod/Lua/Interface.h"
#include <noise/noise.h>

void AddMethod(lua_State*, GarrysMod::Lua::CFunc, const char*);
class Vector {
public:
	double x;
	double y;
	double z;
};

Vector *GetVector(lua_State *state, int stackPos);

#endif