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
	auto sprite = Sprite::create("1.jpg");
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	//产生方阵：
	createPopSquare(visibleSize);
	//绘制方阵
	drawSquare();
	//设置监听
	auto touchListenerBegin = EventListenerTouchOneByOne::create();
	touchListenerBegin->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
	touchListenerBegin->onTouchMoved = CC_CALLBACK_2(MyScene::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListenerBegin, this);

	
}

//监听点击
bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	touchPopBegin = NULL;
	touchPopEnd = NULL;
	if (canTouch) {
		//获取整个屏幕的大小
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//获取点击的位置
		touchBeginPosition = touch->getLocation();
		//将位置信息交给getPopStarSprite函数
		touchPopBegin = getPopStarSprite(visibleSize, touchBeginPosition);
		//log调试
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


//getPopStarSprite函数
PopSprite* MyScene::getPopStarSprite(Size size, Point touch)
{
	//PopSprite 精灵的长和宽
	const int len = (size.width-28) / 10;
	//求出所点的位置在方阵中的位置
	float touchX = (touch.x-28) / len;
	float touchY = (touch.y - 20-size.height / 6) / len;
	if (touchX < 10 && touchY < 10 && touchX >= 0 && touchY >= 0)
	{
		return popSquare[(int)touchX][(int)touchY];
	}
	else
		return NULL;
}

// 填充空白方阵，保证没有可消除的组合,dfs
void MyScene::fillSquare(int x, int y)
{
	// 遇到边界则返回
	if (x == -1 || x == 10 || y == -1 || y == 10)
		return;

	// 随机生成类型
	int randcolor = rand() % 4 + 1;

	// 填充
	if (popSquare[x][y]->getColor() == -1)
	{
		popSquare[x][y]->setColor(randcolor);

		checkPopCanRemove();
		// 如果没有消除则继续填充
		if (!canRemove)
		{
			// 四个方向递归填充
			fillSquare(x + 1, y);
			fillSquare(x - 1, y);
			fillSquare(x, y - 1);
			fillSquare(x, y + 1);
		}
		else
			popSquare[x][y]->setColor(-1); // 还原
	}
}

//绘制方阵
void MyScene::drawSquare()
{
	srand(unsigned(time(0))); // 初始化随机数发生器

	// 先在内存中生成，保证初始没有可消除的
	fillSquare(0, 0);

	// 如果生成的方阵的含有可以消除的
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

	//如果需要重新绘制
	if (isNeedRegenerate)
	{
		CCLOG("redraw game board");
		drawSquare();
		return;
	}
}

//添加产生的方阵
void MyScene::createPopSquare(Size size) {
	//每一个色块的长宽设置
	const int len = (size.width - 28) / 10;
	//放置色块
	for (int i = 0; i < squareWidth; i++)
	{
		for (int j = 0; j < squareHeight ; j++)
		{
			//设置block方块
			PopSprite* block = PopSprite::createPopSprite(-1, len, len, len * i + 20, len * j + 20 + size.height / 6);
			
			//设置坐标和颜色
			block->setPopX(i);
			block->setPopY(j);
			block->setColor(-1);

			//把精灵添加到当前场景中
			addChild(block);

			//添加到数组中；
			popSquare[i][j] = block;
		}
	}
}

//检测消除的函数
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

	//下降填充
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
			{  //如果该列有消除就降落原来的方块
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
 }

Point MyScene::getPositionOfPop(Size size,int row,int col)
{
	const int len = (size.width - 28) / 10;
	float x = len * row + 20;
	float y = len * (col) + 20 + size.height / 6;
	return Point(x, y);
}