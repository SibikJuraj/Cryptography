#include "Stream.h"

Stream::Stream()
	: Cipher(std::vector<int>(2))
{
}

Text Stream::encrypt(const Text& input, bool fineTuning)
{
	//StreamGen::init(StreamGen::CipherMode::MODE_ENCRYPT);
	return Text();
}

Text Stream::decrypt(const Text& input, bool fineTuning)
{
	//StreamGen::init(StreamGen::CipherMode::MODE_DECRYPT);
	return Text();
}

char Stream::encryptingFormula(char letter)
{
	return 0;
}

char Stream::decryptingFormula(char letter)
{
	return 0;
}