#ifndef UTIL_HPP
#define UTIL_HPP

#include <exception>
#include <filesystem>
#include <stdexcept>
#include <string>
#include <utility>

inline void cd(const std::filesystem::path &path) {
    /*
       Letting this exception reach main, even though main doesn't explicitly
       handle std::filesystem_error. `cd` is only ever used when it is certain
       that the directory exists. If this is not the case, it is an internal
       error and will be handled by the catch-all at the end of main.
    */
    std::filesystem::current_path(path);
}

#define ASSERT(X) \
    if (!(X))     \
        throw AssertionError(#X " evaluates to false");

template<typename Fn>
struct Defer {
private:
    Fn m_fn;
public:
    explicit Defer(Fn &&fn)
            : m_fn(std::forward<Fn>(fn)) { }
    ~Defer() {
        m_fn();
    }
    Defer(const Defer &) = delete;
    Defer &operator=(const Defer &) = delete;
    Defer(Defer &&) = delete;
    Defer &operator=(Defer &&) = delete;
};


enum class PlatformType {
    Posix,
    Windows,
    Unknown,
};

#ifdef __GNUC__
static constexpr auto Platform = PlatformType::Posix;
#elif defined(_MSC_VER)
static constexpr auto Platform = PlatformType::Windows;
#else
static constexpr auto Platform = PlatformType::Unknown;
#endif

static_assert(Platform == PlatformType::Windows || Platform == PlatformType::Posix,
    "Only windows and POSIX operating systems are supported");


template<typename T>
auto &&lazyGet(T &&t) {
    return t;
}

template<std::invocable T>
auto lazyGet(T &&t) {
    return t();
}



template<typename Posix, typename Win>
auto platformAssign(Posix &&posix, Win &&win) {
    if constexpr (Platform == PlatformType::Posix) {
        return lazyGet(std::forward<Posix>(posix));
    } else if constexpr (Platform == PlatformType::Windows) {
        return lazyGet(std::forward<Win>(win));
    }
}

#pragma GCC diagnostic push
#if (defined(__GNUC__) && !defined(__clang__))
// Not sure what gcc is unhappy about, this shoudl be fine
#pragma GCC diagnostic ignored "-Wrestrict"
#endif
inline std::size_t replaceAll(std::string &inout, std::string_view what, std::string_view with) {
    std::size_t count {};
    for (std::string::size_type pos = 0; std::string::npos != (pos = inout.find(what.data(), pos, what.length()));
         pos += with.length(), ++count) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
    return count;
}
#pragma GCC diagnostic pop

#endif  // UTIL_HPP
