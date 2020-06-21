#include "cocos2d.h"
#include "cocos-ext.h"
#include"ThePopSprite.h"

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
	static cocos2d::Scene* createScene(int last_sceneNum);

	//��ʼ��
	virtual bool init();

	void menuPauseCallback(CCObject* pSender);

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

	CREATE_FUNC(MyScene);

protected:
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
	void specialXExplode(Size size, PopSprite* pop);
	void specialYExplode(Size size, PopSprite* pop);

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
	int iTime = 10;


	//��ʱ����
	void timeCount(float dt);

	bool is_pause = false;

	//�޶�����
	int stepLeft=5;

	//�����޶�������
	int limitScore=250;

	//����
	int iScore = 0;

	//��ǰ����
	int sceneNum;

	
	//�����
	SpriteBatchNode* spriteSheet;
};

