#pragma once

#include<stdio.h>

#include<graphics.h>   //ͼ�ν����ͷ�ļ�

#include<math.h>       //����Բ�εĹ켣����

#include<conio.h>

#include<time.h>

#include<stdlib.h>

#include<mmsystem.h>

#pragma comment(lib,"winmm.lib")

//#include ����ͷ�ļ�

//#pragma comment��lib."�ļ�����"��  �������ļ�



#define WND_WIDTH  1000

#define WND_HEIGHT 600

#define PI         3.1415926548

#define NUM        13



/***********�ṹ****************/

struct JET  //�̻���

{

	int x, y;      //���������

	int hx, hy;    //��ߵ�����  ��ը����

	int height;    //�߶�  ��ߵ�y �����y�Ĳ�ֵ

	bool isshoot;  //�Ƿ���״̬



	DWORD t1, t2, dt;   //����ʱ��  ʱ������������������ٶ�

	IMAGE img[2];       //�����̻�һ��һ����ͼƬ

	byte n : 1;         //�����̻���������״̬  λ��

	//�ֽ�Ϊ��λ int 4 char 1 nһ��λ 0-1

}jet[NUM];    //�ṹ������13  img�������



struct FIRE

{

	int r;

	int max_r;

	int x, y;

	int cen_x, cen_y;

	int width, height;

	int xy[240][240];



	bool show;

	bool draw;

	DWORD t1, t2, dt;

}fire[NUM];



void welcome();

void init(int i);

void loadimages();

void choice(DWORD& t1);

void shoot();

void Show(DWORD * pMem); 


#pragma once
