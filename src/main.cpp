#include <iostream>
#include <CLI/CLI.hpp>

int main(int argc, char** argv) {
    CLI::App app{ "AutoGit-CLI - A command-line tool to easily create and remove repositories from GitHub and local system." };

    CLI11_PARSE(app, argc, argv);
    return 0;
}