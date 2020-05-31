#include "cocos2d.h"
#include "ThePopSprite.h"
USING_NS_CC;

class MyScene : public cocos2d::Scene
{
public:
	//���ɳ���
	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();
	//�رհ�ť
	void menuCloseCallback(cocos2d::Ref* pSender);
	//������Ϸ����
	void createPopSprite(Size size);
    //����
	CREATE_FUNC(MyScene);
private:
	PopSprite* popStarSprite[10][10];
};

