#pragma once
#include "IHistoryController.h"
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(std::string const& path, int width, int height, IHistoryController& historyController);

	std::string GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

private:
	std::string m_path;

	int m_width;
	int m_height;

	IHistoryController& m_historyController;
};