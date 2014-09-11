#include "CylindersModule.h"

namespace Modules {
	namespace CylindersModule {

		noise::module::Cylinders *FetchModule(lua_State *state, int iStackPos) {
				if (!LUA->IsType(1, GarrysMod::Lua::Type::USERDATA)) {
					LUA->ThrowError("No userdata.");
					return NULL;
				}
				return *(noise::module::Cylinders**)LUA->GetUserdata(iStackPos);
		}

		int GetValue(lua_State* state) {
			noise::module::Cylinders *module = FetchModule(state, 1);

			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			LUA->CheckType(3, GarrysMod::Lua::Type::NUMBER);
			LUA->CheckType(4, GarrysMod::Lua::Type::NUMBER);

			double x = LUA->GetNumber(2);
			double y = LUA->GetNumber(3);
			double z = LUA->GetNumber(4);

			double result = module->GetValue(x, y, z);
			LUA->PushNumber(result);
			
			return 1;
		}

		int GetSourceModuleCount(lua_State* state) {
			noise::module::Cylinders *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetSourceModuleCount());
			return 1;
		}

		//

		int GetFrequency(lua_State* state) {
			noise::module::Cylinders *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetFrequency());
			return 1;
		}

		int SetFrequency(lua_State* state) {
			noise::module::Cylinders *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			double value = LUA->GetNumber(2);
			module->SetFrequency(value);
			return 0;
		}

		int CreateModule(lua_State* state) {
			noise::module::Cylinders* newModule = new noise::module::Cylinders();

			noise::module::Cylinders **ud = (noise::module::Cylinders **)LUA->NewUserdata(sizeof(noise::module::Cylinders*));
				*ud = newModule;
				LUA->CreateMetaTableType("NoiseCylinders", GarrysMod::Lua::Type::USERDATA);
			LUA->SetMetaTable(-2);
			
			return 1;
		}

		void Register(lua_State* state) {
			LUA->PushCFunction(CreateModule);
			LUA->SetField(-2, "Cylinders");

			LUA->CreateMetaTableType("NoiseCylinders", GarrysMod::Lua::Type::USERDATA);
				LUA->Push(-1);
				LUA->SetField(-2, "__index");

				LUA->PushString("NoiseCylinders");
				LUA->SetField(-2, "__type");

				AddMethod(state, GetValue, "GetValue");
				AddMethod(state, GetSourceModuleCount, "GetSourceModuleCount");

				AddMethod(state, GetFrequency, "GetFrequency");
				AddMethod(state, SetFrequency, "SetFrequency");
			LUA->Pop();
		}
	}
}