#ifndef SOL2TEST_LUA_H
#define SOL2TEST_LUA_H

#include "platform.h"

#include <memory>
#include <sol/sol.hpp>

namespace lib {
/**
 * Class that uses sol::state
 */
class API_EXPORT Lua {
public:
    Lua();
    explicit Lua(std::unique_ptr<sol::state> state);

    sol::state& state();

    sol::global_table& getGlobalEnvironment();

private:
    static void initEnvironment(sol::environment &env);

private:
    std::unique_ptr<sol::state> m_lua;
};
}

#endif //SOL2TEST_LUA_H
