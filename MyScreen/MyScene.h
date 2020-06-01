#include "cocos2d.h"
#include "ThePopSprite.h"

//方块矩阵的宽和高
#define squareWidth  10
#define squareHeight 10

//方块的颜色
#define remove (-1);

USING_NS_CC;

class MyScene : public cocos2d::Scene
{
public:
	//生成场景
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();
	//生成游戏方阵
	void createPopSquare(Size size);
	//填每一个方块到方阵中
	void fillSquare(int x, int y);
	//绘制地图
	void drawSquare();
    //监听点击
	virtual bool onTouchBegan(Touch* touch, Event* event);
	/*virtual bool onTouchMoved(Touch* touch, Event* event);
	virtual bool onTouchEnded(Touch* touch, Event* event);*/
	CREATE_FUNC(MyScene);
private:
	//色块方阵
	PopSprite* popSquare[squareWidth][squareHeight];
	//检查方块的上下左右相连接的函数，返回到PopNearBy中
	Array* checkPopNearBy(PopSprite *PopStar);
	//可以消除
	bool canRemove = false;
	//储存某个Pop的上下左右的Pop的数组
	Array* PopNearBy;
	//获取所点击位置的方块
	PopSprite* getPopStarSprite(Size size, Point touch);
	/*//点击的位置
	Point touchBeginPosition;
	Point touchEndPosition;
	//点击的Pop
	PopSprite* touchPopBegin;
	PopSprite* touchPopEnd;
	//状态量
	bool canTouchBegin=true;
	bool canMove = false;*/
};

