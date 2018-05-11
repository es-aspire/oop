#pragma once

struct ColorRGBA
{
public:
	ColorRGBA()
		: r(0)
		, g(0)
		, b(0)
		, a(255) {};

	ColorRGBA(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255)
		: r(red)
		, g(green)
		, b(blue)
		, a(alpha)
	{
	}

	unsigned int r;
	unsigned int g;
	unsigned int b;
	unsigned int a;
};
inline std::istream& operator>>(std::istream& input, ColorRGBA& color)
{
	unsigned int r = 0;
	unsigned int g = 0;
	unsigned int b = 0;

	if (input >> r && input.get() == ',' && input >> g && input.get() == ',' && input >> b)
	{
		color = ColorRGBA(r, g, b);
	}
	else
	{
		input.setstate(std::ios_base::failbit | input.rdstate());
	}

	return input;
}

inline bool operator==(const ColorRGBA& verifiedClr, const ColorRGBA& expectedClr)
{
	return verifiedClr.r == expectedClr.r
		&& verifiedClr.g == expectedClr.g
		&& verifiedClr.b == expectedClr.b
		&& verifiedClr.a == expectedClr.a;
}