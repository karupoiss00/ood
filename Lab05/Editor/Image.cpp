#include "Image.h"
#include "TrivialCommand.h"

using namespace std;

CImage::CImage(string const& path, int width, int height, IHistoryController& historyController)
	: m_path(path), m_width(width), m_height(height), m_historyController(historyController)
{
}

std::string CImage::GetPath() const
{
	return m_path;
}

int CImage::GetWidth() const
{
	return m_width;
}

int CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(int width, int height)
{
	auto oldWidth = m_width;
	auto oldHeight = m_height;

	m_historyController.AddAndExecuteCommand(make_unique<TrivialCommand>(
		[this, width, height]() {
			this->m_width = width;
			this->m_height = height;
		},
		[this, oldWidth, oldHeight]() {
			this->m_width = oldWidth;
			this->m_height = oldHeight;
		})
	);
}
