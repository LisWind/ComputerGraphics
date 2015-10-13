﻿
#include<stdlib.h>
#include<cstdio>
#include<stdlib.h>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

#include<gl/glut.h> 
#include "00-DataDefinition.h"

/*		本文 学习到内容

Bresenham 画线算法

待自己实现一遍。
*/

// 前置声明
void creat_Line_Point_Set(const Line2D & drawLine, std::vector<Point2D> &pointSet);

// 定义要画的直线的集合
const Line2D  drawLineSet[]	= {
	{ {0, 0},	{100, 90} },
	{ {0, 0},	{190, 190} },
	{ {0, 0},	{190, 50} },
};		
std::vector<Point2D> drawPointSet;					// 集成了要画出的点

//=========================================================================
//
//							画个坐标系
//
//=========================================================================

void myDisplay_GL_LINE_LOOP_Draw_Sine_function(void)  
{  
	const GLfloat factor = 0.1f;  //缩放因子，将普通正弦函数的图像缩小10倍画到屏幕上。

	glClear(GL_COLOR_BUFFER_BIT);  
	glBegin(GL_LINES);  
	glVertex2f(-1.0f, 0.0f);  
	glVertex2f(1.0f, 0.0f);         // 以上两个点可以画x轴，坐标原点在正中心。  
	glVertex2f(0.0f, -1.0f);  
	glVertex2f(0.0f, 1.0f);         // 以上两个点可以画y轴  
	glEnd();  

	

	//用描点法画出直线来  
	glBegin(GL_POINTS); 

	for (const auto & line : drawLineSet)
	{
		drawPointSet.clear();

		//计算出要画的点
		creat_Line_Point_Set(line, drawPointSet);
		for (const auto & point : drawPointSet)
		{
			glVertex2f(point.x *2.0f/ScreenArea.x, point.y*2.0f/ScreenArea.y);		// 坐标转换，转换成 -1.0～1.0的坐标
		}
	}
	

	glEnd();  
	glFlush();  
}  

//=========================================================================
//
//					 Bresenham's line algorithm - 布雷森汉姆直线算法
//
//=========================================================================

// 第1版

// 第一个参数是要画的直线， 第2个参数 接收 画这条线 所需要的 点的集合。
void creat_Line_Point_Set(const Line2D & drawLine, std::vector<Point2D> &pointSet)
{
	float dy = drawLine.endPos.y - drawLine.startPos.y;
	float dx = drawLine.endPos.x - drawLine.startPos.x;
	float k = dy/dx;	// 直线的斜率

	Point2D frontP = drawLine.startPos;		// 前一个点
	Point2D backP;							// 下一个点

	// X方向每前进一个单位时，Y方向就相应的判断 是+1还是+0个单位。
	for (float addy = 0; addy < dy; addy += k) {	//增量y
		
		backP = frontP;
		backP.x += 1;

		// 判断 Y方向是 +1 还是 +0 个单位
		if (addy - frontP.y > 0.5f)
		{
			backP.y += 1;
		}

		// 把点压入集合中
		pointSet.push_back(backP);

		frontP = backP;
	}
}

// 第2版 - 改成整数运算

// 第3版 - 8个区间都可以画 

//=========================================================================
// 其他优化版本

// 中点画法

// 