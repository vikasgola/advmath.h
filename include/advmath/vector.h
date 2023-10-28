#pragma once
#include<fstream>

#define RAD2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.0174533f)

template<unsigned int T>
class vec{
    public:
        float array[T] = {0.0f};

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
            this->array[0] = x;
            this->array[1] = y;
        }
        vec2(const vec<2>& v){
            for(int i=0;i<2;i++){
                this->array[i] = v.array[i];
            }
        }
        vec2(){}

        float x() const { return this->array[0];}
        float y() const { return this->array[1];}
};


class vec3: public vec<3>{
    public:
        vec3(float x, float y, float z){
            this->array[0] = x;
            this->array[1] = y;
            this->array[2] = z;
        }
        vec3(const vec<3>& v){
            for(int i=0;i<3;i++){
                this->array[i] = v.array[i];
            }
        }

        vec3 cross(vec3 &other){
            vec3 res(
                this->y()*other.z() - this->z()*other.y(),
                this->z()*other.x() - this->x()*other.z(),
                this->x()*other.y() - this->y()*other.x()
            );
            return res;
        }
        vec3(){}

        float x() const { return this->array[0];}
        float y() const { return this->array[1];}
        float z() const { return this->array[2];}
};

class vec4: public vec<4>{
    public:
        vec4(float x, float y, float z, float w){
            this->array[0] = x;
            this->array[1] = y;
            this->array[2] = z;
            this->array[3] = w;
        }
        vec4(const vec<4>& v){
            for(int i=0;i<4;i++){
                this->array[i] = v.array[i];
            }
        }
        vec4(){}

        float x() const { return this->array[0];}
        float y() const { return this->array[1];}
        float z() const { return this->array[2];}
        float w() const { return this->array[3];}
};
