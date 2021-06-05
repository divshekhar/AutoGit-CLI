#include <autogit-cli/Application.hpp>

namespace AutoGitCLI {

    void logo() {

        std::string logo = R"raw(
        ___         __        _______ __ 
       /   | __  __/ /_____  / ____(_) /_
      / /| |/ / / / __/ __ \/ / __/ / __/
     / ___ / /_/ / /_/ /_/ / /_/ / / /_  
    /_/  |_\__,_/\__/\____/\____/_/\__/  
                                     
)raw";

        std::cout << Color::reset << Color::green;
        std::cout << logo;
        std::cout << Color::reset << std::flush;
    }

    std::string description() {
        std::string desc;
        desc = "\nAutoGit - A command-line tool to easily create and remove repositories from GitHub and local system.\n";
        return desc;
    }

    void infoScreen() {
        logo();
        std::cout << Color::green << Color::bold << description() << Color::reset;
    }

    void cli_version() {
        std::cout << Color::green << Color::bold << "\nAutoGit Version: 2.0.0\n" << Color::reset;
    }

    Application::Application(std::string description, int argc, char** argv)
        : CLI::App(description), m_argc(argc), m_argv(argv) 
    {

        /// Version flag
        add_flag_function("-v,--version",
            [this](int i) {
                cli_version();
                throw CLI::Success();
            },
            "Version of the AutoGit CLI");

        /// Info flag    
        add_flag_function(
            "-i,--info",
            [this](int i) {
                infoScreen();
                cli_version();
                throw CLI::Success();
            },
            "Info about AutoGit CLI");

    }

    void Application::run() { parse(m_argc, m_argv); }

    auto Application::exit(const CLI::Error& e) -> int {
        std::cout << (e.get_exit_code() == 0 ? Color::green : Color::red);
        int val = CLI::App::exit(e);
        std::cout << Color::reset << std::flush;
        return val;
    }

    Application::~Application() {}
} // AutoGitCLI namespace