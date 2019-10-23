#include "ModelLoader.h"
#include <stdlib.h>
#include <stdio.h>


// std::vector<std::string> split(char str[], char delim) {
//     std::vector<std::string> result;
//     std::string buff = "";
//     for (int i = 0; i < strlen(str); i++) {
//         if (str[i] != delim) {
//             buff += str[i];
//         } else if (buff.length() > 0) {
//             result.push_back(buff);
//             buff = "";
//         }
//     }
//     return result;
// }

std::vector<std::string> split(std::string str, char delim) {
    std::vector<std::string> result;
    std::string buff = "";
    for (int i = 0; i <= str.length(); i++) {
        if (str[i] != delim) {
            buff += str[i];
        } else if (buff.length() > 0) {
            result.push_back(buff);
            buff = "";
        }
    }
    result.push_back(buff);
    return result;
}

/*

    Quick info
    Layout of an obj file : 
    
    o ObjectName
    v x y z
    ...
    vt u v
    ...
    vn x y z
    ...
    f i/j/k i2/j2/k2 i3/j3/k3
      ( ^ )
    in/jn/kn are the indices of the vertex vector, uv vector and the normal vector for the nth vertex of the face.
    A trianglular face has three vertices so, i1/j1/k1 will correspond to the vertex vector, uv vector and the normal
    respectively, of that vertex. To get the actual vectors just look up the ith, jth and kth vectors described above.
     
*/

bool LoadModel(std::string file_path, GLfloat* destination, bool isObj) {

    std::ifstream file(file_path);
    std::vector<float*> verts;
    std::vector<float*> normals;
    std::vector<float*> uvs;
    std::vector<unsigned int> vertexIndices, normalIndices, uvIndices;

    if (file) {
        char line_c[180];
        while (file) {
            file.getline(line_c, 180);
            std::string line = static_cast<std::string>(line_c);
            std::vector<std::string> tokens = split(line, ' ');
            if (tokens[0] == "v") {
                // The line describes a vertex
                float temp_vert[3] = {std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])};
                verts.push_back(temp_vert);
            } else if (tokens[0] == "vt") {
                // The line describes a uv coordinate
                float temp_uv[2] = {std::stof(tokens[1]), std::stof(tokens[2])};
                uvs.push_back(temp_uv);
            } else if (tokens[0] == "vn") {
                float temp_normal[3] = {std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3])};
                normals.push_back(temp_normal);
            } else if (tokens[0] == "f") {
                // The line describes a face
                for (int i = 1; i <= 3; i++) {
                    std::vector<std::string> indices = split(tokens[i], '/');
                    vertexIndices.push_back(std::stoi(indices.at(0)));
                    uvIndices.push_back(std::stoi(indices.at(1)));
                    normalIndices.push_back(std::stoi(indices.at(2)));
                }
            } else continue;
        }
        for (float* v : verts) {
            std::cout << "x:" << v[0] << "y:" << v[1] << "z:" << v[2] << std::endl;
            delete[] v;
        }
        for (float* v : normals) {
            std::cout << "x:" << v[0] << "y:" << v[1] << "z:" << v[2] << std::endl;
            delete[] v;
        }
        for (float* v : uvs) {
            std::cout << "x:" << v[0] << "y:" << v[1] << std::endl;
            delete[] v;
        }
        return true;
    } else return false;
}