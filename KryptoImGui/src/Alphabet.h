#pragma once
#include <vector>
#include <string_view>

struct Alphabet
{
	const std::vector<std::pair<char, double>> m_Alphabet;
	const double m_IC;
};