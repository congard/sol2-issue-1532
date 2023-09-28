#include "Foo.h"

#include <iostream>
#include <sol/sol.hpp>

namespace lib {
template<typename T>
void registerType(sol::table &table);

template<>
void registerType<Foo>(sol::table &table) {
    if (table["Foo"].valid())
        return;
    auto usertype = table.new_usertype<Foo>("Foo");
}
}