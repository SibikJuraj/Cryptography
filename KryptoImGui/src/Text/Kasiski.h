#pragma once
#include<vector>

#include "Text.h"

class Kasiski
{
public:
	static std::vector<int> getPasswordLengths(const Text& text);
	static bool compare_ints(const std::pair<int, int>& pair1, const std::pair<int, int>& pair2);
	static bool compare_doubles(const std::pair<int, double>& pair1, const std::pair<int, double>& pair2);
};