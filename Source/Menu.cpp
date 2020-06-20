#include "Menu.h"
#include "Layer.h"
#include "Composite.h"

void Menu::mainManu()
{
	while (1) {
		int x;
		std::cout << "==============================" << std::endl;
		std::cout << "Select an option" << std::endl;
		std::cout << "1. Layer" << std::endl;
		std::cout << "2. Selecetion" << std::endl;
		std::cout << "3. Export" << std::endl;
		std::cout << "4. Operation" << std::endl;
		std::cout << "5. Load project from .toza" << std::endl;
		std::cout << "6. Exit" << std::endl;
		std::cout << "==============================" << std::endl;

		std::cin >> x;

		switch (x) {
		case 1:
			Layer1();
			export1 = false;
			break;
		case 2:
			Seletcion1();
			export1 = false;
			break;
		case 3:
			Export();
			export1 = true;
			break;
		case 4:
			Operation1();
			export1 = false;
			break;
		case 5:
			LoadFromToza();
			export1 = false;
			break;
		case 6:
			exit1();
			break;
		}
		
		
		if (e) break;
		

	}
}



void Menu::LoadFromToza() {
	std::cout << "Enter the path to the .toza file" << std::endl;
	std::string s;
	std::cin >> s;

	image->LoadFromTFile(s);
}

void Menu::Layer1()
{
	int x;
	std::cout << "===========================================" << std::endl;
	std::cout << "Select an option" << std::endl;
	std::cout << " 1. Create Layer with image" << std::endl;
	std::cout << " 2. Create layer without image" << std::endl;
	std::cout << " 3. Set the activity of the desired layer " << std::endl;
	std::cout << " 4. Set the visibility of the desired layer " << std::endl;
	std::cout << " 5. Set the opacity of the desired layer " << std::endl;
	std::cout << " 6. Delete desired layer " << std::endl;
	std::cout << "===========================================" << std::endl;

	std::cin >> x;

	switch (x) {
	case 1:
		addLayer(x);
		break;
	case 2:
		addLayer(x);
		break;
	case 3:
		setActivity();
		break;
	case 4:
		setVisibility();
		break;
	case 5:
		setOpacity();
		break;
	case 6:
		deleteLayer();
		break;
	}

}

void Menu::deleteLayer() {
	if (!image->getLayers().size())
		throw LayerError("There is not a single layer in the project");
	int x;
	std::cout << "Enter the position of desired layer" << std::endl;
	std::cin >> x;
	if (x > image->getLayers().size() - 1)
		throw LayerError("Desired layer does not exist");
	image->deleteLayer(x);
}

void Menu::exit1()
{
	if (!export1) {
		std::cout << "Are you sure you want to leave the program without saving the project ? [y/n]";
		char c;
		std::cin >> c;
		if (c == 'y') e = true;
	}
	else 
		e = true;
	

}

void Menu::addLayer(int x)
{
	if (x == 1) {
		std::string pom;
		std::cout << "Enter the path to the image" << std::endl;
		std::cin >> pom;
		Layer *l = new Layer(pom);
		image->addLayer(l);
	}
	else {
		int w, h;
		std::cout << "Enter width and height of layer";
		std::cin >> w;
		std::cin >> h;
		Layer* l = new Layer(w, h);
		image->addLayer(l);
	}
}

void Menu::setVisibility()
{
	if (!image->getLayers().size()) throw LayerError("There is not a single layer in the project");
	int x, y;
	std::cout << "Enter the position of the desired layer" << std::endl;
	std::cin >> x;
	if (x > image->getLayers().size() - 1)
		throw LayerError("Desired layer does not exist");
	std::cout << "" << "Enter visibility (0 or 1)" << std::endl;
	std::cin >> y;

	bool v = y ? true : false;

	std::vector<Layer*>tmp = image->getLayers();
	tmp[x]->setVisible(v);

}

void Menu::setActivity()
{
	if (!image->getLayers().size()) throw LayerError("There is not a single layer in the project");
	int x, y;
	std::cout << "Enter the position of the desired layer" << std::endl;
	std::cin >> x;
	if (x > image->getLayers().size() - 1)
		throw LayerError("Desired layer does not exist");
	std::cout << "" << "Enter activity (0 or 1)" << std::endl;
	std::cin >> y;

	bool v = y ? true : false;

	std::vector<Layer*>tmp = image->getLayers();
	tmp[x]->setActive(v);
}

