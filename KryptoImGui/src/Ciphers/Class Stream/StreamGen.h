#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

namespace StreamGen {

	#define MAX_TEXT_SIZE 10000

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

	byte* getKey(const std::string& passwd)
	{
		for (int i = 0, j = 0; i < 256; i++)
		{
			rc4_k[i] = (byte)passwd[j];
			if (passwd[j] != 0) j++;
			else j = 0;
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

	size_t readFile(const char* name, byte* memory, size_t max)
	{
		size_t count = 0;
		FILE* stream = fopen(name, "rb");
		if (stream == NULL)
		{
			fprintf(stderr, "Nepodarilo sa nacitat subor '%s'!\n", name);
		}
		else
		{
			count = fread(memory, sizeof(byte), max, stream);
			fclose(stream);
		}

		return count;
	}

	void writeFile(const char* name, const char* memory, int count)
	{
		FILE* stream = fopen(name, "wb");
		if (stream == NULL)
		{
			fprintf(stderr, "Nepodarilo sa zapisat subor '%s'!\n", name);
		}
		else
		{
			fwrite(memory, sizeof(byte), count, stream);
			fclose(stream);
		}
	}

	void encrypt(const std::string& passwd, const byte* plainText, byte* cipherText, size_t count)
	{
		// nastav random seed - toto je hodnota kluca
		rc4_init(getKey(passwd));

		int i;
		for (i = 0; i < count; i++)
		{
			byte p = plainText[i];
			byte r = rc4_rand();
			byte c = p ^ r;
			cipherText[i] = c;
		}
	}

	void decrypt(const std::string& passwd, const byte* cipherText, byte* plainText, size_t count)
	{
		// vzhladom na operaciu XOR je sifrovanie a desifrovanie uplne rovnake
		encrypt(passwd, cipherText, plainText, count);
	}

	int init()
	{
		CipherMode mode = MODE_DECRYPT;
		std::string passwd = "100000";
		const char* inputFilename = "texts/stream/text4_enc.txt";
		const char* outputFilename = "texts/stream/decoded/text4_dec.txt";

		int i = 1;

		byte* inputText = (byte*)malloc(MAX_TEXT_SIZE);
		byte* outputText = (byte*)malloc(MAX_TEXT_SIZE);
		if (inputText == NULL || outputText == NULL)
		{
			fprintf(stderr, "Nepodarilo sa alokovat pamat na text!\n");
			return -1;
		}

		size_t count = readFile(inputFilename, inputText, MAX_TEXT_SIZE);
		if (count == 0)
		{
			fprintf(stderr, "Vstupny text je prazdny!\n");
			return -1;
		}

		double closest = 10.00;
		int nOLetters = 0;
		AnalysisOfSKLang skLang{};
		std::string decryptedText{};
		for (int i{ 100'000 }; i <= 999'999; ++i)
		{
			passwd = std::to_string(i);
			if (mode == MODE_ENCRYPT)
				encrypt(passwd, inputText, outputText, count);
			else if (mode == MODE_DECRYPT)
				decrypt(passwd, inputText, outputText, count);

			if (i == 123456)
				auto a{ 0 };
			

			auto* text{ reinterpret_cast<char*>(outputText) };
			auto analysis{ TextLoader::analyzeText(text)};
			if (analysis && analysis->getNOLetters() > 50 && 
				analysis->getNOLetters() > nOLetters/* &&
				abs(analysis->getIC() - skLang.getIC()) < closest*/)
			{
				closest = abs(analysis->getIC() - skLang.getIC());
				nOLetters = analysis->getNOLetters();
				decryptedText.assign("Password : ");
				decryptedText.append(std::to_string(i));
				decryptedText.append("\n");
				decryptedText.append(text);
			}
		}

		writeFile(outputFilename, decryptedText.c_str(), count);

		free(inputText);
		free(outputText);

		return 0;
	}
}