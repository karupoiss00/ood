#pragma once
#include "ICommonExecutor.h"
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(std::string const& path, int width, int height, ICommonExecutor& historyController);

	std::string GetPath() const override;

	int GetWidth() const override;
	int GetHeight() const override;

	void Resize(int width, int height) override;

private:
	std::string m_path;

	int m_width;
	int m_height;

	ICommonExecutor& m_historyController;
};