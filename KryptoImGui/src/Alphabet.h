#pragma once
#include <vector>
#include <string_view>

struct Alphabet
{
	enum Letters
	{
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		alphabet_length
	};
	std::vector<double> m_LetterIC;
	double m_IC;
};