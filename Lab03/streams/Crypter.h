#pragma once
#include <cstdint>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <functional>

class CCryptographer
{
public:
	CCryptographer(int32_t key);

	uint8_t Encrypt(uint8_t value);
	uint8_t Decrypt(uint8_t value);

private:
	std::vector<uint8_t> m_encryptTable;
	std::vector<uint8_t> m_decryptTable;
};
