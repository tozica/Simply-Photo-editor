#pragma once
#include<algorithm>
#include<vector>
#include<string>
#include<valarray>

class Image;
class Pixel;

class Operation
{
public:
	friend Image;
	Operation(Image* i) :myImage(i) {}
	virtual void operate();
	virtual void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int) {}
	virtual std::string getPath() { return ""; }
	virtual std::string getOperation() = 0;
	virtual std::string getConst() = 0;
	
protected:
	Image *myImage;
};

class Addition:public Operation {
public:
	
	Addition(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	 std::string getOperation() override { return "Add"; }
	 std::string getConst()override { return std::to_string(c); }
private:
	int c;
};

class PaintSelection :public Operation {
public:

	PaintSelection(Image* i, int r1, int g1, int b1) : Operation(i), r(r1), g(g1), b(b1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
    std::string getOperation() override { return ""; }
	std::string getConst() override { return ""; }
private:
	int r, g, b;
};

class Substract :public Operation {
public:

	Substract(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "Sub"; }
	std::string getConst() override { return std::to_string(c); }
private:
	int c;
};

class Multiply :public Operation {
public:

	Multiply(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "Mul"; }
	std::string getConst() override { return std::to_string(c); }
private:
	int c;
};

class Division :public Operation {
public:

	Division(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "Div"; }
	std::string getConst()override { return std::to_string(c); }
private:
	int c;
};

class InverseDiv :public Operation {
public:

	InverseDiv(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "InvDiv"; }
	std::string getConst()override { return std::to_string(c); }
private:
	int c;
};

class InverseSub : public Operation{
public:

	InverseSub(Image * i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "InvSub"; }
	std::string getConst()override { return std::to_string(c); }
private:
	int c;
};

class Power : public Operation {
public:

	Power(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "Pow"; }
	std::string getConst()override { return std::to_string(c); }
private:
	int c;
};


class Min : public Operation {
public:

	Min(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "Min"; }
	std::string getConst()override { return std::to_string(c); }
private:
	int c;
};


class Max : public Operation {
public:

	Max(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "Max"; }
	std::string getConst()override { return std::to_string(c); }
private:
	int c;
};

class Inverse : public Operation {
public:

	Inverse(Image* i) : Operation(i) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "Inv"; }
	std::string getConst() override { return ""; }
private:
	
};


class ConverteGrey : public Operation {
public:

	ConverteGrey(Image* i) : Operation(i) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "ConvGrey"; }
	std::string getConst() override { return ""; }
private:
	
};

class ConverteBW : public Operation {
public:

	ConverteBW(Image* i) : Operation(i) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "ConvBW"; }
	std::string getConst() override { return ""; }
private:
	
};

class ConverteR : public Operation {
public:

	ConverteR(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return ""; }
	std::string getConst()override { return ""; }
private:
	int c;
};

class Log1 : public Operation {
public:

	Log1(Image* i) : Operation(i) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return "Log"; }
	std::string getConst() override { return ""; }
private:
	
};

class Abs1 : public Operation {
public:

	Abs1(Image* i) : Operation(i) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int);
	std::string getOperation() override { return "Abs"; }
	std::string getConst() override { return ""; }
private:
	
};

class ConvertG : public Operation {
public:

	ConvertG(Image* i, int c1) : Operation(i), c(c1) {}
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::string getOperation() override { return ""; }
	std::string getConst()override { return ""; }
private:
	int c;
};

class Mediana : public Operation {
public:
	Mediana(Image* i) :Operation(i) {};
	
	void addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int)override;
	std::vector<Pixel*> pixelDataCopy(std::vector<Pixel*> data);
	std::string getOperation() override { return "Med"; }
	std::string getConst()override { return ""; }
private:
	
	
};