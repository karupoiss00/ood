#include <filesystem>
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <array>
#include "Core.h"

using namespace std;
namespace fs = std::filesystem;

string Core::GenerateRandomFileName(size_t fileNameLength)
{
	vector<char> charset({ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
		'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_' });

	default_random_engine rng(random_device{}());
	uniform_int_distribution<> dist(0, charset.size() - 1);

	auto getRandomChar = [charset, &dist, &rng]() {
		return charset[dist(rng)];
	};

	string randomFileName(fileNameLength, 0);
	generate_n(randomFileName.begin(), fileNameLength, getRandomChar);

	return randomFileName;
}

std::string Core::EncodeHtml(const string& str)
{
	array<pair<string, string>, 5> symbols = {
		{ { "&", "&amp;" }, { "\"", "&quot;" }, { "'", "&apos;" }, { "<", "&lt;" }, { ">", "&gt;" } }
	};
	string html = str;

	for (auto const& symbol : symbols)
	{
		size_t pos = 0;

		while ((pos = html.find(symbol.first, pos)) != string::npos)
		{
			html.replace(pos, symbol.first.length(), symbol.second);
			pos += symbol.second.length();
		}
	}

	return html;
}

void Core::SaveToHtml(const unique_ptr<IDocument>& document, ofstream& file, const fs::path& imageFolder)
{
	file << "<!DOCTYPE html>" << endl;
	file << "<html>" << endl;
	file << "<head>" << endl;
	file << "</head>" << endl;

	file << "<body>" << endl;

	const auto title = document->GetTitle();

	if (!title.empty())
	{
		file << "<h1>" << document->GetTitle() << "</h1>" << endl;
	}

	for (size_t i = 0; i < document->GetItemsCount(); i++)
	{
		auto item = document->GetItem(i);

		if (item->GetParagraph() != nullptr)
		{
			auto paragraph = item->GetParagraph();
			file << "    <p>" << Core::EncodeHtml(paragraph->GetText()) << "</p>" << endl;
		}
		else if (item->GetImage() != nullptr)
		{
			if (!fs::exists(imageFolder))
			{
				fs::create_directory(imageFolder);
			}

			auto image = item->GetImage();

			fs::path itemImagePath = image->GetPath();
			fs::path docImagePath = imageFolder.string() + "/" + itemImagePath.filename().string();

			fs::copy_file(itemImagePath, docImagePath);

			file << "    <img src=\"" + imageFolder.filename().string() + "/" + docImagePath.filename().string() + "\"";
			file << " width=\"" << image->GetWidth() << "px\"";
			file << " height=\"" << image->GetHeight() << "px\"";
			file << ">" << endl;
		}
	}

	file << "</body>" << endl;
	file << "</html>" << endl;
}

void Core::AssertImageSize(int width, int height)
{
	if (width < 1 || width > 10000 || height < 1 || height > 10000)
	{
		throw out_of_range("Invalid image size");
	}
}

bool Core::ParseNumber(std::string const& str, size_t& number)
{
	std::stringstream iss(str);

	iss >> number;

	return !iss.fail();
}