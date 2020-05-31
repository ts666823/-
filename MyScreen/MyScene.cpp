#include "MyScene.h"
USING_NS_CC;
//��������
Scene* MyScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MyScene::create();
	scene->addChild(layer);
	return scene;
}
//��ʼ����ʽ
bool MyScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//��ȡ�����ֻ�������Ļ�ߴ�
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�ֻ�������ԭ�������
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//����һ����ʾ"MyScene"���ֵ�Label
	auto label = Label::createWithTTF("MyScene", "fonts/Marker Felt.ttf", 24);
	//���ð�ɫ
	label->setColor(Color3B::WHITE);
	// ����label����Ļ�е���ʾλ��
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	// ��label��ӵ������
	this->addChild(label, 1);
	auto sprite = Sprite::create("1.jpg");
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	//��������
	createPopSprite(visibleSize);

	//���ü���
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

//��Ӳ����ķ���
void MyScene::createPopSprite(Size size) {
	//ÿһ��ɫ��ĳ�������
	const int len = (size.width - 28) / 10;
	int randcolor = 0;
	//����ɫ��
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			//����1��4�������
			randcolor= rand() % 4 + 1;
			//����block����
			PopSprite* block = PopSprite::createPopSprite(-1, len, len, len * i + 20, len * j + 20 + size.height / 6);
			//�����������ɫ
			block->setPopX(i);
			block->setPopY(j);
			block->setColor(randcolor);
			//�Ѿ�����ӵ���ǰ������
			addChild(block);
			//��ӵ������У�
			popStarSprite[i][j] = block;
		}
	}
}

//�������
bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	//��ȡ������Ļ�Ĵ�С
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ȡ�����λ��
	Point touchPosition = touch->getLocation();
	//��λ����Ϣ����getPopStarSprite����
	PopSprite* touchPop = getPopStarSprite(visibleSize, touchPosition);
	//��ʼ����¼���ݵ�����
	PopNearBy = Array::create();
	//������ݻ����Ĵ���Pop��ΪNULL
	if (touchPop != NULL)
	{	
		PopNearBy = checkPopNearBy(touchPop);
	}
	//log����
	//log("x%i y%i color%i", touchPop->popX, touchPop->popY, touchPop->getColor());
	return true;
}

//getPopStarSprite����
PopSprite* MyScene::getPopStarSprite(Size size, Point touch)
{
	//PopSprite ����ĳ��Ϳ�
	const int len = (size.width-28) / 10;
	//��������λ���ڷ����е�λ��
	float touchX = (touch.x-28) / len;
	float touchY = (touch.y - 20-size.height / 6) / len;
	if (touchX < 10 && touchY < 10 && touchX >= 0 && touchY >= 0)
	{
		return popStarSprite[(int)touchX][(int)touchY];
	}
	else
		return NULL;
}

//����������ҵĺ���
Array* MyScene::checkPopNearBy(PopSprite* popStar)
{
	//�����鴢������
	Array* tempArr = Array::create();
	//�ж��Ƿ���ͬ��ɫ
	bool isSamePop = false;
	//��ȡ���λ�õ�x��y����
	int y = popStar->getPopY();
	int x = popStar->getPopX();
	int yUpCount = 0;
	int yDownCount = 0;
	int xRightCount = 0;
	int xLeftCount = 0;
	//�жϵ��λ�����ϵ���ͬɫ����
	for (int up = y + 1; up < 10; up++)
	{
		if (popStarSprite[x][up]->getColor() == popStarSprite[x][y]->getColor())
		{
			yUpCount++;
		}
		else
			break;
	}
	//�жϵ��λ�����µ���ͬɫ����
	for (int down = y - 1; down >= 0; down--)
	{
		if (popStarSprite[x][down]->getColor() == popStarSprite[x][y]->getColor())
		{
			yDownCount++;
		}
		else
			break;
	}
	//�жϵ��λ�����ҵ���ͬɫ����
	for (int right = x + 1; right < 10; right++)
	{
		if (popStarSprite[right][y]->getColor() == popStarSprite[x][y]->getColor())
		{
			xRightCount++;
		}
		else
			break;
	}
	//�жϵ��λ���������ͬɫ����
	for (int left = x - 1; left >= 0; left--)
	{
		if (popStarSprite[left][y]->getColor() == popStarSprite[x][y]->getColor())
		{
			xLeftCount++;
		}
		else
			break;
	}

	//����3�Ϳ�������
	if (yUpCount + yDownCount >= 2)
	{
		isSamePop = true;
		for (int i = 1; i <= yUpCount; i++)
		{
			tempArr->addObject(popStarSprite[x][y + i]);
			//������ɻ�ɫ��������
			popStarSprite[x][y + i]->setColor(-1);
		}
		for (int i = 1; i <= yDownCount; i++)
		{
			tempArr->addObject(popStarSprite[x][y - i]);
			//������ɻ�ɫ��������
			popStarSprite[x][y - i]->setColor(-1);
		}
	}
	if (xRightCount + xLeftCount >= 2)
	{
		isSamePop = true;
		for (int i = 1; i <= xRightCount; i++)
		{
			tempArr->addObject(popStarSprite[x+i][y]);
			//������ɻ�ɫ��������
			popStarSprite[x+i][y]->setColor(-1);
		}
		for (int i = 1; i <= xLeftCount; i++)
		{
			tempArr->addObject(popStarSprite[x-i][y]);
			//������ɻ�ɫ��������
			popStarSprite[x-i][y]->setColor(-1);
		}
	}
	//���������ͰѸõ���룻
	if (isSamePop)
	{
		//������ɻ�ɫ��������
		popStarSprite[x][y]->setColor(-1);

		tempArr->addObject(popStarSprite[x][y]);
	}
	return tempArr;
}
