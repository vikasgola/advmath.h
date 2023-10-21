#pragma once
#include<fstream>

#define RAD2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.0174533f)

template<unsigned int T>
class vec{
    public:
        union {
            struct {
                float x;
                float y;
                float z;
                float w;
            };
            struct {
                float r;
                float g;
                float b;
                float a;
            };
            float array[T] = {0.0f};
        };

        vec(){}
        vec(float value);

        float& operator[] (int i);
        vec<T> operator+(const vec<T>& other);
        vec<T> operator-(const vec<T>& other);
        vec<T> operator*(const vec<T>& other);
        vec<T> operator*(const float value);
        vec<T> operator/(const float value);
        bool operator==(const vec<T>& other);
        bool operator!=(const vec<T>& other);

        float dot(const vec<T>& other);
        float mag();
        float angle(vec<T> &other);
        vec<T> proj(vec<T> &other);
        vec<T> perp(vec<T> &other);
        vec<T> refl(vec<T> &other);
        void normalize();
        vec<T> normalized();
};

template <unsigned int T>
inline std::ostream &operator<<(std::ostream &out, vec<T> const &v){
    out<<"{";
    for(int i=0;i<T;i++){
        out<<v.array[i];
        if(i+1 != T) out<<", ";
    }
    out<<"}";
    return out;
}

class vec2: public vec<2>{
    public:
        vec2(float x, float y){
            this->x = x;
            this->y = y;
        }
        vec2(const vec<2>& v){
            this->x = v.x;
            this->y = v.y;
        }
        vec2(){}
};


class vec3: public vec<3>{
    public:
        vec3(float x, float y, float z){
            this->x = x;
            this->y = y;
            this->z = z;
        }
        vec3(const vec<3>& v){
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }

        vec3 cross(vec3 &other){
            vec3 res(
                this->y*other.z - this->z*other.y,
                this->z*other.x - this->x*other.z,
                this->x*other.y - this->y*other.x
            );
            return res;
        }

        vec3(){}
};

class vec4: public vec<4>{
    public:
        vec4(float x, float y, float z, float w){
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
        vec4(const vec<4>& v){
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
            this->w = v.w;
        }
        vec4(){}
};
