#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"Formater.h"


#pragma pack (push, 1)

class BMPFheader {
public:
	friend class BMP;
private:
	uint16_t fType{ 0x4D42 };
	uint32_t fSize{ 0 };
	uint16_t reserv1{ 0 };
	uint16_t reserv2{ 0 };
	uint32_t offset_data;
};

class BMPIheader {
public:
	friend class BMP;
private:
	uint32_t size{ 0 };
	int32_t width{ 0 };
	int32_t height{ 0 };

	uint16_t planes{ 1 };
	uint16_t bit_count{ 0 };
	uint32_t compression{ 0 };
	uint32_t imageSize{ 0 };
	int32_t XpixelsPM{ 0 };
	int32_t YpixelsPM{ 0 };
	uint32_t usedColors{ 0 };
	uint32_t importantColors{ 0 };
};

class BMPCheader {
public:
	friend class BMP;

private:
	uint32_t   maskRed{ 0x00ff0000 };
	uint32_t maskGreen{ 0x0000ff00 };
	uint32_t  maskBlue{ 0x000000ff };
	uint32_t maskAlpha{ 0xff000000 };
	uint32_t colorSpace{ 0x73524742 };
	uint32_t unused[16]{ 0 };
};

#pragma pack(pop)

class BMP : public Formater {
public:
	BMP(int w, int h);
	BMP() = default;
	void read(const char* fName, Layer*)override;
	void write(const char* file, Layer*)override;
private:
	BMPFheader fileheder;
	BMPIheader infoheader;
	BMPCheader colorheader;
	std::vector<unsigned char> data;
};