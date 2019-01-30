#pragma once

class CDrawItem
{
public:
	static const int GAMEBACK=1;//游戏背景
	static const int GAMEPASS=2;//游戏的过牌按钮
	static const int GAMEOK=3;//游戏的出牌按钮
	static const int GAMEEXIT=4;//游戏的退出按钮
	static const int CHOOSE=5;//是否当地主的按钮
	static const int LORD_FACE=6;//地主的脸
	static const int FARMER_FACE=7;//农民的脸
	static const int PASS=8;
public:
	HDC m_hBack;//游戏背景DC
	HDC m_hPassButtom;//过牌DC按钮
	HDC m_hOk;//出牌DC 
	HDC m_hExit;//退出游戏DC
	HDC m_hYesNo;//是否当地主 
	HDC m_hLordFace;
	HDC m_hFarmerFace;
	HDC m_hPass;//过牌的图片
	
	//私有方法
private:
	BOOL BitmapToDC(HDC hdc,char* fileName,int Width,int Height);
public:
	int initDrawItem();
	int DrawGameItem(HDC hdc,int x,int y,int type);
	int DrawMapText(char* text,int x,int y,COLORREF color,int size,HDC hdc);
	
public:
	CDrawItem(void);
	~CDrawItem(void);
};
