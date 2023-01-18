#pragma once
#include <vector>
#include <algorithm>
#include <string>

namespace Kasiski
{
	inline bool compare_ints(const std::pair<int, int>& pair1,
		const std::pair<int, int>& pair2)
	{
		int result{ 0 };
		if (pair2.second < pair1.second)
			result = 1;

		return result;
	}

	inline bool compare_doubles(const std::pair<int, double>& pair1,
		const std::pair<int, double>& pair2)
	{
		int result{ 0 };
		if (pair2.second < pair1.second)
			result = 1;

		return result;
	}

	inline std::vector<int> getPasswordLengths(const std::string_view text)
	{
		std::vector<int> distances{};
		std::string s{};
		for (int i{ 0 }; i < text.size() - 2; ++i)
		{
			for (int j{ i + 1 }; j < text.size() - 2; ++j)
			{
				if (text[i] == text[j] &&
					text[i + 1] == text[j + 1] &&
					text[i + 2] == text[j + 2])
				{
					for (int z{ 0 }; z < s.size(); ++z)
						s[z] = text[i + z];

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
}