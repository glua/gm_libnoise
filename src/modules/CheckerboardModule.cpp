#include "CheckerboardModule.h"

namespace Modules {
	namespace CheckerboardModule {

		noise::module::Checkerboard *FetchModule(lua_State *state, int iStackPos) {
				if (!LUA->IsType(1, GarrysMod::Lua::Type::USERDATA)) {
					LUA->ThrowError("No userdata.");
					return NULL;
				}
				return *(noise::module::Checkerboard**)LUA->GetUserdata(iStackPos);
		}

		int GetValue(lua_State* state) {
			noise::module::Checkerboard *module = FetchModule(state, 1);

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
			noise::module::Checkerboard *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetSourceModuleCount());
			return 1;
		}

		int CreateModule(lua_State* state) {
			noise::module::Checkerboard* newModule = new noise::module::Checkerboard();

			noise::module::Checkerboard **ud = (noise::module::Checkerboard **)LUA->NewUserdata(sizeof(noise::module::Checkerboard*));
				*ud = newModule;
				LUA->CreateMetaTableType("NoiseCheckerboard", GarrysMod::Lua::Type::USERDATA);
			LUA->SetMetaTable(-2);
			
			return 1;
		}

		void Register(lua_State* state) {
			LUA->PushCFunction(CreateModule);
			LUA->SetField(-2, "Checkerboard");

			LUA->CreateMetaTableType("NoiseCheckerboard", GarrysMod::Lua::Type::USERDATA);
				LUA->Push(-1);
				LUA->SetField(-2, "__index");

				LUA->PushString("NoiseCheckerboard");
				LUA->SetField(-2, "__type");

				AddMethod(state, GetValue, "GetValue");
				AddMethod(state, GetSourceModuleCount, "GetSourceModuleCount");
			LUA->Pop();
		}
	}
}