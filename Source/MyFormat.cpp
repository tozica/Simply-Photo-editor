#include "MyFormat.h"
#include"Bmp.h"
#include "Layer.h"
#include"Composite.h"

void MyFormat::write(const char* file, Layer* l)
{
	std::ofstream of(file);
	if (of) {
		of << "<image>" << std::endl;

		writeLayers(of);
		writeSelection(of);
		writeComposite(of);

		of << "</image>" << std::endl;
		of.close();
	}
	else
		throw FileError("Unable to open file in mtehod write in class MyFormat");
	of.close();
}

void MyFormat::read(const char* file, Layer* l)
{
	std::regex rx("<image>");
	std::regex rx1("</image>");
	std::regex rx2("\t\t<layer>");
	std::regex rx3("\t\t\t<path>([^<]*)</path>");
	std::regex rx4("\t<selection>");
	std::regex rx5("\t\t<name>([^<]*)</name>");
	std::regex rx6("\t\t<active>([^<]*)</active>");
	std::regex rx7("\t\t<rectangle>");
	std::regex rx8("\t\t\t<dimensions>([0-9]*),([0-9]*),([0-9]*),([0-9]*)</dimensions>");
	std::regex rx9("\t<operation>");
	std::regex rx10("\t\t<composite>([^<]*)</composite>");
	std::regex rx11("\t</selection>");
	std::regex rx12("\t\t</rectangle>");
	std::regex rx13("\t\t\t<opacity>([^<]*)</opacity>");
	std::regex rx14("\t\t\t<visible>([^<]*)</visible>");
	std::regex rx15("\t\t\t<active>([^<]*)</active>");
	

	std::smatch result;
	std::string s;


	std::ifstream ifs(file);
	if (ifs) {
		std::getline(ifs, s);
		if (!std::regex_match(s, result, rx)) 
			throw FileError("The file type is not .toza");
		while (1) {
			std::getline(ifs, s);
			if (std::regex_match(s, result, rx2)) {
				std::getline(ifs, s);
				if (std::regex_match(s, result, rx3)) {
					Layer* l = new Layer(result.str(1));
					std::getline(ifs, s);
					std::regex_match(s, result, rx13);
					l->setOpacity(std::stod(result.str(1)));
					std::getline(ifs, s);
					std::regex_match(s, result, rx14);
					l->setVisible(std::stoi(result.str(1)));
					std::getline(ifs, s);
					std::regex_match(s, result, rx15);
					l->setActive(std::stoi(result.str(1)));
					image->addLayer(l);
				}
			}
			if (std::regex_match(s, result, rx4)) {
				std::getline(ifs, s);
				if (!std::regex_match(s, result, rx11)) {
					std::regex_match(s, result, rx5);
					Seletcion* s1 = new Seletcion(result.str(1));
					image->addSelection(s1);
					std::getline(ifs, s);
					std::regex_match(s, result, rx6);
					image->getSelecetion()->setActive(std::stoi(result.str(1)));
					while (1) {
						std::getline(ifs, s);
						if (std::regex_match(s, result, rx11))
							break;
						if (std::regex_match(s, result, rx8)) {
							Rectangle r(std::stoi(result.str(1)), std::stoi(result.str(2)), std::stoi(result.str(3)), std::stoi(result.str(4)));
							image->addRectangleInSelection(r);
						}
					}

				}
			}
			
			if (std::regex_match(s, result, rx9)) {
				std::getline(ifs, s);
				if (std::regex_match(s, result, rx10)) {
					Operation *o = new Composite(image, result.str(1));
					image->setOperation(o);

				}
			}
							
			if (std::regex_match(s, result, rx1))
				break;

		}

	}
	else
		throw FileError("Unable to open a file in class MyFormat in method read");
	ifs.close();
}

void MyFormat::writeLayers(std::ofstream &of)
{
	int i = 0;
	std::string path;
	std::vector<Layer*>tmp = image->getLayers();
	of << "\t<layers>" << std::endl;
	for (Layer* it : tmp) {
		path = "Layer" + std::to_string(i) + ".bmp";
		BMP* b = new BMP(it->getW(), it->getH());
		b->write(path.c_str(), it);
		of << "\t\t<layer>" << std::endl;
		of << "\t\t\t<path>" << path << "</path>" << std::endl;
		of << "\t\t\t<opacity>" << it->getOpacity() << "</opacity>" << std::endl;
		of << "\t\t\t<visible>" << it->getVisible() << "</visible>" << std::endl;
		of << "\t\t\t<active>" << it->getActive() << "</active>" << std::endl;
		of << "\t\t</layer>" << std::endl;

		i++;
	}
	of << "\t</layers>" << std::endl;
}

void MyFormat::writeSelection(std::ofstream& of)
{
	of << "\t<selection>" << std::endl;

	int i = 0;
	if (image->getSelecetion()) {
		of << "\t\t<name>" << image->getSelecetion()->getName() << "</name>" << std::endl;
		std::vector<Rectangle>tmp = image->getSelecetion()->getRectangles();
		of << "\t\t<active>" << image->getSelecetion()->getActive() << "</active>" << std::endl;
		if (tmp.size()) {
			for (Rectangle it : tmp) {
				of << "\t\t<rectangle>" << std::endl;
				of << "\t\t\t<dimensions>" << it.getPos().first << "," << it.getPos().second << "," << it.getWidth() << "," << it.getLenght() << "</dimensions>" << std::endl;
				of << "\t\t</rectangle>" << std::endl;
			}
		}
	}

	of << "\t</selection>" << std::endl;
}

void MyFormat::writeComposite(std::ofstream& of)
{
	of << "\t<operation>" << std::endl;

	if (dynamic_cast<Composite*>(image->getOperation()) != nullptr) {
		of << "\t\t<composite>" << image->getOperation()->getPath() << "</composite>" << std::endl;
	}

	of << "\t</operation>" << std::endl;
}
