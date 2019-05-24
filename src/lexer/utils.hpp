#pragma once
#include <cstdio>
#include <iostream>
#include <string>
#include <string_view>


inline int to_number(std::string_view sv)
{
    return std::atoi(sv.data());
}
