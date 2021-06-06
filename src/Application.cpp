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
        std::cout << Color::green << Color::bold << "AutoGit Version: 2.0.0" << Color::reset << std::endl;
    }

    Application::Application(std::string description, int argc, char** argv)
        : CLI::App(description), m_argc(argc), m_argv(argv) 
    {
        //require_subcommand(1);

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

        CLI::App* config = add_subcommand("config", "Configuration command for AutoGit");
        config->add_option("-e,--email", m_credentials.email, "GitHub email");
        config->add_option("-u,--user-name", m_credentials.username, "GitHub Username");
        config->add_option("-p,--password", m_credentials.password, "GitHub Password");
    }

    void Application::run() { parse(m_argc, m_argv); }

    Credentials Application::getCredentials() {
        return m_credentials;
    }

    auto Application::exit(const CLI::Error& e) -> int {
        std::cout << (e.get_exit_code() == 0 ? Color::green : Color::red);
        int val = CLI::App::exit(e);
        std::cout << Color::reset << std::flush;
        return val;
    }

    Application::~Application() {}
} // AutoGitCLI namespace