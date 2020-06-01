#include "cocos2d.h"
#include "ThePopSprite.h"

//�������Ŀ�͸�
#define squareWidth  10
#define squareHeight 10

//�������ɫ
#define remove (-1);

USING_NS_CC;

class MyScene : public cocos2d::Scene
{
public:
	//���ɳ���
	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();
	//������Ϸ����
	void createPopSquare(Size size);
	//��ÿһ�����鵽������
	void fillSquare(int x, int y);
	//���Ƶ�ͼ
	void drawSquare();
    //�������
	virtual bool onTouchBegan(Touch* touch, Event* event);
	/*virtual bool onTouchMoved(Touch* touch, Event* event);
	virtual bool onTouchEnded(Touch* touch, Event* event);*/
	CREATE_FUNC(MyScene);
private:
	//ɫ�鷽��
	PopSprite* popSquare[squareWidth][squareHeight];
	//��鷽����������������ӵĺ��������ص�PopNearBy��
	Array* checkPopNearBy(PopSprite *PopStar);
	//��������
	bool canRemove = false;
	//����ĳ��Pop���������ҵ�Pop������
	Array* PopNearBy;
	//��ȡ�����λ�õķ���
	PopSprite* getPopStarSprite(Size size, Point touch);
	/*//�����λ��
	Point touchBeginPosition;
	Point touchEndPosition;
	//�����Pop
	PopSprite* touchPopBegin;
	PopSprite* touchPopEnd;
	//״̬��
	bool canTouchBegin=true;
	bool canMove = false;*/
};

