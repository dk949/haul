#ifndef CMAKE_HPP
#define CMAKE_HPP

#include "string_view"
namespace Cmake {

constexpr std::string_view buildDir = "build";

void configure();
void build();
void clean();
}

#endif  // CMAKE_HPP
