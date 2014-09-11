#include "VoronoiModule.h"

namespace Modules {
	namespace VoronoiModule {

		noise::module::Voronoi *FetchModule(lua_State *state, int iStackPos) {
				if (!LUA->IsType(1, GarrysMod::Lua::Type::USERDATA)) {
					LUA->ThrowError("No userdata.");
					return NULL;
				}
				return *(noise::module::Voronoi**)LUA->GetUserdata(iStackPos);
		}

		int GetValue(lua_State* state) {
			noise::module::Voronoi *module = FetchModule(state, 1);

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
			noise::module::Voronoi *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetSourceModuleCount());
			return 1;
		}

		int GetSeed(lua_State* state) {
			noise::module::Voronoi *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetSeed());
			return 1;
		}

		int SetSeed(lua_State* state) {
			noise::module::Voronoi *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			int value = (int)LUA->GetNumber(2);
			module->SetSeed(value);
			return 0;
		}


		//

		int GetFrequency(lua_State* state) {
			noise::module::Voronoi *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetFrequency());
			return 1;
		}

		int SetFrequency(lua_State* state) {
			noise::module::Voronoi *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			double value = LUA->GetNumber(2);
			module->SetFrequency(value);
			return 0;
		}

		//

		int EnableDistance(lua_State* state) {
			noise::module::Voronoi *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::BOOL);
			bool value = LUA->GetBool(2);
			module->EnableDistance(value);
			return 0;
		}

		int IsDistanceEnabled(lua_State* state) {
			noise::module::Voronoi *module = FetchModule(state, 1);
			LUA->PushBool(module->IsDistanceEnabled());
			return 1;
		}

		//

		int GetDisplacement(lua_State* state) {
			noise::module::Voronoi *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetDisplacement());
			return 1;
		}

		int SetDisplacement(lua_State* state) {
			noise::module::Voronoi *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			double value = LUA->GetNumber(2);
			module->SetDisplacement(value);
			return 0;
		}

		//


		int CreateModule(lua_State* state) {
			noise::module::Voronoi* newModule = new noise::module::Voronoi();

			noise::module::Voronoi **ud = (noise::module::Voronoi **)LUA->NewUserdata(sizeof(noise::module::Voronoi*));
				*ud = newModule;
				LUA->CreateMetaTableType("NoiseVoronoi", GarrysMod::Lua::Type::USERDATA);
			LUA->SetMetaTable(-2);
			
			return 1;
		}

		void Register(lua_State* state) {
			LUA->PushCFunction(CreateModule);
			LUA->SetField(-2, "Voronoi");

			LUA->CreateMetaTableType("NoiseVoronoi", GarrysMod::Lua::Type::USERDATA);
				LUA->Push(-1);
				LUA->SetField(-2, "__index");

				LUA->PushString("NoiseVoronoi");
				LUA->SetField(-2, "__type");

				AddMethod(state, GetValue, "GetValue");
				AddMethod(state, GetSourceModuleCount, "GetSourceModuleCount");

				AddMethod(state, SetSeed, "SetSeed");
				AddMethod(state, GetSeed, "GetSeed");

				AddMethod(state, GetFrequency, "GetFrequency");
				AddMethod(state, SetFrequency, "SetFrequency");

				AddMethod(state, EnableDistance, "EnableDistance");
				AddMethod(state, IsDistanceEnabled, "IsDistanceEnabled");

				AddMethod(state, GetDisplacement, "GetDisplacement");
				AddMethod(state, SetDisplacement, "SetDisplacement");

			LUA->Pop();
		}
	}
}