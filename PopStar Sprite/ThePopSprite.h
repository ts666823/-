#define KIND_OF_POP 6

#include "cocos2d.h"
USING_NS_CC;


class PopSprite : public Sprite {
public:
	//初始化游戏的数值，宽度，高度，x轴，y轴
	static PopSprite* createPopSprite(int color, int x, int y);
	virtual bool init();
	//获取颜色的函数
	int getColor();
	//设置颜色的函数
	bool setColor(int colors);
	//获取X,Y坐标的函数
	int getPopX();
	int getPopY();
	//设置X,Y坐标的函数
	bool setPopX(int x);
	bool setPopY(int y);
	//获取canRemove
	bool getCanRemove();
	//设置canRemove
	void setCanRemove(bool state);
	//宏定义，内存管理
	CREATE_FUNC(PopSprite);
private:
	//PopSprite的坐标
	int popX, popY;
	//是否可以消除
	bool canRemove = false;
	//颜色
	int iColor;
};

//显示的精灵图片
static const char* popNormal[KIND_OF_POP] = {
	"icon1.png",
	"icon2.png",
	"icon3.png",
	"icon4.png",
	"icon5.png",
	"icon6.png"
};


