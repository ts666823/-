#include "cocos2d.h"
USING_NS_CC;
class PopSprite : public Sprite{
public:
	//��ʼ����Ϸ����ֵ����ȣ��߶ȣ�x�ᣬy��
	static PopSprite* createPopSprite(int color,int width,int height,float popSpriteX,float popSpriteY);
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
	//��ȡĳ��PopSpriteλ�õĺ���,��point��ʽ����
	Point getPoint();
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
	//˽�л��ĳ�ʼ����
	bool privateInit(int color,int width, int height, float popSpriteX, float popSpriteY);
	//��ʾ����ɫ
	LayerColor* ColorBlock;
};

