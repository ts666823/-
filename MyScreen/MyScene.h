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
	//生成精灵,特效
	void createPop(int color, int width, int height, int x, int y);
	//生成游戏方阵
	void createPopSquare(Size size);
	//填每一个方块到方阵中
	void fillSquare(int x, int y);
	//绘制地图
	void drawSquare();
    //监听点击
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	//是否正在进行移除、填充
	bool isRemoving;
	bool isFilling;
	//是否有需要填充
	bool isNeedFill;
	//交换函数
	//void swap(PopSprite* touchPopBegin,PopSprite* touchPopEnd);
	CREATE_FUNC(MyScene);
private:
	//色块方阵
	PopSprite* popSquare[squareWidth][squareHeight];
	//检测是否有可以消除的精灵
	void checkPopCanRemove();
	//标记可以移除的精灵，做效果
	void markPopRemove(PopSprite* pop);
	//移除精灵
	void removePop();
	//爆炸移除效果
	void explodeSprite(PopSprite* pop);
	// 对移除的精灵进行的操作
	void actionEndCallback(Node* node);
	// 纵向检查
	void getYCheck(PopSprite* pop, std::list<PopSprite*>& iList);
	// 横向检查
	void getXCheck(PopSprite* pop, std::list<PopSprite*>& iList);
	// 填补空缺
	void fillSprite(Size size);
	//获取pop在坐标系的位置
	Point getPositionOfPop(Size size, int row, int col);
	//获取所点击位置的方块
	PopSprite* getPopStarSprite(Size size, Point touch);
	//点击的位置
	Point touchBeginPosition = Point(-1,-1);
	Point touchEndPosition = Point(-1,-1);
	//点击的Pop
	PopSprite* touchPopBegin;
	PopSprite* touchPopEnd;
	//状态量
	bool canTouch;
	bool secondTouch;
};

