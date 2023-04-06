/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "interpreter/variable_map.h"
#include <iostream>

// return the value of a variable
int VariableMap::get(const std::string& name) const
{
    auto iter = map.find(name);
    if (iter == map.end())
        throw std::logic_error("Unknown variable");
    return (*iter).second;
}

// set the value of a variable
void VariableMap::set(const std::string& name, int value)
{
    map[name] = value;
}

// Have any variables been declared?
[[maybe_unused]] bool VariableMap::isEmpty() const
{
    return map.empty();
}

// print all variables and their values
void VariableMap::print(std::ostream& os) const
{
    for (const auto& i : map)
        os << i.first << "=" << i.second << std::endl;
}

// clear all variables and their values
[[maybe_unused]] void VariableMap::reset()
{
    map.clear();
}
