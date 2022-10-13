#pragma once
#include "Cipher.h"
#include <string_view>

class Affine : public Cipher
{
public:
	Affine();
	~Affine();

	virtual std::string encrypt(const std::string_view& text) override;
	virtual std::string decrypt(const std::string_view& text) override;
};