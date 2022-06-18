#include "git.hpp"

#include "cmd.hpp"
#include "error.hpp"

#include <fmt/format.h>
#include <string>
#include <string_view>


namespace Git {

void cloneImpl(const Cmd::Args &args) {
    if (Cmd::run(args) != 0) {
        throw GitError(fmt::format("could not clone {}. See stderr.", args[2]));
    }
}

// NOLINTNEXTLINE (bugprone-easily-swappable-parameters)
void clone(std::string_view repo, std::string_view dir) {
    cloneImpl(Cmd::Args {"git", "clone", repo, dir});
}

void clone(std::string_view repo) {
    cloneImpl(Cmd::Args {"git", "clone", repo});
}


void checkout(std::string_view hash) {
    int status = Cmd::run(Cmd::Args {"git", "checkout", hash});
    if (status != 0) {
        throw GitError(fmt::format("could not checkout {}. See stderr.", hash));
    }
}


}  // namespace Git
