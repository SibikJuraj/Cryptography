#pragma once

namespace Config
{
	constexpr int c_FontSize{ 18 };

	enum CipherMode
	{
		MODE_DECRYPT,
		MODE_ENCRYPT
	};

	static CipherMode s_CipherMode{ MODE_DECRYPT };
}

