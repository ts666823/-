#define KIND_OF_POP 6

#include "cocos2d.h"
USING_NS_CC;


class PopSprite : public Sprite {
public:
	//��ʼ����Ϸ����ֵ����ȣ��߶ȣ�x�ᣬy��
	static PopSprite* createPopSprite(int color, int x, int y);
	virtual bool init();
	//��ȡ��ɫ�ĺ���
	int getColor();
	//������ɫ�ĺ���
	bool setColor(int colors);
	//��ȡX,Y����ĺ���
	int getPopX();
	int getPopY();
	//����X,Y����ĺ���
	bool setPopX(int x);
	bool setPopY(int y);
	//��ȡcanRemove
	bool getCanRemove();
	//����canRemove
	void setCanRemove(bool state);
	//�궨�壬�ڴ����
	CREATE_FUNC(PopSprite);
private:
	//PopSprite������
	int popX, popY;
	//�Ƿ��������
	bool canRemove = false;
	//��ɫ
	int iColor;
};

//��ʾ�ľ���ͼƬ
static const char* popNormal[KIND_OF_POP] = {
	"icon1.png",
	"icon2.png",
	"icon3.png",
	"icon4.png",
	"icon5.png",
	"icon6.png"
};


