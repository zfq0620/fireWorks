/*******************************

�ļ����ƣ�main.cpp

�ļ�������ʵ��һ��ģ���̻����ŵĳ���

ͼ�ν��棺easyX

<2020.1.1> <��������--�޸�>

*******************************/

#include"main.h"


int main()

{

	initgraph(WND_WIDTH, WND_HEIGHT);       //init��ʼ��  graphͼ�ν��� ����

	srand((unsigned int)time(NULL));

	DWORD t1 = timeGetTime();

	DWORD* pMem = GetImageBuffer();

	//��һ������

	welcome();

	

	//��ʼ��

	for (int i = 0; i < NUM; i++)

	{

		init(i);

	}



	loadimages();

	//wav �̻����ֲ���
	PlaySound(L".\\res\\1.WAV", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	BeginBatchDraw();

	while (!_kbhit())

	{

		//Sleep(10);

		for (int i = 0; i < 1000; i++)

		{

			for (int j = 0; j < 3; j++)

			{



				int px1 = rand() % 1000;

				int py1 = rand() % 600;



				if (py1 < 599)

				{

					pMem[py1 * 1000 + px1] = pMem[py1 * 1000 + px1 + 1] = BLACK;

				}

			}

		}
	
		choice(t1);

		shoot();

		Show(pMem);

		EndBatchDraw();

	}

	return 0;

}



void welcome()

{

	settextcolor(YELLOW);



	for (int i = 0; i < 50; i++)

	{

		//Բ�ģ�500,300�� �뾶150  60�����ȵ��x,y

		int x = 500 + int(150 * sin(PI * 2 * i / 60));

		int y = 300 + int(150 * cos(PI * 2 * i / 60));

		cleardevice();

		settextstyle(i, 0, L"΢���ź�");

		outtextxy(x - 100, y - 150, L"δ����ÿһ��һ��ӡ");     //��ָ����λ��ȥ����ַ�

		outtextxy(x, y - 100, L"̤�ű˴�����ǰ��");

		Sleep(25);

		//�ܽ� ��� ��Ϸ ����Ķ��� ���ԣ�������

	}



	//_getch();   //�����ַ� ������ ֱ�ӽ���

	Sleep(2000);

	cleardevice();

	settextstyle(25, 0, L"����");

	outtextxy(400, 150, L"Ը���䣬");

	outtextxy(400, 200, L"��������أ�");

	outtextxy(400, 250, L"����Ψ��һ���㣬");

	outtextxy(400, 300, L"���ֱ�ϲ��");

	outtextxy(400, 350, L"��ʧ�о������졣");

	outtextxy(560, 400, L"---z_��������");



	Sleep(1000);

	//_getch();

}



void init(int i)

{

	int r[13] = { 120,120,155,123,130,147,138,138,130,135,140,132,155 };

	int x[13] = { 120,120,110,117,110,93,102,102,110,105,100,108,110 };

	int y[13] = { 120,120,85,118,120,105,103,110,110,120,1201,04,85 };



	fire[i].x = 0;

	fire[i].y = 0;

	fire[i].width = 240;

	fire[i].height = 240;

	fire[i].max_r = r[i];

	fire[i].cen_x = x[i];

	fire[i].cen_y = y[i];

	fire[i].show = false;

	fire[i].dt = 5;

	fire[i].t1 = timeGetTime();

	fire[i].r = 0;





	//��ʼ��  �̻���

	jet[i].x = 0;

	jet[i].y = 0;

	jet[i].hx = 0;

	jet[i].hy = 0;

	jet[i].height = 0;

	jet[i].t1 = timeGetTime();   //��ȡϵͳʱ��

	jet[i].dt = rand() % 10;   //0-9�����ʱ��

	jet[i].n = 0;

	jet[i].isshoot = false;

}



void loadimages()

{

	IMAGE fm, gm;

	loadimage(&fm, L"./res/flower.jpg", 3120, 240);

	for (int i = 0; i < NUM; i++)

	{

		SetWorkingImage(&fm);

		getimage(&gm, i * 240, 0, 240, 240);

		SetWorkingImage(&gm);



		for (int a = 0; a < 240; a++)

		{

			for (int b = 0; b < 240; b++)

			{

				fire[i].xy[a][b] = getpixel(a, b);

			}

		}

	}



	IMAGE jetimg;

	loadimage(&jetimg, L"./res/shoot.jpg", 200, 50);



	//set���� working���ڹ����� imageͼƬ

	SetWorkingImage(&jetimg);



	for (int i = 0; i < NUM; i++)

	{

		int n = rand() % 5;   //0-4�������



		getimage(&jet[i].img[0], n * 20, 0, 20, 50);

		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);

	}

	SetWorkingImage(NULL);



}



