#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <memory>

#include "camera.h"
#include "object.h"

using namespace PathTrace;

namespace FileSystemUtil
{
    inline static void load(const std::string& url, std::ifstream& stream)
    {
        if (url != "")
        {
            stream.open(url.c_str());
            if (!stream.is_open())
            {
                std::cout << "ERROR: file not loaded: " << url.c_str() << std::endl;
                exit(-1);
            }
        }
    }

    static void readSDLFile(const std::string& path, Scene& s)
    {
        std::ifstream stream;
        std::string line;

        load(path, stream);

        while(!stream.eof()) {
            getline(stream, line);

            if(line[0] != '#') {
                if (line.find("objectquadric") != std::string::npos) {
                    float a, b, c, d, e, f, g, h, j, k, red, green, blue, ka, kd, ks, kt;
                    int n;

                    sscanf(line.c_str(), 
                           "%*s %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d",
                           &a, &b, &c, &d, &e, &f, &g, &h, &j, &k, &red, &green, &blue, &ka, &kd, &ks, &kt, &n);

                    s.add(std::unique_ptr<Object>(new Quadric(a,b,c,d,e,f,g,h,j,k, vec3(red,green,blue), ka, kd, ks, kt, n)));
                } 
                else if (line.find("background") != std::string::npos) {

                }
                else if (line.find("eye") != std::string::npos) {
                    float x, y, z;
                    sscanf(line.c_str(), "%*s %f %f %f", &x, &y, &z);

                    Camera cam(vec3(x, y , z));
                    s.setCamera(cam);
                } 
            }
        }

        stream.close();
    }
}