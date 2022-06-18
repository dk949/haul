#include "new.hpp"

#include "error.hpp"
#include "git.hpp"
#include "util.hpp"
#include "vcpkg.hpp"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <string>

namespace fs = std::filesystem;

const std::string &checkHash(const std::string &hash) {
    if (!std::all_of(std::begin(hash), std::end(hash), [](char c) { return std::isxdigit(c); })) {
        throw NewError(fmt::format("{} is an invalid hash", hash));
    }
    return hash;
}

std::string checkName(const std::string &name) {
    if (!std::all_of(std::begin(name), std::end(name), [](char c) {
            // NOLINTNEXTLINE (readability-implicit-bool-conversion) // It'c a c API, not much I can do
            return std::islower(c) || std::isdigit(c) || c == '-' || c == '_';
        })) {
        throw NewError(fmt::format("{} is an invalid name.\n"
                                   "A valid project name consists of lower case alphanumeric characters\n"
                                   "\twith optional dashes (-) or underscores (_).\n"
                                   "\tNote: all dashes will be converted to underscores for the executable name.\n"
                                   "These are vcpkg naming requirements.",
            name));
    }
    if (name.find('-') != std::string::npos) {
        auto out = name;
        replaceAll(out, "-", "_");
        return out;
    }
    return name;
}

std::string vcpkgifyString(const std::string &name) {
    if (name.find('_') != std::string::npos) {
        auto out = name;
        replaceAll(out, "_", "-");
        return out;
    }
    return name;
}

New::New(const ArgsT &args) {
    ASSERT(args.at("<project_name>"));
    m_name = checkName(args.at("<project_name>").asString());
    if (args.at("--template")) {
        m_hash = checkHash(args.at("--template").asString());
    }
}

void New::run() {
    gitClone();        // git clone $dk949/cpp-init $m_name
    cd(m_name);        // cd $m_name
    gitCheckout();     // $m_hash && git checkout $m_hash
    rmGit();           // rm -rf .git
    updateVcpkg();     // sed -i "s/cpp-init/$m_name/" vcpkg.json && sed -i "s/$desc/\"\"/" vcpkg.json
    bootstrapVcpkg();  // ./vcpkg/bootstrap-vcpkg.sh -disableMetrics
    postNew();         // echo $post_new_msg
}

void New::gitClone() const {
    Git::clone(repo, m_name);
}
void New::gitCheckout() const {
    if (!m_hash.empty()) {
        Git::checkout(m_hash);
    }
}

void New::rmGit() {
    try {
        fs::remove_all(".git");
    } catch (const fs::filesystem_error &e) {
        throw NewError(fmt::format("Could not remove .git directory: {}", e.what()));
    }
}
void New::updateVcpkg() const {
    std::ifstream i {"vcpkg.json"};
    if (!i) {
        throw NewError("Could not read from vcpkg.json");
    }
    nlohmann::ordered_json j;
    i >> j;
    i.close();

    j["name"] = vcpkgifyString(m_name);
    j["description"] = "";
    j["$url"] = "";


    std::ofstream o {"vcpkg.json"};
    if (!o) {
        throw NewError("Could not write to vcpkg.json");
    }

    o << std::setw(2) << j;
}

void New::bootstrapVcpkg() {
    Vcpkg::clone();
    Vcpkg::bootstrap();
}


void New::postNew() const {
    fmt::print("\n"
               "{} is setup.\n"
               "Use ",
        m_name);
    fmt::print(fmt::fg(fmt::terminal_color::green), "haul build");
    fmt::print(" to build the program.\n"
               "Run it with ");
    fmt::print(fmt::fg(fmt::terminal_color::green), "{}{}\n", platformAssign("./build/bin/", R"(.\build\bin\)"), m_name);
}
