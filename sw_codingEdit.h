#ifndef SW_CODINGEDIT_H
#define SW_CODINGEDIT_H

#include"sw_dataType.h"
#include"sw_functions.h"

#include"stdlib.h"
#include<fstream>
#include<iostream>
#include<sstream>
#include"algorithm"
#include <string>
#include<map>
#include<vector>

using namespace std;

namespace SW{

//////////////////////////////////////////STRUCTURE ALPHABET///////////////////////////////////////
static char alphabet[84]={

    // 0    1     2    3    4    5    6
    'a', 'b',  'c', 'd', 'e' ,'f', 'g',
    // 7    8     9    10   11   12   13
    'h', 'i',  'j', 'k', 'l', 'm', 'n',
    // 14   15    16   17   18   19   20
    'o', 'p',  'q', 'r', 's', 't', 'u',
    // 21   22    23   24,  25   26   27
    'v', 'w',  'x', 'y', 'z',  'A', 'B',
    // 28   29    30   31   32   33   34
    'C', 'D',   'E', 'F', 'G', 'H', 'I',
    // 35   36    37   38   39   40   41
    'J', 'K',   'L', 'M', 'N', 'O', 'P',
    // 42   43    44   45   46   47   48
    'Q', 'R',   'S', 'T', 'U', 'V', 'W',
    // 49   50    51   52   53    54  55
    'X', 'Y',  'Z', '0', '1', '2', '3',
    // 56   57    58   59   60    61  62
    '4', '5',  '6', '7', '8',  '9', '!',
    // 63  64     65  66    67    68  69
    '@', '#',  '$', '%', '^	',  '&', '*',
    // 70  71     72  73    74    75  76
    '(', ')',  '-', '+',  '_', '=', ':',
    // 77  78     79  80    81    82  83
    ';', '.',  '<', '>',  '?',  '/', ','

};


//////////////////////////////////////////CLASS LETTER/////////////////////////////////////////////
class Letter{

public:
    Letter(){}
    Letter(int clockWise, float angle, float length):
        clockWise_(clockWise), angle_(angle), length_(length){}

    bool operator == (const Letter & let)
    {
        return (clockWise_ == let.clockWise_)
                &&(abs(angle_-let.angle_)< 10)
                &&(abs(length_ - let.length_)<0.05);
    }

    Letter & operator =(const Letter & let)
    {
        clockWise_ = let.clockWise_;
        angle_ = let.angle_;
        length_ = let.length_;
        return *this;
    }

    bool operator < ( const Letter & let) const // 对< 进行重载，const是必须的，否则会出现错误
    {                                           // map  根据<来排序，如果两个元素之间的“小于”关系
        // 都是false 则判断两个元素为“相等”。

        bool flag0 = false;
        bool flag1 = false;
        bool flag2 = false;

        if(clockWise_ != let.clockWise_)
        {
            flag0 =  clockWise_< let.clockWise_ ? true: false;
        }
        if((clockWise_== let.clockWise_)&& fabs(angle_ - let.angle_)>= 5)
        {
            flag1 =  angle_< let.angle_ ? true: false;
        }
        if( (clockWise_== let.clockWise_)&&fabs(angle_ - let.angle_) < 5
                &&fabs(length_ - let.length_) >= TR_)
        {
            flag2 =  length_ < let.length_? true: false;
        }
        return flag0||flag1||flag2;
    }

    static void TR(float tr){ TR_ = tr;}

public:

    int clockWise_;
    float angle_;
    float length_;

private:

    static float TR_ ; // 只是声明，并没有
};


//////////////////////////////////////////CLASS BLOCK3/////////////////////////////////////////////
class Block3{
public:
    Block3(){}

public:
    vector<PointXYZRGBNormal> start_pos_;
    vector<vector<PointXYZRGBNormal> > curves_;

    string word_;

    float start_h_;
    float end_h_;

};

};

using namespace SW;


/////////////////////////////////////////SUBCURVESPOSITIONADJUSTMENT///////////////////////////////
//如果每一层含有多个轮廓，则对轮廓进行调整，保证是按照同一顺序排列
void subCurvesPositionAdjustment(vector<vector<PointXYZRGBNormal> > &curves, 
                                 Vec3&ref_pt);



/////////////////////////////////////////STARTPOSADJUSTMENT////////////////////////////////////////
// 对提取的轮廓进行对齐，保证起始位置一致
void startPosAdjustment(vector<vector<PointXYZRGBNormal> > & curves, Vec3 &ref_pt);



//////////////////////////////////////////MAKE_DICTIONARY//////////////////////////////////////////
//创建编码字典，每一个有向线段用一个字符代表
map<Letter, string> make_dictionary(vector<vector<PointXYZRGBNormal> > &allCorners);




