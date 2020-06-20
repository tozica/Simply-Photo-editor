#pragma once
#include "image.h"


class Menu
{
public:
	Menu(Image *i):image(i){}
	void mainManu();
	void Layer1();
	void addLayer(int x);
	void setVisibility();
	void setActivity();
	void setOpacity();
	void Seletcion1();
	void addSelection();
	void setSelectionActivity();
	void addRectangle();
	void Export();
	void Operation1();
	void CompositeO();
	void BasicO();
	void Add();
	void Sub();
	void InvSub();
	void Mul();
	void Div();
	void InvDiv();
	void Pow1();
	void Min1();
	void Max1();
	void Logg();
	void Inv();
	void Abss();
	void ConvToGrey();
	void ConvToBW();
	void Med();
	void LoadFromToza();
	void paintS();
	bool getE()const { return e; }
	void exportComposite();
	void deleteSelection();
	void deleteLayer();
	void exit1();

private:
	Image* image;
	bool e = false, export1 = false;
};

