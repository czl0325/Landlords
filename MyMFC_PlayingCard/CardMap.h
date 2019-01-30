#pragma once
//牌的地图类
class CCardMap
{
public:
	//游戏中心坐标
	static const int X=360;
	static const int Y=200;
	//姓名坐标
	/***/
	static const int LEFT_POINT_NAME_X=110;
	static const int LEFT_POINT_NAME_Y=510;
	static const int LEFT_POINT_SOURCE_X=235;
	static const int LEFT_POINT_SOURCE_Y=510;
	static const int LEFT_POINT_WIN_X=188;
	static const int LEFT_POINT_WIN_Y=510;

	/***/
	static const int PLAY_POINT_NAME_X=110;
	static const int PLAY_POINT_NAME_Y=526;
	static const int PLAY_POINT_SOURCE_X=235;
	static const int PLAY_POINT_SOURCE_Y=526;
	static const int PLAY_POINT_WIN_X=188;
	static const int PLAY_POINT_WIN_Y=526;

	/***/
	static const int RIGHT_POINT_NAME_X=110;
	static const int RIGHT_POINT_NAME_Y=542;
	static const int RIGHT_POINT_SOURCE_X=235;
	static const int RIGHT_POINT_SOURCE_Y=542;
	static const int RIGHT_POINT_WIN_X=188;
	static const int RIGHT_POINT_WIN_Y=542;

	/***/
	//选择谁是地主的框框的坐标
	static const int CHOOSE_X=300;
	static const int CHOOSE_Y=350;

	//标明谁是地主的三个坐标
	static const int LEFT_NAME_X=200;
	static const int LEFT_NAME_Y=170;
	static const int CENTER_NAME_X=360;
	static const int CENTER_NAME_Y=280;
	static const int RIGHT_NAME_X=520;
	static const int RIGHT_NAME_Y=170;
	//地主牌的坐标系
	static const int LORD_X0=300;
	static const int LORD_Y0=40;

	static const int LORD_X1=375;
	static const int LORD_Y1=40;
	
	static const int LORD_X2=445;
	static const int LORD_Y2=40;
	//出牌往上提的距离
	static const int UP_CARD=30;
	//玩家拿牌区
	static const int CENTER_X0=280;
	static const int CENTER_Y0=480;
	//玩家已经出过牌的放牌区
	static const int CENTER_X1=220;
	static const int CENTER_Y1=370;
	//左边玩家拿牌区
	static const int LEFT_X0=20;
	static const int LEFT_Y0=40;
	//左边玩家已经出过牌的放牌区
	static const int LEFT_X1=110;
	static const int LEFT_Y1=20;
	//右边玩家拿牌区
	static const int RIGHT_X0=710;
	static const int RIGHT_Y0=40;
   //左边玩家已经出过牌的放牌区
	static const int RIGHT_X1=630;
	static const int RIGHT_Y1=20;
	
	
	//退出游戏按钮的坐标系
	static const int EXIT_X=690;
	static const int EXIT_Y=540;
	//出牌游戏按钮的坐标系
	static const int OK_X=660;
	static const int OK_Y=480;

public:
    int m_nMoveX;//每次牌位移时的X坐标
	int m_nMoveY;//每次牌位移时的Y坐标
	RECT CenterRect[20];//中间玩家放牌的矩阵位置
	RECT CenterDisCardRect[20];//中间玩家出牌的矩阵位置

	RECT LeftRect[20];//左边玩家放牌的矩阵位置
	RECT LeftDisCardRect[20];//左边玩家出牌的矩阵位置

	RECT RightRect[20];//右边玩家放牌的矩阵位置
    RECT RightDisCardRect[20];//右边玩家出牌的矩阵位置
public:
	void InitRect();//重新初始化牌的位置 
public:
	CCardMap(void);
	~CCardMap(void);
};
