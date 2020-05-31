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
	//关闭按钮
	void menuCloseCallback(cocos2d::Ref* pSender);
	//生成游戏方阵
	void createPopSprite(Size size);
    //监听
	CREATE_FUNC(MyScene);
private:
	PopSprite* popStarSprite[10][10];
};

