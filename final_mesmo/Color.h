#ifndef _COLOR_H
#define _COLOR_H

class Color
{
	double red, green, blue, special;

public:
	Color()
	{
		red = 0.5;
		green = 0.5;
		blue = 0.5;
	}

	Color(double r, double g, double b, double s)
	{
		red = r;
		green = g;
		blue = b;
		special = s;
	}

	// method functions
	double getColorRed() { return red; }
	double getColorGreen() { return green; }
	double getColorBlue() { return blue; }
	double getColorSpecial() { return special; }

	Color colorScalar(double scalar)
	{
		return Color(red * scalar, green * scalar, blue * scalar, special);
	}

	Color colorAdd(Color color)
	{
		return Color(red + color.getColorRed(), green + color.getColorGreen(), blue + color.getColorBlue(), special);
	}

	Color colorMultiply(Color color)
	{
		return Color(red * color.getColorRed(), green * color.getColorGreen(), blue * color.getColorBlue(), special);
	}

	Color clip()
	{
		double alllight = red + green + blue;
		double excesslight = alllight - 3;
		if (excesslight > 0)
		{
			red = red + excesslight * (red / alllight);
			green = green + excesslight * (green / alllight);
			blue = blue + excesslight * (blue / alllight);
		}
		if (red > 1)
		{
			red = 1;
		}
		if (green > 1)
		{
			green = 1;
		}
		if (blue > 1)
		{
			blue = 1;
		}
		if (red < 0)
		{
			red = 0;
		}
		if (green < 0)
		{
			green = 0;
		}
		if (blue < 0)
		{
			blue = 0;
		}

		return Color(red, green, blue, special);
	}
};

#endif