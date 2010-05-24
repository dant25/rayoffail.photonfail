
#include "Mesh.h"

#include "../math/Vec3.h"


Mesh::Mesh()
//TODO: Object precisa de um construtor sem argumentos
:   Object(Material(SpectralQuantity(1.0, 1.0, 1.0), SpectralQuantity(1.0, 1.0, 1.0), SpectralQuantity(1.0, 1.0, 1.0), 1.0, 0.0))
{
}


Mesh::Mesh(const Material &m) : Object(m)
{
}

void Mesh::addVertex(float x, float y, float z){
    Vector* vertex = new Vector;
    vertex->data[0] = x;
    vertex->data[1] = y;
    vertex->data[2] = z;

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

bool Mesh::intersect(const Ray &r){
    //Transforma o raio pela inversa da transformada de mesh
   Ray ray = t.getInverse()*r;
	bool hit =false;
	float min_dist = 999999999999.0;
	Vec3 c_p1, c_p2, c_p3;

    unsigned int k;
    int faceIndex;
	for(k = 0; k<faces.size(); k++)
	{

	    Vec3 p1(faces[k]->vertices[0]->data[0], faces[k]->vertices[0]->data[1], faces[k]->vertices[0]->data[2]);
	    Vec3 p2(faces[k]->vertices[1]->data[0], faces[k]->vertices[1]->data[1], faces[k]->vertices[1]->data[2]);
	    Vec3 p3(faces[k]->vertices[2]->data[0], faces[k]->vertices[2]->data[1], faces[k]->vertices[2]->data[2]);

        bool cull_face = false;

        const float epsilon = 0.000001;

        Vec3 intersection_point;

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
                i.point = intersection_point;
                i.point.w = 1.0;
                i.point = this->t*i.point;
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
                i.point = intersection_point;
                i.point.w = 1.0;
                i.point = this->t*i.point;
                c_p1 = p1;
                c_p2 = p2;
                c_p3 = p3;
            }
        }
	}

    if(hit)
    {
       i.dist = min_dist;
       i.normal = Vec3(faces[faceIndex]->normal[0]->data[0], faces[faceIndex]->normal[0]->data[1], faces[faceIndex]->normal[0]->data[2]);
        //normal = Vec3(normals[faces[i]->normal]->data[0], normals[faces[i]->normal]->data[1], normals[faces[i]->normal]->data[2]);
        //i.normal = (c_p2 - c_p1).cross(c_p3 - c_p1);
        //intersection.normal = (c_p3 - c_p1).crossProduct(c_p2 - c_p1);
        //i.normal.normalize();
        i.point = i.point + i.normal*0.0000001;
        //intersection.toOrigin = ray.d*(-1.0);
        //intersection.reflected = intersection.normal * ( 2.0 * intersection.toOrigin.dotProduct ( intersection.normal ) ) - intersection.toOrigin;

        //std::cout << "interseção com mesh" << std::endl;
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
