#pragma once
#include"Errors.h"
#include<cmath>
class Pixel
{
public:
	Pixel(int b = 0, int g = 0, int r = 0, int a = 122);
	Pixel operator+(const int& c);
	Pixel& operator+=(const int& c);
	Pixel operator-(const int& c);
	Pixel& operator-=(const int& c);
	void inverseSub(const int& c);
	Pixel operator*(const int& c);
	Pixel& operator*=(const int& c);
	Pixel operator/(const int& c);
	Pixel& operator/=(const int& c);
	void iverseDiv(const int& c);
	void power(const int& c);
	void min(const int& c);
	void max(const int& c);
	void Log();
	void inversePixel();
	int average();
	void Abs();
	void convertGrey();
	void convertBW();
	int getR()const {
		return red;
	}
	int getG()const {
		return green;
	}
	int getB()const {
		return blue;
	}
	int getA()const {
		return alpha;
	}
	void setA(int a) { alpha = a > 255 ? 255 : a < 0 ? 0 : a; }
	void setG(int a) { green = a > 255 ? 255 : a < 0 ? 0 : a; }
	void setB(int a) { blue = a > 255 ? 255 : a < 0 ? 0 : a; }
	void setR(int a) { red = a > 255 ? 255 : a < 0 ? 0 : a; }
	void checkAndSet();
	// Dodati medijanu i skup kompozitnih funkcija!!!

	friend std::ostream& operator<<(std::ostream& os, const Pixel& p);


private:
	int red;
	int green;
	int blue;
	int alpha;
};

