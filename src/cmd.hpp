#ifndef CMD_HPP
#define CMD_HPP

#include <reproc++/run.hpp>
#include <string_view>
#include <vector>



namespace Cmd {

using Args = std::vector<std::string_view>;
// NOLINTNEXTLINE(fuchsia-statically-constructed-objects,cert-err58-cpp)
static const inline reproc::options opts = []() {
    reproc::options o;
    o.redirect.parent = true;
    return o;
}();

int run(const Args &args);

}  // namespace Cmd

#endif  // CMD_HPP
