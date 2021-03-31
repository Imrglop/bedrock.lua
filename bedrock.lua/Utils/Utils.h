#pragma once
#include "../shared.h"
#include "../shared_types.h"
namespace utils {
	std::string getParentFolderOf(std::string in, int purgeAmount = 0, char ch1 = '\\', char ch2 = '/');
}