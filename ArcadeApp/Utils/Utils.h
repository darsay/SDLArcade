#pragma once
#include <cstdint>
#include <string>

static const float EPSILON = 0.0001f;
const float PI = 3.14159f;
const float TWO_PI = 2.0f * PI;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

bool IsLessThanOrEqual(float x, float y);

float MillisecondsToSeconds(unsigned int milliseconds);

uint32_t GetIndex(unsigned int width, unsigned int r, unsigned int c);

bool StringCompare(const std::string& a, const std::string& b);

float Clamp(float val, float min, float max);

struct Size
{
	unsigned int width = 0;
	unsigned int height = 0;
};