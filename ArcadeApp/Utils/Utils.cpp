#include "Utils.h"

#include <cmath>
#include <algorithm>

bool IsEqual(float x, float y)
{
	return fabsf(x - y) < EPSILON;
}

bool IsGreaterThanOrEqual(float x, float y)
{
	return x > y || IsEqual(x, y);
}

bool IsLessThanOrEqual(float x, float y)
{
	return x < y || IsEqual(x, y);
}

float MillisecondsToSeconds(unsigned milliseconds)
{
	return static_cast<float>(milliseconds) / 1000.0f;
}

uint32_t GetIndex(unsigned width, unsigned r, unsigned c)
{
	return r * width + c;
}

bool StringCompare(const std::string& a, const std::string& b)
{
	if(a.length() == b.length())
	{
		return std::equal(a.begin(), a.end(), b.begin(), b.end(),
			[](unsigned char a, unsigned char b)
			{
				return std::tolower(a) == std::tolower(b);
			});
	}

	return false;
}

float Clamp(float val, float min, float max)
{
	if(val < min)
	{
		return min;
	}

	if(val > max)
	{
		return max;
	}

	return val;
}