void Menu::setOpacity()
{
	if (!image->getLayers().size()) 
		throw LayerError("There is not a single layer in the project");
	int x;
	double y;
	std::cout << "Enter the position of the desired layer" << std::endl;
	std::cin >> x;
	if (x > image->getLayers().size() - 1)
		throw LayerError("Desired layer does not exist");
	std::cout << "" << "Enter opacity (between 0 and 100 %)" << std::endl;
	std::cin >> y;


	std::vector<Layer*>tmp = image->getLayers();
	tmp[x]->setOpacity(y / 100.0);
}

void Menu::Seletcion1()
{
	int x;
	std::cout << "==========================================" << std::endl;
	std::cout << "Select an option" << std::endl;
	std::cout << " 1. Add a selection" << std::endl;
	std::cout << " 2. Set activity of the selected selection" << std::endl;
	std::cout << " 3. Add rectangle in selection" << std::endl;
	std::cout << " 4. Paint selection in specfic color" << std::endl;
	std::cout << " 5. Delete selection" << std::endl;
	std::cout << "==========================================" << std::endl;

	std::cin >> x;

	switch (x) {
	case 1:
		addSelection();
		break;
	case 2:
		setSelectionActivity();
		break;
	case 3:
		addRectangle();
		break;
	case 4:
		paintS();
		break;
	case 5:
		deleteSelection();
		break;
	}
	
}

void Menu::paintS() {
	if (!image->getLayers().size())
		throw LayerError("There is not a single layer in the project, before doing an operation, you have to add layer");
	if (!image->getSelecetion())
		throw SelectionError();
	int r, g, b;
	std::cout << "Enter the value of red green and blue components";
	std::cin >> r;
	std::cin >> g;
	std::cin >> b;

	Operation* o = new PaintSelection(image, r, g, b);
	image->setOperation(o);
}

void Menu::deleteSelection() {
	image->deleteSelection();
}

void Menu::exportComposite()
{
	std::string s;
	std::cout << "Enter the path to file" << std::endl;
	std::cin >> s;
	
	image->writeComposite(s);
}

void Menu::addSelection()
{	
	if (!image->getLayers().size())
		throw LayerError("There is not a single layer in the project, before doing an operation, you have to add layer");
	char c = 'y';
	if (image->getSelecetion()) {
		std::cout << "The selection already exists, are you sure you want to add a new one ? the old one will be deleted. (y / n); " << std::endl;
		std::cin >> c;
	}
	if (c == 'y') {
		std::string tmp;
		std::cout << "Enter a name of selection" << std::endl;
		std::cin >> tmp;

		Seletcion* s = new Seletcion(tmp);
		image->addSelection(s);
	}

	
}

void Menu::setSelectionActivity()
{
	if (!image->getSelecetion()) throw SelectionError();
	int y;
	Seletcion* tmp;
	std::cout << "" << "Enter activity (0 or 1)" << std::endl;
	std::cin >> y;

	bool v = y ? true : false;

	tmp = image->getSelecetion();
	tmp->setActive(v);
}

void Menu::addRectangle()
{
	if (!image->getSelecetion()) throw SelectionError();
	std::cout << "Enter the position of the upper left corner (x0, y0)";
	int x, y;

	std::cin >> x;
	std::cin >> y;

	std::cout << "Enter the width and height of the rectangle" << std::endl;
	int w, h;

	std::cin >> w;
	std::cin >> h;

	int wtmp = image->getLayers()[0]->getWS();
	int htmp = image->getLayers()[0]->getHS();

	if (w + x > wtmp || h + y > htmp) throw SelectionError("A rectangle with the given parameters is outside the range of the image surface");

	Rectangle r(x, y, w, h);
	image->addRectangleInSelection(r);
}

void Menu::Export()
{
	std::cout << "Enter the path to the file where you want to save the photo" << std::endl;
	std::string tmp;
	std::cin >> tmp;

	image->writeImage(tmp);
}

void Menu::Operation1()
{
	if (!image->getLayers().size())
		throw LayerError("There is not a single layer in the project, before doing an operation, you have to add layer");
	int x;
	std::cout << "==========================================" << std::endl;
	std::cout << "1. Basic operation" << std::endl;
	std::cout << "2. Composite operation" << std::endl;
	std::cout << "3. Export composite" << std::endl;
	std::cout << "==========================================" << std::endl;

	std::cin >> x;

	switch (x) {
	case 1:
		BasicO();
		break;
	case 2:
		CompositeO();
		break;
	case 3:
		exportComposite();
	}


}