void choice(DWORD& t1)

{

	DWORD t2 = timeGetTime();



	if (t2 - t1 > 100)   //100ms����һ���̻���

	{

		int n = rand() % 20;     //0-19

		if (n < NUM && jet[n].isshoot == false && fire[n].show == false)

		{

			//�����̻���

			jet[n].x = rand() % (WND_WIDTH - 20);

			jet[n].y = rand() % 100 + 400;   //450-549

			jet[n].hx = jet[n].x;

			jet[n].hy = rand() % 400;        //0-399

			jet[n].height = jet[n].y - jet[n].hy;

			jet[n].isshoot = true;



			//n

			putimage(jet[n].x, jet[n].y, &jet[n].img[jet[n].n]);

		}

		t1 = t2;

	}

}



void shoot()

{

	for (int i = 0; i < NUM; i++)

	{

		jet[i].t2 = timeGetTime();

		if (jet[i].t2 - jet[i].t1 > jet[i].dt&& jet[i].isshoot == true)

		{

			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n]);



			if (jet[i].hy < jet[i].y)

			{

				jet[i].n++;  //0-1  ��������

				jet[i].y -= 5;

			}

			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n]);



			if (jet[i].y <= jet[i].hy)

			{

				fire[i].y = jet[i].hy;

				fire[i].x = jet[i].hx;

				fire[i].show = true;

				jet[i].isshoot = false;

			}

			jet[i].t1 = jet[i].t2;

		}

	}

}



void Show(DWORD* pMem)

{

	int drt[16] = { 5,5,5,5,5,6,25,25,25,25,25,55,55,55,55,55 };    //dt



	for (int i = 0; i < NUM; i++)

	{

		fire[i].t2 = timeGetTime();



		if (fire[i].t2 - fire[i].t1 > fire[i].dt&& fire[i].show == true)

		{

			if (fire[i].r < fire[i].max_r)

			{

				fire[i].r++;

				fire[i].dt = drt[fire[i].r / 10];

				fire[i].draw = true;

			}



			if (fire[i].r >= fire[i].max_r - 1)

			{

				fire[i].draw = false;

				init(i);

			}

			fire[i].t1 = fire[i].t2;

		}



		if (fire[i].draw)

		{

			for (double a = 0; a <= 6.28; a += 0.01)

			{

				int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a));

				int y1 = (int)(fire[i].cen_y + fire[i].r * sin(a));



				if (x1 > 0 && x1 < fire[i].width && y1>0 && y1 < fire[i].height)

				{

					int b = fire[i].xy[x1][y1] & 0xff;

					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;

					int r = (fire[i].xy[x1][y1] >> 16);

					int xx = (int)(fire[i].x + fire[i].r * cos(a));

					int yy = (int)(fire[i].y + fire[i].r * sin(a));



					if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1000 && yy < 600 && yy>0)

					{

						pMem[yy * 1000 + xx] = BGR(fire[i].xy[x1][y1]);

					}

				}

			}

			fire[i].draw = true;

		}

	}



}