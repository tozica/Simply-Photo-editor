#pragma once
#include"Formater.h"
#include"Image.h"
#include<fstream>

class MyFormat : public Formater
{
public:
	MyFormat(Image* i) : image(i) {}
	void write(const char *file, Layer* l)override;
	void read(const char* file, Layer* l)override;
private:
	void writeLayers(std::ofstream &of);
	void writeSelection(std::ofstream& of);
	void writeComposite(std::ofstream& of);
	Image* image;
};

