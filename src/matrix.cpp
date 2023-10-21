#include<advmath/matrix.h>
#include<cstdio>
#include<cfloat>

#define CMP(x, y)                    \
    (\
        fabsf( (x)-(y) ) <= FLT_EPSILON * \
        fmaxf(1.0f,                    \
        fmaxf(fabsf(x), fabsf(y)))     \
   )

template<unsigned int T>
float* mat<T>::operator[] (int i){
    return &(this->array[i*T]);
}

template<>
float* mat<1>::operator[] (int i){
    return &(this->array[i*1]);
}

template<unsigned int T>
mat<T>::mat(){
}

template<unsigned int T>
mat<T>::mat(const float (&values)[T*T]){
    memcpy(this->array, values, T*T*sizeof(float));
}

template<unsigned int T>
mat<T>::~mat(){
}

template<unsigned int T>
mat<T>::mat(float value){
    for(int i=0;i<T;i++){
        (*this)[i][i] = value;
    }
}

template <unsigned int T>
mat<T> mat<T>::tras(){
    mat<T> res;
    for(int i=0;i<T;i++){
        for(int j=0;j<T;j++){
            res[i][j] = (*this)[j][i];
        }
    }
    return res;
}

template<unsigned int T>
mat<T> mat<T>::operator*(const float value){
    mat<T> res;
    for(int i=0;i<T*T;i++){
        res.array[i] = this->array[i]*value;
    }
    return res;
}

template<unsigned int T>
mat<T> mat<T>::operator/(const float value){
    return (*this)*(1.0f/value);
}

template<unsigned int T>
mat<T> mat<T>::operator+(const mat<T>& other){
    mat<T> res;
    for(int i=0;i<T*T;i++){
        res.array[i] = this->array[i]+other.array[i];
    }
    return res;
}

template<unsigned int T>
mat<T> mat<T>::operator-(const mat<T>& other){
    mat<T> res;
    for(int i=0;i<T*T;i++){
        res.array[i] = this->array[i]-other.array[i];
    }
    return res;
}

template<unsigned int T>
mat<T> mat<T>::operator*(const mat<T> &other){
    mat<T> res;
    int rowsA = T;
    int rowsB = T;
    int colsA = T;
    int colsB = T;
    for(int i=0; i<rowsA;i++){
        for(int j=0;j<colsB;j++){
            res.array[colsB*i + j] = 0.0f;
            for(int k=0;k<colsA;k++){
                int ai = colsA*i + k;
                int bi = colsB*k + j;
                res.array[colsB*i+j] += this->array[ai]*other.array[bi];
            }
        }
    }
    return res;
}

template <unsigned int T>
mat<T - 1> mat<T>::cut(int row, int col){
    mat<T-1> res;

    int index = 0;
    for(int i=0;i<T;i++){
        for(int j=0;j<T;j++){
            if(i == row || j == col) continue;
            res.array[index++] = (*this)[i][j];
        }
    }
    return res;
}

template <unsigned int T>
float mat<T>::cofactor(int row, int col){
    float res = 0;
    float sign = powf(-1.0f, row+col);
    return this->minor(row, col)*sign;
}

template <unsigned int T>
float mat<T>::adjugate(int row, int col){
    return this->minor(col, row);
}

template <unsigned int T>
mat<T> mat<T>::adjugate(){
    mat<T> res;
    for(int i=0;i<T;i++){
        for(int j=0;j<T;j++){
            res[i][j] = this->adjugate(i, j);
        }
    }
    return res;
}


template <unsigned int T>
mat<T> mat<T>::inverse(){
    float det = this->det();
    if(CMP(det, 0.0f)){
        fprintf(stdout, "[WARN]: Inverse not possible (determinant = 0). returning zero matrix.\n");
        mat<T> res;
        return res;
    }
    return this->adjugate()/this->det();
}


template <unsigned int T>
float mat<T>::det(){
    float res = 0;

    for(int i=0;i<T;i++){
        res += (*this)[0][i]*this->cofactor(0, i);
    }
    return res;
}

template <unsigned int T>
float mat<T>::minor(int row, int col){
    return this->cut(row, col).det();
}

template<>
float mat<2>::minor(int row, int col){
    if(row == 0 && col == 0) return this->array[3];
    if(row == 0 && col == 1) return this->array[2];
    if(row == 1 && col == 0) return this->array[1];
    return this->array[0];
}

mat4 translation(float x, float y, float z){
    mat4 t(1.0f);
    t[3][0] = x;
    t[3][1] = y;
    t[3][2] = z;
    return t;
}

mat4 translation(const vec3& loc){
    mat4 t(1.0f);
    t[3][0] = loc.x;
    t[3][1] = loc.y;
    t[3][2] = loc.z;
    return t;
}

