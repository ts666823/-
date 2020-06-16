#include "MyScene.h"
USING_NS_CC;
//创建场景
Scene* MyScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MyScene::create();
	scene->addChild(layer);
	return scene;
}
//初始化方式
bool MyScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	//获取整个手机可视屏幕尺寸
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取手机可视屏原点的坐标
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//创建一个显示"MyScene"文字的Label
	auto label = Label::createWithTTF("MyScene", "fonts/Marker Felt.ttf", 24);
	//设置白色
	label->setColor(Color3B::WHITE);
	// 设置label在屏幕中的显示位置
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	// 把label添加到画面层
	this->addChild(label, 1);

	//时间label
	auto timeLabel = Label::createWithTTF(StringUtils::format("Time : %d",iTime), "fonts/Marker Felt.ttf", 30);
	timeLabel->setPosition(Vec2(timeLabel->getContentSize().width, visibleSize.height - timeLabel->getContentSize().height));
	//需要通过tag来找到并改变timeLabel
	timeLabel->setTag(1);
	this->addChild(timeLabel,1);

	//分数label
	auto scoreLabel = Label::createWithTTF(StringUtils::format("Score : %d", iScore), "fonts/Marker Felt.ttf", 30);
	scoreLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - scoreLabel->getContentSize().height * 3));
	scoreLabel->setTag(2);
	this->addChild(scoreLabel, 1);
	
	//背景图片
	auto sprite = Sprite::create("1.jpg");
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
		// add the sprite as a child to this layer
		this->addChild(sprite, 0);

	//精灵列表
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("icon.plist");
		spriteSheet = SpriteBatchNode::create("icon.png");
		this->addChild(spriteSheet);


	//产生方阵：
		createPopSquare(visibleSize);

	//更新函数：
		scheduleUpdate();

	//利用schedule来设置时间间隔的更新
		schedule(schedule_selector(MyScene::timeCount), 1.0f);


	//设置监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MyScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

		return true;
}

//监听点击
bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	touchBeginPop = NULL;
	touchEndPop = NULL;
	if (canTouch) {
		//获取整个屏幕的大小
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//获取点击的位置
		touchBeginPosition = touch->getLocation();
		//将位置信息交给getPopStarSprite函数
		touchBeginPop = getPop(visibleSize, touchBeginPosition);
	}
	return canTouch;
}


