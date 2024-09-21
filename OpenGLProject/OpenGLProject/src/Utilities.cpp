#include "Utilities.h"

std::array<Vertex3Pos4Col, 4> Utilities::CreateQuadPositions(float x, float y, float width, float height)
{
	Vertex3Pos4Col v0;
	v0.Position = { x - width / 2.0f, y - height / 2.0f, 0.0f };

	Vertex3Pos4Col v1;
	v1.Position = { x + width / 2.0f, y - height / 2.0f, 0.0f };

	Vertex3Pos4Col v2;
	v2.Position = { x + width / 2.0f, y + height / 2.0f, 0.0f };

	Vertex3Pos4Col v3;
	v3.Position = { x - width / 2.0f, y + height / 2.0f, 0.0f };
	return { v0, v1, v2, v3 };
}

Vertex3Pos4Col* Utilities::CreateQuadPositionsAndFillArray(Vertex3Pos4Col* arr, float x, float y, float width, float height)
{
	arr->Position = { x - width / 2.0f, y - height / 2.0f, 0.0f };
	arr->Color = { 1, 1, 1, 1 };
	arr++;

	arr->Position = { x + width / 2.0f, y - height / 2.0f, 0.0f };
	arr->Color = { 1, 1, 1, 1 };
	arr++;

	arr->Position = { x + width / 2.0f, y + height / 2.0f, 0.0f };
	arr->Color = { 1, 1, 1, 1 };
	arr++;

	arr->Position = { x - width / 2.0f, y + height / 2.0f, 0.0f };
	arr->Color = { 1, 1, 1, 1 };
	arr++;
	return arr;
}

const char* Utilities::GetFormattedCurrentTime(const std::string& format)
{
	tm* tmp = new tm[1];
	auto timeNow = std::chrono::system_clock::now();
	auto timeFormatted = std::chrono::system_clock::to_time_t(timeNow);

	unsigned int size = format.length();

	localtime_s(tmp, &timeFormatted);
	char timeBuffer[sizeof(format)];
	strftime(timeBuffer, sizeof(timeBuffer), format.c_str(), tmp);
	delete[] tmp;

	return timeBuffer;
}
