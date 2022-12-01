#pragma once

enum CipherMode
{
	MODE_DECRYPT,
	MODE_ENCRYPT
};

static CipherMode s_CipherMode{ MODE_DECRYPT };