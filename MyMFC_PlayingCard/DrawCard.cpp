#include "StdAfx.h"
#include "DrawCard.h"
#include "CardMap.h"
CDrawCard::CDrawCard(void)
{
}

CDrawCard::~CDrawCard(void)
{
}
int CDrawCard::initDrawCard()
{
	for(int i=0;i<15;i++)
	{
		m_hCardDC[i]=::CreateCompatibleDC(NULL);
	}
	for(int i=3;i<=10;i++)
	{
		char file[50];
		sprintf(file,"bmp\\Cards\\%d.bmp",i);
		BOOL b=BitmapToDC(m_hCardDC[i-3],file,g_CARDWIDTH*4,g_CARDHEIGHT);
	}
	BitmapToDC(m_hCardDC[8],"bmp\\Cards\\J.bmp",g_CARDWIDTH*4,g_CARDHEIGHT);
	BitmapToDC(m_hCardDC[9],"bmp\\Cards\\Q.bmp",g_CARDWIDTH*4,g_CARDHEIGHT);
	BitmapToDC(m_hCardDC[10],"bmp\\Cards\\K.bmp",g_CARDWIDTH*4,g_CARDHEIGHT);
	BitmapToDC(m_hCardDC[11],"bmp\\Cards\\A.bmp",g_CARDWIDTH*4,g_CARDHEIGHT);
	BitmapToDC(m_hCardDC[12],"bmp\\Cards\\2.bmp",g_CARDWIDTH*4,g_CARDHEIGHT);
	BitmapToDC(m_hCardDC[13],"bmp\\Cards\\Jokers.bmp",g_CARDWIDTH*2,g_CARDHEIGHT);
	BitmapToDC(m_hCardDC[14],"bmp\\Cards\\card_back1.bmp",g_CARDWIDTH,g_CARDHEIGHT);

	return 1;
}
//将位图贴到DC上
BOOL CDrawCard::BitmapToDC(HDC DestDC,char* fileName,int Bitmap_Width,int Bitmap_Height)
{
	CString str;
	HBITMAP hBitmap=(HBITMAP)::LoadImage(NULL,fileName,IMAGE_BITMAP,Bitmap_Width,Bitmap_Height,LR_LOADFROMFILE);
	if(hBitmap==NULL)
	{
		str.Format("无法打开位图%s",fileName);
		AfxMessageBox(str);
		return FALSE;
	}
	if(FAILED(SelectObject(DestDC,hBitmap)))
	{
		return FALSE;
	}
	return TRUE;

}
//画牌背
int CDrawCard::DrawCard(HDC hdc,int x,int y)
{
	if(!::TransparentBlt(hdc,x,y,g_CARDWIDTH,g_CARDHEIGHT,m_hCardDC[14],
		0,0,g_CARDWIDTH,g_CARDHEIGHT,RGB(255,255,255)))
	{
		return -1;
	}
	
	return 1;
}
//画牌面
int CDrawCard::DrawCard(HDC hdc,int x,int y,int Color,int number)
{
  if(number==17)
  {
	  if(!BitBlt(hdc,x,y,g_CARDWIDTH,g_CARDHEIGHT,m_hCardDC[number-4],g_CARDWIDTH*Color,0,SRCCOPY))
		{
			 return -1;
		}

  }else if(!BitBlt(hdc,x,y,g_CARDWIDTH,g_CARDHEIGHT,m_hCardDC[number-3],g_CARDWIDTH*Color,0,SRCCOPY))
  {
	  return -1;
  }
  return 1;
}

//画地主牌
int CDrawCard::DrawLordCard(HDC hdc,int index,int Color,int number,int disPlay)
{
	if(disPlay)
	{
	switch(index)
	{
	case 1:
		if(number==17)
		{
			if(!BitBlt(hdc,CCardMap::LORD_X0,CCardMap::LORD_Y0,g_CARDWIDTH,
		g_CARDHEIGHT,m_hCardDC[number-4],g_CARDWIDTH*Color,0,SRCCOPY))
			{
				return -1;
			}
		}else if(!BitBlt(hdc,CCardMap::LORD_X0,CCardMap::LORD_Y0,g_CARDWIDTH,
		g_CARDHEIGHT,m_hCardDC[number-3],g_CARDWIDTH*Color,0,SRCCOPY))
		{
			return -1;
		}
	break;
	case 2:
		if(number==17)
		{
			if(!BitBlt(hdc,CCardMap::LORD_X1,CCardMap::LORD_Y1,g_CARDWIDTH,
			g_CARDHEIGHT,m_hCardDC[number-4],g_CARDWIDTH*Color,0,SRCCOPY))
			{
				return -1;
			}
		}else if(!BitBlt(hdc,CCardMap::LORD_X1,CCardMap::LORD_Y1,g_CARDWIDTH,
			g_CARDHEIGHT,m_hCardDC[number-3],g_CARDWIDTH*Color,0,SRCCOPY))
		{
			return -1;
		}
		break;
	case 3:
		if(number==17)
		{
			if(!BitBlt(hdc,CCardMap::LORD_X2,CCardMap::LORD_Y2,g_CARDWIDTH,
			g_CARDHEIGHT,m_hCardDC[number-4],g_CARDWIDTH*Color,0,SRCCOPY))
			{
				return -1;
			}
		}else if(!BitBlt(hdc,CCardMap::LORD_X2,CCardMap::LORD_Y2,g_CARDWIDTH,
			g_CARDHEIGHT,m_hCardDC[number-3],g_CARDWIDTH*Color,0,SRCCOPY))
		{
			return -1;
		}
		break;
	}
	}else
	{
		switch(index)
		{
		case 1:
			if(!BitBlt(hdc,CCardMap::LORD_X0,CCardMap::LORD_Y0,g_CARDWIDTH,
				g_CARDHEIGHT,m_hCardDC[14],0,0,SRCCOPY))
			{
				return -1;
			}
			break;
		case 2:
			if(!BitBlt(hdc,CCardMap::LORD_X1,CCardMap::LORD_Y1,g_CARDWIDTH,
				g_CARDHEIGHT,m_hCardDC[14],0,0,SRCCOPY))
			{
				return -1;
			}
		break;
	case 3:
		if(!BitBlt(hdc,CCardMap::LORD_X2,CCardMap::LORD_Y2,g_CARDWIDTH,
			g_CARDHEIGHT,m_hCardDC[14],0,0,SRCCOPY))
		{
			return -1;
		}
		break;
	}
	}
	return 1;
}
