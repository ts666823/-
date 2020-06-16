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

	//ʱ��label
	auto timeLabel = Label::createWithTTF(StringUtils::format("Time : %d",iTime), "fonts/Marker Felt.ttf", 30);
	timeLabel->setPosition(Vec2(timeLabel->getContentSize().width, visibleSize.height - timeLabel->getContentSize().height));
	//��Ҫͨ��tag���ҵ����ı�timeLabel
	timeLabel->setTag(1);
	this->addChild(timeLabel,1);

	//����label
	auto scoreLabel = Label::createWithTTF(StringUtils::format("Score : %d", iScore), "fonts/Marker Felt.ttf", 30);
	scoreLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - scoreLabel->getContentSize().height * 3));
	scoreLabel->setTag(2);
	this->addChild(scoreLabel, 1);
	
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

	//���º�����
		scheduleUpdate();

	//����schedule������ʱ�����ĸ���
		schedule(schedule_selector(MyScene::timeCount), 1.0f);


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

//���������������
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
		touchBeginPop->runAction(MoveTo::create(0.2, endPos));
		touchEndPop->runAction(MoveTo::create(0.2, beginPos));
		log("1");
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
			pop->setIsNew(false);
		}
	}
	
	for (int i = 0; i < SQUARE_WIDTH; i++)
	{
		for (int j = 0; j < SQUARE_HEIGHT; j++)
		{
			bool createXRemovePop;

			pop = popSquare[i][j];

			//�����ɵ����⾫�鲻���
			if (pop->getIsNew())
			{
				continue;
			}

			//���Ƿ��Ѿ�������
			bool haveChecked = false;
			// ����һ��list �洢�ڱ�������Χ�����£��뱾������ͬ�ľ���
			std::list< PopSprite*> yList;
			getYCheck(pop, yList);
			// ����һ��list �洢�ڱ�������Χ�����ң��뱾������ͬ�ľ���
			std::list< PopSprite*> xList;
			getXCheck(pop, xList);

			// ������������list ��ֵ ��longList
			std::list< PopSprite*>& longList = yList.size() > xList.size() ? yList : xList;
			createXRemovePop = xList.size() > yList.size() ? true : false;
			// �����ͬ����ĸ���С��3�� ������
			if (longList.size() < 3) {
				continue;
			}
			for (std::list<PopSprite*>::iterator itor = longList.begin(); itor != longList.end(); itor++)
			{
				PopSprite* popInList;
				popInList = (PopSprite*)* itor;

				//��������ľ���
				if (longList.size() >= 4)
				{
					//�õ������������pop��������
					if (popInList == touchBeginPop || popInList == touchEndPop)
					{
						haveChecked = true;
						popInList->setCanRemove(false);
						popInList->setIsNew(true);
						popInList->setStatus(createXRemovePop ? X_REMOVE_POP:Y_REMOVE_POP);
						continue;
					}
				}
				markPopRemove(popInList);
			}
			//�������ʱ���������⾫��
			if (!haveChecked && longList.size() > 3)
			{
				pop->setIsNew(true);
				pop->setCanRemove(false);
				pop->setStatus(createXRemovePop ? X_REMOVE_POP : Y_REMOVE_POP);
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
    Size size = Director::getInstance()->getVisibleSize();
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
				//���������ľ���
				if (pop->getStatus()== X_REMOVE_POP)
				{
					specialXExplode(size, getPositionOfPop(size, pop->getPopX(), pop->getPopY()));
				}
				else if (pop->getStatus() == Y_REMOVE_POP)
				{
					specialYExplode(size, getPositionOfPop(size, pop->getPopX(), pop->getPopY()));
				}
				explodeSprite(pop);

			}
		}
	}
}

//��ը����Ч��
void MyScene::explodeSprite(PopSprite* pop)
{
	 Size size = Director::getInstance()->getVisibleSize();
	pop->runAction(Sequence::create(
		ScaleTo::create(0.2f, 0.0),
		CallFuncN::create(CC_CALLBACK_1(MyScene::actionEndCallback, this)),
		NULL
	));

	auto circleSprite = Sprite::create("circle.png");
	addChild(circleSprite, 10);
	circleSprite->setPosition(getPositionOfPop(size,pop->getPopX(),pop->getPopY()));
	circleSprite->setScale(0);// start size
	circleSprite->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, circleSprite)),
		NULL));
}

