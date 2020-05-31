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
	//������Ϸ����
	void createPopSprite(Size size);
    //�������
	virtual bool onTouchBegan(Touch* touch, Event* event);
	CREATE_FUNC(MyScene);
private:
	//ɫ�鷽��
	PopSprite* popStarSprite[10][10];
	//��鷽����������������ӵĺ��������ص�PopNearBy��
	Array* checkPopNearBy(PopSprite *PopStar);
	//����ĳ��Pop���������ҵ�Pop������
	Array* PopNearBy;
	//��ȡ�����λ�õķ���
	PopSprite* getPopStarSprite(Size size, Point touch);
};

