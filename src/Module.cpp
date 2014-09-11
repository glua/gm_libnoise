#include "Module.h"
#include "modules/BillowModule.h"

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
		LUA->SetField(-2, "libnoise");

	LUA->SetTable(-1);

	return 0;
}

GMOD_MODULE_CLOSE() {
	return 0;
}