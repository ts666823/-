#include "cocos2d.h"
#include "ThePopSprite.h"

//�������Ŀ�͸�
#define SQUARE_WIDTH  8
#define SQUARE_HEIGHT 8

//����ĳ��ͼ��
#define POP_LENTH 48
#define BOARDER_WIDTH 2


USING_NS_CC;

class MyScene : public cocos2d::Scene
{
public:
	//���ɳ���
	static cocos2d::Scene* createScene();

	//��ʼ��
	virtual bool init();

	//���ɾ���,��Ч
	void createPop(Size size,int color,int x, int y);

	//������Ϸ����
	void createPopSquare(Size size);

	//��ȡpop������ϵ��λ��
	Point getPositionOfPop(Size size, int row, int col);

	//��ȡ��Ӧ�����pop
	PopSprite* getPop(Size size, Point point);

    //�������
	virtual bool onTouchBegan(Touch* touch, Event* event);

	virtual void onTouchMoved(Touch* touch, Event* event);

	//��������pop
	void swapPop();

	//��ʱ����
	void timeCount(float dt);

	CREATE_FUNC(MyScene);
private:
	//ɫ�鷽��
	PopSprite* popSquare[SQUARE_WIDTH][SQUARE_HEIGHT];

	
	//���ĳ�������������
	bool getPopChecked(PopSprite* pop);

	//����Ƿ��п��������ľ���
	void checkAndRemove();

	//��ǿ����Ƴ��ľ��飬��Ч��
	void markPopRemove(PopSprite* pop);

	//�Ƴ�����
	void removePop();

	//��ը�Ƴ�Ч��
	void explodeSprite(PopSprite* pop);

	//���⾫�������
	void specialXExplode(Size size,Point point);
	void specialYExplode(Size size,Point point);

	// ���Ƴ��ľ�����еĲ������ص�����
	void actionEndCallback(Node* node);

	// ������
	void getYCheck(PopSprite* pop, std::list<PopSprite*>& iList);

	// ������
	void getXCheck(PopSprite* pop, std::list<PopSprite*>& iList);

	// ���ȱ
	void fillSprite(Size size);

	//���µĺ���
	void update(float dt);

	//״̬��
	//�Ƿ���Դ���
	bool canTouch = true;

	//�Ƿ���ִ�в���������ʱ���ܴ���
	bool isRunningAction = false;

	//�Ƿ����ڽ����Ƴ������
	bool isRemoving = false;
	bool isFilling = false;
	bool isSwapping = false;

	//�Ƿ�����Ҫ���
	bool isNeedFill = false;

	//�����λ��
	Point touchBeginPosition = Point(-1,-1);
	Point touchEndPosition = Point(-1,-1);

	//�����Pop
	PopSprite* touchBeginPop;
	PopSprite* touchEndPop;

	//ʱ��
	int iTime= 30;
	
	//����
	int iScore = 0;
	
	//�����
	SpriteBatchNode* spriteSheet;

	
};

