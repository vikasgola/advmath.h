#include<iostream>
#include<advmath/advmath.h>

template<typename T>
void print(std::string text, T const& text2){
    std::cout<<text<<text2<<std::endl<<std::endl;
}

int main(){
    // matrix operations
    std::cout<<"=== Matrix Operations ==="<<std::endl;
    mat2 m(3.0, 2.0, 4.0, 5.0);
    mat3 m2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    mat3 m3(1.0);

    print("m1 -> \n", m);
    print("|m1| -> ", m.det());
    print("inv m1 -> \n", m.inverse());

    print("m2 -> \n", m2);
    print("|m2| -> ", m2.det());
    print("m2 trans -> \n", m2.tras());
    print("inv m2 -> \n", m2.inverse());
    print("adj m2 -> \n", m2.adjugate());

    print("m3 -> \n", m3);

    print("m2+m3 -> \n", m2+m3);
    print("m2-m3 -> \n", m2-m3);
    print("m2*m3 -> \n", m2*m3);
    print("m2/10 -> \n", m2/10);

    mat4 trans = transform(vec3(45.0, 45.0, 45.0), vec3(45.0, 45.0, 45.0), vec3(45.0, 45.0, 45.0));
    print("trans -> \n", trans);
    return 0;
}