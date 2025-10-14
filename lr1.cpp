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
    std::vector<RGB> pixels;

    Image1(const string& filepath)
    {
        ifstream stream(filepath, ios::binary);
        if (!stream) {
            cout << "Cant open file" << endl;
            return;
        }
        stream.ignore(100, '\n');
        stream >> width >> height;
        stream.ignore(100, '\n');
        stream.ignore(100, '\n');

        pixels.resize(width * height);
        stream.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * sizeof(RGB));
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
        stream << "P6\n" << width << " " << height << "\n255\n";
        stream.write(reinterpret_cast<const char*>(pixels.data()), pixels.size() * sizeof(RGB));
        return true;
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