mat4 scale(float x, float y, float z){
    mat4 t(1.0f);
    t[0][0] = x;
    t[1][1] = y;
    t[2][2] = z;
    return t;
}

mat4 scale(const vec3& loc){
    mat4 t(1.0f);
    t[0][0] = loc.x;
    t[1][1] = loc.y;
    t[2][2] = loc.z;
    return t;
}


mat4 xrotation(float angle){
    angle = DEG2RAD(angle);
    mat4 t(1.0f);
    t[1][1] = cosf(angle);
    t[1][2] = sinf(angle);
    t[2][1] = -sinf(angle);
    t[2][2] = cosf(angle);
    return t;
}

mat4 yrotation(float angle){
    angle = DEG2RAD(angle);
    mat4 t(1.0f);
    t[0][0] = cosf(angle);
    t[0][2] = -sinf(angle);
    t[2][0] = sinf(angle);
    t[2][2] = cosf(angle);
    return t;
}

mat4 zrotation(float angle){
    angle = DEG2RAD(angle);
    mat4 t(1.0f);
    t[0][0] = cosf(angle);
    t[0][1] = sinf(angle);
    t[1][0] = -sinf(angle);
    t[1][1] = cosf(angle);
    return t;
}

mat3 xrotation3x3(float angle){
    angle = DEG2RAD(angle);
    mat3 t(1.0f);
    t[1][1] = cosf(angle);
    t[1][2] = sinf(angle);
    t[2][1] = -sinf(angle);
    t[2][2] = cosf(angle);
    return t;
}

mat3 yrotation3x3(float angle){
    angle = DEG2RAD(angle);
    mat3 t(1.0f);
    t[0][0] = cosf(angle);
    t[0][2] = -sinf(angle);
    t[2][0] = sinf(angle);
    t[2][2] = cosf(angle);
    return t;
}

mat3 zrotation3x3(float angle){
    angle = DEG2RAD(angle);
    mat3 t(1.0f);
    t[0][0] = cosf(angle);
    t[0][1] = sinf(angle);
    t[1][0] = -sinf(angle);
    t[1][1] = cosf(angle);
    return t;
}

mat2 zrotation2x2(float angle){
    angle = DEG2RAD(angle);
    mat2 t(1.0f);
    t[0][0] = cosf(angle);
    t[0][1] = sinf(angle);
    t[1][0] = -sinf(angle);
    t[1][1] = cosf(angle);
    return t;
}

mat4 rotation(float pitch, float yaw, float roll){
    return zrotation(roll)*xrotation(pitch)*yrotation(yaw);
}

mat3 rotation3x3(float pitch, float yaw, float roll){
    return zrotation3x3(roll)*xrotation3x3(pitch)*yrotation3x3(yaw);
}

mat4 transform(const vec3& scale_factor, const vec3& euler_rotation, const vec3& translate){
    return scale(scale_factor)*rotation(
        euler_rotation.x, euler_rotation.y, euler_rotation.z
    )*translation(translate);
}

mat4 lookat(vec3 position, vec3 target, vec3 up){
    vec3 forward = target-position;
    forward.normalize();
    vec3 right = up.cross(forward);
    right.normalize();
    vec3 new_up = forward.cross(right);

    return mat4({
        right.x, new_up.x, forward.x, 0.0f,
        right.y, new_up.y, forward.y, 0.0f,
        right.z, new_up.z, forward.z, 0.0f,
        -right.dot(position), -new_up.dot(position), -forward.dot(position), 1.0f
    });
}

mat4 perspective(float fov, float aspect, float near, float far){
    float tanHalfFov = tanf(DEG2RAD((fov * 0.5f)));
    float fovY = 1.0f / tanHalfFov; // cot(fov/2)
    float fovX = fovY / aspect; // cot(fov/2) / aspect
    mat4 result;

    result[1-1][1-1] = fovX;
    result[2-1][2-1] = fovY;
    result[3-1][3-1] = far / (far - near);
    result[3-1][4-1] = 1.0f;
    result[4-1][3-1] = -near * result[3-1][3-1];
    result[4-1][4-1] = 0.0f;
    return result;
}

mat4 ortho(float left, float right, float bottom, float top, float near, float far){
    float _11 = 2.0f / (right - left);
    float _22 = 2.0f / (top - bottom);
    float _33 = 2.0f / (far - near);
    float _41 = (left + right) / (left - right);
    float _42 = (top + bottom) / (bottom - top);
    float _43 = (near) / (near - far);
    return mat4({
        _11, 0.0f, 0.0f, 0.0f,
        0.0f,  _22, 0.0f, 0.0f,
        0.0f, 0.0f,  _33, 0.0f,
        _41,  _42,  _43, 1.0f
    });
}


template class mat<2>;
template class mat<3>;
template class mat<4>;
