#pragma once
#include <autogit-cli/Application.hpp>
#include <autogit-cli/Authentication.hpp>
#include <pybind11/embed.h>

namespace py = pybind11;

int main(int argc, char** argv) {
    std::string description = AutoGitCLI::description();
    AutoGitCLI::Application app{ description,argc,argv };

    // Parsing CLI
    AutoGitCLI_PARSE(app, argc, argv);

    AutoGitCLI::Authentication auth{ app };

    py::scoped_interpreter guard{};
    py::exec(R"(
        print("[PYTHON] CODE RUNNING")   
    )");
    
    //AutoGitCLI::infoScreen();

    return 0;
}

