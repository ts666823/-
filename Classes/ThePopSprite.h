#define KIND_OF_POP 6

//横向消除和纵向消除精灵
#define X_REMOVE_POP 1
#define Y_REMOVE_POP 2

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
	//设置精灵是否为特殊精灵
	void setStatus(int status);
	//获取精灵是否为特殊精灵‘
	int getStatus();
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
	//获取isNew
	bool getIsNew();
	//设置isNew
	void setIsNew(bool state);
	//宏定义，内存管理
	CREATE_FUNC(PopSprite);
private:
	//PopSprite的坐标
	int popX, popY;
	//是否可以消除
	bool canRemove = false;
	//颜色
	int iColor;
	//状态，是否为特殊精灵
	int iStatus;
	//是否为新生成的精灵
	bool isNew;
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
//横向消除的精灵
static const char* XReomvePop[KIND_OF_POP] = {
	"icon1_h.png",
	"icon2_h.png",
	"icon3_h.png",
	"icon4_h.png",
	"icon5_h.png",
	"icon6_h.png"
};

//纵向消除的精灵
static const char* YRemovePop[KIND_OF_POP] = {
	"icon1_z.png",
	"icon2_z.png",
	"icon3_z.png",
	"icon4_z.png",
	"icon5_z.png",
	"icon6_z.png"
};