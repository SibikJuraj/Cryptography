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

	/* funkcia na generovanie kluca zo zadaneho hesla
	 * budem heslo opakovat tak, aby som vytvoril 256 bajtove pole kluca
	 *
	 * !!! POZOR !!!
	 * Opakuje sa aj ukoncenie retazca, t.j. jednotlive opakovania
	 * su oddelene znakom '\0'.
	 * Ak heslo bude "password", kluc bude "password\0password\0...pass",
	 * HEX dump:
	00000000  70 61 73 73 77 6f 72 64  00 70 61 73 73 77 6f 72  |password.passwor|
	00000010  64 00 70 61 73 73 77 6f  72 64 00 70 61 73 73 77  |d.password.passw|
	00000020  6f 72 64 00 70 61 73 73  77 6f 72 64 00 70 61 73  |ord.password.pas|
	00000030  73 77 6f 72 64 00 70 61  73 73 77 6f 72 64 00 70  |sword.password.p|
	00000040  61 73 73 77 6f 72 64 00  70 61 73 73 77 6f 72 64  |assword.password|
	00000050  00 70 61 73 73 77 6f 72  64 00 70 61 73 73 77 6f  |.password.passwo|
	00000060  72 64 00 70 61 73 73 77  6f 72 64 00 70 61 73 73  |rd.password.pass|
	00000070  77 6f 72 64 00 70 61 73  73 77 6f 72 64 00 70 61  |word.password.pa|
	00000080  73 73 77 6f 72 64 00 70  61 73 73 77 6f 72 64 00  |ssword.password.|
	00000090  70 61 73 73 77 6f 72 64  00 70 61 73 73 77 6f 72  |password.passwor|
	000000a0  64 00 70 61 73 73 77 6f  72 64 00 70 61 73 73 77  |d.password.passw|
	000000b0  6f 72 64 00 70 61 73 73  77 6f 72 64 00 70 61 73  |ord.password.pas|
	000000c0  73 77 6f 72 64 00 70 61  73 73 77 6f 72 64 00 70  |sword.password.p|
	000000d0  61 73 73 77 6f 72 64 00  70 61 73 73 77 6f 72 64  |assword.password|
	000000e0  00 70 61 73 73 77 6f 72  64 00 70 61 73 73 77 6f  |.password.passwo|
	000000f0  72 64 00 70 61 73 73 77  6f 72 64 00 70 61 73 73  |rd.password.pass|
	 * */

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
		_setmode(_fileno(stdout), _O_U8TEXT);
		_setmode(_fileno(stdin), _O_U8TEXT);

		std::string inputText{ TextLoader::loadByteFile("texts/stream/text4_enc.txt") };
		std::string outputText{ };
		outputText.resize(inputText.size());

		std::string passwd{};
		int letterCountBest{ 0 };
		AnalysisOfSKLang skLang{};
		std::string decryptedText{};
		for (int i{ 100'000 }; i <= 999'999; ++i)
		{
			passwd = std::to_string(i) + '\0';

			decrypt(passwd, inputText, outputText);

			auto letterCountText{ TextLoader::numberOfLetters(outputText) };
			if (letterCountText > letterCountBest)
			{
				letterCountBest = letterCountText;
				decryptedText.assign("Password : " + std::to_string(i) + '\n' + outputText);
			}
		}

		TextLoader::saveText("texts/stream/decoded/text4_dec.txt", decryptedText);

		return 0;
	}
}