#include "Editor.h"

const std::string DEFAULT_TOOL = "pen";
const Color CLEAR_COLOR = 0xFFFFFF; 

Editor::Editor(std::shared_ptr<Image> image, IDrawingStrategyFactory& drawingStrategyFactory)
	: m_drawingStrategyFactory(drawingStrategyFactory)
	, m_hasUnsavedChanges(false)
	, m_image(image)
{
	SetDrawingTool(DEFAULT_TOOL);
}

void Editor::StartPaint(QMouseEvent* event)
{
	m_hasUnsavedChanges = true;
	m_drawingStrategy->StartPaint(event);
}

void Editor::Paint(QMouseEvent* event)
{
	m_drawingStrategy->Paint(event);
}

void Editor::EndPaint(QMouseEvent* event)
{
	m_drawingStrategy->EndPaint(event);
}

DrawingSettings Editor::GetDrawingSettings()
{
	return m_drawingStrategy->GetSettings();
}

void Editor::Undo()
{

}

void Editor::Redo()
{

}

void Editor::ClearImage()
{
	m_image->Fill(CLEAR_COLOR);
	m_hasUnsavedChanges = true;
}

void Editor::SaveChanges()
{
	m_hasUnsavedChanges = false;
}

void Editor::SetDrawingTool(std::string toolName)
{
	m_drawingStrategy = m_drawingStrategyFactory.GetStrategy(DEFAULT_TOOL);
}

void Editor::SetDrawingSettings(DrawingSettings settings)
{
	m_drawingStrategy->SetSettings(settings);
}

bool Editor::HasUnsavedChanges()
{
	return m_hasUnsavedChanges;
}