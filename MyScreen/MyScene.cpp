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
	createPopSquare(visibleSize);
	//���Ʒ���
	drawSquare();

	/*//���ü���,������ʽ��������pop
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MyScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MyScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);*/
	//���ü���
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
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
	log("x%i y%i color%i", touchPop->popX, touchPop->popY, touchPop->getColor());
	return true;
}
/*//�������
bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	if (canTouchBegin) {
		//��ȡ������Ļ�Ĵ�С
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//��ȡ�����λ��
		touchBeginPosition = touch->getLocation();
		//��λ����Ϣ����getPopStarSprite����
		touchPopBegin = getPopStarSprite(visibleSize, touchBeginPosition);
		log("beginx:%i,beginy:%i", touchPopBegin->getPopX(), touchPopBegin->getPopY());
		canTouchBegin = false;
		canMove= true;
		return true;
	}
	else
	{
		return false;
	}
	
}

//��������
bool MyScene::onTouchMoved(Touch* touch, Event* event)
{
	if (canMove) {
		//��ȡ������Ļ�Ĵ�С
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//��ȡ�����������λ��
		touchEndPosition = touch->getLocation();
		//��λ����Ϣ����getPopStarSprite����
		touchPopEnd = getPopStarSprite(visibleSize, touchBeginPosition);
		log("endx:%i,endy:%i", touchPopEnd->getPopX(), touchPopEnd->getPopY());
		return true;
	}
	else
	{
		return false;
	}

}*/

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
		return popSquare[(int)touchX][(int)touchY];
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
	canRemove = false;
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
		if (popSquare[x][up]->getColor() == popSquare[x][y]->getColor())
		{
			yUpCount++;
		}
		else
			break;
	}
	//�жϵ��λ�����µ���ͬɫ����
	for (int down = y - 1; down >= 0; down--)
	{
		if (popSquare[x][down]->getColor() == popSquare[x][y]->getColor())
		{
			yDownCount++;
		}
		else
			break;
	}
	//�жϵ��λ�����ҵ���ͬɫ����
	for (int right = x + 1; right < 10; right++)
	{
		if (popSquare[right][y]->getColor() == popSquare[x][y]->getColor())
		{
			xRightCount++;
		}
		else
			break;
	}
	//�жϵ��λ���������ͬɫ����
	for (int left = x - 1; left >= 0; left--)
	{
		if (popSquare[left][y]->getColor() == popSquare[x][y]->getColor())
		{
			xLeftCount++;
		}
		else
			break;
	}

	//����3�Ϳ�������
	if (yUpCount + yDownCount >= 2)
	{
		canRemove = true;
		for (int i = 1; i <= yUpCount; i++)
		{
			tempArr->addObject(popSquare[x][y + i]);
			//������ɻ�ɫ��������
			popSquare[x][y + i]->setColor(-1);
		}
		for (int i = 1; i <= yDownCount; i++)
		{
			tempArr->addObject(popSquare[x][y - i]);
			//������ɻ�ɫ��������
			popSquare[x][y - i]->setColor(-1);
		}
	}
	if (xRightCount + xLeftCount >= 2)
	{
		canRemove = true;
		for (int i = 1; i <= xRightCount; i++)
		{
			tempArr->addObject(popSquare[x+i][y]);
			//������ɻ�ɫ��������
			popSquare[x+i][y]->setColor(-1);
		}
		for (int i = 1; i <= xLeftCount; i++)
		{
			tempArr->addObject(popSquare[x-i][y]);
			//������ɻ�ɫ��������
			popSquare[x-i][y]->setColor(-1);
		}
	}
	
	if (canRemove)
	{
		//������ɻ�ɫ��������
		popSquare[x][y]->setColor(-1);
		//���������ͰѸõ���룻
		tempArr->addObject(popSquare[x][y]);
		
	}
	return tempArr;
}

// ���հ׷��󣬱�֤û�п����������,dfs
void MyScene::fillSquare(int x, int y)
{
	// �����߽��򷵻�
	if (x == -1 || x == 10 || y == -1 || y == 10)
		return;

	// �����������
	int randcolor = rand() % 4 + 1;

	// ���
	if (popSquare[x][y]->getColor() == -1)
	{
		popSquare[x][y]->setColor(randcolor);

		checkPopNearBy(popSquare[x][y]);
		// ���û��������������
		if (!canRemove)
		{
			// �ĸ�����ݹ����
			fillSquare(x + 1, y);
			fillSquare(x - 1, y);
			fillSquare(x, y - 1);
			fillSquare(x, y + 1);
		}
		else
			popSquare[x][y]->setColor(-1); // ��ԭ
	}
}

//���Ʒ���
void MyScene::drawSquare()
{
	srand(unsigned(time(0))); // ��ʼ�������������

	// �����ڴ������ɣ���֤��ʼû�п�������
	fillSquare(0, 0);

	// ������ɵķ���ĺ��п���������
	bool isNeedRegenerate = false;
	for (int i = 0; i < squareWidth; i++)
	{
		for (int j = 0; j <squareHeight; j++)
		{
			if (popSquare[i][j]->getColor() == -1)
			{
				isNeedRegenerate = true;
			}
		}

		if (isNeedRegenerate)
			break;
	}

	//�����Ҫ���»���
	if (isNeedRegenerate)
	{
		CCLOG("redraw game board");
		drawSquare();
		return;
	}
}

//��Ӳ����ķ���
void MyScene::createPopSquare(Size size) {
	//ÿһ��ɫ��ĳ�������
	const int len = (size.width - 28) / 10;
	//����ɫ��
	for (int i = 0; i < squareWidth; i++)
	{
		for (int j = 0; j < squareHeight ; j++)
		{
			//����block����
			PopSprite* block = PopSprite::createPopSprite(-1, len, len, len * i + 20, len * j + 20 + size.height / 6);
			//�����������ɫ
			block->setPopX(i);
			block->setPopY(j);
			block->setColor(-1);
			//�Ѿ�����ӵ���ǰ������
			addChild(block);
			//��ӵ������У�
			popSquare[i][j] = block;
		}
	}
}