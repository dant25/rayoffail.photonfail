#ifndef VEC3_H_
#define VEC3_H_

class Vec3 {
public:
	Vec3();
	Vec3(float _x, float _y, float _z, float _w);
   	Vec3(float _x, float _y, float _z);
	
    Vec3 operator+(const Vec3& v) const;
	Vec3& operator+=(const Vec3& v);

	Vec3 operator-(const Vec3& v) const;
	Vec3& operator-=(const Vec3& v);

	Vec3 operator*(float s) const;
	Vec3& operator*=(float s);

	Vec3 operator*(const Vec3& v) const{
		return Vec3(x*v.x, y*v.y, z*v.z);
	}

	Vec3 operator/(float s) const;
	Vec3& operator/=(float s);

	bool operator==(const Vec3& v) const;
	bool operator!=(const Vec3& v) const;

	inline float dot(const Vec3& v) const {
		return (x*v.x + y*v.y + z*v.z);
	}

	inline Vec3 cross(const Vec3& v) const{
		return Vec3(this->y*v.z - v.y*this->z,
					this->z*v.x - v.z*this->x,
					this->x*v.y - v.x*this->y);
	}

	void normalize(){
		float len = length();
		x = x/len;
		y = y/len;
		z = z/len;
	}

	float length() const;

	inline Vec3 getReflected(const Vec3 &normal) const {
       Vec3 vec = normal* this->dot(normal)*2.0 - *this;
       vec.normalize();
       return vec;
	}

	float x, y, z;
    float w;
};


float dot(const Vec3& v1, const Vec3& v2);
Vec3 cross(const Vec3& v1, const Vec3& v2);
Vec3 normalize(const Vec3& v);
float angle(const Vec3& v1, const Vec3& v2);


#endif
