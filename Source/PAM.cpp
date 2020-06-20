#include "PAM.h"
#include "Layer.h"



void PAM::write(const char* file, Layer* l)
{
    data.resize(l->width * l->hight * header.depth);
    
    int i = 0;

    for (int y = 0; y < l->hight; y++)
        for (int x = 0; x < l->width; x++) {
            unsigned int ind = header.depth * (y * l->width + x);
            data[ind] = l->pixelData[i]->getR();
            data[ind + 1] = l->pixelData[i]->getG();
            data[ind + 2] = l->pixelData[i]->getB();
            data[ind + 3] = l->pixelData[i]->getA();
            i++;
        }

    std::ofstream of(file, std::ios_base::binary);
    if (of) {
        of << header;
        of.write((const char*)data.data(), data.size());
    }
    of.close();
}

void PAM::read(const char* fName, Layer* l)
{
    std::ifstream inp(fName, std::ios_base::binary);
    if (inp) {

        std::string s, pom;
        for (int i = 0; i < 7; i++) {
            std::getline(inp, pom);
            s += pom;
            s += " ";
        }

        std::regex rx("([^ ]*) WIDTH ([^ ]*) HEIGHT ([^ ]*) DEPTH ([^ ]*) MAXVAL ([^ ]*) TUPLTYPE ([^ ]*) ENDHDR ");
        std::smatch result;

        if (std::regex_match(s, result, rx)) {
            header.type = result.str(1);
            header.tuplType = result.str(6);

            std::string w = result.str(2);
            header.width = stoi(w, nullptr, 0);

            w = result.str(3);
            header.height = stoi(w, nullptr, 0);

            w = result.str(4);
            header.depth = stoi(w, nullptr, 0);

            w = result.str(5);
            header.maxval = stoi(w, nullptr, 0);

        }

        data.resize(header.height * header.width * header.depth);

        inp.read((char*)data.data(), data.size());

        l->hight = header.height;
        l->width = header.width;


       // unsigned int c = headerInfo.bit_count / 8;
        
        

        for (int y = 0; y < header.height; y++)
            for (int x = 0; x < header.width; x++) {
                unsigned int ind = 4*(y * header.width + x);
                l->pixelData.push_back(new Pixel(data[ind + 2], data[ind + 1], data[ind], data[ind + 3]));
            }
        inp.close();
    }

    
}
