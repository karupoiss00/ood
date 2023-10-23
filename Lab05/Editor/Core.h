#pragma once

#include <string>
#include <filesystem>
#include "IDocument.h"

namespace Core
{
	const size_t TEMP_FOLDER_NAME_LENGTH = 6;
	const size_t TEMP_FILE_NAME_LENGTH = 12;

	std::string GenerateRandomFileName(size_t fileNameLength);
	std::string EncodeHtml(const std::string& str);

	void SaveToHtml(const std::unique_ptr<IDocument>& document, std::ofstream& file, const std::filesystem::path& imageFolder);

	void AssertImageSize(int width, int height);

	bool ParseNumber(std::string const& str, size_t& number);
}