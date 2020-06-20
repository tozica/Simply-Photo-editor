#include "Image.h"
#include "Layer.h"
#include "MyFormat.h"
#include"Composite.h"

Layer* Image::mergeLayers = nullptr;



void Image::addLayer(Layer* l)
{
    layers.push_back(l);
    findMaxLayer();
}

void Image::addSelection(Seletcion *s) {
    if (!selection) 
        selection = s;
    else
    {
        delete selection;
        selection = s;
    }
}

void Image::addRectangleInSelection(Rectangle r)
{
    if (r.getPos().first + r.getLenght() > Layer::getWS() || r.getPos().second + r.getWidth() > Layer::getHS())
        throw SelectionError("The selection dimensions come out of the image dimensions ");
    selection->add(r);
}

Layer* Image::setToFirstALayer()
{
    
    if (layers.capacity()) {
        for (Layer* it : layers) {
            if (it->getActive())
                return it;

        }
    }
        
}

void Image::combinateImage()
{
   
    mergeLayers = new Layer();
    std::vector<Pixel*>tmp;
   
   
    for (Layer* it : layers) {
        double p = 0;
        if (!it->active) continue;
        if (!tmp.size()) {
            mergeLayers->opacity = it->opacity;
            for (int j = 0; j < it->pixelData.size(); j++)
                tmp.push_back(new Pixel(it->pixelData[j]->getB(), it->pixelData[j]->getG(), it->pixelData[j]->getR(), it->pixelData[j]->getA()));
        }
        else {
            
            for (int i = 0; i < it->pixelData.size(); i++) {
                p = mergeLayers->opacity;
                
                double R = tmp[i]->getR();
                double G = tmp[i]->getG();
                double B = tmp[i]->getB();
                double A = p;

                double R1 = it->pixelData[i]->getR();
                double G1 = it->pixelData[i]->getG();
                double B1 = it->pixelData[i]->getB();
                double A1 = it->opacity;
                double a = tmp[i]->getA();
                double a1 = it->pixelData[i]->getA();

               // double alpha = (A + (1 - A) * A1);
                double alpha = p;

               /* tmp[i]->setB(B * A / alpha + B1 * (1 - A) * A1 / alpha);
                tmp[i]->setG(G * A / alpha + G1 * (1 - A) * A1 / alpha);
                tmp[i]->setR(R * A / alpha + R1 * (1 - A) * A1 / alpha);*/
               // tmp[i]->setA(a*A/alpha + a1*(1 - A)*A1/alpha);
                tmp[i]->setB(p * B + (1 - p) * B1);
                tmp[i]->setG(p * G + (1 - p) * G1);
                tmp[i]->setR(p * R + (1 - p) * R1);
                tmp[i]->setA(p * a + (1 - p) * a1);
               

            }
        }
        mergeLayers->opacity = p + it->opacity - p * it->opacity;
    }
    
    mergeLayers->pixelData = tmp;
    
}

void Image::writeImage(std::string s)
{
    this->combinateImage();
    std::regex rx("[^.]*.bmp");
    std::regex rx1("[^.]*.pam");
    std::regex rx2("[^.]*.toza");
    std::smatch result;

    if (std::regex_match(s, result, rx)) {
        Formater* tmp = new BMP(mergeLayers->getWS(), mergeLayers->getHS());
        tmp->write(s.c_str(), mergeLayers);
        delete tmp;
    }
    else
        if (std::regex_match(s, result, rx1)) {
            Formater* tmp = new PAM(mergeLayers->getW(), mergeLayers->getH());
            tmp->write(s.c_str(), mergeLayers);
            delete tmp;
        }
        else
            if (std::regex_match(s, result, rx2)) {
                Formater* tmp = new MyFormat(this);
                tmp->write(s.c_str(), mergeLayers);
                delete tmp;
            }
            else
                throw FileError("Unsupported file type");



 
    delete mergeLayers;
}


void Image::extendAllLayers(int w, int h)
{
    for (Layer* it : layers)
        it->extendLayer(w, h, it->getW(), it->getH());
}

void Image::findMaxLayer()
{
    int w = 0;
    int h = 0;

    for (Layer* it : layers) {
        if (it->getH() > h) h = it->getH();
        if (it->getW() > w) w = it->getW();
    }

    extendAllLayers(w, h);
}

void Image::LoadFromTFile(std::string s)
{
    Formater* f = new MyFormat(this);
    f->read(s.c_str(), mergeLayers);
}

void Image::writeComposite(std::string s)
{
    if (dynamic_cast<Composite*>(operation)) {
        Composite* c = dynamic_cast<Composite*>(operation);
        c->writeComposite(s);
    }
}

Image::~Image()
{
    delete selection;
    delete operation;
}
