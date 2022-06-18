#include "cmake.hpp"

#include "cmd.hpp"
#include "error.hpp"

namespace Cmake {


void configure() {
    if (Cmd::run(Cmd::Args {"cmake", "-B", buildDir}) != 0) {
        throw CmakeError("Configuration failed. See stderr.");
    }
}

void build() {
    if (Cmd::run(Cmd::Args {"cmake", "--build", buildDir}) != 0) {
        throw CmakeError("build failed. See stderr.");
    }
}


void clean() {
    // FIXME: breaks on windows
    if (Cmd::run(Cmd::Args {"cmake", "--build", buildDir, "--target", "clean"}) != 0) {
        throw CmakeError("build failed. See stderr.");
    }
}

}  // namespace Cmake
