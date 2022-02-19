
#include <iostream>
#include <string>
#include <fstream>
#include "examples/example1.h"
void writeToPPM(const std::unique_ptr<Film> &film, const std::string &filename)
{
    std::ofstream file(filename);
    file << "P3\n"
         << film->width << " " << film->height << "\n255\n";
    for (int j = 0; j < film->height; j++)
    {
        for (int i = 0; i < film->width; i++)
        {
            auto color = film->get(i, j);

            // Gamma correction
            auto r = sqrt(color.x);
            auto g = sqrt(color.y);
            auto b = sqrt(color.z);

            file << (int)(255.99 * r) << " " << (int)(255.99 * g) << " " << (int)(255.99 * b) << "\n";
        }
    }
}

int main()
{
    const int width = 300;
    const int height = 200;
    Example1 renderer(width, height, 10);
    renderer.render();
    writeToPPM(renderer.film(), "output.ppm");
    return 0;
}