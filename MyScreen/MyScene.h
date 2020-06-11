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
	//���ɾ���,��Ч
	void createPop(int color, int width, int height, int x, int y);
	//������Ϸ����
	void createPopSquare(Size size);
	//��ÿһ�����鵽������
	void fillSquare(int x, int y);
	//���Ƶ�ͼ
	void drawSquare();
    //�������
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	//�Ƿ����ڽ����Ƴ������
	bool isRemoving;
	bool isFilling;
	//�Ƿ�����Ҫ���
	bool isNeedFill;
	//��������
	//void swap(PopSprite* touchPopBegin,PopSprite* touchPopEnd);
	CREATE_FUNC(MyScene);
private:
	//ɫ�鷽��
	PopSprite* popSquare[squareWidth][squareHeight];
	//����Ƿ��п��������ľ���
	void checkPopCanRemove();
	//��ǿ����Ƴ��ľ��飬��Ч��
	void markPopRemove(PopSprite* pop);
	//�Ƴ�����
	void removePop();
	//��ը�Ƴ�Ч��
	void explodeSprite(PopSprite* pop);
	// ���Ƴ��ľ�����еĲ���
	void actionEndCallback(Node* node);
	// ������
	void getYCheck(PopSprite* pop, std::list<PopSprite*>& iList);
	// ������
	void getXCheck(PopSprite* pop, std::list<PopSprite*>& iList);
	// ���ȱ
	void fillSprite(Size size);
	//��ȡpop������ϵ��λ��
	Point getPositionOfPop(Size size, int row, int col);
	//��ȡ�����λ�õķ���
	PopSprite* getPopStarSprite(Size size, Point touch);
	//�����λ��
	Point touchBeginPosition = Point(-1,-1);
	Point touchEndPosition = Point(-1,-1);
	//�����Pop
	PopSprite* touchPopBegin;
	PopSprite* touchPopEnd;
	//״̬��
	bool canTouch;
	bool secondTouch;
};

