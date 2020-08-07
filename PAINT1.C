
#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#include<ctype.h>

	int iRow=0,iCol=0,iStatus=0;
	int fColor=0,Action=1,bcolor=15;


	void initmouse(void); //initialize mouse
	void yesmouse(void); //show mouse
	void nomouse(void); //hide mouse
	void mouse(void);  //get mouse postion and button status
	void graphics_mode(void); //initialize graphic mode
	void screen(void);   //draw screen
	void titlebar(void); //draw title bar
	void toolbar(void); //draw toolbar
	void colorbar(void); // draw color bars
	void actionbox(void); //draw action box
	void colorbox(void);  // draw current colors box
	void fbcolors(int x,int y); //change colors
	void draw(int x1,int y1,int x2,int y2); //draw selected shape




void initmouse(void)
{
	iRow = 0,iCol = 0,iStatus = 0;
	asm {
		mov ax,0;
		int 0x33;
	}
}
void yesmouse(void)
{
	asm {
		 mov ax,1;
		 int 0x33;
	}
}



void nomouse(void)
{
	asm {
		 mov ax,2;
		 int 0x33;
	}
}



void mouse(void)
{
	 asm {
		  mov ax,3;
		  int 0x33;
		  mov iRow,dx;
		  mov iCol,cx;
		  mov iStatus,bx;
	 }
}


void graphics_mode(void)
{


   int gdriver = DETECT, gmode, errorcode;


   initgraph(&gdriver, &gmode, "");


   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }

}

void titlebar(void)
{
	setfillstyle(3,3);
	bar(0,0,640,20);

	setcolor(15);
	rectangle(621,3,636,18);
	line(621,3,636,18);
	line(636,3,621,18);

	settextstyle(1,0,1);
	outtextxy(295,0,"PAINT 1.0");
}

void actionbox(void)
{
	setfillstyle(1,7);
	bar(0,200,79,225);

	setcolor(1);
	settextstyle(2,0,5);
	if(Action==1) {outtextxy(10,200,"Rectangle");}
	if(Action==2) {outtextxy(10,200,"Circle");}
	if(Action==3) {outtextxy(10,200,"Line");}
	if(Action==4) {outtextxy(10,200,"Bar");}
	if(Action==5) {outtextxy(10,200,"Arc");}
	if(Action==6) {outtextxy(10,200,"Pixels");}
	if(Action==7) {outtextxy(10,200,"PieSlice");}
	if(Action==8) {outtextxy(10,200,"Bar3D");}
}

void colorbox(void)
{
	setfillstyle(1,fColor);
	bar(20,250,40,270);
	setcolor(0);
	rectangle(20,250,40,270);
}

void toolbar(void)
{
	setfillstyle(1,7);
	bar(0,21,79,435);
	setcolor(0);

	rectangle(12,30,32,50);
	rectangle(42,30,62,50);
	rectangle(12,62,32,82);
	rectangle(42,62,62,82);
	rectangle(12,92,32,112);
	rectangle(42,92,62,112);
	rectangle(12,122,32,142);
	rectangle(42,122,62,142);

	rectangle(16,33,28,46);
	circle(52,40,8);
	line(15,80,27,64);
	setfillstyle(1,0);
	bar(46,64,58,80);
	arc(22,102,0,170,5);
	settextstyle(1,0,1);
	  outtextxy(52,85,".");

	pieslice(22,132,0,170,5);
	bar3d(45,126,56,140,3,1);

	settextstyle(1,0,1);
	outtextxy(8,170,"Action");
	actionbox();
	setcolor(0);
	settextstyle(1,0,1);
	outtextxy(8,222,"Color");

	setcolor(2);
	rectangle(4,280,70,305);
	outtextxy(8,280,"Eraser");

       //	setfillstyle(1,15);
       //	bar(20,310,40,330);

	colorbox();

}

void colorbar(void)
{
	int ccount;

	setfillstyle(1,7);
	bar(0,436,640,480);
	for(ccount=0;ccount<16;ccount++)
		{
		setfillstyle(1,ccount);
		bar(80+(ccount*20),441,80+(ccount*20)+15,456);

		setcolor(0);
		rectangle(80+(ccount*20),441,80+(ccount*20)+15,456);

	}
	settextstyle(2,0,5);
	outtextxy(2,441,"Fore Colors");

	setfillstyle(1,0);
	bar(550,441,565,456);
}


void screen(void)
{
	setfillstyle(1,bcolor);
	bar(80,21,640,435);

	titlebar();
	toolbar();
	colorbar();
}

