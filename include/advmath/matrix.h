#pragma once
#include<fstream>
#include<advmath/vector.h>

template<unsigned int T>
class mat{
    public:
        float *array;

        mat();
        ~mat();

        void malloc();
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

class mat2: public mat<2>{
    public:
        union {
            struct {
                float _11, _12,
                      _21, _22;
            };
            float array[2*2] = {0};
        };

        mat2(float _11, float _12, float _21, float _22)
            : _11(_11), _12(_12), _21(_21), _22(_22){
            mat<2>::array = this->array;
        }

        mat2(float value){
            mat<2>::array = this->array;
            for(int i=0;i<2;i++){
                (*this)[i][i] = value;
            }
        }

        mat2(){
            mat<2>::array = this->array;
        }

        mat2(const mat<2> m){
            for(int i=0;i<2*2;i++){
                this->array[i] = m.array[i];
            }
            delete[] m.array;
        }
};

class mat3: public mat<3>{
    public:
        union {
            struct {
                float _11, _12, _13,
                      _21, _22, _23,
                      _31, _32, _33;
            };
            float array[3*3] = {0};
        };

        mat3(
            float _11, float _12, float _13,
            float _21, float _22, float _23,
            float _31, float _32, float _33
        ): _11(_11), _12(_12), _13(_13),
           _21(_21), _22(_22), _23(_23),
           _31(_31), _32(_32), _33(_33){

            mat<3>::array = this->array;
        }

        mat3(float value){
            mat<3>::array = this->array;
            for(int i=0;i<3;i++){
                (*this)[i][i] = value;
            }
        }

        mat3(){
            mat<3>::array = this->array;
        }

        mat3(const mat<3> m){
            for(int i=0;i<3*3;i++){
                this->array[i] = m.array[i];
            }
            delete[] m.array;
        }
};

class mat4: public mat<4>{
    public:
        union {
            struct {
                float _11, _12, _13, _14,
                      _21, _22, _23, _24,
                      _31, _32, _33, _34,
                      _41, _42, _43, _44;
            };
            float array[4*4] = {0};
        };

        mat4(
            float _11, float _12, float _13, float _14,
            float _21, float _22, float _23, float _24,
            float _31, float _32, float _33, float _34,
            float _41, float _42, float _43, float _44
        ): _11(_11), _12(_12), _13(_13), _14(_14),
           _21(_21), _22(_22), _23(_23), _24(_24),
           _31(_31), _32(_32), _33(_33), _34(_34),
           _41(_41), _42(_42), _43(_43), _44(_44){

            mat<4>::array = this->array;
        }

        mat4(float value){
            mat<4>::array = this->array;
            for(int i=0;i<4;i++){
                (*this)[i][i] = value;
            }
        }

        mat4(){
            mat<4>::array = this->array;
        }

        mat4(const mat<4>& m){
            mat<4>::array = this->array;
            for(int i=0;i<4*4;i++){
                this->array[i] = m.array[i];
            }
            delete[] m.array;
        }
};

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
