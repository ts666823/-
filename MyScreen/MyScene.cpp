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

	//����ͼƬ
	auto sprite = Sprite::create("1.jpg");
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		this->addChild(sprite, 0);

	//�����б�
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist");
		spriteSheet = SpriteBatchNode::create("icon.png");
		this->addChild(spriteSheet);


	//��������
		createPopSquare(visibleSize);
	//���ü���
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MyScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

		return true;
}

//�������
bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	touchBeginPop = NULL;
	touchEndPop = NULL;
	if (canTouch) {
		//��ȡ������Ļ�Ĵ�С
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//��ȡ�����λ��
		touchBeginPosition = touch->getLocation();
		//��λ����Ϣ����getPopStarSprite����
		touchBeginPop = getPop(visibleSize, touchBeginPosition);
	}
	return canTouch;
}


void MyScene::onTouchMoved(Touch* touch, Event* event)
{
	 if (!touchBeginPop || !canTouch) {
		 return;
	}
	 //��ȡ�ߴ�
	 Size size = Director::getInstance()->getVisibleSize();
	 const int len = (size.width - 28) / 10;
	 //���λ��
	 touchEndPosition = touch->getLocation();
	 int beginX = touchBeginPop->getPopX();
	 int beginY = touchBeginPop->getPopY();
	 //���ϵķ���,������Σ��ж�λ��
	 auto upRect = Rect(touchBeginPosition.x - len / 2,
		 touchBeginPosition.y + len / 2,
		 len,
		 len);
	 //���µķ���
	 auto downRect = Rect(touchBeginPosition.x - len / 2,
		 touchBeginPosition.y - (3*len / 2),
		 len,
		 len);
	 //���ҵķ���
	 auto rightRect = Rect(touchBeginPosition.x + len / 2,
		 touchBeginPosition.y - len / 2,
		 len,
		 len);
	 //����ķ���
	 auto leftRect = Rect(touchBeginPosition.x -(3*len / 2),
		 touchBeginPosition.y -  len / 2,
		 len,
		 len);
	 if (upRect.containsPoint(touchEndPosition))
	 {
		 beginY++;
		 if (beginY < SQUARE_HEIGHT)
		 {
			touchEndPop = popSquare[beginX][beginY];
		 }
		 swapPop();
		 return;
	 }
	 else if (downRect.containsPoint(touchEndPosition))
	 {
		 beginY--;
		 if (beginY >= 0)
		 {
			 touchEndPop = popSquare[beginX][beginY];
		 }
		 swapPop();
		 return;
	 }
	 else if (leftRect.containsPoint(touchEndPosition))
	 {
		 beginX--;
		 if (beginX >= 0)
		 {
			 touchEndPop = popSquare[beginX][beginY];
		 }
		 swapPop();
		 return;
	 }
	 else if (rightRect.containsPoint(touchEndPosition))
	 {
		 beginX++;
		 if (beginX < SQUARE_WIDTH)
		 {
			 touchEndPop = popSquare[beginX][beginY];
		 }
		 swapPop();
		 return;
	 }
}

//��ȡ���λ�õ�pop
PopSprite* MyScene::getPop(Size size, Point point)
{
	//����һ��pop����Χ�ľ���
	Rect popRect = Rect(0, 0, POP_LENTH,POP_LENTH);

	for (int i = 0; i < SQUARE_HEIGHT; i++) {
		for (int j = 0; j < SQUARE_WIDTH; j++) {
				//���ε����½�����
				popRect.origin.x = getPositionOfPop(size,i,j).x - (POP_LENTH / 2.0);
				popRect.origin.y = getPositionOfPop(size, i, j).y - (POP_LENTH / 2.0);
				//log("1 %f 1 %f", touchBeginPosition.x, touchBeginPosition.y);
				//log("2 %f 2 %f", popRect.origin.x, popRect.origin.y);
				if (popRect.containsPoint(point)) {
					return popSquare[i][j];
			}
		}
	}
	return NULL;
}

