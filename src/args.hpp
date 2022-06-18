#ifndef ARGS_HPP
#define ARGS_HPP

#include <docopt.h>
#include <fmt/format.h>
#include <project/config.hpp>

using ArgsT = std::map<std::string, docopt::value>;

[[nodiscard]] inline ArgsT parseArgs(int argc, const char **argv) {
    return docopt::docopt(std::string {haul::project::docstring},
        std::vector<std::string> {argv + 1, argv + argc},
        true,
        fmt::format("v{}", haul::project::version::full));
}

#endif  // ARGS_HPP
