#pragma once
#include <autogit-cli/Application.hpp>

namespace AutoGitCLI {
	class Authentication {
	private:
		Application& m_app;
	public:
		Authentication(Application&);
		
		void inputCredentials();

		~Authentication();
	};
}