#include "Mesh.h"
#include "../math/Vec3.h"
#include "../math/Utilities.h"
#include <iostream>


Mesh::Mesh()
    //TODO: Object precisa de um construtor sem argumentos
:   Object(Material(SpectralQuantity(1.0, 1.0, 1.0), SpectralQuantity(1.0, 1.0, 1.0), SpectralQuantity(1.0, 1.0, 1.0), 1.0, 0.0))
{
}


Mesh::Mesh(const Material &m) : Object(m)
{
    bbox.maxx = -INFINITY;
    bbox.maxy = -INFINITY;
    bbox.maxz = -INFINITY;
    bbox.minx = INFINITY;
    bbox.miny = INFINITY;
    bbox.minz = INFINITY;
}

void Mesh::addVertex(float x, float y, float z){
    Vector* vertex = new Vector;
    vertex->data[0] = x;
    vertex->data[1] = y;
    vertex->data[2] = z;

    bbox.maxx = (x > bbox.maxx) ? x : bbox.maxx;
    bbox.maxy = (y > bbox.maxy) ? y : bbox.maxy;
    bbox.maxz = (z > bbox.maxz) ? z : bbox.maxz;
    bbox.minx = (x < bbox.minx) ? x : bbox.minx;
    bbox.miny = (y < bbox.miny) ? y : bbox.miny;
    bbox.minz = (z < bbox.minz) ? z : bbox.minz;

    vertices.push_back(vertex);
}

void Mesh::addFace(int index1, int index2, int index3, int nid1, int nid2, int nid3) {
    Face* face = new Face;
    face->vertices[0] = vertices[index1];
    face->vertices[1] = vertices[index2];
    face->vertices[2] = vertices[index3];

    //face->normal = normal;
    face->normal[0] = normals[nid1];
    face->normal[1] = normals[nid2];
    face->normal[2] = normals[nid3];

    face->tex[0] = face->tex[1] = face->tex[2] = NULL;

    faces.push_back(face);
}
void Mesh::addFace(int index1, int index2, int index3, int nid1, int nid2, int nid3,
        int tex1, int tex2, int tex3) {
    Face* face = new Face;
    face->vertices[0] = vertices[index1];
    face->vertices[1] = vertices[index2];
    face->vertices[2] = vertices[index3];

    //face->normal = normal;
    face->normal[0] = normals[nid1];
    face->normal[1] = normals[nid2];
    face->normal[2] = normals[nid3];

    face->tex[0] = texcoords[tex1];
    face->tex[1] = texcoords[tex2];
    face->tex[2] = texcoords[tex3];

    faces.push_back(face);
}


void Mesh::addNormal(float x, float y, float z)
{
    Vector* normal = new Vector;
    normal->data[0] = x;
    normal->data[1] = y;
    normal->data[2] = z;

    normals.push_back(normal);
}

void Mesh::addTexCoord(float s, float t)  {
    TexCoord* tex = new TexCoord;
    tex->data[0] = s;
    tex->data[1] = t;

    texcoords.push_back(tex);
}


