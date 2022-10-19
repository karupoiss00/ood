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

inline CCryptographer::CCryptographer(int32_t key)
{
	m_encryptTable.resize(256);
	m_decryptTable.resize(256);

	uint8_t value = 0;

	std::random_device rd;
	std::mt19937 generator(rd());

	std::transform(m_encryptTable.begin(), m_encryptTable.end(), m_encryptTable.begin(), [&value](uint8_t) {
		return value++;
	});

	std::shuffle(m_encryptTable.begin(), m_encryptTable.end(), generator);

	for (unsigned i = 0; i < m_encryptTable.size(); ++i)
	{
		m_decryptTable[m_encryptTable[i]] = static_cast<uint8_t>(i);
	}
}

inline uint8_t CCryptographer::Encrypt(uint8_t value)
{
	return m_encryptTable[value];
}

inline uint8_t CCryptographer::Decrypt(uint8_t value)
{
	return m_decryptTable[value];
}