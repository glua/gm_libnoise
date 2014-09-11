#include "ConstModule.h"

namespace Modules {
	namespace ConstModule {

		noise::module::Const *FetchModule(lua_State *state, int iStackPos) {
				if (!LUA->IsType(1, GarrysMod::Lua::Type::USERDATA)) {
					LUA->ThrowError("No userdata.");
					return NULL;
				}
				return *(noise::module::Const**)LUA->GetUserdata(iStackPos);
		}

		int GetValue(lua_State* state) {
			noise::module::Const *module = FetchModule(state, 1);

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
			noise::module::Const *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetSourceModuleCount());
			return 1;
		}

		int GetConstValue(lua_State* state) {
			noise::module::Const *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetConstValue());
			return 1;
		}

		int SetConstValue(lua_State* state) {
			noise::module::Const *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			double value = LUA->GetNumber(2);
			module->SetConstValue(value);
			return 0;
		}

		int CreateModule(lua_State* state) {
			noise::module::Const* newModule = new noise::module::Const();

			noise::module::Const **ud = (noise::module::Const **)LUA->NewUserdata(sizeof(noise::module::Const*));
				*ud = newModule;
				LUA->CreateMetaTableType("NoiseConst", GarrysMod::Lua::Type::USERDATA);
			LUA->SetMetaTable(-2);
			
			return 1;
		}

		void Register(lua_State* state) {
			LUA->PushCFunction(CreateModule);
			LUA->SetField(-2, "Const");

			LUA->CreateMetaTableType("NoiseConst", GarrysMod::Lua::Type::USERDATA);
				LUA->Push(-1);
				LUA->SetField(-2, "__index");

				LUA->PushString("NoiseConst");
				LUA->SetField(-2, "__type");

				AddMethod(state, GetValue, "GetValue");
				AddMethod(state, GetSourceModuleCount, "GetSourceModuleCount");

				AddMethod(state, GetConstValue, "GetConstValue");
				AddMethod(state, SetConstValue, "SetConstValue");

			LUA->Pop();
		}
	}
}