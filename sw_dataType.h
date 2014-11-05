#ifndef DATATYPE_H
#define DATATYPE_H

#include"stdlib.h"
#include"algorithm"
#include"cmath"
#include<vector>
#include"cmath"
#include"opencv2/opencv.hpp"

#include <iostream>
#include <string>
#include<QSet>

using namespace std;



////////////////////////////////////////////////PointXY///////////////////////////////////////////////////////////////////
class PointXY
{
public:

    PointXY(){x = 0; y=0;}
    PointXY(const PointXY&pt)
    {
       this->x = pt.x;
       this->y = pt.y;
    }
    PointXY(float x, float y)
    {
      this->x = x;
      this->y = y;
    }

    PointXY & operator- (const PointXY & pt)
    {
        this->x -= pt.x;
        this->y -= pt.y;

        return *this;
    }

    PointXY &operator = (const PointXY & pt)
    {
      this->x = pt.x;
      this->y = pt.y;
    }

    float x;
    float y;
};
////////////////////////////////////////////////PointXYZ///////////////////////////////////////////////////////////////////
class PointXYZ
{
public:

    PointXYZ(){}
    PointXYZ(const PointXYZ&pt)
    {
      this->x = pt.x;
      this->y = pt.y;
      this->z = pt.z;
    }
    PointXYZ(float x, float y, float z)
    {
       this->x = x;
       this->y = y;
       this->z = z;
    }

    PointXYZ & operator =(const PointXYZ & pt)
    {
        this->x = pt.x;
        this->y = pt.y;
        this->z = pt.z;

        return *this;
    }

    bool operator ==(const PointXYZ &pt)
    {
        // return(x == pt.x && y==pt.y &&z == pt.z);
        return(abs(x -pt.x)<0.01 && abs(y-pt.y)<0.01 &&abs(z - pt.z)<0.01);
    }

public:
    QSet<int> vis;

    float x;
    float y;
    float z;
    bool isProcessed;
    bool inconsist_;

};
////////////////////////////////////////////////PointXYZRGB////////////////////////////////////////////////////////////////
class PointXYZRGB
{
public:

    PointXYZRGB(){}
    PointXYZRGB(const PointXYZRGB&pt)
    {
       this->x = pt.x;
       this->y = pt.y;
       this->z = pt.z;

       this->r = pt.r;
       this->g = pt.g;
       this->b = pt.b;
       
       this->isProcessed = pt.isProcessed;
       this->id = pt.id;

       this-> vis = pt.vis;
       this-> inconsist_ = pt.inconsist_;

    }
    PointXYZRGB(float x, float y, float z, uchar r, uchar g, uchar b)
   {
        this->x = x;
        this->y = y;
        this->z = z;
     
        this->r = (float)r;
        this->g = (float)g;
        this->b = (float)b;
   }

    bool isProcessed;

    int id;

    float x;
    float y;
    float z;

    float r;
    float g;
    float b;

    QSet<int> vis;
    bool inconsist_;
};

class PointXYZNormal{

public:

    PointXYZNormal(){}
    PointXYZNormal(const PointXYZNormal & pt)
    {
        this->x = pt.x;
        this->y = pt.y;
        this->z = pt.z;


        this->normal_x = pt.normal_x;
        this->normal_y = pt.normal_y;
        this->normal_z = pt.normal_z;

        this->inconsist_ = pt.inconsist_;
    }
    PointXYZNormal(float xx, float yy, float zz): x(xx), y(yy), z(zz)
    {
        this->normal_x = 0.0;
        this->normal_y = 0.0;
        this->normal_z = 0.0;

        this->inconsist_= false;
    }
    PointXYZNormal(float xx, float yy, float zz,
                   float nor_x, float nor_y, float nor_z): x(xx), y(yy), z(zz),
        normal_x(nor_x), normal_y(nor_y), normal_z(nor_z)
    {
        this->inconsist_= false;
    }
    PointXYZNormal &operator =(const PointXYZNormal & pt)
    {
        this->x = pt.x;
        this->y = pt.y;
        this->z = pt.z;

        this->normal_x = pt.normal_x;
        this->normal_y = pt.normal_y;
        this->normal_z = pt.normal_z;

        this->inconsist_ = pt.inconsist_;

        return *this;
    }

    bool operator ==( const PointXYZNormal & pt)
    {
        return(abs(x -pt.x)<0.01 && abs(y-pt.y)<0.01 &&abs(z - pt.z)<0.01&&
               abs(normal_x - pt.normal_x)<0.01&&abs(normal_y - pt.normal_y)<0.01&&
               abs(normal_z - pt.normal_z)<0.01);

    }

    float x;
    float y;
    float z;

    float normal_x;
    float normal_y;
    float normal_z;

    bool inconsist_;

};
/////////////////////////////////////////////////////////////////////////////////
class PointXYZRGBNormal
{
public:

