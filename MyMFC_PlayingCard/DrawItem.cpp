#include "StdAfx.h"
#include "DrawItem.h"

CDrawItem::CDrawItem(void)
{
}

CDrawItem::~CDrawItem(void)
{
}
int CDrawItem::initDrawItem()
{
	m_hBack=::CreateCompatibleDC(NULL);
	m_hPassButtom=::CreateCompatibleDC(NULL);
	m_hOk=::CreateCompatibleDC(NULL);
	m_hExit=::CreateCompatibleDC(NULL);
	m_hYesNo=::CreateCompatibleDC(NULL);
	m_hLordFace=::CreateCompatibleDC(NULL);
	m_hFarmerFace=::CreateCompatibleDC(NULL);
	m_hPass=::CreateCompatibleDC(NULL);
	BitmapToDC(m_hBack,"bmp\\Game_Back.bmp",800,600);
    BitmapToDC(m_hPassButtom,"bmp\\Cards\\item\\Pass_Button.bmp",80,30);
	BitmapToDC(m_hOk,"bmp\\Cards\\item\\Ok_Button.bmp",80,30);
	BitmapToDC(m_hExit,"bmp\\Cards\\item\\退出游戏.bmp",100,30);
	BitmapToDC(m_hYesNo,"bmp\\Cards\\item\\choose_lord.bmp",200,80);
	BitmapToDC(m_hLordFace,"bmp\\Lord.bmp",90,80);
	BitmapToDC(m_hFarmerFace,"bmp\\Farmer.bmp",90,80);
	BitmapToDC(m_hPass,"bmp\\PASS.bmp",70,30);
	return 1;
}
BOOL CDrawItem::BitmapToDC(HDC hdc,char *fileName,int Width,int Height)
{
	HBITMAP hBitmap=(HBITMAP)::LoadImage(NULL,fileName,IMAGE_BITMAP,Width,
		Height,LR_LOADFROMFILE);
	CString str;
	if(hBitmap==NULL)
	{
		str.Format("无法载入图片%s",fileName);
		return FALSE;
	}
	if(FAILED(::SelectObject(hdc,hBitmap)))
	{
		return FALSE;
	}
	return TRUE;
}
int CDrawItem::DrawGameItem(HDC hdc,int x,int y,int type)
{
  switch(type)
  {
  case GAMEBACK:
	  if(!BitBlt(hdc,x,y,800,600,m_hBack,0,0,SRCCOPY))
	  {
		  return -1;
	  }
	  break;
  case GAMEPASS:
	  if(!BitBlt(hdc,x,y,80,30,m_hPassButtom,0,0,SRCCOPY))
	  {
		  return -1;
	  }
	  break;
  case GAMEOK:
	  if(!BitBlt(hdc,x,y,80,30,m_hOk,0,0,SRCCOPY))
	  {
		  return -1;
	  }
	  break;
  case GAMEEXIT:
	  if(!TransparentBlt(hdc,x,y,100,30,m_hExit,0,0,100,30,RGB(255,255,255)))
	  {
		  return -1;
	  }
	  break;
  case LORD_FACE:
	  if(!BitBlt(hdc,x,y,90,80,m_hLordFace,0,0,SRCCOPY))
	  {
		  return -1;
	  }
	  break;
  case FARMER_FACE:
	  if(!BitBlt(hdc,x,y,90,80,m_hFarmerFace,0,0,SRCCOPY))
	  {
		  return -1;
	  }
	  break;
  case CHOOSE:
	  if(!BitBlt(hdc,x,y,200,80,m_hYesNo,0,0,SRCCOPY))
	  {
		  return -1;
	  }
	  break;
  case PASS:
	  if(!TransparentBlt(hdc,x,y,70,30,m_hPass,0,0,70,30,RGB(255,255,255)))
	  {
		  return -1;
	  }
	  break;
  }
  return 1;
}
int CDrawItem::DrawMapText(char *text, int x, int y, 
						   COLORREF color, int size, HDC hdc)
{
	LOGFONT my_Font;
	memset(&my_Font,0,sizeof(my_Font));
	//lfCharSet制定字符集
	my_Font.lfCharSet=DEFAULT_CHARSET;
	my_Font.lfHeight=size;
    
	HFONT hFont;
	hFont=::CreateFontIndirect(&my_Font);
	SelectObject(hdc,hFont);
	
	SetTextColor(hdc,color);
	SetBkMode(hdc,TRANSPARENT);
	TextOut(hdc,x,y,text,strlen(text));

return 1;
}