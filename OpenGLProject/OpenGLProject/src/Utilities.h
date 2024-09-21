#pragma once
#include "VertexType.h"
#include "array"
#include "chrono"
#include "string"

class Utilities
{
public:
	static std::array<Vertex3Pos4Col, 4> CreateQuadPositions(float x, float y, float width, float height);
	static Vertex3Pos4Col* CreateQuadPositionsAndFillArray(Vertex3Pos4Col* arr, float x, float y, float width, float height);
	static const char* GetFormattedCurrentTime(const std::string& format);
};

