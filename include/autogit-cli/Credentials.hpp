#pragma once
#include <string>

namespace AutoGitCLI {

	struct Credentials {
		std::string email;
		std::string username;
		std::string password;
	};
}