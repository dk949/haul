
#include "cmd.hpp"

#include "error.hpp"

#include <fmt/format.h>

namespace Cmd {


int run(const Args &args) {
    const auto [status, ec] = reproc::run(args, opts);
    if (ec == std::errc::no_such_file_or_directory) {
        throw CmdError(fmt::format("{}  not found. Please install it and make sure it is in PATH.", args[0]));
    }
    if (ec != std::errc {}) {
        throw std::system_error(ec);
    }
    return status;
}


}  // namespace Cmd
