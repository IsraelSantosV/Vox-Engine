//
// Created by Israel on 05/04/2022.
//

#include "vox-engine/math/Vector3.h"

const Vector3 Vector3::ZERO = Vector3(0, 0, 0);
const Vector3 Vector3::ONE = Vector3(1, 1, 1);
const Vector3 Vector3::UNIT_X = Vector3(1, 0, 0);
const Vector3 Vector3::UNIT_Y = Vector3(0, 1, 0);
const Vector3 Vector3::UNIT_Z = Vector3(0, 0, 1);
const Vector3 Vector3::UP = Vector3(0, 1, 0);
const Vector3 Vector3::DOWN = Vector3(0, -1, 0);
const Vector3 Vector3::LEFT = Vector3(-1, 0, 0);
const Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
const Vector3 Vector3::FORWARD = Vector3(0, 0, 1);
const Vector3 Vector3::BACK = Vector3(0, 0, -1);

Vector3::Vector3():x(0.0),y(0.0),z(0.0){};
Vector3::Vector3(float uX,float uY,float uZ):x(uX),y(uY),z(uZ){}
Vector3::~Vector3(){}
Vector3::Vector3(const Vector3& v):x(v.x),y(v.y),z(v.z){}

Vector3& Vector3::operator=(const Vector3& v){

    x=v.x;
    y=v.y;
    z=v.z;

    return *this;

}


void Vector3::operator+=(const Vector3& v){

    x+=v.x;
    y+=v.y;
    z+=v.z;

}

Vector3 Vector3::operator+(const Vector3& v)const{


    return Vector3(x+v.x,y+v.y,z+v.z);
}

void Vector3::operator-=(const Vector3& v){

    x-=v.x;
    y-=v.y;
    z-=v.z;
}

Vector3 Vector3::operator-(const Vector3& v)const{

    return Vector3(x-v.x,y-v.y,z-v.z);
}

void Vector3::operator*=(const float s){

    x*=s;
    y*=s;
    z*=s;

}

Vector3 Vector3::operator*(const float s) const{

    return Vector3(s*x,s*y,s*z);
}


//divide by scalar
void Vector3::operator /=(const float s){

    x=x/s;
    y=y/s;
    z=z/s;
}

Vector3 Vector3::operator/(const float s)const{

    return Vector3(x/s,y/s,z/s);
}

float Vector3::operator*(const Vector3& v) const{

    return x*v.x+y*v.y+z*v.z;

}

float Vector3::dot(const Vector3& v) const{

    return x*v.x+y*v.y+z*v.z;

}

float Vector3::angle(const Vector3& v){

    float theta;

    Vector3 u=v;
    Vector3 m=*this;

    theta=dot(u)/(m.magnitude()*u.magnitude());

    theta=RadToDegrees(acos(theta));

    return theta;

}

Vector3 Vector3::cross(const Vector3& v) const{

    return Vector3(y*v.z-z*v.y,
                       z*v.x-x*v.z,
                       x*v.y-y*v.x);

}

void Vector3::operator %=(const Vector3& v){

    *this=cross(v);

}

Vector3 Vector3::operator %(const Vector3& v) const{

    return Vector3(y*v.z-z*v.y,
                       z*v.x-x*v.z,
                       x*v.y-y*v.x);
}

void Vector3::normalize(){

    float mag=std::sqrt(x*x+y*y+z*z);

    if (mag>0.0f) {

        //normalize it
        float oneOverMag=1.0f/mag;

        x=x*oneOverMag;
        y=y*oneOverMag;
        z=z*oneOverMag;

    }

}

void Vector3::conjugate(){

    x=-1*x;
    y=-1*y;
    z=-1*z;

}

#pragma mark-magnitude

float Vector3::magnitude(){

    float magnitude=std::sqrt(x*x+y*y+z*z);

    return magnitude;

}

float Vector3::magnitudeSquare(){

    float magnitude=x*x+y*y+z*z;

    return magnitude;
}


//clear
void Vector3::zero(){
    x=0;
    y=0;
    z=0;
}

void Vector3::absolute(){

    x=std::abs(x);
    y=std::abs(y);
    z=std::abs(z);

}

void Vector3::show(){
    std::cout<<"("<<x<<","<<y<<","<<z<<")"<<std::endl;
}


void Vector3::negate(){
    x=-1*x;
    y=-1*y;
    z=-1*z;
}

bool Vector3::operator!=(const Vector3 &v) const {
    return v.x != x || v.y != y || v.z != z;
}