#include "Operation.h"
#include"Image.h"
#include"Layer.h"


void Operation::operate()
{
	std::vector<Layer*>tmp = myImage->getLayers();
	std::for_each(tmp.begin(), tmp.end(), [&](Layer* l) {
		if (l->getActive()) {
			if (myImage->getSelecetion()) {
				std::vector<Rectangle> rec = myImage->getSelecetion()->getRectangles();
				std::for_each(rec.begin(), rec.end(), [&](Rectangle r) {
					int x = r.getPos().first;
					int y = r.getPos().second;
					addConst(r.getLenght(), r.getWidth(), x, y, l->getData(), l->getW());
				});
			}
			else {
				addConst(l->getW(), l->getH(), 0, 0, l->getData(), l->getW());

			}
			
		}
	});
}

void Addition::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			*data[j + i * widthg] = *data[j + i * widthg] + c;
		}
	}
	
}



void Substract::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			*data[j + i * widthg] = *data[j + i * widthg] - c;
		}
	}
}



void Multiply::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			*data[j + i * widthg] = *data[j + i * widthg] * c;
		}
	}
}



void Division::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			*data[j + i * widthg] = *data[j + i * widthg] / c;
		}
	}
}



void InverseDiv::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->iverseDiv(c);
		}
	}
}



void InverseSub::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->inverseSub(c);
		}
	}
}



void Power::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->power(c);
		}
	}
}



void Min::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->min(c);
		}
	}
}





void Max::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->max(c);
		}
	}
}



void Inverse::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->inversePixel();
		}
	}
}



void ConverteGrey::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->convertGrey();
		}
	}
}



void Log1::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->Log();
		}
	}
}


void ConverteBW::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->convertBW();
		}
	}
}



void ConverteR::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->setB(255);
			data[j + i * widthg]->setG(0);
			data[j + i * widthg]->setA(100);
			data[j + i * widthg]->setR(0);
		}
	}
}



void Abs1::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->Abs();

		}
	}
}



void ConvertG::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + h; i++) {
		for (int j = x0; j < x0 + w; j++) {
			data[j + i * widthg]->setB(0);
			data[j + i * widthg]->setG(150);
			data[j + i * widthg]->setA(100);
			data[j + i * widthg]->setR(0);
		}
	}
}



void Mediana::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	std::vector<Pixel*> copy = pixelDataCopy(data);
	std::vector<int> r, g, b, a;

	for (int i = y0; i < h; i++) {
		for (int j = x0; j < w; j++) {
			if (i - 1 > 0) {
				r.push_back(copy[j + (i - 1) * widthg]->getR());
				g.push_back(copy[j + (i - 1) * widthg]->getG());
				b.push_back(copy[j + (i - 1) * widthg]->getB());
				a.push_back(copy[j + (i - 1) * widthg]->getA());
			}
			if (i + 1 < h) {
				r.push_back(copy[j + (i + 1) * widthg]->getR());
				g.push_back(copy[j + (i + 1) * widthg]->getG());
				b.push_back(copy[j + (i + 1) * widthg]->getB());
				a.push_back(copy[j + (i + 1) * widthg]->getA());
			}
			if (j - 1 > 0) {
				r.push_back(copy[j - 1 + i * widthg]->getR());
				g.push_back(copy[j - 1 + i * widthg]->getG());
				b.push_back(copy[j - 1 + i * widthg]->getB());
				a.push_back(copy[j - 1 + i * widthg]->getA());
			}
			if (j + 1 < w) {
				r.push_back(copy[j + 1 + i * widthg]->getR());
				g.push_back(copy[j + 1 + i * widthg]->getG());
				b.push_back(copy[j + 1 + i * widthg]->getB());
				a.push_back(copy[j + 1 + i * widthg]->getA());
			}
			r.push_back(copy[j + i * widthg]->getR());
			g.push_back(copy[j + i * widthg]->getG());
			b.push_back(copy[j + i * widthg]->getB());
			a.push_back(copy[j + i * widthg]->getA());


			std::sort(r.begin(), r.end());
			std::sort(g.begin(), g.end());
			std::sort(b.begin(), b.end());
			std::sort(a.begin(), a.end());

			data[j + i * widthg]->setA(a[a.size() / 2]);
			data[j + i * widthg]->setB(b[b.size() / 2]);
			data[j + i * widthg]->setG(g[g.size() / 2]);
			data[j + i * widthg]->setR(r[r.size() / 2]);
			r.clear();
			g.clear();
			b.clear();
			a.clear();

		}
	
	}


}

std::vector<Pixel*> Mediana::pixelDataCopy(std::vector<Pixel*> data)
{
	std::vector<Pixel*> copy;
	for (Pixel* it : data) {
		int R = it->getR();
		int G = it->getG();
		int B = it->getB();
		int A = it->getA();
		copy.push_back(new Pixel(B, G, R, A));
	}
	return copy;
}



void PaintSelection::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
	for (int i = y0; i < y0 + w; i++) {
		for (int j = x0; j < x0 + h; j++) {
			data[j + i * widthg]->setB(this->b);
			data[j + i * widthg]->setG(this->g);
			data[j + i * widthg]->setR(this->r);
		}
	}
}
