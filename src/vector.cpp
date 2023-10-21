#include<advmath/vector.h>
#include<cfloat>

#define CMP(x, y)                    \
    (\
        fabsf( (x)-(y) ) <= FLT_EPSILON * \
        fmaxf(1.0f,                    \
        fmaxf(fabsf(x), fabsf(y)))     \
   )

template <unsigned int T>
vec<T>::vec(float value){
    for(int i=0;i<T;i++){
        this->array[i] = value;
    }
}

template <unsigned int T>
void vec<T>::malloc(){
    this->array = new float[T];
}

template<unsigned int T>
float& vec<T>::operator[](int i){
    return this->array[i];
}

template<unsigned int T>
vec<T> vec<T>::operator+(const vec<T> &other){
    vec<T> res;
    res.malloc();
    for(int i=0;i<T;i++){
        res.array[i] = this->array[i]+other.array[i];
    }
    return res;
}

template<unsigned int T>
vec<T> vec<T>::operator-(const vec<T> &other){
    vec<T> res;
    res.malloc();
    for(int i=0;i<T;i++){
        res.array[i] = this->array[i]-other.array[i];
    }
    return res;
}

template<unsigned int T>
vec<T> vec<T>::operator*(const vec<T> &other){
    vec<T> res;
    res.malloc();
    for(int i=0;i<T;i++){
        res.array[i] = this->array[i]*other.array[i];
    }
    return res;
}

template<unsigned int T>
vec<T> vec<T>::operator*(const float value){
    vec<T> res;
    res.malloc();
    for(int i=0;i<T;i++){
        res.array[i] = this->array[i]*value;
    }
    return res;
}

template<unsigned int T>
vec<T> vec<T>::operator/(const float value){
    vec<T> res;
    res.malloc();
    for(int i=0;i<T;i++){
        res.array[i] = this->array[i]/value;
    }
    return res;
}

template<unsigned int T>
bool vec<T>::operator==(const vec<T> &other){
    for(int i=0;i<T;i++){
        if(!CMP(this->array[i], other.array[i])) return false;
    }
    return true;
}

template<unsigned int T>
bool vec<T>::operator!=(const vec<T> &other){
    return !(*this == other);
}

template<unsigned int T>
float vec<T>::dot(const vec<T> &other){
    float res = 0;
    for(int i=0;i<T;i++){
        res += this->array[i]*other.array[i];
    }
    return res;
}


template<unsigned int T>
float vec<T>::mag(){
    return sqrtf(this->dot(*this));
}

template<unsigned int T>
float vec<T>::angle(vec<T> &other){
    float adotb = this->dot(other);
    float mag = (this->mag()*other.mag());
    return acosf(adotb/mag);
}

template<unsigned int T>
vec<T> vec<T>::proj(vec<T> &other){
    float mag = this->dot(other)/(other.mag()*other.mag());
    return other*mag;
}

template<unsigned int T>
vec<T> vec<T>::perp(vec<T> &other){
    return *this - this->proj(other);
}

template<unsigned int T>
vec<T> vec<T>::refl(vec<T> &other){
    return *this - this->proj(other)*2.0f;
}

template<unsigned int T>
void vec<T>::normalize(){
    *this = (*this)*(1.0f/this->mag());
}

template<unsigned int T>
vec<T> vec<T>::normalized(){
    return (*this)*(1.0f/this->mag());
}


template class vec<2>;
template class vec<3>;
template class vec<4>;
