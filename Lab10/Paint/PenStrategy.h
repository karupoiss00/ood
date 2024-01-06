#pragma once
#include <QWidget>
#include <algorithm>
#include "DrawingStrategyBase.h"
#include "Drawer.h"

class PenStrategy : public DrawingStrategyBase
{
public:
	PenStrategy(std::shared_ptr<Image> image, QWidget* view)
		: DrawingStrategyBase(image)
		, m_drawing(false)
		, m_view(view)
	{
	}

	void StartPaint(QMouseEvent* event) override
	{
		if (event->button() == Qt::LeftButton)
		{
			m_drawing = true;
			m_lastPoint = ClampPoint(event->pos());
		}
	}

	void Paint(QMouseEvent* event) override
	{
		if (!m_drawing)
		{
			return;
		}

		if (event->buttons() & Qt::LeftButton)
		{
			auto pos = ClampPoint(event->pos());
			auto radius = (m_settings.size / 2) + 2;
			DrawLine(
				*m_image,
				{ m_lastPoint.x(), m_lastPoint.y() },
				{ pos.x(), pos.y() },
				m_settings.color.rgb(),
				m_settings.size);

			auto dirtyRect = QRect(m_lastPoint, pos).normalized().adjusted(-radius, -radius, +radius, +radius);

			m_view->update(dirtyRect);

			m_lastPoint = pos;
		}
	}

	void EndPaint(QMouseEvent* event) override
	{
		m_drawing = false;
	}

private:
	QPoint ClampPoint(QPoint const& point)
	{
		auto imageSize = m_image->GetSize();
		return { 
			std::clamp(point.x(), 0, imageSize.width), 
			std::clamp(point.y(), 0, imageSize.height) 
		};
	};

	bool m_drawing;
	QPoint m_lastPoint;
	QWidget* m_view;
};