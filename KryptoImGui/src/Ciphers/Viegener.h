#pragma once
#include "Cipher.h"
#include <string_view>

class Viegener : public Cipher
{
public:
	Viegener();
	~Viegener();

	virtual std::string encrypt(const std::string_view& text) override;
	virtual std::string decrypt(const std::string_view& text) override;
};