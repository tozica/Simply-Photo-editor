#pragma once
#include<string>
#include<regex>
#include<fstream>
#include<map>
#include"Operation.h"
#include"Errors.h"


class Composite : public Operation{
public:
	Composite(Image* i, std::string p) : Operation(i), path(p) {
		inicMap();
		readAndParese();
	}
	void readAndParese();
	void decide(std::string, std::string c ="");
	void inicMap();
	void operate()override;
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)override;
	std::string getPath()override { return path; }
	static bool isComposite;
    std::string getOperation() override { return "Composite"; }
	std::string getConst()override { return path; }
	void writeComposite(std::string);
private:
	std::vector<Operation*> operations;
	std::string path;
	std::map<std::string, int> map;
};

