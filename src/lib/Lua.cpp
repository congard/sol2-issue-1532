#include "Lua.h"
#include "Foo.h"
#include "Bar.h"

namespace lib {
Lua::Lua()
    : Lua(std::make_unique<sol::state>()) {}

Lua::Lua(std::unique_ptr<sol::state> state)
    : m_lua(std::move(state))
{
    m_lua->open_libraries();

    sol::environment env = getGlobalEnvironment();
    initEnvironment(env);
}

sol::state& Lua::state() {
    return *m_lua;
}

sol::global_table& Lua::getGlobalEnvironment() {
    return state().globals();
}

template<typename T>
void registerType(sol::table &table);

void Lua::initEnvironment(sol::environment &env) {
    env["loadType"] = [](std::string_view type, sol::this_environment tenv) {
        sol::environment &env = tenv;
        sol::table table = env;

        // just if-else in order to simplify code
        if (type == "Foo") {
            registerType<Foo>(table);
        } else if (type == "Bar") {
            registerType<Bar>(table);
        }
    };
}
}
