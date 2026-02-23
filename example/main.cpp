#include "parser.h"
#include "scene.h"
#include "simple_bmp.hpp"
#include <iostream>
#include <string>
#include <random>
#include <chrono>


class Examples{
    using Parser = parser::Parser;
    using Scene  = scene::Scene;

    public:
    static void ExampleOne(const std::string &file_path=kFileOne){
        SimpleBMP(file_path, "files/output_1_1024.bmp"); 

        Parser prs(file_path);
        Scene sc;
        prs.Parse(sc);

        sc.SetResolution(50);   // smaller than minimum
        sc.RenderToBMP("files/output_1_100.bmp");

        sc.SetResolution(3000); // bigger than maximum
        sc.RenderToBMP("files/output_1_2048.bmp");
    }
    static void ExampleTwo(const std::string &file_path=kFileTwo){
        Parser prs(file_path);
        Scene sc;
        prs.Parse(sc);

        auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::mt19937 mt(seed);
        std::uniform_int_distribution<uint8_t> int_dist(0, 255);   
        for(size_t i = 0; i < sc.GetObjectsCount(); i++){
            sc(i)->SetColor(scene::Color3(int_dist(mt), int_dist(mt), int_dist(mt)));
        }

        sc.SetResolution(100);
        sc.RenderToBMP("files/output_2_100.bmp");
        sc.SetResolution(1000);
        sc.RenderToBMP("files/output_2_1000.bmp");
        sc.SetResolution(2000);
        sc.RenderToBMP("files/output_2_2000.bmp");
    }
    private:
    static constexpr std::string kFileOne = "files/1.txt";
    static constexpr std::string kFileTwo = "files/2.txt";
    static constexpr std::string kFileThree = "files/3.txt";

};

int main() { 
    Examples::ExampleOne();
    Examples::ExampleTwo();
    return 0;    
}