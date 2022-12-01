#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

namespace StreamGen {

	/* generator pseudonahodnych cisel zalozeny na RC4 */
	typedef unsigned char byte;
	/* vnutorny stav RC4 generatora */

	byte rc4_i, rc4_j;
	byte rc4_s[256];

	/* staticky alokovany pouzity kluc pre RC4 */

	byte rc4_k[256];

	byte* getKey(const std::string_view passwd)
	{
		for (int i{ 0 }, j = { 0 }; i < 256; ++i)
		{
			rc4_k[i] = (byte)passwd[j];
			if (passwd[j] != 0)
				++j;
			else
				j = 0;
		}

		return rc4_k;
	}

	/* pociatocna inicializacia generatora */

	void rc4_init(const byte* key)
	{
		for (int i = 0; i < 256; i++)
		{
			rc4_s[i] = i;
		}

		for (int i = 0, j = 0; i < 256; i++)
		{
			j = (j + rc4_s[i] + key[i]) % 256;
			// swap(rc4_s[i], rc4_s[j])
			byte tmp = rc4_s[i]; rc4_s[i] = rc4_s[j]; rc4_s[j] = tmp;
		}

		rc4_i = 0;
		rc4_j = 0;
	}

	/* generuje nahodny byte (8-bitove cislo 0-255) */

	byte rc4_rand()
	{
		rc4_i = (rc4_i + 1) % 256; // kedze rc4_i je typu byte, stacilo by aj rc4_i++;
		rc4_j = (rc4_j + rc4_s[rc4_i]) % 256; // aj tu je modulo 256 nepotrebne
		// swap(rc4_s[rc4_i], rc4_s[rc4_j])
		byte tmp = rc4_s[rc4_i]; rc4_s[rc4_i] = rc4_s[rc4_j]; rc4_s[rc4_j] = tmp;

		byte t = (rc4_s[rc4_i] + rc4_s[rc4_j]) % 256;
		return rc4_s[t];
	}

	/* koniec generatora pseudonahodnych cisel */

	typedef enum {
		MODE_ENCRYPT = 0,
		MODE_DECRYPT = 1
	} CipherMode;

	void encrypt(const std::string_view passwd, const std::string_view plainText, std::string& cipherText)
	{
		// nastav random seed - toto je hodnota kluca
		rc4_init(getKey(passwd));

		for (int i{ 0 }; i < plainText.size(); ++i)
		{
			byte p = (byte)plainText[i];
			byte r = rc4_rand();
			byte c = p ^ r;
			cipherText[i] = c;
		}
	}

	void decrypt(const std::string_view passwd, const std::string_view cipherText, std::string& plainText)
	{
		// vzhladom na operaciu XOR je sifrovanie a desifrovanie uplne rovnake
		encrypt(passwd, cipherText, plainText);
	}

	int init()
	{
		std::string inputText{ TextLoader::loadByteFile("texts/stream/text1_enc.txt") };
		std::string outputText{ };
		outputText.resize(inputText.size());

		for (int i{ 100'000 }; i <= 999'999; ++i)
		{
			decrypt(std::to_string(i)+'\0', inputText, outputText);

			auto letterCountText{ TextLoader::numberOfLetters(outputText) };
			if (letterCountText > inputText.length() * 0.65)
			{
				outputText.erase(std::remove(outputText.begin(), outputText.end(), '\r'), outputText.end());

				outputText += "\nPassword : " + std::to_string(i);
				break;
			}
		}

		TextLoader::saveText("texts/stream/decoded/text1_dec.txt", outputText);

		return 0;
	}
}