#include <autogit-cli/Application.hpp>

namespace AutoGitCLI {

    std::string logo() {
        std::string logo = R"raw(

_____/\\\\\\\\\__________________________________________________/\\\\\\\\\\\\_____________________        
 ___/\\\\\\\\\\\\\______________________________________________/\\\//////////______________________       
  __/\\\/////////\\\___________________/\\\_____________________/\\\______________/\\\_____/\\\______      
   _\/\\\_______\/\\\__/\\\____/\\\__/\\\\\\\\\\\_____/\\\\\____\/\\\____/\\\\\\\_\///___/\\\\\\\\\\\_     
    _\/\\\\\\\\\\\\\\\_\/\\\___\/\\\_\////\\\////____/\\\///\\\__\/\\\___\/////\\\__/\\\_\////\\\////__    
     _\/\\\/////////\\\_\/\\\___\/\\\____\/\\\_______/\\\__\//\\\_\/\\\_______\/\\\_\/\\\____\/\\\______   
      _\/\\\_______\/\\\_\/\\\___\/\\\____\/\\\_/\\__\//\\\__/\\\__\/\\\_______\/\\\_\/\\\____\/\\\_/\\__  
       _\/\\\_______\/\\\_\//\\\\\\\\\_____\//\\\\\____\///\\\\\/___\//\\\\\\\\\\\\/__\/\\\____\//\\\\\___ 
        _\///________\///___\/////////_______\/////_______\/////______\////////////____\///______\/////____

)raw";
        return logo;
    }

    std::string description() {
        std::string desc = logo();
        desc += "\nAutoGit-CLI - A command-line tool to easily create and remove repositories from GitHub and local system.";
        return desc;
    }

    void infoScreen() {
        std::string autogitLogo = description();
        /*for (int i = 0; i < autogitLogo.size(); i++) {
            std::string letter = autogitLogo.substr(i,1);
            if (letter == "\\" || letter == "/") 
            {
                std::cout << Color::reset << Color::green;
            }
            std::cout << autogitLogo[i];
            if (autogitLogo[i] == '\n') 
            {
                std::cout << std::flush;
            }
        }*/
        std::cout << autogitLogo;
    }

    Application::Application(std::string description, int argc, char** argv)
        : CLI::App(description), m_argc(argc), m_argv(argv) 
    {

        /// Info flag    
        add_flag_function(
            "-i,--info",
            [this](int i) {
                infoScreen();
                throw CLI::Success();
            },
            "Give info about AutoGitCLI");

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