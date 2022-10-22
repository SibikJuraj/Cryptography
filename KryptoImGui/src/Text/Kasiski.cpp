#include <algorithm>

#include "Kasiski.h"

bool Kasiski::compare_ints(const std::pair<int, int>& pair1,
	const std::pair<int, int>& pair2)
{
	int result{ 0 };
	if (pair2.second < pair1.second)
		result = 1;

	return result;
}

bool Kasiski::compare_doubles(const std::pair<int, double>& pair1,
	const std::pair<int, double>& pair2)
{
	int result{ 0 };
	if (pair2.second < pair1.second)
		result = 1;

	return result;
}

std::vector<int> Kasiski::getPasswordLengths(const Text& text)
{
	std::vector<int> distances{};
	std::string s{};
	for (int i{ 0 }; i < text.getText().size() - 2; ++i)
	{
		for (int j{ i + 1 }; j < text.getText().size() - 2; ++j)
		{
			if (text.getText()[i] == text.getText()[j] &&
				text.getText()[i + 1] == text.getText()[j + 1] &&
				text.getText()[i + 2] == text.getText()[j + 2])
			{
				for (int z{ 0 }; z < s.size(); ++z)
					s[z] = text.getText()[i + z];

				distances.push_back(j - i);
			}
		}
	}
	std::vector<std::pair<int, int>> passwordLengths(11);
	for (int i{ 15 }; i <= 25; ++i)
	{
		for (int distance : distances)
		{
			if (distance % i == 0)
			{
				passwordLengths[i - 15].first = i;
				++(passwordLengths[i - 15]).second;
			}
		}
	}
	std::sort(passwordLengths.begin(), passwordLengths.end(), &compare_ints);

	distances.resize(passwordLengths.size());
	for (int i{ 0 }; i < distances.size(); ++i)
	{
		distances[i] = passwordLengths[i].first;
	}
	return distances;
}
