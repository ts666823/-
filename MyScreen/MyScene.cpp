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
		touchBeginPop->runAction(MoveTo::create(1, endPos));
		touchEndPop->runAction(MoveTo::create(1, beginPos));
		log("1");
		log("B:%i  %i", touchBeginPop->getPopX(), touchBeginPop->getPopY());
		log("E:%i  %i", touchEndPop->getPopX(), touchEndPop->getPopY());
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
	log("B:%i  %i", touchBeginPop->getPopX(), touchBeginPop->getPopY());
	log("E:%i  %i", touchEndPop->getPopX(), touchEndPop->getPopY());
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
			if (pop->getCanRemove())
				continue;
			// 建立一个list 存储在本精灵周围（上下）与本精灵相同的精灵
			std::list< PopSprite*> yList;
			getYCheck(pop, yList);
			// 建立一个list 存储在本精灵周围（左右）与本精灵相同的精灵
			std::list< PopSprite*> xList;
			getXCheck(pop, xList);

			// 将精灵个数多的list 赋值 给longList
			std::list< PopSprite*>& longList = yList.size() > xList.size() ? yList : xList;
			// 如果相同精灵的个数小于3个 则跳过
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

//爆炸消除效果
void MyScene::explodeSprite(PopSprite* pop)
{
	pop->runAction(Sequence::create(
		ScaleTo::create(0.2f, 0.0),
		CallFuncN::create(CC_CALLBACK_1(MyScene::actionEndCallback, this)),
		NULL
	));
}

//回调函数
void MyScene::actionEndCallback(Node* popNode)
{
	PopSprite* pop = (PopSprite*)popNode;
	popSquare[pop->getPopX()][pop->getPopY()] = NULL;
	pop->removeFromParent();
}

//检查周围的相同精灵
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

/*void MyScene::fillSprite(Size size)
{
	isFilling = true;

	const int len = (size.width - 28) / 10;

	int* xNeedFill = (int*)malloc(sizeof(int) * SQUARE_WIDTH);
	memset(xNeedFill, 0, sizeof(int) * SQUARE_WIDTH);

	//下降填充
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
			PopSprite* block = PopSprite::createPopSprite(-1, len, len, len * i + 20, len * j + 20 + size.height / 6);

			int randcolor = rand() % 4 + 1;
			//设置坐标和颜色
			block->setPopX(i);
			block->setPopY(j);
			block->setColor(randcolor);

			//把精灵添加到当前场景中
			addChild(block);

			//添加到数组中；
			popSquare[i][j] = block;
		}
	}
 }*/