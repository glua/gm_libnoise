#include "../Module.h"

namespace Modules {
	namespace BillowModule {

		noise::module::Billow *FetchModule(lua_State *state, int iStackPos);
		int GetValue(lua_State* state);
		int GetFrequency(lua_State* state);
		int GetLacunarity(lua_State* state);
		int GetNoiseQuality(lua_State* state);
		int GetOctaveCount(lua_State* state);
		int GetPersistence(lua_State* state);
		int GetSeed(lua_State* state);
		int GetSourceModuleCount(lua_State* state);
		int SetFrequency(lua_State* state);
		int CreateModule(lua_State* state);
		void Register(lua_State* state);
	}
}