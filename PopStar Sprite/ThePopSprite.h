#include "cocos2d.h"
USING_NS_CC;
class PopSprite : public Sprite{
public:
	//初始化游戏的数值，宽度，高度，x轴，y轴
	static PopSprite* createPopSprite(int color,int width,int height,float popSpriteX,float popSpriteY);
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
	//获取某个PopSprite位置的函数,以point形式返回
	Point getPoint();
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
	//私有化的初始方法
	bool privateInit(int color,int width, int height, float popSpriteX, float popSpriteY);
	//显示的颜色
	LayerColor* ColorBlock;
};

