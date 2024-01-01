#pragma once

#include "Image.h"

/**
 * ������ ������� ������ ����� ����� ������� from � to ������ color �� ����������� Image.
 *
 * ��� ��������� ������������ �������� ����������.
 * (https://ru.wikipedia.org/wiki/��������_����������)
 */
void DrawLine(Image& image, Point from, Point to, Color color);
void DrawCircle(Image& image, Point center, int radius, Color color);
void FillCircle(Image& image, Point center, int radius, Color color);