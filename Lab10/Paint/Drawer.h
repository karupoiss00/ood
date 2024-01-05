#pragma once

#include "Image.h"

void DrawLine(Image& image, Point from, Point to, Color color, int width = 1);
void DrawCircle(Image& image, Point center, int radius, Color color);
void FillCircle(Image& image, Point center, int radius, Color color);