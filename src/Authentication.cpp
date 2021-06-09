#pragma once

#include <autogit-cli/Authentication.hpp>

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

#ifdef __linux__
#include <termios.h>
#include <unistd.h>
#endif // __linux__

#include <pybind11/embed.h>

namespace py = pybind11;

namespace AutoGitCLI {
	Authentication::Authentication(Application& app) : m_app(app) {
        if (m_app.got_subcommand("config")) {
            inputCredentials();
        }
    }

	void Authentication::inputCredentials() {

        std::string& username = m_app.getCredentials().username;
        std::string& email = m_app.getCredentials().email;
        std::string& password = m_app.getCredentials().password;

        if (username == "" && email == "") {
            std::cout << "> GitHub Username: ";
            std::getline(std::cin, username);
        }
        if (email == "" && username == "") {
            std::cout << "> GitHub Email: ";
            std::getline(std::cin, email);
        }
        if (password == "")
        {
            #ifdef _WIN32
                HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
                DWORD mode = 0;
                GetConsoleMode(hStdin, &mode);
                SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
            #endif // _WIN32

            #ifdef __linux__
                termios oldt;
                tcgetattr(STDIN_FILENO, &oldt);
                termios newt = oldt;
                newt.c_lflag &= ~ECHO;
                tcsetattr(STDIN_FILENO, TCSANOW, &newt);
            #endif // __linux__  

            std::cout << "> GitHub Password: ";
            std::getline(std::cin, password);
            std::cout << std::endl;
        }

        py::scoped_interpreter guard{};
        try {
            auto  authModule = py::module::import("python.auth");
            auto func = authModule.attr("authentication");
            func(username,password);
        }
        catch (py::error_already_set& e) {
            std::cout << e.what() << std::endl;
        }
        
	}

	Authentication::~Authentication() {}
}