#include <iostream>

#include <sol/sol.hpp>

#include "lib/Lua.h"
#include "lib/Foo.h"
#include "lib/Bar.h"

template<bool applyWorkaround>
static void testFor(lib::Lua &lua) {
    std::cout << "\033[0;36mTesting with workaround " << (applyWorkaround ? "enabled" : "disabled") << "\033[0m\n";

    auto &state = lua.state();

    state["func"] = [](lib::Foo *obj) {
        std::cout << "Ok\n";
    };

    state.script("loadType('Foo') loadType('Bar') function f(o) func(o) end");

    lib::Bar bar;

    if constexpr (applyWorkaround) {
        class Baz : public lib::Foo {};
        state.new_usertype<Baz>("Baz", sol::base_classes, sol::bases<lib::Foo>());
    }

    if (auto res = state["f"].get<sol::function>()(&bar); !res.valid()) {
        sol::error err = res;
        printf("\033[0;33m%s\033[0m\n", err.what());
    }
}

int main() {
    // fails
    {
        lib::Lua lua;
        testFor<false>(lua);
    }

    // also fails
    {
        lib::Lua lua(std::make_unique<sol::state>());
        testFor<false>(lua);
    }

    // ok
    {
        lib::Lua lua;
        testFor<true>(lua);
    }

    // ok
    {
        lib::Lua lua(std::make_unique<sol::state>());
        testFor<true>(lua);
    }

    return 0;
}
