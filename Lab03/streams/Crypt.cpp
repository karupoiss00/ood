#include "Crypter.h"

constexpr size_t SIZE_OF_TABLE = 256;

using namespace std;

CCryptographer::CCryptographer(int32_t key)
{
	m_encryptTable.resize(SIZE_OF_TABLE);
	m_decryptTable.resize(SIZE_OF_TABLE);

	uint8_t value = 0;

	mt19937 generator(key);

	transform(m_encryptTable.begin(), m_encryptTable.end(), m_encryptTable.begin(), [&value](uint8_t) {
		return value++;
	});

	shuffle(m_encryptTable.begin(), m_encryptTable.end(), generator);

	for (unsigned i = 0; i < m_encryptTable.size(); ++i)
	{
		m_decryptTable[m_encryptTable[i]] = static_cast<uint8_t>(i);
	}
}

uint8_t CCryptographer::Encrypt(uint8_t value)
{
	return m_encryptTable[value];
}

uint8_t CCryptographer::Decrypt(uint8_t value)
{
	return m_decryptTable[value];
}