bool Mesh::intersect(const Ray &r, Intersection &intersection){
    //Transforma o raio pela inversa da transformada de mesh
    Ray ray = t.getInverse()*r;

    if(!intersectBoundingBox(ray))
        return false;

    bool hit =false;
    float min_dist = INFINITY;
    Vec3 c_p1, c_p2, c_p3;

    unsigned int k;
    int faceIndex;
    for(k = 0; k<faces.size(); k++)
    {

        Vec3 p1(faces[k]->vertices[0]->data[0], faces[k]->vertices[0]->data[1], faces[k]->vertices[0]->data[2], 1.0);
        Vec3 p2(faces[k]->vertices[1]->data[0], faces[k]->vertices[1]->data[1], faces[k]->vertices[1]->data[2], 1.0);
        Vec3 p3(faces[k]->vertices[2]->data[0], faces[k]->vertices[2]->data[1], faces[k]->vertices[2]->data[2], 1.0);

        bool cull_face = false;

        const float epsilon = 0.000001;

        Vec3 intersection_point(0.0, 0.0, 0.0, 1.0);

        Vec3 edge1 = p2 - p1;
        Vec3 edge2 = p3 - p1;

        Vec3 pvec = ray.d.cross(edge2);

        float det = edge1.dot(pvec);

        if(cull_face)
        {
            if(det < epsilon)
                continue;

            Vec3 tvec = ray.o - p1;
            float u = tvec.dot(pvec);

            if(u < 0.0 || u > det)
                continue;

            Vec3 qvec = tvec.cross(edge1);

            float v = ray.d.dot(qvec);

            if(v < 0.0 || u + v > det)
                continue;

            float t = edge2.dot(qvec);

            float inv_det = 1.0 / det;

            t *= inv_det;
            u *= inv_det;
            v *= inv_det;

            intersection_point = p1*(1 - u - v) + p2*u + p3*v;
            hit = true;
            float d = (intersection_point - ray.o).length();
            if(d < min_dist){
                faceIndex = k;
                min_dist = d;
                intersection.point = intersection_point;
                intersection.point.w = 1.0;
                intersection.point = this->t*intersection.point;
                intersection.dist = min_dist;
                /*i.point = intersection_point;
                  i.point.w = 1.0;
                  i.point = this->t*i.point;*/
                c_p1 = p1;
                c_p2 = p2;
                c_p3 = p3;
            }
        }
        else
        {
            if(det > -epsilon && det < epsilon)
                continue;

            float inv_det = 1.0 / det;

            Vec3 tvec = ray.o - p1;

            float u = tvec.dot(pvec) * inv_det;

            if(u < 0.0 || u > 1.0)
                continue;

            Vec3 qvec = tvec.cross(edge1);

            float v = ray.d.dot(qvec) * inv_det;

            if(v < 0.0 || u + v > 1.0)
                continue;

            double t = edge2.dot(qvec) * inv_det;
            if(t < epsilon)
                continue;

            intersection_point = p1*(1.0 - u - v) + p2*u + p3*v;
            hit = true;
            float d = (intersection_point - ray.o).length();
            if(d < min_dist){
                faceIndex = k;
                min_dist = d;
                intersection.point = intersection_point;
                intersection.point.w = 1.0;
                intersection.point = this->t*intersection.point;
                /*i.point = intersection_point;
                  i.point.w = 1.0;
                  i.point = this->t*i.point;*/
                c_p1 = p1;
                c_p2 = p2;
                c_p3 = p3;
            }
        }
    }

    if(hit)
    {
        intersection.dist = (intersection.point - r.o).length();
        Vec3 v1, v2, v3;
        v1 = Vec3(faces[faceIndex]->vertices[0]->data[0], faces[faceIndex]->vertices[0]->data[1],
                faces[faceIndex]->vertices[0]->data[2]);
        v2 = Vec3(faces[faceIndex]->vertices[1]->data[0], faces[faceIndex]->vertices[1]->data[1],
                faces[faceIndex]->vertices[1]->data[2]);
        v3 = Vec3(faces[faceIndex]->vertices[2]->data[0], faces[faceIndex]->vertices[2]->data[1],
                faces[faceIndex]->vertices[2]->data[2]);
        //Modo do pbrt de achar coordenadas baricêntricas
        Vec3 e1 = v2 - v1;
        Vec3 e2 = v3 - v1;
        Vec3 s1 = cross(ray.d, e2);
        float divisor = dot(s1, e1);
        Vec3 d = ray.o - v1;
        float b1 = dot(d, s1)/divisor;
        Vec3 s2 = cross(d, e1);
        float b2 = dot(ray.d, s2)/divisor;
        float b3 = 1.0 - b1 - b2;
        //Modo mazela de achar coordenadas baricêntricas
        float l1, l2, l3;
        //barycentricCoords(v1, v2, v3, i.point, l1, l2, l3);
        Vec3 n1, n2, n3;
        n1 = Vec3(faces[faceIndex]->normal[0]->data[0], faces[faceIndex]->normal[0]->data[1],
                faces[faceIndex]->normal[0]->data[2]);
        n2 = Vec3(faces[faceIndex]->normal[1]->data[0], faces[faceIndex]->normal[1]->data[1],
                faces[faceIndex]->normal[1]->data[2]);
        n3 = Vec3(faces[faceIndex]->normal[2]->data[0], faces[faceIndex]->normal[2]->data[1],
                faces[faceIndex]->normal[2]->data[2]);
        intersection.normal = n1*b3+ n2*b1 + n3*b2;
        intersection.normal = normalize(intersection.normal);
        intersection.normal = t.transformNormal(intersection.normal);

        if(this->m.tex) {
            intersection.texCoord[0] = b3*faces[faceIndex]->tex[0]->data[0] + b1*faces[faceIndex]->tex[1]->data[0]
                + b2*faces[faceIndex]->tex[2]->data[0];
            intersection.texCoord[1] = b3*faces[faceIndex]->tex[0]->data[1] + b1*faces[faceIndex]->tex[1]->data[1]
                + b2*faces[faceIndex]->tex[2]->data[1];
        }
        intersection.point = intersection.point + intersection.normal*0.0001;
        return true;
    }

    return false;
}