//////////////////////////////////////////CODING///////////////////////////////////////////////////
// 对每一个轮廓进行编码
string  coding(vector<PointXYZRGBNormal>&corners, map<Letter, string> &dictionary);



////////////////////////////////////////CONVERTCURVESTOWORDS///////////////////////////////////////
//对所有的层的轮廓进行编码
vector<string>  convertCurvesToWords(vector<vector<vector< PointXYZRGBNormal> > > &allCorners,
                                     map<Letter, string> & table);



//////////////////////////////////////////OPERATOR << //////////////////////////////////////////////
//重载输出流
ostream &operator << (ostream& os, const Letter& let);



//////////////////////////////////////////EDITDIST///////////////////////////////////////////////////
//计算编辑距离
int EditDist(string str0, string str1 );



//////////////////////////////////////////SIMILARITY///////////////////////////////////////////////////
//加算相似性
float similarity(string str0, string str1);



//////////////////////////////////////////CODECENTERCLUSTRING//////////////////////////////////////////
//对字符串进行聚类 本质上是一个统计的过程
vector<string > codeCentersClustering(vector<string> &words, vector<float> &weights,
                                      vector<vector<PointXYZRGBNormal> > &start_pos, vector<vector<PointXYZRGBNormal> > &centers_pos);



//////////////////////////////////////////MULTILABELASSIGNMENT///////////////////////////////////////
//多目标分配----图优化
vector<string> multiLabelAssignment(vector<string>& words, vector<string> &centers, 
                                    vector<float>&weights, vector<vector<PointXYZRGBNormal> > &start_pos,
                                    vector<vector<PointXYZRGBNormal> > &centers_pos, float sim_thresh, float labmda);




///////////////////////////////////////////GETBLOCKS///////////////////////////////////////////////////
//从每层的编码中获取BLOCK3
vector<Block3> getBlocks(vector<string> &words, vector<vector<PointXYZRGBNormal> >& start_pts, float step);




///////////////////////////////////////////DECODING//////////////////////////////////////////////////
//解码，由字符串得到一个轮廓并进行重建
vector<PointXYZRGBNormal> deCoding(string &word, map<string, Letter> &table_inv);




///////////////////////////////////////////BCLOCKRECONSTRUCTION////////////////////////////////////
//对Block进行重建*************************/
// Block3::word_中含有多个轮廓，每个轮廓的字符由空格间隔
// 重建出的轮廓存储在Block3::curves_中
void blockReconstruction(vector<Block3> &blocks, map<string, Letter> &table_inv);



/////////////////////////////////////////POSPROCESSING/////////////////////////////////////////////
//对Blocks进行后处理，去掉相邻的Block之间的间隙
void posProcessing(vector<Block3> &blocks, float TR);


/////////////////////////////////////////ISWORDVALID///////////////////////////////////////////////
//判断编码是否有效
bool isWordValid(string &word);



////////////////////////////////////////STARTDIRECIONADJUSTMENT////////////////////////////////////
//对提取的轮廓进行调整，保证曲线是按照逆时针方向旋转
void startDirectionAdjustment(vector<vector<PointXYZRGBNormal> > &curves);



////////////////////////////////////////WRITEURVESTOOFFFILE////////////////////////////////////////
//将未进行编码之前的模型三角化，保存成OFF文件
void writeCurvesToOFFFile(vector<vector<vector<PointXYZRGBNormal> > > & allcorners, string file_dir);



///////////////////////////////////////WRITEBLOCKSTOOFFFILE////////////////////////////////////////
//将BLOCK进行三角化，并保存成OFF文件
void writeBlocksToOFFFile(const vector<Block3> &blocks, string file_dir);



////////////////////////////////////////GETTINGTRAINGULATIONSFRMALLCORNERS//////////////////////////
//从编码的曲线中获取三角面片
void gettingTriangulationsFromAllCorners(const vector<vector<vector<PointXYZRGBNormal> > > & allcorners,
                                         vector<Vec3>& vertices, vector<vector<int> > &facets);


/////////////////////////////////////////GETTINGTRIANGULATIONSFROMBLOCKS///////////////////////////
//从blocks 中获取三角面片
void gettingTriangulationsFromBlocks(const vector<Block3> &blocks, vector<Vec3>& vertices, vector<vector<int> >&facets);


////////////////////////////////////////WRITEOFFILES/////////////////////////////////////////////////
void writeOFFFiles(const vector<Vec3>& vertices, const vector<vector<int> >&facets, string file_dir);

#endif
