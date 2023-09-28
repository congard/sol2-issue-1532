#include "Bar.h"

#include <iostream>
#include <sol/sol.hpp>

namespace lib {
template<typename T>
void registerType(sol::table &table);

template<>
void registerType<Bar>(sol::table &table) {
    if (table["Bar"].valid())
        return;
    auto usertype = table.new_usertype<Bar>("Bar", sol::base_classes, sol::bases<Foo>());
}
}