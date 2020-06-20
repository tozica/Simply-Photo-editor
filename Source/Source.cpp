#include<iostream>
#include"Pixel.h"
#include"BMP.h"
#include"Layer.h"
#include"Image.h"
#include"Composite.h"
#include"Menu.h"

int main(int argc, char* argv[]) {
	Image* i = new Image();
	Menu* m = new Menu(i);
	if (argc == 3) {
		Layer* l = new Layer(argv[1]);
		i->addLayer(l);
		Operation* o = new Composite(i, argv[2]);
		i->setOperation(o);
		i->writeImage(argv[1]);
	}
	else {

		while (1) {
			try {
				m->mainManu();
			}
			catch (std::exception & e) {
				std::cout << e.what() << std::endl;
				std::cout << std::endl;
				std::cout << std::endl;
			}
			if (m->getE()) break;
		}
	}

}