Vec3 Mesh::samplePoint(){
    //TODO: Implementar
    return Vec3();
}


void Mesh::getNormal(Vec3 point, Vec3 &normal){
    //TODO: Implementar
}


bool Mesh::intersectBoundingBox(const Ray &ray)
{
    float tnear = -INFINITY , tfar = INFINITY;

    if(fabs(ray.d.x) < 0.000001){
        if (ray.o.x < bbox.minx || ray.o.x > bbox.maxx)
            return false;
    }
    else
    {
        float t1 = (bbox.minx - ray.o.x) / ray.d.x; //(time at which ray intersects minimum X plane)
        float t2 = (bbox.maxx - ray.o.x) / ray.d.x; //(time at which ray intersects maximum X plane)
        if (t1 > t2)
        {
            float aux = t1;
            t1 = t2;
            t2 = aux;
        }
        if(t1 > tnear)
            tnear = t1;
        if(t2 < tfar)
            tfar = t2;
        if(tnear > tfar)
            return false;
        if(tfar < 0.0)
            return false;
    }

    if(fabs(ray.d.y) < 0.000001){
        if (ray.o.y < bbox.miny || ray.o.y > bbox.maxy)
            return false;
    }
    else
    {
        float t1 = (bbox.miny - ray.o.y) / ray.d.y; //(time at which ray intersects minimum X plane)
        float t2 = (bbox.maxy - ray.o.y) / ray.d.y; //(time at which ray intersects maximum X plane)
        if (t1 > t2)
        {
            float aux = t1;
            t1 = t2;
            t2 = aux;
        }
        if(t1 > tnear)
            tnear = t1;
        if(t2 < tfar)
            tfar = t2;
        if(tnear > tfar)
            return false;
        if(tfar < 0.0)
            return false;
    }

    if(fabs(ray.d.z) < 0.000001){
        if (ray.o.z < bbox.minz || ray.o.z > bbox.maxz)
            return false;
    }
    else
    {
        float t1 = (bbox.minz - ray.o.z) / ray.d.z; //(time at which ray intersects minimum X plane)
        float t2 = (bbox.maxz - ray.o.z) / ray.d.z; //(time at which ray intersects maximum X plane)
        if (t1 > t2)
        {
            float aux = t1;
            t1 = t2;
            t2 = aux;
        }
        if(t1 > tnear)
            tnear = t1;
        if(t2 < tfar)
            tfar = t2;
        if(tnear > tfar)
            return false;
        if(tfar < 0.0)
            return false;
    }

    return true;
}
