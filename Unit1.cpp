﻿//---------------------------------------------------------------------------
#include<time.h>
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int sum=0;
int  time1=60;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{   r_num=5;
	time_t t;
	srand((unsigned) time(&t));    //為亂樹種子(沒有他值就固定)
	for(int i=0;i<r_num;i++)
		{
			for(int y=0;y<r_num;y++)
			{
			img[i][y]=NULL;
			}
		}
		Label2->Caption=IntToStr(time1);
}
void TForm1::check()
{
	for(int i=0;i<r_num;i++)
		{
			for(int j=0;j<(r_num-2);j++)
			{
				if(a[i][j+2]==a[i][j]&&a[i][j]==a[i][j+1])  //橫
				{
					hit[i][j+2]=2;
					hit[i][j+1]=2;
					hit[i][j]=2;
					a[i][j+2]=5;
					a[i][j+1]=5;
					a[i][j]=5;
					img[i][j+2]->Picture->LoadFromFile("5.png");
					img[i][j+1]->Picture->LoadFromFile("5.png");
					img[i][j]->Picture->LoadFromFile("5.png");
					break;
				}
				if(a[j+1][i]==a[j][i]&&a[j][i]==a[j+2][i])  //直
				{
					hit[j+2][i]=2;
					hit[j+1][i]=2;
					hit[j][i]=2;
					a[j+2][i]=5;
					a[j+1][i]=5;
					a[j][i]=5;
					img[j][i]->Picture->LoadFromFile("5.png");
					img[j+2][i]->Picture->LoadFromFile("5.png");
					img[j+1][i]->Picture->LoadFromFile("5.png");
                    break;
				}
			}
		}
        dd=true;
}
void TForm1::number() //生成圖片編號
{
		String  str="";
		for(int i=0;i<r_num;i++)
		{
			for(int j=0;j<r_num;j++)
			{
				hit[i][j]=0;
				a[i][j]=(rand()%4)+1;
				str+=a[i][j];
			}
		   Memo2->Lines->Add(str);
		   str="";
		}
}
void TForm1::show()   //是否按到
{
	String  str="";
		for(int i=0;i<r_num;i++)
		{
		for(int j=0;j<r_num;j++)
		{
			str+=hit[i][j];
		}
			Memo1->Lines->Add(str);
			str="";
		}
			Memo1->Lines->Add("\r\n");
}
void TForm1::checkch()       //確認是否可換
{
	String ch;
	for(int i=0;i<r_num;i++)
	{
	  for(int j=0;j<r_num;j++)
		{
		if(hit[i][j]==hit[i][j+1]&&hit[i][j+1]==1)
		 {
			ch=a[i][j];
			a[i][j]=a[i][j+1];
			a[i][j+1]=ch;
			img[i][j+1]->Picture->LoadFromFile(a[i][j+1]+".png");
			img[i][j]->Picture->LoadFromFile(a[i][j]+".png");
            state=true;
		 }
		else if(hit[i+1][j]==hit[i][j]&&hit[i+1][j]==1)
		 {
		  ch=a[i][j];
		  a[i][j]=a[i+1][j];
		  a[i+1][j]=ch;
		  img[i][j]->Picture->LoadFromFile(a[i][j]+".png");
		  img[i+1][j]->Picture->LoadFromFile(a[i+1][j]+".png");
		  state=true;
		}
	  }
	}
}
void TForm1::image()      //生成圖片
{
	int b=0;
		for(int i=0;i<r_num;i++)
	{
		for(int j=0;j<r_num;j++)
		{

		if(img[i][j]!=NULL)
		return;
		img[i][j]=new TImage(this);
		img[i][j]->Picture->LoadFromFile(a[i][j]+".png");
		img[i][j]->Stretch=True;
		img[i][j]->Top=100+i*80;
		img[i][j]->Left=100+j*80;
		img[i][j]->Height=70;
		img[i][j]->Width=70;
		img[i][j]->Tag=b;
		img[i][j]->Parent=this;
		img[i][j]->OnClick=AAA;
		b++;
		}
	}
}//---------------------------------------------------------------------------
void TForm1::down()
{        String str="";
		 String ch;
		for(int i=0;i<r_num;i++)
		{
			for(int j=0;j<r_num;j++)
			{  str+=a[i][j];
				if(hit[i][j]==2||a[i][j]==5)
				{
					 for(int aa=i;aa>0;aa--)
					 {
						hit[aa][j]=0;
						hit[aa-1][j]=2;
						ch=a[aa][j];
						a[aa][j]=a[aa-1][j];
						a[aa-1][j]=ch;
						img[aa-1][j]->Picture->LoadFromFile(a[aa-1][j]+".png");
						img[aa][j]->Picture->LoadFromFile(a[aa][j]+".png");
					 }
					 if(i==0)
						{
							hit[i][j]=0;
							a[i][j]=(rand()%4)+1;
							img[i][j]->Picture->LoadFromFile(a[i][j]+".png");
						}
				}
			}
			Memo2->Lines->Add(str);
			str="";
		}
		 Memo2->Lines->Add("\r\n");
dd=false;
}
void __fastcall TForm1::Button1Click(TObject *Sender)    //開始遊戲
{       Timer1->Enabled=true;
		Timer2->Enabled=true;
		Timer4->Enabled=true;
		time1=60;
		String  str="";
		number();
		for(int i=0;i<r_num;i++)
		{
			for(int j=0;j<r_num;j++)
			{
				str+=a[i][j];
			}
				str="";
		}
		image();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{   if(state==true)
		noch();
	else
	  checkch();

	 if(dd==true)
		down();
     if(dd==false)
	  check();

      end_ok();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::AAA(TObject *Sender)    //判斷按下
{
	 TImage *img;
	 img=(TImage *)Sender;
	 int aa=0;
	 int b=0;
	 int c=0 ;
	 c=img->Tag;
	 aa= c/r_num;
	 b=(c%r_num);
	 hit[aa][b]=1;
}
void TForm1::dele() //關
{
		Timer1->Enabled=false;
	  for (int i = 0; i < r_num; i++)
	  {
		  for (int j = 0; j < r_num; j++)
		{
		  if(img[i][j]!=NULL)
		   {
			delete img[i][j];
		   }
		}
	  }
}
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)  //關
{
	dele();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)    //清除點擊
{
	for(int x=0;x<r_num;x++)
	{ for(int y=0;y<r_num;y++)
		{
			hit[x][y]=0;
		}
	}
}
//---------------------------------------------------------------------------
void  TForm1::noch()
{   String ch="";
	for(int i=0;i<r_num;i++)
	{
	  for(int j=0;j<r_num;j++)
		{
		   if(hit[i][j]==1)
		   {
				if(hit[i][j+1]==hit[i][j])
				{
					hit[i][j]=0;
					hit[i][j+1]=0;
					ch=a[i][j];
					a[i][j]=a[i][j+1];
					a[i][j+1]=ch;
					img[i][j+1]->Picture->LoadFromFile(a[i][j+1]+".png");
					img[i][j]->Picture->LoadFromFile(a[i][j]+".png");
					state=false;
				}
			   else if(hit[i][j-1]==hit[i][j])
				{
					hit[i][j]=0;
					hit[i][j-1]=0;
					ch=a[i][j];
					a[i][j]=a[i][j-1];
					a[i][j-1]=ch;
					img[i][j-1]->Picture->LoadFromFile(a[i][j-1]+".png");
					img[i][j]->Picture->LoadFromFile(a[i][j]+".png");
					state=false;
				}
				else if(hit[i+1][j]==hit[i][j])
				{
					hit[i][j]=0;
					hit[i+1][j]=0;
					ch=a[i][j];
					a[i][j]=a[i+1][j];
					a[i+1][j]=ch;
					img[i][j]->Picture->LoadFromFile(a[i][j]+".png");
					img[i+1][j]->Picture->LoadFromFile(a[i+1][j]+".png");
					state=false;
				}
				else if (hit[i-1][j]==hit[i][j])
				{
					hit[i][j]=0;
					hit[i-1][j]=0;
					ch=a[i][j];
					a[i][j]=a[i-1][j];
					a[i-1][j]=ch;
					img[i][j]->Picture->LoadFromFile(a[i][j]+".png");
					img[i-1][j]->Picture->LoadFromFile(a[i-1][j]+".png");
					state=false;
				}
			}
		 }
	}
}
void  TForm1::end(int i,int j,int x,int y)
{
		if (
		( a[x-1][y]==a[i][j]&&a[i][j]==a[x+1][y])
		|| (a[x][y-1]==a[i][j]&&a[i][j]==a[x][y+1])
		|| (a[x-2][y]==a[x-1][y]&&a[x-1][y]==a[i][j]&& i-2>=0)
		|| (a[x][y-2]==a[x][y-1]&&a[x][y-1]==a[i][j]&& j-2>=0)
		|| (a[x+2][y]==a[x+1][y]&&a[x+1][y]==a[i][j]&& i+2<r_num)
		|| (a[x][y+2]==a[x][y+1]&&a[x][y+1]==a[i][j]&&j+2<r_num)
		)
		{
			sum++;
		}
}
//---------------------------------------------------------------------------
void  TForm1::end_ok()
{                        //------------------新舊都要傳-------------
   sum=0;
	for(int i=0;i<r_num;i++)
	{
	  for(int j=0;j<r_num;j++)
		{
			end(i+1,j,i,j);  //下
			end(i-1,j,i,j); //上
			end(i,j+1,i,j); //又
			end(i,j-1,i,j);//左
		}
	}
	if(sum==0)
	{   Timer1->Enabled=false;
		Timer2->Enabled=false;
		Timer4->Enabled=false;
		ShowMessage("沒得消了");
	}
}
void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
	 show();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
  time1=60;
  if(Timer1->Enabled!=true)
	Timer1->Enabled=true;
	if(Timer2->Enabled!=true)
	Timer2->Enabled=true;
	if(Timer4->Enabled!=true)
	Timer4->Enabled=true;
	number();
		for(int i=0;i<r_num;i++)
		 {
			for(int j=0;j<r_num;j++)
			{
			  img[i][j]->Picture->LoadFromFile(a[i][j]+".png");
			}
		 }
         end_ok();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer4Timer(TObject *Sender)
{
   	time1--;
	Label2->Caption=IntToStr(time1);
	if(time1==0)
	{     Timer1->Enabled=false;
		  Timer2->Enabled=false;
		  Timer4->Enabled=false;
		  ShowMessage("時間到了");
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
for(int i=0;i<r_num;i++)
		 {
			for(int j=0;j<r_num;j++)
			{
			  img[i][j]->Picture->LoadFromFile(ab[i][j]+".png");
			}
		 }

}
//---------------------------------------------------------------------------

