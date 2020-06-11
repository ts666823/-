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
	//���ü���
	auto touchListenerBegin = EventListenerTouchOneByOne::create();
	touchListenerBegin->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
	touchListenerBegin->onTouchMoved = CC_CALLBACK_2(MyScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenerBegin, this);

	
}

//�������
bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	touchPopBegin = NULL;
	touchPopEnd = NULL;
	if (canTouch) {
		//��ȡ������Ļ�Ĵ�С
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//��ȡ�����λ��
		touchBeginPosition = touch->getLocation();
		//��λ����Ϣ����getPopStarSprite����
		touchPopBegin = getPopStarSprite(visibleSize, touchBeginPosition);
		//log����
		log("1x%i 1y%i 1color%i", touchPopBegin->getPopX(), touchPopBegin->getPopY(), touchPopBegin->getColor());
	}
	return canTouch;
}
void MyScene::onTouchMoved(Touch* touch, Event* event)
{
	 if (!touchPopBegin || !canTouch) {
		 return;
	}

	 int startX = touchPopBegin->getPopX();
	 int startY = touchPopBegin->getPopY();

	 
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
		return popSquare[(int)touchX][(int)touchY];
	}
	else
		return NULL;
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

		checkPopCanRemove();
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

//��������ĺ���
void MyScene::checkPopCanRemove()
{
	PopSprite* pop;
	for (int i = 0; i < squareWidth; i++)
	{
		for (int j = 0; j < squareHeight; j++)
		{
			pop = popSquare[i][j];
			if (pop->getCanRemove())
				continue;
			// ����һ��list �洢�ڱ�������Χ�����£��뱾������ͬ�ľ���
			std::list< PopSprite*> yList;
			getYCheck(pop, yList);
			// ����һ��list �洢�ڱ�������Χ�����ң��뱾������ͬ�ľ���
			std::list< PopSprite*> xList;
			getXCheck(pop, xList);

			// ������������list ��ֵ ��longList
			std::list< PopSprite*>& longList = yList.size() > xList.size() ? yList : xList;
			// �����ͬ����ĸ���С��3�� ������
			if (longList.size() < 3) {
				continue;
			}
			for (std::list<PopSprite*>::iterator itor = longList.begin(); itor != longList.end(); itor++)
			{
				PopSprite* popInList;
				popInList = (PopSprite*)* itor;
				markPopRemove(popInList);
			}
		}
	}
	removePop();
}

void MyScene::markPopRemove(PopSprite* pop)
{
	if (pop->getCanRemove())
		return;
	pop->setCanRemove(true);
}

void MyScene::removePop()
{
	isRemoving = true;
	for (int i = 0; i < squareWidth; i++)
	{
		for (int j = 0; j < squareHeight; j++)
		{
			PopSprite* pop = popSquare[i][j];
			if (!pop)
				continue;
			if (pop->getCanRemove())
			{
				isNeedFill = true;
				explodeSprite(pop);
			}
		}
	}
}

void MyScene::explodeSprite(PopSprite* pop)
{
	pop->runAction(Sequence::create(
		ScaleTo::create(0.2f, 0.0),
		CallFuncN::create(CC_CALLBACK_1(MyScene::actionEndCallback, this)),
		NULL
	));
}

//�ص�����
void MyScene::actionEndCallback(Node* popNode)
{
	PopSprite* pop = (PopSprite*)popNode;
	popSquare[pop->getPopX()][pop->getPopY()] = NULL;
	pop->removeFromParent();
}

//�����Χ����ͬ����
void MyScene::getXCheck(PopSprite* pop, std::list<PopSprite*>& xList)
{
	xList.push_back(pop);
	int left = pop->getPopX() - 1;
	int right = pop->getPopX() + 1;
	//�������
	while (left >= 0)
	{
		PopSprite* popNear = popSquare[left][pop->getPopY()];
		if (popNear && popNear->getColor() == pop->getColor()&&!popNear->getCanRemove())
		{
			xList.push_back(popNear);
			left--;
		}
		else
		{
			break;
		}
	}
	//�����ж�
	while (right < squareWidth )
	{
		PopSprite* popNear = popSquare[right][pop->getPopY()];
		if (popNear && popNear->getColor() == pop->getColor() && !popNear->getCanRemove())
		{
			xList.push_back(popNear);
			right++;
		}
		else
		{
			break;
		}
	}
}

void MyScene::getYCheck(PopSprite* pop, std::list<PopSprite*>& xList)
{
	xList.push_back(pop);
	int down = pop->getPopY() - 1;
	int up = pop->getPopY() + 1;
	//���²���
	while (down >= 0)
	{
		PopSprite* popNear = popSquare[pop->getPopX()][down];
		if (popNear && popNear->getColor() == pop->getColor() && !popNear->getCanRemove())
		{
			xList.push_back(popNear);
			down--;
		}
		else
		{
			break;
		}
	}
	//�����ж�
	while (up < squareWidth)
	{
		PopSprite* popNear = popSquare[pop->getPopX()][up];
		if (popNear && popNear->getColor() == pop->getColor() && !popNear->getCanRemove())
		{
			xList.push_back(popNear);
			up++;
		}
		else
		{
			break;
		}
	}
}

void MyScene::fillSprite(Size size)
{
	isFilling = true;

	const int len = (size.width - 28) / 10;

	int* xNeedFill = (int*)malloc(sizeof(int) * squareWidth);
	memset(xNeedFill, 0, sizeof(int) * squareWidth);

	//�½����
	PopSprite* oldPop = NULL;
	for (int i = 0; i < squareWidth; i++)
	{

		int numRomvedPop;
		for (int j = 0; j < squareHeight; j++)
		{
			oldPop = popSquare[i][j];
			if (oldPop == NULL)
			{
				numRomvedPop++;
			}
			else
			{  //��������������ͽ���ԭ���ķ���
				if (numRomvedPop > 0) {
					popSquare[i][j - numRomvedPop] = oldPop;
					popSquare[i][j] = NULL;

					Point startPosition = oldPop->getPosition();
					Point endPosition = getPositionOfPop(size,i,j-numRomvedPop);
					float speed = (startPosition.y - endPosition.y) / size.height * 3;
					oldPop->stopAllActions();
					oldPop->runAction(CCMoveTo::create(speed, endPosition));
					oldPop->setPopY = j - numRomvedPop;
				}
			}
		}
		xNeedFill[i] = numRomvedPop;
	}
	for (int i = 0; i < squareWidth; i++)
	{
		for (int j = squareHeight - xNeedFill[i]; j < squareHeight; j++)
		{
			PopSprite* block = PopSprite::createPopSprite(-1, len, len, len * i + 20, len * j + 20 + size.height / 6);

			int randcolor = rand() % 4 + 1;
			//�����������ɫ
			block->setPopX(i);
			block->setPopY(j);
			block->setColor(randcolor);

			//�Ѿ�����ӵ���ǰ������
			addChild(block);

			//��ӵ������У�
			popSquare[i][j] = block;
		}
	}
 }

Point MyScene::getPositionOfPop(Size size,int row,int col)
{
	const int len = (size.width - 28) / 10;
	float x = len * row + 20;
	float y = len * (col) + 20 + size.height / 6;
	return Point(x, y);
}