#pragma once
#include <Ciphers/Cipher.h>

class Stream : public CipherCore<int>
{
public:
	Stream();
	virtual Text encrypt(const Text& input, bool fineTuning) override;
	virtual Text decrypt(const Text& input, bool fineTuning) override;
	virtual char encryptingFormula(char letter) override;
	virtual char decryptingFormula(char letter) override;
};

inline Stream::Stream() 
	: CipherCore(std::vector<int>(2))
{
}

inline Text Stream::encrypt(const Text& input, bool fineTuning)
{
	//StreamGen::init(StreamGen::CipherMode::MODE_ENCRYPT);
	return Text();
}

inline Text Stream::decrypt(const Text& input, bool fineTuning)
{
	//StreamGen::init(StreamGen::CipherMode::MODE_DECRYPT);
	return Text();
}

inline char Stream::encryptingFormula(char letter)
{
	return 0;
}

inline char Stream::decryptingFormula(char letter)
{
	return 0;
}