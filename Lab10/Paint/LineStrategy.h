#pragma once
#include <algorithm>
#include <QWidget>
#include <QPainter>

#include "Drawer.h"
#include "DrawingStrategyBase.h"
#include "IEditorView.h"

class LineStrategy : public DrawingStrategyBase
{
public:
	LineStrategy(std::shared_ptr<Image> image, IEditorView* view) 
		: DrawingStrategyBase(image)
		, m_drawing(false)
		, m_view(view)
		, m_temporaryImage(std::make_shared<Image>(*image))
	{
	
	}

	void StartPaint(QMouseEvent* event) override
	{
		if (event->button() == Qt::LeftButton){
			m_drawing = true;
			m_startPoint = ClampPoint(event->pos());
			*m_temporaryImage = *m_image;
			m_view->SetImage(m_temporaryImage);
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
			*m_temporaryImage = *m_image;

			DrawImpl(m_temporaryImage, event->pos());
		}
	}

	void EndPaint(QMouseEvent* event) override
	{
		DrawImpl(m_image, event->pos());

		m_drawing = false;
	}

private:

	void DrawImpl(std::shared_ptr<Image>& image, QPoint endPoint)
	{
		auto pos = ClampPoint(endPoint);
		auto radius = (m_settings.size / 2) + 2;

		DrawLine(
			*image,
			{ m_startPoint.x(), m_startPoint.y() },
			{ pos.x(), pos.y() },
			m_settings.color.rgb(),
			m_settings.size
		);

		auto dirtyRect = QRect(m_startPoint, pos).normalized().adjusted(-radius, -radius, +radius, +radius);

		m_view->SetImage(image);
		m_view->update(dirtyRect);
	};

	QPoint ClampPoint(QPoint const& point)
	{
		auto imageSize = m_image->GetSize();
		return {
			std::clamp(point.x(), 0, imageSize.width),
			std::clamp(point.y(), 0, imageSize.height)
		};
	};

	bool m_drawing;
	QPoint m_startPoint;
	QPoint m_lastPoint;

	std::shared_ptr<Image> m_temporaryImage;

	IEditorView* m_view;
};
#pragma once
