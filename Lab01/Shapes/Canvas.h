#pragma once
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include "ICanvas.h"
#include "Point.h"

class Canvas : public sfx::ICanvas
{
public:
	Canvas()
	{
		m_window.create(sf::VideoMode(800, 600), "Shapes");
	}

	void Run()
	{
		m_window.clear();

		while (m_window.isOpen())
		{
			sf::Event event;
			while (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window.close();
				}
			}
			m_window.display();
		}
	}

	void MoveTo(double x, double y)
	{
		m_drawPoint = { x , y };
	}

	void SetColor(sfx::Color color)
	{
		m_color = ToColor(color);
	}

	void LineTo(double x, double y)
	{
		sf::Vertex line[] = {
			{sf::Vector2f(static_cast<float>(m_drawPoint.m_x), static_cast<float>(m_drawPoint.m_y)), m_color},
			{sf::Vector2f(static_cast<float>(x), static_cast<float>(y)), m_color }
		};
		m_window.draw(line, 2, sf::Lines);
	}

	void DrawEllipse(double cx, double cy, double rx, double ry)
	{
		std::cout << "Draw ellipse " << cx << " " << cy << " " << rx << " " << ry << std::endl;
	}

	void DrawText(double x, double y, std::string const& text)
	{
		std::cout << "DrawText " << x << " " << y << " " << text << std::endl;
	}
private:
	static sf::Color ToColor(sfx::Color color)
	{
		return sf::Color(
			static_cast<sf::Uint8>(color.r),
			static_cast<sf::Uint8>(color.g),
			static_cast<sf::Uint8>(color.b),
			static_cast<sf::Uint8>(color.a)
		);
	}

	Point m_drawPoint;
	sf::Color m_color;
	sf::RenderWindow m_window;
	std::thread m_windowThread;
};