void Menu::CompositeO()
{
	std::string tmp;
	std::cout << "Enter the path of Composite function" << std::endl;
	std::cin >> tmp;

	Operation* o = new Composite(image, tmp);
	image->setOperation(o);
}

void Menu::BasicO()
{
	int x;
	std::cout << "==========================================" << std::endl;
	std::cout << "Select an option" << std::endl;
	std::cout << " 1. Addition" << std::endl;
	std::cout << " 2. Substract" << std::endl;
	std::cout << " 3. InverseSub" << std::endl;
	std::cout << " 4. Multiply" << std::endl;
	std::cout << " 5. Division" << std::endl;
	std::cout << " 6. InverseDiv" << std::endl;
	std::cout << " 7. Power" << std::endl;
	std::cout << " 8. Min" << std::endl;
	std::cout << " 9. Max" << std::endl;
	std::cout << " 10. Log" << std::endl;
	std::cout << " 11. Inverse" << std::endl;
	std::cout << " 12. Abs" << std::endl;
	std::cout << " 13. Convert to Grey" << std::endl;
	std::cout << " 14. Convert to Black and White" << std::endl;
	std::cout << " 15. Mediana" << std::endl;
	std::cout << "==========================================" << std::endl;

	std::cin >> x;

	switch (x) {
	case 1:
		Add();
		break;
	case 2:
		Sub();
		break;
	case 3:
		InvSub();
		break;
	case 4:
		Mul();
		break;
	case 5:
		Div();
		break;
	case 6:
		InvDiv();
		break;
	case 7:
		Pow1();
		break;
	case 8:
		Min1();
		break;
	case 9:
		Max1();
		break;
	case 10:
		Logg();
		break;
	case 11:
		Inv();
		break;
	case 12:
		Abss();
		break;
	case 13:
		ConvToGrey();
		break;
	case 14:
		ConvToBW();
		break;
	case 15:
		Med();
		break;
	}
	

}

void Menu::Add()
{
	int x;
	std::cout << "Enter const" << std::endl;
	std::cin >> x;

	Operation* o = new Addition(image, x);
	image->setOperation(o);
}

void Menu::Sub()
{
	int x;
	std::cout << "Enter const" << std::endl;
	std::cin >> x;

	Operation* o = new Substract(image, x);
	image->setOperation(o);
}

void Menu::InvSub()
{
	int x;
	std::cout << "Enter const" << std::endl;
	std::cin >> x;

	Operation* o = new InverseSub(image, x);
	image->setOperation(o);
}

void Menu::Mul()
{
	int x;
	std::cout << "Enter const" << std::endl;
	std::cin >> x;

	Operation* o = new Multiply(image, x);
	image->setOperation(o);
}

void Menu::Div()
{
	int x;
	std::cout << "Enter const" << std::endl;
	std::cin >> x;

	Operation* o = new Division(image, x);
	image->setOperation(o);
}

void Menu::InvDiv()
{
	int x;
	std::cout << "Enter const" << std::endl;
	std::cin >> x;

	Operation* o = new InverseDiv(image, x);
	image->setOperation(o);
}

void Menu::Pow1()
{
	int x;
	std::cout << "Enter const" << std::endl;
	std::cin >> x;

	Operation* o = new Power(image, x);
	image->setOperation(o);
}

void Menu::Min1()
{
	int x;
	std::cout << "Enter const" << std::endl;
	std::cin >> x;

	Operation* o = new Min(image, x);
	image->setOperation(o);
}

void Menu::Max1()
{
	int x;
	std::cout << "Enter const" << std::endl;
	std::cin >> x;

	Operation* o = new Max(image, x);
	image->setOperation(o);
}

void Menu::Logg()
{

	Operation* o = new Log1(image);
	image->setOperation(o);
}

void Menu::Inv()
{

	Operation* o = new Inverse(image);
	image->setOperation(o);
}

void Menu::Abss()
{

	Operation* o = new Abs1(image);
	image->setOperation(o);
}

void Menu::ConvToGrey()
{

	Operation* o = new ConverteGrey(image);
	image->setOperation(o);
}

void Menu::ConvToBW()
{

	Operation* o = new ConverteBW(image);
	image->setOperation(o);
}

void Menu::Med()
{

	Operation* o = new Mediana(image);
	image->setOperation(o);
}
