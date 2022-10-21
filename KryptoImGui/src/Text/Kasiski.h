#pragma once
#include<vector>

#include "Text.h"

class Kasiski
{
public:
	static std::vector<int> getPasswordLengths(const Text& text);
private:
	static bool compare_pair(const std::pair<int, int>& pair1, const std::pair<int, int>& pair2);
};