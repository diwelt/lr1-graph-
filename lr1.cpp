#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

struct RGB {
    unsigned char r, g, b;
};
struct Point {
    int x, y;
};
class Image1
{
public:
    int width, height;
    std::string magic_number;
    std::vector<RGB> pixels;

    Image1(const string& filepath)
    {
        ifstream stream(filepath, ios::binary);
        if (!stream) {
            cout << "Cant open file" << endl;
            return;
        }
        stream >> magic_number;
        stream.ignore(100, '\n');
        stream >> width >> height;
        stream.ignore(100, '\n');
        stream.ignore(100, '\n');

        pixels.resize(width * height);
        if(magic_number=="P6"){
            stream.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * sizeof(RGB));
        }else if (magic_number=="P3"){
            for (int i = 0; i < width * height; i++) {
                int r, g, b;
                stream >> r >> g >> b;
                pixels[i] = {static_cast<unsigned char>(r), 
                            static_cast<unsigned char>(g), 
                            static_cast<unsigned char>(b)};
            }
        }else{
            return;
        }
    }
    void Replace_Pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b)
    {
        pixels[y * width + x] = { r, g, b };
    }
    bool Save_image(const string& filepath)
    {
        ofstream stream(filepath, ios::binary);
        if (!stream) {
            cout << "Cant make file" << endl;
            return false;
        }
        if(magic_number == "P6"){
            stream << "P6\n" << width << " " << height << "\n255\n";
            stream.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(RGB));
            return true;
        }else if (magic_number=="P3"){
            stream << "P3\n" << width << " " << height << "\n255\n";
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    const RGB& pixel = pixels[i * width + j];
                    stream << static_cast<int>(pixel.r) << " "
                        << static_cast<int>(pixel.g) << " "
                        << static_cast<int>(pixel.b);
                    if (j < width - 1) stream << " ";
                    }
                stream << "\n";
            }
            return true;
        }else{
            return false;
        }
    }
};

int main(int argc, char *argv[])
{
    string input = "input.ppm";
    string output = "output.ppm";
    if(argc==2){
        input = argv[1];
    }else if(argc==3){
        input = argv[1];
        output = argv[2];
    }
    Image1 img(input);
    img.Replace_Pixel(0,0,255,127,127);
    img.Replace_Pixel(img.width/2,0,127,255,127);
    img.Replace_Pixel(0,img.height-1,127,127,255);
    img.Save_image(output);
}