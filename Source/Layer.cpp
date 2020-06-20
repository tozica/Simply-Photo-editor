#include"Layer.h"

int Layer::hightS = 0;
int Layer::widthS = 0;



Layer::Layer(int w, int h){
    
    
    hight = h;
    width = w;
    if (!hightS && !widthS) {
        hightS = h;
        widthS = w;
    }

    pixelData.resize(w * h);
    for (int i = 0; i < w * h; i++)
        pixelData[i] = new Pixel(0, 0, 0, 255);
    
}

Layer::Layer(){
    if(!hightS && !widthS) 
        throw LayerError("The first layer was not made, you have to set dimensions  ");
    else{
        hight = hightS;
        width = widthS;
    }
}

void Layer::extendLayer(int w, int h, int oldW, int oldH)
{
    std::vector<Pixel*> tmp;
    tmp.resize(h * w);
    for (int i = oldH; i < h; i++)
        for (int j = 0; j < w; j++)
            tmp[j + i * w] = new Pixel(0, 0, 0, 0);

    for (int i = 0; i < oldH; i++) {
        for (int j = 0; j < oldW; j++) {
            tmp[j + i * w] = pixelData[j + i * oldW];
        }
        for (int j = oldW; j < w; j++)
            tmp[j + i * w] = new Pixel(0, 0, 0, 0);
    }

    pixelData.clear();
    pixelData = tmp;
    width = w;
    hight = h;
    widthS = w;
    hightS = h;
    
}



Layer::Layer(std::string s) {
    std::regex rx("[^.]*.bmp");
    std::regex rx1("[^.]*.pam");
    std::smatch result;

    if (std::regex_match(s, result, rx)) {
       Formater* myFormater = new BMP();
        myFormater->read(s.c_str(), this);
    }
    else {
        if (std::regex_match(s, result, rx1)) {
            Formater* myFormater = new PAM();
            myFormater->read(s.c_str(), this);
        }
        else
            throw FileError("Not supported type of file (supported files : PAM, BMP, toza)");
    }
    widthS = widthS ? widthS : width;
    hightS = hightS ? hightS : hight;

   
     
}