void fbcolors(int x,int y)
{

if((y>=441) && (y<=456))
{
	if((x>=80) && (x<=95)) {fColor=0;}
	if((x>=100) && (x<=115)) {fColor=1;}
	if((x>=120) && (x<=135)) {fColor=2;}
	if((x>=140) && (x<=155)) {fColor=3;}
	if((x>=160) && (x<=175)) {fColor=4;}
	if((x>=180) && (x<=195)) {fColor=5;}
	if((x>=200) && (x<=215)) {fColor=6;}
	if((x>=220) && (x<=235)) {fColor=7;}
	if((x>=240) && (x<=255)) {fColor=8;}
	if((x>=260) && (x<=275)) {fColor=9;}
	if((x>=280) && (x<=295)) {fColor=10;}
	if((x>=300) && (x<=315)) {fColor=11;}
	if((x>=320) && (x<=335)) {fColor=12;}
	if((x>=340) && (x<=355)) {fColor=13;}
	if((x>=360) && (x<=375)) {fColor=14;}
	if((x>=380) && (x<=395)) {fColor=15;}
}

colorbox();
}


void draw(int x1,int y1,int x2,int y2)
{

int i,j,radius;
radius=sqrt(pow((x2-x1),2)+pow((y2-y1),2));

setcolor(fColor);
setfillstyle(1,fColor);


nomouse();

if(Action==1) rectangle(x1,y1,x2,y2);
if(Action==2) circle(x1,y1,radius);
if(Action==3) line(x1,y1,x2,y2);
if(Action==4) bar(x1,y1,x2,y2);

if(Action==5)
{
arc(x1+(x2-x1),y1+(y2-y1),0,180,radius/2);
}

if(Action==6)
{
// for(i=0;i<30;i++)
 //{
   for(j=0;j<30;j++)
   {
putpixel(x1,y1,fColor);
putpixel(x1,y1,fColor);
putpixel(x1,y1,fColor);
putpixel(x1,y1,fColor);
   }
 //}
}

if(Action==7)
{
pieslice(x1+(x2-x1),y1+(y2-y1),0,180,radius/2);
}

if(Action==8)
{
bar3d(x1,y1,x2,y2,radius/4,1);
}
if(Action==9)
{

 setfillstyle(1,15);
 setcolor(15);
 bar(x1,y1,x2,y2);

}
titlebar();
toolbar();
colorbar();

yesmouse();
}

void main(void)
{
	int x1,y1,x2,y2;

	initmouse();
	graphics_mode();
	screen();
	yesmouse();

	while(1)
	{
		mouse();

		if((iRow>=3) && (iRow<=18) && (iCol>=621) && (iCol<=636) && (iStatus==1))
		{
		closegraph();
		exit(0);     //end program
		}

		if((iRow>=441) && (iRow<=476) && (iCol>=80) && (iCol<=395) && (iStatus==1))
		{
		fbcolors(iCol,iRow);
		}

		if((iRow>=30) && (iRow<=50) && (iCol>=12) && (iCol<=32) && (iStatus==1))
		{
		Action=1;
		actionbox();
		}

		if((iRow>=30) && (iRow<=50) && (iCol>=42) && (iCol<=62) && (iStatus==1))
		{
		Action=2;
		actionbox();
		}

		if((iRow>=62) && (iRow<=82) && (iCol>=12) && (iCol<=32) && (iStatus==1))
		{
		Action=3;
		actionbox();
		}

		if((iRow>=62) && (iRow<=82) && (iCol>=42) && (iCol<=62) && (iStatus==1))
		{
		Action=4;
		actionbox();
		}

		if((iRow>=92) && (iRow<=112) && (iCol>=12) && (iCol<=32) && (iStatus==1))
		{
		Action=5;
		actionbox();
		}

		if((iRow>=92) && (iRow<=112) && (iCol>=42) && (iCol<=62) && (iStatus==1))
		{
		Action=6;
		actionbox();
		}
		if((iRow>=122) && (iRow<=142) && (iCol>=12) && (iCol<=32) && (iStatus==1))
		{
		Action=7;
		actionbox();
		}
		if((iRow>=122) && (iRow<=142) && (iCol>=42) && (iCol<=62) && (iStatus==1))
		{
		Action=8;
		actionbox();
		}

		if((iRow>=280) && (iRow<=305) && (iCol>=4) && (iCol<=70) && (iStatus==1))
		{
		Action=9;

		}

		if((iRow>=21) && (iRow<=435) && (iCol>=81) && (iCol<=640) && (iStatus==1))
		{
			y1=iRow;
			x1=iCol;
			if(Action!=6)
				{
					while(iStatus!=0)
					mouse();
				}
			y2=iRow;
			x2=iCol;
			draw(x1,y1,x2,y2);
		}
		if((iRow>=441)&&(iRow<=456)&&(iCol>=550)&&(iCol<=565)&&(iStatus==1))
		  {
		    floodfill(100,100,4);
		    }

	}   //end of while(1) loop

}   //end of code :)
