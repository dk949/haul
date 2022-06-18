#ifndef ERROR_HPP
#define ERROR_HPP

#include <exception>
#include <fmt/color.h>
#include <fmt/format.h>
#include <stdexcept>
#include <system_error>

inline int pritnErrorAndExit(std::string_view errType, const std ::exception &e, int ec = 1) {
    fmt::print(stderr, "{}: ", errType);
    fmt::print(stderr, fmt::fg(fmt::terminal_color::red), "{}\n", e.what());
    return ec;
}

struct InternalError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct Unreachable : InternalError {
    using InternalError::InternalError;
};

struct AssertionError : InternalError {
    using InternalError::InternalError;
};

struct CmdError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct VcpkgError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct GitError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct CmakeError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

struct NewError : std::runtime_error {
    using std::runtime_error::runtime_error;
};

inline int handleError(const std::exception &e) {
    if (dynamic_cast<const InternalError *>(&e)) {
        return pritnErrorAndExit("internal error error", e, -1);
    }
    if (dynamic_cast<const CmdError *>(&e)) {
        return pritnErrorAndExit("command execution error", e);
    }
    if (dynamic_cast<const VcpkgError *>(&e)) {
        return pritnErrorAndExit("vcpkg error", e);
    }
    if (dynamic_cast<const GitError *>(&e)) {
        return pritnErrorAndExit("git error", e);
    }
    if (dynamic_cast<const CmakeError *>(&e)) {
        return pritnErrorAndExit("cmake error", e);
    }
    if (dynamic_cast<const NewError *>(&e)) {
        return pritnErrorAndExit("new error", e);
    }
    if (dynamic_cast<const std::system_error *>(&e)) {
        return pritnErrorAndExit("system error", e);
    }
    return pritnErrorAndExit("unexpected error", e, -1);
}

#endif  // ERROR_HPP
