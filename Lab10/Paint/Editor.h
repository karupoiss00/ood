#pragma once
#include <memory>
#include <QMouseEvent>
#include "Image.h"
#include "IDrawingStrategy.h"
#include "IDrawingStrategyFactory.h"

class Editor
{
public:
	Editor(std::shared_ptr<Image> image, IDrawingStrategyFactory& drawingStrategyFactory);

	void StartPaint(QMouseEvent* event);
	void Paint(QMouseEvent* event);
	void EndPaint(QMouseEvent* event);

	void Undo();
	void Redo();

	void SetDrawingTool(std::string toolName);
	void SetDrawingSettings(DrawingSettings settings);

	void ClearImage();
	void SaveChanges();

	bool HasUnsavedChanges();
	DrawingSettings GetDrawingSettings();

private:
	IDrawingStrategyFactory& m_drawingStrategyFactory;
	std::shared_ptr<IDrawingStrategy> m_drawingStrategy;
	std::shared_ptr<Image> m_image;
	bool m_hasUnsavedChanges;
};