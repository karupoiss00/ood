#pragma once
#include "IMemento.h"
#include "Image.h"

struct EditorData
{
	Image image;
	bool hasUnsavedChanges;
};

class EditorMemento : public IMemento<EditorData>
{
public:
	EditorMemento(EditorData data)
		: m_data(data)
	{
	}

	EditorData State() const 
	{
		return m_data;
	}

private: 
	EditorData m_data;
};