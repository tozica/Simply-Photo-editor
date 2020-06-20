#include "Pixel.h"
#include"Composite.h"

Pixel::Pixel(int b, int g, int r, int a)
{
		alpha = a;
		red = r > 255 ? 255 : r < 0 ? 0 : r;
		green = g> 255 ? 255 : g < 0 ? 0 : g;
		blue = b > 255 ? 255 : b < 0 ? 0 : b;
	
}

Pixel Pixel::operator+(const int &c)
{
	
	green = green + c > 255 && !Composite::isComposite ? 255 : green + c;
	red = red + c > 255 && !Composite::isComposite ? 255 : red + c;
	blue = blue + c > 255 && !Composite::isComposite ? 255 : blue + c;
	return *this;
	
}

Pixel& Pixel::operator+=(const int &c)
{
	*this = *this + c;
	return *this;
}

Pixel Pixel::operator-(const int &c)
{

	green = green - c > 255 && !Composite::isComposite ? 255 : green - c;
	red = red - c > 255 && !Composite::isComposite ? 255 : red - c;
	blue = blue - c > 255 && !Composite::isComposite ? 255 : blue - c;
	return *this;
}

Pixel& Pixel::operator-=(const int& c)
{
	*this = *this - c;
	return *this;
}

void Pixel::inverseSub(const int& c)
{

	
	red = c - red < 0 && !Composite::isComposite ? 0 : c - red;
	green = c - green < 0 && !Composite::isComposite ? 0 : c - green;
	blue = c - blue < 0 && !Composite::isComposite ? 0 : c - blue;

	
}

Pixel Pixel::operator*(const int& c)
{
	green = green * c > 255 && !Composite::isComposite ? 255 : green * c;
	red = red * c > 255 && !Composite::isComposite ? 255 : red * c;
	blue = blue * c > 255 && !Composite::isComposite ? 255 : blue * c;
	return *this;
}

Pixel& Pixel::operator*=(const int& c)
{
	*this = *this * c;
	return *this;
}

Pixel Pixel::operator/(const int& c)
{
	if (!c) throw PixelError("Division by zero, please try with the other value");
	else {
		red /= c;
		green /= c;
		blue /= c;
	}
	return *this;
}

Pixel& Pixel::operator/=(const int& c)
{
	*this = *this / c;
	return *this;
}

void Pixel::iverseDiv(const int& c)
{
	
	red = red ? c / red : 0;
	green = green ? c / green : 0;
	blue = blue ? c / blue : 0;

	
}

void Pixel::power(const int& c)
{
	int tmp1 = pow(red, c);
	red = tmp1 > 255 && !Composite::isComposite ? 255 : tmp1;

	tmp1 = pow(green, c);
	green = tmp1 > 255 && !Composite::isComposite? 255:tmp1;

    tmp1 = pow(blue, c);
	blue = tmp1 > 255 && !Composite::isComposite ? 255 : tmp1;

	
}

void Pixel::min(const int& c)
{

	red = red > c ? c : red;
	green = green > c ? c : green;
	blue = blue > c ? c : blue;

	checkAndSet();
}

void Pixel::max(const int& c)
{
	red = red < c ? c : red;
	green = green < c ? c : green;
	blue = blue < c ? c : blue;

	checkAndSet();
	
}

void Pixel::Log()
{
	red = log10(red) < 0 && !Composite::isComposite ? 0 : log10(red);
	green = log10(green) < 0 && !Composite::isComposite ? 0: log10(green);
	blue = log10(blue) < 0 && !Composite::isComposite ? 0 : log10(blue);
}

void Pixel::inversePixel()
{
	red = 255 - red;
	green = 255 - green;
	blue = 255 - blue;

	checkAndSet();
}

int Pixel::average()
{
	return (red + green + blue) / 3;
}

void Pixel::Abs()
{
	red = abs(red);
	green = abs(green);
	blue = abs(blue);
}

void Pixel::convertGrey()
{
	red = static_cast<int>(this->average());
	green = static_cast<int>(this->average());
	blue = static_cast<int>(this->average());
	
}

void Pixel::convertBW()
{
	if (this->average() < 127) {
		red = 0;
		green = 0;
		blue = 0;
	}
	else {
		red = 255;
		green = 255;
		blue = 255;
	}
}

void Pixel::checkAndSet()
{
	red = red > 255 && !Composite::isComposite ? 255 : red < 0 && !Composite::isComposite ? 0 : red;
	green = green > 255 && !Composite::isComposite ? 255 : green < 0 && !Composite::isComposite ? 0 : green;
	blue = blue > 255 && !Composite::isComposite ? 255 : blue < 0 && !Composite::isComposite ? 0 : blue;
}

std::ostream& operator<<(std::ostream& os, const Pixel& p)
{
	return os << "(" << static_cast<int>(p.red) << " " << static_cast<int>(p.green) << " " << static_cast<int>(p.blue) << ")" << std::endl;
}
