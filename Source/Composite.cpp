#include "Composite.h"
#include "Layer.h"

bool Composite::isComposite = false;

void Composite::readAndParese()
{
    std::regex rx("[^.]*.fun");
    std::smatch result;

    if (!std::regex_match(path, result, rx))
        throw FileError("The file type is not .fun, please try again with another file!");
    else {
        std::ifstream file(path.c_str());
        if (file) {

            std::string s;
            std::regex rx("<Comoposite_fun>");
            std::smatch result;
            std::getline(file, s);

            if (std::regex_match(s, result, rx)) {
                std::string s;
                std::regex rx1("\t\t<name>([^<]*)</name>");
                std::regex rx2("\t\t<arg>([^<]*)</arg>");
                std::regex rx3("</Comoposite_fun>");
                std::smatch result;
                std::smatch result1;

                while (std::getline(file, s)) {
                    if (std::regex_match(s, result, rx1)) {
                        std::string pom = result.str(1);
                        std::getline(file, s);
                        if (std::regex_match(s, result1, rx2)) {
                            std::string pom1 = result1.str(1);
                            if (pom1 == "")
                                decide(pom);
                            else
                                decide(pom, pom1);
                        }
                    }
                    else {
                        if (std::regex_match(s, result, rx3))
                            break;
                    }
                }
            }
            else
                throw FileError("Not recnocize my type of xml");
        }
        else
            throw FileError("Unable to open file in class Composite");
        file.close();
    }
    
}

void Composite::decide(std::string fun, std::string c)
{
    int x = map[fun];

    switch (x) {
    case 1:
        operations.push_back(new Addition(myImage, stoi(c)));
        break;
    case 2:
        operations.push_back(new Substract(myImage, stoi(c)));
        break;
    case 3:
        operations.push_back(new InverseSub(myImage, stoi(c)));
        break;
    case 4:
        operations.push_back(new Multiply(myImage, stoi(c)));
        break;
    case 5:
        operations.push_back(new Division(myImage, stoi(c)));
        break;
    case 6:
        operations.push_back(new InverseDiv(myImage, stoi(c)));
        break;
    case 7:
        operations.push_back(new Power(myImage, stoi(c)));
        break;
    case 8:
        operations.push_back(new Min(myImage, stoi(c)));
        break;
    case 9:
        operations.push_back(new Max(myImage, stoi(c)));
        break;
    case 10:
        operations.push_back(new Log1(myImage));
        break;
    case 11:
        operations.push_back(new Inverse(myImage));
        break;
    case 12:
        operations.push_back(new Abs1(myImage));
        break;
    case 13:
        operations.push_back(new ConverteGrey(myImage));
        break;
    case 14:
        operations.push_back(new ConverteBW(myImage));
        break;
    case 15:
        operations.push_back(new Composite(myImage, c));
        break;
    case 16:
        operations.push_back(new Mediana(myImage));
    }
    
    
 
}

void Composite::inicMap()
{
    map.insert(std::pair<std::string, int>("Add", 1));
    map.insert(std::pair<std::string, int>("Sub", 2));
    map.insert(std::pair<std::string, int>("InvSub", 3));
    map.insert(std::pair<std::string, int>("Mul", 4));
    map.insert(std::pair<std::string, int>("Div", 5));
    map.insert(std::pair<std::string, int>("InvDiv", 6));
    map.insert(std::pair<std::string, int>("Pow", 7));
    map.insert(std::pair<std::string, int>("Min", 8));
    map.insert(std::pair<std::string, int>("Max", 9));
    map.insert(std::pair<std::string, int>("Log", 10));
    map.insert(std::pair<std::string, int>("Inv", 11));
    map.insert(std::pair<std::string, int>("Abs", 12));
    map.insert(std::pair<std::string, int>("ConvGrey", 13));
    map.insert(std::pair<std::string, int>("ConvBW", 14));
    map.insert(std::pair<std::string, int>("Composite", 15));
    map.insert(std::pair<std::string, int>("Med", 16));

}

void Composite::operate()
{
    isComposite = true;
    
    for (Operation* i : operations) 
        i->operate();

    std::vector<Layer*>tmp = myImage->getLayers();
    std::for_each(tmp.begin(), tmp.end(), [&](Layer* l) {
        if (l->getActive()) {
            if (myImage->getSelecetion()) {
                std::vector<Rectangle> rec = myImage->getSelecetion()->getRectangles();
                std::for_each(rec.begin(), rec.end(), [&](Rectangle r) {
                    int x = r.getPos().first;
                    int y = r.getPos().second;
                    addConst(r.getWidth(), r.getLenght(), x, y, l->getData(), l->getW());
                });
            }
            else {
                addConst(l->getW(), l->getH(), 0, 0, l->getData(), l->getW());
            }

        }
    });
    
  

    isComposite = false;
}

void Composite::addConst(int w, int h, int x0, int y0, std::vector<Pixel*> data, int widthg)
{
    for (int i = y0; i < y0 + h; i++) {
        for (int j = x0; j < x0 + w; j++) {
            data[j + i * widthg]->max(0);
            data[j + i * widthg]->min(255);
        }
    }
}

void Composite::writeComposite(std::string path)
{
    std::ofstream file(path.c_str());
    if (file) {
        file << "<Comoposite_fun>" << std::endl;
        
        std::for_each(operations.begin(), operations.end(), [&](Operation *o) {
            file << "\t<operation>" << std::endl;
            file << "\t\t<name>" << o->getOperation() << "</name>" << std::endl;
            file << "\t\t<arg>" << o->getConst() << "</arg>" << std::endl;
            file << "\t</operation>" << std::endl;
        });

        file << "</Comoposite_fun>" << std::endl;
    }
    else
        throw FileError("Unable to open file in method writeComposite in class Composite");
    file.close();
}
