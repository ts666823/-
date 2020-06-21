#include "cocos2d.h"

USING_NS_CC;
class GameOver : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// 退出游戏
	void menuCloseCallback(cocos2d::Ref* pSender);
	// 返回主界面
	void menuMainCallback(cocos2d::Ref* pSender);
	//初始化方法
	CREATE_FUNC(GameOver);

	//分数
	int finalScore;
private:
};


