#include "cocos2d.h"
#include "ThePopSprite.h"
USING_NS_CC;

class MyScene : public cocos2d::Scene
{
public:
	//生成场景
	static cocos2d::Scene* createScene();
	//初始化
	virtual bool init();
	//生成游戏方阵
	void createPopSprite(Size size);
    //监听点击
	virtual bool onTouchBegan(Touch* touch, Event* event);
	CREATE_FUNC(MyScene);
private:
	//色块方阵
	PopSprite* popStarSprite[10][10];
	//检查方块的上下左右相连接的函数，返回到PopNearBy中
	Array* checkPopNearBy(PopSprite *PopStar);
	//储存某个Pop的上下左右的Pop的数组
	Array* PopNearBy;
	//获取所点击位置的方块
	PopSprite* getPopStarSprite(Size size, Point touch);
};

