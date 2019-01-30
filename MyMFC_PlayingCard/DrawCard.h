#pragma once

class CDrawCard
{
public:
	static const int g_CARDWIDTH=64;
	static const int g_CARDHEIGHT=89;
private:
	HDC m_hCardDC[15];//15个放牌的DC
//私有方法
private:
	BOOL BitmapToDC(HDC DestDC,char* fileName,int Bitmap_Width,int Bitmap_Height);
public:
	int initDrawCard();
	//将牌画出来
	int DrawCard(HDC hdc,int x,int y,int Color,int number);

	//将牌的背面画出来
	int DrawCard(HDC hdc,int x,int y);
	//画地主牌
	int DrawLordCard(HDC hdc,int index,int Color,int number,BOOL disPlay);
	
public:
	CDrawCard(void);
	~CDrawCard(void);
};
