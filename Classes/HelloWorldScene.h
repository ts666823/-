#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define MUSICKEY "musicKey"
#define SOUNDKEY "soundKey"

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	//���ֺ���Ч״̬
	int musicStatus;
	int soundStatus;
    
    //�رհ�ť
    void menuCloseCallback(cocos2d::Ref* pSender);
	//��ʼ��Ϸ��ť
	void menuNextCallback(cocos2d::Ref* pSender);
	//��Ч���ذ�ť
	/*void soundCallback(cocos2d::Ref* pSender);
	//���ֿ��ذ�ť
	void musicCallback(cocos2d::Ref* pSender);*/
    //��ʼ������
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
