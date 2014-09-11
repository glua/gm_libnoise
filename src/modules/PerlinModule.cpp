#include "PerlinModule.h"

namespace Modules {
	namespace PerlinModule {

		noise::module::Perlin *FetchModule(lua_State *state, int iStackPos) {
				if (!LUA->IsType(1, GarrysMod::Lua::Type::USERDATA)) {
					LUA->ThrowError("No userdata.");
					return NULL;
				}
				return *(noise::module::Perlin**)LUA->GetUserdata(iStackPos);
		}

		int GetValue(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);

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
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetSourceModuleCount());
			return 1;
		}

		int GetSeed(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetSeed());
			return 1;
		}

		int SetSeed(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			int value = (int)LUA->GetNumber(2);
			module->SetSeed(value);
			return 0;
		}

		//

		int GetFrequency(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetFrequency());
			return 1;
		}

		int GetLacunarity(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetLacunarity());
			return 1;
		}

		int GetNoiseQuality(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetNoiseQuality());
			return 1;
		}

		int GetOctaveCount(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetOctaveCount());
			return 1;
		}

		int GetPersistence(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->PushNumber(module->GetPersistence());
			return 1;
		}


		int SetFrequency(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			double value = LUA->GetNumber(2);
			module->SetFrequency(value);
			return 0;
		}

		int SetNoiseQuality(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			noise::NoiseQuality value = static_cast<noise::NoiseQuality>((int)LUA->GetNumber(2));
			module->SetNoiseQuality(value);
			return 0;
		}

		int SetLacunarity(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			double value = LUA->GetNumber(2);
			module->SetLacunarity(value);
			return 0;
		}

		int SetOctaveCount(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			int value = (int)LUA->GetNumber(2);
			module->SetOctaveCount(value);
			return 0;
		}

		int SetPersistence(lua_State* state) {
			noise::module::Perlin *module = FetchModule(state, 1);
			LUA->CheckType(2, GarrysMod::Lua::Type::NUMBER);
			double value = LUA->GetNumber(2);
			module->SetPersistence(value);
			return 0;
		}

		int CreateModule(lua_State* state) {
			noise::module::Perlin* newModule = new noise::module::Perlin();

			noise::module::Perlin **ud = (noise::module::Perlin **)LUA->NewUserdata(sizeof(noise::module::Perlin*));
				*ud = newModule;
				LUA->CreateMetaTableType("NoisePerlin", GarrysMod::Lua::Type::USERDATA);
			LUA->SetMetaTable(-2);
			
			return 1;
		}

		void Register(lua_State* state) {
			LUA->PushCFunction(CreateModule);
			LUA->SetField(-2, "Perlin");

			LUA->CreateMetaTableType("NoisePerlin", GarrysMod::Lua::Type::USERDATA);
				LUA->Push(-1);
				LUA->SetField(-2, "__index");

				LUA->PushString("NoisePerlin");
				LUA->SetField(-2, "__type");

				AddMethod(state, GetValue, "GetValue");
				AddMethod(state, GetSourceModuleCount, "GetSourceModuleCount");

				AddMethod(state, SetSeed, "SetSeed");
				AddMethod(state, GetSeed, "GetSeed");

				AddMethod(state, GetNoiseQuality, "GetNoiseQuality");
				AddMethod(state, SetNoiseQuality, "SetNoiseQuality");

				AddMethod(state, GetFrequency, "GetFrequency");
				AddMethod(state, GetLacunarity, "GetLacunarity");
				AddMethod(state, GetOctaveCount, "GetOctaveCount");
				AddMethod(state, GetPersistence, "GetPersistence");

				AddMethod(state, SetFrequency, "SetFrequency");
				AddMethod(state, SetLacunarity, "SetLacunarity");
				AddMethod(state, SetOctaveCount, "SetOctaveCount");
				AddMethod(state, SetPersistence, "SetPersistence");
			LUA->Pop();
		}
	}
}