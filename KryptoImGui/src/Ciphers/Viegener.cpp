#include "Viegener.h"

//std::string Viegener::decrypt(const std::string_view& text)
//{
//	std::string output{};
//	std::string s{};
//	for (int i{ 0 }; i < text.size() - 2; ++i)
//	{
//		for (int j{ i + 1 }; j < text.size() - 2; ++j)
//		{
//			if (text[i] == text[j] && text[i + 1] == text[j + 1] && text[i + 2] == text[j + 2])
//			{
//				for (int z{ 0 }; z < s.size(); ++z)
//					s[z] = text[i + z];
//
//				output.append(std::to_string(j - i));
//				output.append(" (");
//				output.append(std::string(std::begin(s), std::end(s)));
//				output.append("), ");
//			}
//		}
//	}
//	return output;
//}
