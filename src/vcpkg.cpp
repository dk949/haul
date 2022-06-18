#include "vcpkg.hpp"

#include "cmd.hpp"
#include "error.hpp"
#include "git.hpp"
#include "util.hpp"

#include <filesystem>
#include <string_view>
namespace fs = std::filesystem;


namespace Vcpkg {
constexpr std::string_view vcpkgRepo = "https://github.com/Microsoft/vcpkg.git";
void clone() {
    Git::clone(vcpkgRepo);
}

void bootstrap() {
    using enum PlatformType;

    Cmd::Args args = platformAssign(                                             //
        []() {                                                                   //
        return Cmd::Args {"./vcpkg/bootstrap-vcpkg.sh", "-disableMetrics"};      // posix
        },                                                                       //
        []() {                                                                   //
        return Cmd::Args {R"(.\vcpkg\bootstrap-vcpkg.bat)", "-disableMetrics"};  // win
    });
    if (Cmd::run(args) != 0) {
        throw VcpkgError("Failed to bootstrap vcpkg. See stderr.");
    }
}
void install() {
    using enum PlatformType;

    if (!fs::exists("./vcpkg/vcpkg")) {
        bootstrap();
    }
    Cmd::Args args = platformAssign(                       //
        []() {                                             //
        return Cmd::Args {"./vcpkg/vcpkg", "install"};     // posix
        },                                                 //
        []() {                                             //
        return Cmd::Args {R"(.\vcpkg\vcpkg", "install)"};  // win
    });

    if (Cmd::run(args) != 0) {
        throw VcpkgError("Failed to install vcpkg. See stderr.");
    }
}
}  // namespace Vcpkg
