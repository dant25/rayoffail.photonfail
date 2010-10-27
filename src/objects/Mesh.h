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
    Mesh(const Material &m);

    void addVertex(float x, float y, float z);
    void addFace(int index1, int index2, int index3, int nid1, int nid2, int nid3);
    void addFace(int index1, int index2, int index3, int nid1, int nid2, int nid3,
                 int tex1, int tex2, int tex3);
    void addNormal(float x, float y, float z);
    void addTexCoord(float s, float t);

    //Implementação da interface de Object
    virtual bool intersect(const Ray& r, Intersection &intersection);
    virtual Vec3 samplePoint();
    virtual void getNormal(Vec3 point, Vec3 &normal);

private:
    struct Vector{
        float data[3];
    };
    
    struct TexCoord {
      float data[2];
    };
    
    struct Face{
        Vector* vertices[3];
        Vector* normal[3];
        TexCoord* tex[3];
    };

    vector<Vector*> vertices;
    vector<Vector*> normals;
    vector<Face*> faces;
    vector<TexCoord*> texcoords;

    BBox bbox;

    bool intersectBoundingBox(const Ray &ray);
};

#endif

