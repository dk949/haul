#ifndef GIT_HPP
#define GIT_HPP
#include <string_view>

namespace Git {
void clone(std::string_view repo, std::string_view dir);
void clone(std::string_view repo);
void checkout(std::string_view hash);
}

#endif  // GIT_HPP
