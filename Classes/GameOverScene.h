#include "cocos2d.h"

USING_NS_CC;
class GameOver : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// �˳���Ϸ
	void menuCloseCallback(cocos2d::Ref* pSender);
	// ����������
	void menuMainCallback(cocos2d::Ref* pSender);
	//��ʼ������
	CREATE_FUNC(GameOver);

	//����
	int finalScore;
private:
};