void MyScene::swapPop()
{
	//��ȡλ�ã�����getPositionOfPop
	Size size = Director::getInstance()->getVisibleSize();

	isSwapping = true;
	canTouch = false;
	//�����ʼ�����ĩβ����û���򲻽���
	if (!touchBeginPop || !touchEndPop)
		return;
	int beginX = touchBeginPop->getPopX();
	int beginY = touchBeginPop->getPopY();
	int endX = touchEndPop->getPopX();
	int endY = touchEndPop->getPopY();
	Point beginPos = getPositionOfPop(size,beginX, beginY);
	Point endPos = getPositionOfPop(size,endX, endY);

	//���������е�λ��
	popSquare[beginX][beginY] = touchEndPop;
	popSquare[endX][endY] = touchBeginPop;

	//�ı�pop��λ��
	touchBeginPop->setPopX(endX);
	touchBeginPop->setPopY(endY);
	touchEndPop->setPopX(beginX);
	touchEndPop->setPopY(beginY);

	//��齻�����Ƿ�������
	if (getPopChecked(touchEndPop) || getPopChecked(touchBeginPop))
	{
		//���������ͽ���λ��
		touchBeginPop->runAction(MoveTo::create(1, endPos));
		touchEndPop->runAction(MoveTo::create(1, beginPos));
		log("1");
		log("B:%i  %i", touchBeginPop->getPopX(), touchBeginPop->getPopY());
		log("E:%i  %i", touchEndPop->getPopX(), touchEndPop->getPopY());
		return;
	}

	//��������
	//���������е�λ��
	popSquare[endX][endY] = touchEndPop;
	popSquare[beginX][beginY] = touchBeginPop;
	//�ı�pop��λ��
	touchBeginPop->setPopX(beginX);
	touchBeginPop->setPopY(beginY);
	touchEndPop->setPopX(endX);
	touchEndPop->setPopY(endY);

	touchBeginPop->runAction(Sequence::create(
		MoveTo::create(0.2, endPos),
		MoveTo::create(0.2, beginPos),
		NULL
	));
	touchEndPop->runAction(Sequence::create(
		MoveTo::create(0.2, beginPos),
		MoveTo::create(0.2, endPos),
		NULL
	));
	log("2");
	log("B:%i  %i", touchBeginPop->getPopX(), touchBeginPop->getPopY());
	log("E:%i  %i", touchEndPop->getPopX(), touchEndPop->getPopY());
	return;
}

//����pop
void MyScene::createPop(Size size, int color, int x, int y)
{
	PopSprite* pop = PopSprite::createPopSprite(color, x, y);

	//���ö�������ʼ������λ��
	Point endPosition = getPositionOfPop(size, x, y);
	Point beginPosition = Point(endPosition.x, endPosition.y + size.height / 6);

	//��������
	pop->setPosition(beginPosition);
	float speed = beginPosition.y / (1.5 * size.height);
	pop->runAction(MoveTo::create(0.1, endPosition));
	
	//���뵽spriteSheet,�ȴ���Ⱦ
	spriteSheet->addChild(pop);
	popSquare[x][y] = pop;
}

//��ȡλ��
Point MyScene::getPositionOfPop(Size size,int x,int y)
{
	//��ʼλ�ã���0��0��λ��
	float positionX = (size.width - POP_LENTH * SQUARE_WIDTH - BOARDER_WIDTH * (SQUARE_WIDTH - 1)) / 2;
	float positionY = (size.height - POP_LENTH * SQUARE_HEIGHT - BOARDER_WIDTH * (SQUARE_HEIGHT - 1)) / 2;

	//λ��
	positionX = positionX + (POP_LENTH + BOARDER_WIDTH) * x + POP_LENTH / 2;
	positionY= positionY + (POP_LENTH + BOARDER_WIDTH) * y + POP_LENTH / 2;

	return Point(positionX, positionY);
}

//��Ӳ����ķ���
void MyScene::createPopSquare(Size size){
	//����ɫ��
	for (int i = 0; i < SQUARE_WIDTH; i++)
	{
		for (int j = 0; j < SQUARE_HEIGHT ; j++)
		{
			//���������ɫ
			int randColor = rand() % 4 + 1;
			//����pop
			createPop(size, randColor, i, j);
		}
	}
}

//���ĳ�������Ƿ��������
bool MyScene::getPopChecked(PopSprite* pop)
{
	std::list<PopSprite*>xList;
	std::list<PopSprite*>yList;

	getXCheck(pop, xList);
	getYCheck(pop, yList);
	if (xList.size() >= 3 || yList.size() >= 3)
	{
		return true;
	}
	return false;
}

//����������Ƴ��ĺ���
void MyScene::checkAndRemove()
{
	PopSprite* pop;
	for (int i = 0; i < SQUARE_WIDTH; i++)
	{
		for (int j = 0; j < SQUARE_HEIGHT; j++)
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

//��ǿ����Ƴ���pop
void MyScene::markPopRemove(PopSprite* pop)
{
	if (pop->getCanRemove())
		return;
	pop->setCanRemove(true);
}

//����
void MyScene::removePop()
{
	isRemoving = true;
	for (int i = 0; i < SQUARE_WIDTH; i++)
	{
		for (int j = 0; j < SQUARE_HEIGHT; j++)
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

//��ը����Ч��
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
	while (right < SQUARE_WIDTH )
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
	while (up < SQUARE_HEIGHT)
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

/*void MyScene::fillSprite(Size size)
{
	isFilling = true;

	const int len = (size.width - 28) / 10;

	int* xNeedFill = (int*)malloc(sizeof(int) * SQUARE_WIDTH);
	memset(xNeedFill, 0, sizeof(int) * SQUARE_WIDTH);

	//�½����
	PopSprite* oldPop = NULL;
	for (int i = 0; i < SQUARE_WIDTH; i++)
	{

		int numRomvedPop;
		for (int j = 0; j < SQUARE_HEIGHT; j++)
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
					oldPop->setPopY ( j - numRomvedPop);
				}
			}
		}
		xNeedFill[i] = numRomvedPop;
	}
	for (int i = 0; i < SQUARE_WIDTH; i++)
	{
		for (int j = SQUARE_HEIGHT - xNeedFill[i]; j < SQUARE_HEIGHT; j++)
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
 }*/