void MyScene::onTouchMoved(Touch* touch, Event* event)
{
	 if (!touchBeginPop || !canTouch) {
		 return;
	}
	 //获取尺寸
	 Size size = Director::getInstance()->getVisibleSize();
	 const int len = (size.width - 28) / 10;
	 //点击位置
	 touchEndPosition = touch->getLocation();
	 int beginX = touchBeginPop->getPopX();
	 int beginY = touchBeginPop->getPopY();
	 //向上的方向,构造矩形，判断位置
	 auto upRect = Rect(touchBeginPosition.x - len / 2,
		 touchBeginPosition.y + len / 2,
		 len,
		 len);
	 //向下的方向
	 auto downRect = Rect(touchBeginPosition.x - len / 2,
		 touchBeginPosition.y - (3*len / 2),
		 len,
		 len);
	 //向右的方向
	 auto rightRect = Rect(touchBeginPosition.x + len / 2,
		 touchBeginPosition.y - len / 2,
		 len,
		 len);
	 //向左的方向
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

//获取点击位置的pop
PopSprite* MyScene::getPop(Size size, Point point)
{
	//创建一个pop所包围的矩形
	Rect popRect = Rect(0, 0, POP_LENTH,POP_LENTH);

	for (int i = 0; i < SQUARE_HEIGHT; i++) {
		for (int j = 0; j < SQUARE_WIDTH; j++) {
				//矩形的左下角坐标
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

//交换两个点击对象
void MyScene::swapPop()
{
	//获取位置，用于getPositionOfPop
	Size size = Director::getInstance()->getVisibleSize();

	isSwapping = true;
	canTouch = false;
	//如果初始精灵和末尾精灵没有则不交换
	if (!touchBeginPop || !touchEndPop)
		return;
	int beginX = touchBeginPop->getPopX();
	int beginY = touchBeginPop->getPopY();
	int endX = touchEndPop->getPopX();
	int endY = touchEndPop->getPopY();
	Point beginPos = getPositionOfPop(size,beginX, beginY);
	Point endPos = getPositionOfPop(size,endX, endY);

	//交换方阵中的位置
	popSquare[beginX][beginY] = touchEndPop;
	popSquare[endX][endY] = touchBeginPop;

	//改变pop的位置
	touchBeginPop->setPopX(endX);
	touchBeginPop->setPopY(endY);
	touchEndPop->setPopX(beginX);
	touchEndPop->setPopY(beginY);

	//检查交换后是否能消除
	if (getPopChecked(touchEndPop) || getPopChecked(touchBeginPop))
	{
		//可以消除就交换位置
		touchBeginPop->runAction(MoveTo::create(0.2, endPos));
		touchEndPop->runAction(MoveTo::create(0.2, beginPos));
		log("1");
		return;
	}

	//不能消除
	//交换方阵中的位置
	popSquare[endX][endY] = touchEndPop;
	popSquare[beginX][beginY] = touchBeginPop;

	//改变pop的位置
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

//产生pop
void MyScene::createPop(Size size, int color, int x, int y)
{
	PopSprite* pop = PopSprite::createPopSprite(color, x, y);

	//设置动画的起始和最终位置
	Point endPosition = getPositionOfPop(size, x, y);
	Point beginPosition = Point(endPosition.x, endPosition.y + size.height / 6);

	//创建动画
	pop->setPosition(beginPosition);
	float speed = beginPosition.y / (1.5 * size.height);
	pop->runAction(MoveTo::create(0.1, endPosition));
	
	//加入到spriteSheet,等待渲染
	spriteSheet->addChild(pop);
	popSquare[x][y] = pop;
}

//获取位置
Point MyScene::getPositionOfPop(Size size,int x,int y)
{
	//初始位置，（0，0）位置
	float positionX = (size.width - POP_LENTH * SQUARE_WIDTH - BOARDER_WIDTH * (SQUARE_WIDTH - 1)) / 2;
	float positionY = (size.height - POP_LENTH * SQUARE_HEIGHT - BOARDER_WIDTH * (SQUARE_HEIGHT - 1)) / 2;

	//位置
	positionX = positionX + (POP_LENTH + BOARDER_WIDTH) * x + POP_LENTH / 2;
	positionY= positionY + (POP_LENTH + BOARDER_WIDTH) * y + POP_LENTH / 2;

	return Point(positionX, positionY);
}

//添加产生的方阵
void MyScene::createPopSquare(Size size){
	//放置色块
	for (int i = 0; i < SQUARE_WIDTH; i++)
	{
		for (int j = 0; j < SQUARE_HEIGHT ; j++)
		{
			//产生随机颜色
			int randColor = rand() % 4 + 1;
			//产生pop
			createPop(size, randColor, i, j);
		}
	}
}

//检测某个精灵是否可以消除
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

//检测消除和移除的函数
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

			//新生成的特殊精灵不检查
			if (pop->getIsNew())
			{
				continue;
			}

			//看是否已经检查过了
			bool haveChecked = false;
			// 建立一个list 存储在本精灵周围（上下）与本精灵相同的精灵
			std::list< PopSprite*> yList;
			getYCheck(pop, yList);
			// 建立一个list 存储在本精灵周围（左右）与本精灵相同的精灵
			std::list< PopSprite*> xList;
			getXCheck(pop, xList);

			// 将精灵个数多的list 赋值 给longList
			std::list< PopSprite*>& longList = yList.size() > xList.size() ? yList : xList;
			createXRemovePop = xList.size() > yList.size() ? true : false;
			// 如果相同精灵的个数小于3个 则跳过
			if (longList.size() < 3) {
				continue;
			}
			for (std::list<PopSprite*>::iterator itor = longList.begin(); itor != longList.end(); itor++)
			{
				PopSprite* popInList;
				popInList = (PopSprite*)* itor;

				//产生特殊的精灵
				if (longList.size() >= 4)
				{
					//让点击交换的两个pop变成特殊的
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
			//下落填充时产生的特殊精灵
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

//标记可以移除的pop
void MyScene::markPopRemove(PopSprite* pop)
{
	if (pop->getCanRemove())
		return;
	pop->setCanRemove(true);
}

//消除
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
				//如果有特殊的精灵
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

//爆炸消除效果
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

//特殊精灵的消除
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

//回调函数
void MyScene::actionEndCallback(Node* popNode)
{
	PopSprite* pop = (PopSprite*)popNode;
	popSquare[pop->getPopX()][pop->getPopY()] = NULL;
	pop->removeFromParent();
}

//检查周围的相同精灵分别是X轴和Y轴方向
void MyScene::getXCheck(PopSprite* pop, std::list<PopSprite*>& xList)
{
	xList.push_back(pop);
	int left = pop->getPopX() - 1;
	int right = pop->getPopX() + 1;
	//向左查找
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
	//向右判断
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
	//向下查找
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
	//向上判断
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

//下降填充
void MyScene::fillSprite(Size size)
{
	isFilling = true;

	const int len = (size.width - 28) / 10;

	int* xNeedFill = (int*)malloc(sizeof(int) * SQUARE_WIDTH);
	memset(xNeedFill, 0, sizeof(int) * SQUARE_WIDTH);

	//下降填充
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
			{  //如果该列有消除就降落原来的方块
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

			//产生随机颜色
			int randColor = rand() % 4 + 1;
			//产生pop
			createPop(size, randColor, i, j);
			iScore += 5;
		}
	}
 }

//更新函数
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
		//不需要执行填充
		else
		{
			checkAndRemove();
		}
	}
	
}

//时间变化
void MyScene::timeCount(float dt)
{
	iTime--;
	//如果时间到了，切换到游戏结束界面
	if (iTime == 0)
	{
		//
		Size size = Director::getInstance()->getVisibleSize();

		//改变timeLabel,以tag寻找子节点
		Label* timeLabel = (Label*)this->getChildByTag(1);
		timeLabel->setScale(0);

		//动画效果，游戏结束
		auto gameOver = Sprite::create("GameOver.png");
		gameOver->setPosition(Point(size.width / 2, size.height / 1));
		addChild(gameOver, 1);
		
		//下落效果
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