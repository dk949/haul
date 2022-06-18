#ifndef NEW_HPP
#define NEW_HPP

#include "args.hpp"

#include <string>
#include <string_view>


class New {

public:
    static constexpr auto hashBase = 16;
private:
    std::string m_name;
    std::string m_hash;
    static constexpr std::string_view repo = "https://github.com/dk949/cpp-init";
public:
    explicit New(const ArgsT &);
    void run();
private:
    void gitClone() const;
    void gitCheckout() const;
    static void rmGit();
    void updateVcpkg() const;
    static void bootstrapVcpkg();
    void postNew() const;
};

#endif  // NEW_HPP
