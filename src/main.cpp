#pragma once
#include <autogit-cli/Application.hpp>

int main(int argc, char** argv) {
    std::string description = AutoGitCLI::description();
    AutoGitCLI::Application app{ description,argc,argv };
    AutoGitCLI_PARSE(app, argc, argv);
    std::cout << AutoGitCLI::Color::green << "Successfully Parsed" << AutoGitCLI::Color::reset << std::endl;
    return 0;
}

