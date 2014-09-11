#include "Module.h"
#include "modules/BillowModule.h"
#include "modules/CheckerboardModule.h"
#include "modules/ConstModule.h"
#include "modules/CylindersModule.h"
#include "modules/PerlinModule.h"
#include "modules/RidgedMultiModule.h"
#include "modules/SpheresModule.h"
#include "modules/VoronoiModule.h"

using namespace GarrysMod::Lua;

void AddMethod(lua_State *state, GarrysMod::Lua::CFunc func, const char *name) {
	LUA->PushCFunction(func);
	LUA->SetField(-2, name);
}

Vector *GetVector(lua_State *state, int stackPos) {
	LUA->CheckType(stackPos, Type::VECTOR);

	UserData *ud = (UserData *)LUA->GetUserdata(stackPos);
	return (Vector *)ud->data;
}

GMOD_MODULE_OPEN() {

	LUA->PushSpecial(SPECIAL_GLOB);

		LUA->GetField(-1, "print");
		LUA->PushString("libnoise loaded!");
		LUA->Call(1, 0);

		LUA->CreateTable();
			Modules::BillowModule::Register(state);
			Modules::CheckerboardModule::Register(state);
			Modules::ConstModule::Register(state);
			Modules::CylindersModule::Register(state);
			Modules::PerlinModule::Register(state);
			Modules::RidgedMultiModule::Register(state);
			Modules::SpheresModule::Register(state);
			Modules::VoronoiModule::Register(state);
		LUA->SetField(-2, "libnoise");

	LUA->SetTable(-1);

	return 0;
}

GMOD_MODULE_CLOSE() {
	return 0;
}