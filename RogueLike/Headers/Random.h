#pragma once
#include <random>
#include <time.h>

class Random
{
public:
	static void Init()
	{
		RandomEngine.seed(static_cast<uint32_t>(time(0)));
	}

	static float Float()
	{
		return (float)Distribution(RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
	}

	static float Float(float min, float max)
	{
		return Float() * (max - min) + min;
	}

	static float Float(float max)
	{
		return Float() * max;
	}

	static int Int()
	{
		return Distribution(RandomEngine);
	}

	static int Int(int min, int max)
	{
		return Int() % (max + 1 - min) + min;
	}

	static int Int(int max)
	{
		return Int() % (max + 1);
	}

	static uint32_t UInt()
	{
		return Distribution(RandomEngine);
	}

	static uint32_t UInt(int min, int max)
	{
		return UInt() % (max + 1 - min) + min;
	}

	static uint32_t UInt(int max)
	{
		return UInt() % (max + 1);
	}

private:
	static std::mt19937 RandomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> Distribution;
};