#include "ThePopSprite.h"
USING_NS_CC;
PopSprite* PopSprite::createPopSprite(int color,int x,int y) {
	PopSprite* pop = new PopSprite();
	if (pop && pop->init())
	{
		//确定x，y坐标
		pop->setPopX(x);
		pop->setPopY(y);
		//确定颜色
		pop->setColor(color);
		pop->initWithSpriteFrameName(popNormal[pop->getColor()]);
		//自动释放
		pop->autorelease();
		return pop;
	}
	//如果生成enemy对象失败
	//使用delete操作符删除一个对象，如果对象为NULL，则不进行操作
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

void PopSprite::setStatus(int status)
{
	iStatus = status;
	
	//改变精灵的显示方式
	SpriteFrame* display;
	switch (iStatus) {
	case X_REMOVE_POP:
		display = SpriteFrameCache::getInstance()->getSpriteFrameByName(XReomvePop[iColor]);
		break;
	case Y_REMOVE_POP:
		display = SpriteFrameCache::getInstance()->getSpriteFrameByName(YRemovePop[iColor]);
		break;
	default:
		return;
	}
	//显示
	setDisplayFrame(display);
}

int PopSprite::getStatus()
{
	return iStatus;
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

//获取isNew
bool PopSprite::getIsNew()
{
	return isNew;
}

//设置isNew
void PopSprite::setIsNew(bool state)
{
	isNew = state;
}