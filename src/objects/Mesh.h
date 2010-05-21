#ifndef MESH_H
#define MESH_H

#include "Object.h"
#include <vector>
#include <string>

using std::vector;
using std::string;


class Mesh: public Object{
public:
    Mesh();

    void addVertex(float x, float y, float z);
    void addFace(int index1, int index2, int index3, int normal_index);
    void addNormal(float x, float y, float z);

    //Implementação da interface de Object
    virtual bool intersect(const Ray& r);
    virtual Vec3 samplePoint();
    virtual void getNormal(Vec3 point, Vec3 &normal);

private:
    struct Vector{
        float data[3];
    };

    struct Face{
        Vector* vertices[3];
        int normal;
    };

    vector<Vector*> vertices;
    vector<Vector*> normals;
    vector<Face*> faces;
};

#endif

