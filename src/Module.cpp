#include "Module.h"

using namespace GarrysMod::Lua;

int testFunction(lua_State *state) {
	noise::module::Perlin perlin;
	perlin.SetSeed(0);
	perlin.SetFrequency(4.0);
	perlin.SetOctaveCount(1);

	double x = LUA->GetNumber(1);
	double y = LUA->GetNumber(2);

	printf("Woop: %f, %f", x, y);

	double value = perlin.GetValue(x, y, 0);
	LUA->PushNumber(value);
	return 1;
}

GMOD_MODULE_OPEN() {

	LUA->PushSpecial(SPECIAL_GLOB);

		LUA->GetField(-1, "print");
		LUA->PushString("libnoise loaded!");
		LUA->Call(1, 0);

		
		LUA->PushCFunction(testFunction);
		LUA->SetField(-2, "NoiseTest");

	LUA->SetTable(-1);

	return 0;
}

GMOD_MODULE_CLOSE() {
	return 0;
}