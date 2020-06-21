#include "cocos2d.h"
#include "cocos-ext.h"
#include"ThePopSprite.h"

//方块矩阵的宽和高
#define SQUARE_WIDTH  8
#define SQUARE_HEIGHT 8

//方块的长和间距
#define POP_LENTH 48
#define BOARDER_WIDTH 2


USING_NS_CC;

class MyScene : public cocos2d::Scene
{
public:
	//生成场景
	static cocos2d::Scene* createScene(int last_sceneNum);

	//初始化
	virtual bool init();

	void menuPauseCallback(CCObject* pSender);

	//生成精灵,特效
	void createPop(Size size,int color,int x, int y);

	//生成游戏方阵
	void createPopSquare(Size size);

	//获取pop在坐标系的位置
	Point getPositionOfPop(Size size, int row, int col);

	//获取对应坐标的pop
	PopSprite* getPop(Size size, Point point);

    //监听点击
	virtual bool onTouchBegan(Touch* touch, Event* event);

	virtual void onTouchMoved(Touch* touch, Event* event);

	//交换两个pop
	void swapPop();

	CREATE_FUNC(MyScene);

protected:
	//色块方阵
	PopSprite* popSquare[SQUARE_WIDTH][SQUARE_HEIGHT];

	
	//检测某个精灵可以消除
	bool getPopChecked(PopSprite* pop);

	//检测是否有可以消除的精灵
	void checkAndRemove();

	//标记可以移除的精灵，做效果
	void markPopRemove(PopSprite* pop);

	//移除精灵
	void removePop();

	//爆炸移除效果
	void explodeSprite(PopSprite* pop);

	//特殊精灵的消除
	void specialXExplode(Size size, PopSprite* pop);
	void specialYExplode(Size size, PopSprite* pop);

	// 对移除的精灵进行的操作，回调函数
	void actionEndCallback(Node* node);

	// 纵向检查
	void getYCheck(PopSprite* pop, std::list<PopSprite*>& iList);

	// 横向检查
	void getXCheck(PopSprite* pop, std::list<PopSprite*>& iList);

	// 填补空缺
	void fillSprite(Size size);

	//更新的函数
	void update(float dt);

	//状态量
	//是否可以触摸
	bool canTouch = true;

	//是否在执行操作，操作时不能触摸
	bool isRunningAction = false;

	//是否正在进行移除、填充
	bool isRemoving = false;
	bool isFilling = false;
	bool isSwapping = false;

	//是否有需要填充
	bool isNeedFill = false;

	//点击的位置
	Point touchBeginPosition = Point(-1,-1);
	Point touchEndPosition = Point(-1,-1);

	//点击的Pop
	PopSprite* touchBeginPop;
	PopSprite* touchEndPop;

	//时间
	int iTime = 10;


	//计时函数
	void timeCount(float dt);

	bool is_pause = false;

	//限定步数
	int stepLeft=5;

	//过关限定分数线
	int limitScore=250;

	//分数
	int iScore = 0;

	//当前关数
	int sceneNum;

	
	//精灵表单
	SpriteBatchNode* spriteSheet;
};

