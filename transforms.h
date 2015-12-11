#pragma once
#include <string>

long long intToLong(int &a)
{
	return a * (1ll << 32) + a;
}
int intToInt(int &a)
{
	return a;
}

std::string intToString(int &a)
{
	std::string s;
	int n = a;
	while (n > 0)
	{
		s += ('A' + n % 26);
		n /= 26;
	}
	return s;
}