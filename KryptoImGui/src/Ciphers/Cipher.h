#pragma once
#include <vector>
#include <string_view>

class Cipher
{
public:
	virtual std::string encrypt(const std::string_view& text) = 0;
	virtual std::string decrypt(const std::string_view& text) = 0;
};