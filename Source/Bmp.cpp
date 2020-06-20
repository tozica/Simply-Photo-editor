#include "BMP.h"
#include"Layer.h"



BMP::BMP(int w, int h)
{
	infoheader.width = w;
	infoheader.height = h;
	infoheader.size = sizeof(BMPIheader) + sizeof(BMPCheader);
	fileheder.offset_data = sizeof(BMPFheader) + sizeof(BMPIheader) + sizeof(BMPCheader);
	infoheader.bit_count = 32;
	infoheader.compression = 3;
	data.resize(w * h * 4);
	fileheder.fSize = fileheder.offset_data + data.size();
	fileheder.fType = 0x4D42;
}

void BMP::read(const char* fName, Layer* l)
{
	std::ifstream file(fName, std::ios_base::binary);
	if (file) {
		file.read((char*)&fileheder, sizeof(fileheder));
		file.read((char*)&infoheader, sizeof(infoheader));
		file.read((char*)&colorheader, sizeof(colorheader));

		file.seekg(fileheder.offset_data, file.beg);

		data.resize(infoheader.width * infoheader.height * 4);

		file.read((char*)data.data(), data.size());

		l->hight = infoheader.height;
		l->width = infoheader.width;


		unsigned int c = infoheader.bit_count / 8;


		for (int y = infoheader.height - 1; y >= 0; y--)
			for (int x = 0; x < infoheader.width; x++) {
				unsigned int ind = c * (y * infoheader.width + x);
				l->pixelData.push_back(new Pixel(data[ind], data[ind + 1], data[ind + 2], data[ind + 3]));
			}

	}
	else
		throw FileError();
	file.close();
}

void BMP::write(const char* file, Layer* l)
{
	


	infoheader.bit_count = 32;
	infoheader.width = l->width;
	infoheader.height = l->hight;
	data.clear();
	data.resize(l->width * l->hight * 4);
	int i = 0;
	unsigned int c = infoheader.bit_count / 8;
	for (int y = l->hight - 1; y >= 0; y--)
		for (int x = 0; x < l->width; x++) {
			unsigned int ind = c * (y * l->width + x);
			data[ind] = l->pixelData[i]->getB();
			data[ind + 1] = l->pixelData[i]->getG();
			data[ind + 2] = l->pixelData[i]->getR();
			data[ind + 3] = l->pixelData[i]->getA();
			i++;
		}


	std::ofstream of(file, std::ios_base::binary);
	if (of) {
		of.write((const char*)&fileheder, sizeof(fileheder));
		of.write((const char*)&infoheader, sizeof(infoheader));
		of.write((const char*)&colorheader, sizeof(colorheader));
		of.write((const char*)data.data(), data.size());
	}
	else
		throw FileError("Unable to open destination file in class BMP");
	of.close();
}