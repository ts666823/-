#define MUSICKEY "musicKey"
#define SOUNDKEY "soundKey"

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	//音乐和音效状态
	bool musicStatus=true;
	bool soundStatus;
    
    //关闭按钮
    void menuCloseCallback(cocos2d::Ref* pSender);
	//开始游戏按钮
	void menuNextCallback(cocos2d::Ref* pSender);
	//音效开关按钮
	void soundCallback(cocos2d::Ref* pSender);
	//音乐开关按钮
	void musicCallback(cocos2d::Ref* pSender);
    //初始化方法
    CREATE_FUNC(HelloWorld);
};
