# pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <CLI/CLI.hpp>
#include <fmt/format.h>
#include <autogit-cli/Colors.hpp>

/// Macro defined for parsing the CLI
#define AutoGitCLI_PARSE(app, ...)               \
    try {                                        \
        app.run();                               \
    } catch(const AutoGitCLI::ParseError &e) {   \
        return app.exit(e);                      \
    }

namespace AutoGitCLI {
    using CLI::App;
    using CLI::NonexistentPath;
    using CLI::ExitCodes;
    using CLI::Option;
    using CLI::ParseError;
    using CLI::Error;
    using CLI::Success;

    std::string description();

    void logo();

    void infoScreen();

    class Application : public CLI::App {
    protected:
        int m_argc;
        char** m_argv;
    public:
        Application(std::string description, int argc, char** argv);

        void run();

        auto exit(const CLI::Error& e) -> int;

        ~Application() override;
    };
} // AutoGitCLI namespace