    PointXYZRGBNormal(){

        this->x = 0;
        this->y = 0;
        this->z = 0;

        this->r = 0;
        this->g = 0;
        this->b = 0;

        this->normal_x = 0;
        this->normal_y = 0;
        this->normal_z = 0;

        this->inconsist_ = 0;

    }
    PointXYZRGBNormal(float x, float y, float z){

        this->x = x;
        this->y = y;
        this->z = z;

        this->r = 0;
        this->g = 0;
        this->b = 0;

        this->normal_x = 0;
        this->normal_y = 0;
        this->normal_z = 0;

        this->inconsist_ = 0;

    }
    PointXYZRGBNormal(const PointXYZRGBNormal &pt )
    {
        this->x = pt.x;
        this->y = pt.y;
        this->z = pt.z;

        this->r = pt.r;
        this->g = pt.g;
        this->b = pt.b;

        this->normal_x = pt.normal_x;
        this->normal_y = pt.normal_y;
        this->normal_z = pt.normal_z;

        this->id = id;
        this->vis = pt.vis;
        this->inconsist_ = pt.inconsist_;
    }

    PointXYZRGBNormal(const PointXYZNormal &pt )
    {
        this->x = pt.x;
        this->y = pt.y;
        this->z = pt.z;

        this->r = 0;
        this->g = 0;
        this->b = 0;

        this->normal_x = pt.normal_x;
        this->normal_y = pt.normal_y;
        this->normal_z = pt.normal_z;

        this->inconsist_ = pt.inconsist_;
    }


    PointXYZRGBNormal & operator =(const PointXYZRGBNormal & pt)
    {
        this->x = pt.x;
        this->y = pt.y;
        this->z = pt.z;

        this->r = pt.r;
        this->g = pt.g;
        this->b = pt.b;

        this->normal_x = pt.normal_x;
        this->normal_y = pt.normal_y;
        this->normal_z = pt.normal_z;

        this->id = id;
        this->vis = pt.vis;
        this->inconsist_ = pt.inconsist_;

        return *this;
    }

    int id;

    float x;
    float y;
    float z;

    float r;
    float g;
    float b;

    float normal_x;
    float normal_y;
    float normal_z;

    QSet<int> vis;

    bool inconsist_;

    int label_;


};

/////////////////////////////////////////////////////////////////////////////////
class Vec3{

public:
    Vec3(){ x_ = 0; y_ =0; z_ =0;}
    Vec3(float x, float y, float z): x_(x), y_(y), z_(z){}

    // 复制构造函数
    Vec3(const Vec3 & v)
    {
        this->x_ = v.x_;
        this->y_ = v.y_;
        this->z_ = v.z_;
    }

    // 复制操作符
    Vec3 & operator =(const Vec3 & v)
    {
        this->x_ = v.x_;
        this->y_ = v.y_;
        this->z_ = v.z_;

        return *this;
    }

#if 1
    // 下标访问操作符需要重载两个版本const 和 非 const版本 // 返回引用可以进行左右操作符的操作
    float & operator [](const size_t index)
    {
        switch(index)
        {
        case 0:
            return x_;
            break;
        case 1:
            return y_;
            break;
        case 2:
            return z_;
            break;
        default:
            break;
        }
    }

    // 注意 const版本需要const
    const float &operator [](const size_t index) const
    {
        switch(index)
        {
        case 0:
            return x_;
            break;
        case 1:
            return y_;
            break;
        case 2:
            return z_;
            break;
        default:
            break;
        }
    }

#endif
    // norm
    float  &norm()
    {
        float v = sqrt(x_*x_ + y_*y_ + z_*z_);
        return  v;
    }

    // normalization
    void normalize()
    {
        float l = this->norm();
        if(l ==0) std::cerr<<"Divided by 0!"<<std::endl;
        if(l!=0)
        {
            x_ /= l;
            y_ /= l;
            z_ /= l;
        }
    }
   
    // 进行map的排序的操作 如果v1 和 v2 之间相互不存在小于的关系，则认为v1 和 v2 相同
     bool operator < ( const Vec3& v) const 
     {
         bool flag0 = false;
         bool flag1 = false;
         bool flag2 = false;

         if(this->x_ != v.x_)
         {
           flag0 =  this->x_< v.x_ ? true: false;
         }
         if((this->x_== v.x_)&& ( this->y_ != v.y_ ))
         {
           flag1 =  this->y_< v.y_ ? true: false;
         }
         if( (this->x_ == v.x_)&&(this->y_ == v.y_)
                 &&(this->z_ != v.z_ ))
         {
           flag2 =  this->z_ < v.z_? true: false;
         }

        return flag0||flag1||flag2;
     }

public:
    float x_;
    float y_;
    float z_;
};



////////////////////////////////////////////////Line3D//////////////////////////////////////////////////////////////////////
class Line3D
{
public:

    Line3D(){}
    Line3D(PointXYZRGBNormal& pt1, PointXYZRGBNormal& pt2){
        pt1_ = pt1;
        pt2_ = pt2;
    }

public:

     enum LineType{VERTICAL, PARALLEL, COLINEAR};

    PointXYZRGBNormal pt1_;
    PointXYZRGBNormal pt2_;

};
Vec3  operator +(const Vec3 & vl, const Vec3 & vr); // 注意返回不能是引用
Vec3  operator -(const Vec3 & vl, const Vec3 & vr);
Vec3  operator *(const Vec3 & v, const float f);
Vec3  operator *( const float f, const Vec3 & v);
Vec3  operator /( const Vec3 & v,const float f);
float operator *(const Vec3& vl, const Vec3& vr);
ostream& operator <<(ostream os, const Vec3 v);
Vec3 cross(const Vec3 &vl, const Vec3 &vr);


#endif // DATATYPE_H