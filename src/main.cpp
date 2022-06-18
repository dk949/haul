#include "args.hpp"
#include "cmake.hpp"
#include "error.hpp"
#include "new.hpp"
#include "vcpkg.hpp"

#include <exception>
#include <filesystem>
#include <fmt/color.h>
#include <fmt/format.h>
#include <system_error>
namespace fs = std::filesystem;


int main(int argc, const char **argv) try {
    const auto args = parseArgs(argc, argv);
    if (args.at("new").asBool()) {
        New {args}.run();
    } else if (args.at("install").asBool()) {
        Vcpkg::install();
    } else if (args.at("configure").asBool()) {
        Cmake::configure();
    } else if (args.at("build").asBool()) {
        if (!fs::exists(Cmake::buildDir)) {
            Cmake::configure();
        }
        Cmake::build();
    } else if (args.at("clean").asBool()) {
        Cmake::clean();
    } else {
        throw Unreachable("Unexpected command");
    }
} catch (const std::exception &e) {  //
    return handleError(e);
} catch (...) {
    fmt::print(stderr, "unexpected error: ");
    fmt::print(stderr, fmt::fg(fmt::color::red), "???\n");
    return -1;
}
