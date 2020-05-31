#include "ThePopSprite.h"
USING_NS_CC;
PopSprite* PopSprite::createPopSprite(int color, int width, int height, float popSpriteX, float popSpriteY) {
	PopSprite* myPrivate = new PopSprite();
	if (myPrivate && myPrivate->init())
	{
		//�Զ��ͷ�
		myPrivate->autorelease();
		//���ɶ���
		myPrivate->privateInit(color, width, height, popSpriteX, popSpriteY);
		return myPrivate;
	}
	//�������enemy����ʧ��
	//ʹ��delete������ɾ��һ�������������ΪNULL���򲻽��в���
	CC_SAFE_DELETE(myPrivate);
	return NULL;
}

bool PopSprite::init() {
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

bool PopSprite::privateInit(int color, int width, int height, float popSpriteX, float popSpriteY)
{
	//��ʼ��
	iColor = color;
	popX = 0;
	popY = 0;
	//��ɫ�ĳ�ʼ��
	ColorBlock = LayerColor::create(Color4B(248, 248, 255,200),width-5,height-5);
	ColorBlock->setPosition(Vec2(popSpriteX, popSpriteY));
	this->addChild(ColorBlock);
	return true;
}

int PopSprite::getColor()
{
	return iColor;
}

bool PopSprite::setColor(int colors)
{
	iColor = colors;
	switch (iColor)
	{
	case -1:ColorBlock->setColor(Color3B(200, 190, 180)); break;
	case 1:ColorBlock->setColor(Color3B(220, 20, 60)); break;
	case 2:ColorBlock->setColor(Color3B(0, 0, 205)); break;
	case 3:ColorBlock->setColor(Color3B(46, 139, 87)); break;
	case 4:ColorBlock->setColor(Color3B(0, 0, 0)); break;
	default:
		return false;
	}
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

Point PopSprite::getPoint()
{
	return ColorBlock->getPosition();
}



