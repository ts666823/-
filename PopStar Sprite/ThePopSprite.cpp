#include "ThePopSprite.h"
USING_NS_CC;
PopSprite* PopSprite::createPopSprite(int color,int x,int y) {
	PopSprite* pop = new PopSprite();
	if (pop && pop->init())
	{
		//ȷ��x��y����
		pop->setPopX(x);
		pop->setPopY(y);
		//ȷ����ɫ
		pop->setColor(color);
		pop->initWithSpriteFrameName(popNormal[pop->getColor()]);
		//�Զ��ͷ�
		pop->autorelease();
		return pop;
	}
	//�������enemy����ʧ��
	//ʹ��delete������ɾ��һ�������������ΪNULL���򲻽��в���
	CC_SAFE_DELETE(pop);
	return NULL;
}

bool PopSprite::init() {
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

int PopSprite::getColor()
{
	return iColor;
}

bool PopSprite::setColor(int colors)
{
	iColor = colors;
	return true;
}

int PopSprite::getPopX()
{
	return popX;
}

int PopSprite::getPopY()
{
	return popY;
}

bool PopSprite::setPopX(int x)
{
	popX = x;
	return true;
}

bool PopSprite::setPopY(int y)
{
	popY = y;
	return true;
}

bool PopSprite::getCanRemove() {
	return canRemove;
}

void PopSprite::setCanRemove(bool state) {
	canRemove = state;
}


