#pragma once

#include <string>

namespace FileDialog {

	 	std::string Open();

	 	std::string Open(char* buffer, size_t size);

	 	std::string Save();

}
