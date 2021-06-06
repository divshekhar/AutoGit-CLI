#pragma once
#include <autogit-cli/Application.hpp>
#include <autogit-cli/Authentication.hpp>

int main(int argc, char** argv) {
    std::string description = AutoGitCLI::description();
    AutoGitCLI::Application app{ description,argc,argv };

    // Parsing CLI
    AutoGitCLI_PARSE(app, argc, argv);

    AutoGitCLI::Authentication auth{ app };
    
    //AutoGitCLI::infoScreen();

    return 0;
}