//���⾫�������
void MyScene::specialXExplode(Size size,Point point)
{
	float scaleX = 4;
	float scaleY = 0.7;
	float time = 0.3;
	Point startPosition = point;
	float speed = 0.6f;

	
	auto colorSpriteRight = Sprite::create("colorHRight.png");
	addChild(colorSpriteRight, 10);
	Point endPosition1 = Point(point.x - size.width, point.y);
	colorSpriteRight->setPosition(startPosition);
	colorSpriteRight->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition1),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteRight)),
		NULL));

	auto colorSpriteLeft = Sprite::create("colorHLeft.png");
	addChild(colorSpriteLeft, 10);
	Point endPosition2 = Point(point.x + size.width, point.y);
	colorSpriteLeft->setPosition(startPosition);
	colorSpriteLeft->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition2),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteLeft)),
		NULL));
}
void MyScene::specialYExplode(Size size,Point point)
{
	float scaleY = 4;
	float scaleX = 0.7;
	float time = 0.3;
	Point startPosition = point;
	float speed = 0.6f;

	auto colorSpriteDown = Sprite::create("colorVDown.png");
	addChild(colorSpriteDown, 10);
	Point endPosition1 = Point(point.x, point.y - size.height);
	colorSpriteDown->setPosition(startPosition);
	colorSpriteDown->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition1),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteDown)),
		NULL));

	auto colorSpriteUp = Sprite::create("colorVUp.png");
	addChild(colorSpriteUp, 10);
	Point endPosition2 = Point(point.x, point.y + size.height);
	colorSpriteUp->setPosition(startPosition);
	colorSpriteUp->runAction(Sequence::create(ScaleTo::create(time, scaleX, scaleY),
		MoveTo::create(speed, endPosition2),
		CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, colorSpriteUp)),
		NULL));
}

//�ص�����
void MyScene::actionEndCallback(Node* popNode)
{
	PopSprite* pop = (PopSprite*)popNode;
	popSquare[pop->getPopX()][pop->getPopY()] = NULL;
	pop->removeFromParent();
}

//�����Χ����ͬ����ֱ���X���Y�᷽��
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

//�½����
void MyScene::fillSprite(Size size)
{
	isFilling = true;

	const int len = (size.width - 28) / 10;

	int* xNeedFill = (int*)malloc(sizeof(int) * SQUARE_WIDTH);
	memset(xNeedFill, 0, sizeof(int) * SQUARE_WIDTH);

	//�½����
	PopSprite* oldPop = NULL;
	for (int i = 0; i < SQUARE_WIDTH; i++)
	{

		int numRomvedPop=0;
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

			//���������ɫ
			int randColor = rand() % 4 + 1;
			//����pop
			createPop(size, randColor, i, j);
			iScore += 5;
		}
	}
 }

//���º���
void MyScene::update(float dt)
{
	if (isRemoving || isFilling || isSwapping)
	{
		isRunningAction = true;
		isRemoving = false;
		isFilling = false;
		isSwapping = false;
	}
	if (isRunningAction)
	{
		isRunningAction = false;
		for (int i = 0; i < SQUARE_HEIGHT; i++)
		{
			for (int j = 0; j < SQUARE_WIDTH; j++)
			{
				PopSprite* pop = popSquare[i][j];
				if (pop)
				{
					if (pop->getNumberOfRunningActions() > 0)
					{
						isRunningAction = true;
						break;
					}
				}
			}
		}
	}
	canTouch = !isRunningAction;
	if(!isRunningAction)
	{
		if (isNeedFill)
		{
			Size size = Director::getInstance()->getVisibleSize();
			fillSprite(size);
			isNeedFill = false;
			Label* scoreLabel = (Label*)this->getChildByTag(2);
			scoreLabel->setString(StringUtils::format("Score : %d", iScore));
		}
		//����Ҫִ�����
		else
		{
			checkAndRemove();
		}
	}
	
}

//ʱ��仯
void MyScene::timeCount(float dt)
{
	iTime--;
	//���ʱ�䵽�ˣ��л�����Ϸ��������
	if (iTime == 0)
	{
		//
		Size size = Director::getInstance()->getVisibleSize();

		//�ı�timeLabel,��tagѰ���ӽڵ�
		Label* timeLabel = (Label*)this->getChildByTag(1);
		timeLabel->setScale(0);

		//����Ч������Ϸ����
		auto gameOver = Sprite::create("GameOver.png");
		gameOver->setPosition(Point(size.width / 2, size.height / 1));
		addChild(gameOver, 1);
		
		//����Ч��
		auto move = MoveTo::create(1, Point(size.width / 2, size.height / 2));
		gameOver->runAction(move);

		return;
	}
	else if(iTime>0)
	{
		Label* timeLabel = (Label*)this->getChildByTag(1);
		timeLabel->setString(StringUtils::format("Time : %d", iTime));
		return;
	}
}