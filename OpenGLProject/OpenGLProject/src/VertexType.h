#pragma once

#define VERTEX3POS4COL 0

struct Vec2 {
	float x, y;
};
struct Vec3 {
	float x, y, z;
};

struct Vec4 {
	float x, y, z, w;
};

struct Vertex3Pos4Col
{
	Vec3 Position;
	Vec4 Color;
};

class VertexType
{
};

