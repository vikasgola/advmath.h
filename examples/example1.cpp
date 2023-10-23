#include<iostream>
#include<iomanip>
#include<advmath/advmath.h>

template<typename T>
void print(std::string text, T const& text2){
    std::cout<<std::left<<std::setw(15)<<text<<text2<<std::endl;
}

int main(){
    std::cout<<"=== Vector Operations ==="<<std::endl;
    vec2 v(1.0f, 2.0f);
    vec2 v2(2.0f, 4.0f);

    print("v1 ->", v);
    print("mag1 ->", v.mag());
    print("norm v1 ->", v.normalized());
    print("v2 ->", v2);
    print("mag2 ->", v2.mag());

    print("v1+v2 ->", v+v2);
    print("v1-v2 ->", v-v2);
    print("v1*v2 ->", v*v2);
    print("v1*4 ->", v*4);
    print("v1[0] ->", v[0]);
    print("v1.v2 ->", v.dot(v2));
    print("v1 angle v2 ->", v.angle(v2));
    print("v1 proj v2 ->", v.proj(v2));
    print("v1 perp v2 ->", v.perp(v2));
    return 0;
}