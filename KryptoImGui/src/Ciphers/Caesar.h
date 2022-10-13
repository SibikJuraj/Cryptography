#pragma once
#include "Cipher.h"
#include <string_view>

class Caesar : public Cipher
{
public:
	Caesar();
	~Caesar();

	virtual std::string encrypt(const std::string_view& text) override;
	virtual std::string decrypt(const std::string_view& text) override;
	int m_K1;
};