#include "cocos2d.h"
USING_NS_CC;
class Gamepause : public cocos2d::CCLayer
{
public:
	virtual bool init();
	static cocos2d::CCScene* scene(CCRenderTexture* sqr);
	CREATE_FUNC(Gamepause);
	//������Ϸ
	void menuContinueCallback(CCObject* pSender);
	//���¿�ʼ��Ϸ
	void menuRestart(CCObject* pSender);
	//��������
	void menuLogin(CCObject* pSender);
private:

};