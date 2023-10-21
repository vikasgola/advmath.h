#pragma once
#include<fstream>
#include<advmath/vector.h>

template<unsigned int T>
class mat{
    public:
        float array[T*T] = {0};

        mat();
        ~mat();

        mat(const float (&values)[T*T]);
        mat(float value);

        float* operator[] (int i);
        mat<T> tras();
        mat<T> operator*(const float value);
        mat<T> operator/(const float value);
        mat<T> operator+(const mat<T>& other);
        mat<T> operator-(const mat<T>& other);
        mat<T> operator*(const mat<T>& other);
        mat<T-1> cut(int row, int col);
        mat<T> inverse();
        mat<T> adjugate();
        float det();
        float cofactor(int row, int col);
        float adjugate(int row, int col);
        float minor(int row, int col);
};


template <unsigned int T>
inline std::ostream &operator<<(std::ostream &out, mat<T> m){
    out<<"{";
    for(int i=0;i<T;i++){
        out<<"{";
        for(int j=0;j<T;j++){
            out<<m[i][j];
            if(j+1 != T) out<<", ";
        }
        out<<"}";
        if(i+1 != T) out<<"\n";
    }
    out<<"}";
    return out;
}

typedef mat<2> mat2;
typedef mat<3> mat3;
typedef mat<4> mat4;

mat4 translation(float x, float y, float z);
mat4 translation(const vec3& loc);
mat4 scale(float x, float y, float z);
mat4 scale(const vec3& loc);

mat4 xrotation(float angle);
mat4 yrotation(float angle);
mat4 zrotation(float angle);

mat3 xrotation3x3(float angle);
mat3 yrotation3x3(float angle);
mat3 zrotation3x3(float angle);

mat2 zrotation2x2(float angle);

mat4 rotation(float pitch, float yaw, float roll);
mat3 rotation3x3(float pitch, float yaw, float roll);

mat4 transform(const vec3& scale, const vec3& euler_rotation, const vec3& translate);

mat4 lookat(vec3 position, vec3 target, vec3 up);

mat4 perspective(float fov, float aspect, float near, float far);
mat4 ortho(float left, float right, float bottom, float top, float near, float far);
