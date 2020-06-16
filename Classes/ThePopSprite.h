#define KIND_OF_POP 6

//����������������������
#define X_REMOVE_POP 1
#define Y_REMOVE_POP 2

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
	//���þ����Ƿ�Ϊ���⾫��
	void setStatus(int status);
	//��ȡ�����Ƿ�Ϊ���⾫�顮
	int getStatus();
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
	//��ȡisNew
	bool getIsNew();
	//����isNew
	void setIsNew(bool state);
	//�궨�壬�ڴ����
	CREATE_FUNC(PopSprite);
private:
	//PopSprite������
	int popX, popY;
	//�Ƿ��������
	bool canRemove = false;
	//��ɫ
	int iColor;
	//״̬���Ƿ�Ϊ���⾫��
	int iStatus;
	//�Ƿ�Ϊ�����ɵľ���
	bool isNew;
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
//���������ľ���
static const char* XReomvePop[KIND_OF_POP] = {
	"icon1_h.png",
	"icon2_h.png",
	"icon3_h.png",
	"icon4_h.png",
	"icon5_h.png",
	"icon6_h.png"
};

//���������ľ���
static const char* YRemovePop[KIND_OF_POP] = {
	"icon1_z.png",
	"icon2_z.png",
	"icon3_z.png",
	"icon4_z.png",
	"icon5_z.png",
	"icon6_z.png"
};