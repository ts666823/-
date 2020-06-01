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

	/*//设置监听,滑动方式交换两个pop
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MyScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MyScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);*/
	//设置监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MyScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	return true;
}

//监听点击
bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	//获取整个屏幕的大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//获取点击的位置
	Point touchPosition = touch->getLocation();
	//将位置信息交给getPopStarSprite函数
	PopSprite* touchPop = getPopStarSprite(visibleSize, touchPosition);
	//初始化记录数据的数组
	PopNearBy = Array::create();
	//如果传递回来的触碰Pop不为NULL
	if (touchPop != NULL)
	{
		PopNearBy = checkPopNearBy(touchPop);
	}
	//log调试
	log("x%i y%i color%i", touchPop->popX, touchPop->popY, touchPop->getColor());
	return true;
}
/*//监听点击
bool MyScene::onTouchBegan(Touch* touch, Event* event)
{
	if (canTouchBegin) {
		//获取整个屏幕的大小
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//获取点击的位置
		touchBeginPosition = touch->getLocation();
		//将位置信息交给getPopStarSprite函数
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

//监听滑动
bool MyScene::onTouchMoved(Touch* touch, Event* event)
{
	if (canMove) {
		//获取整个屏幕的大小
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//获取滑动结束后的位置
		touchEndPosition = touch->getLocation();
		//将位置信息交给getPopStarSprite函数
		touchPopEnd = getPopStarSprite(visibleSize, touchBeginPosition);
		log("endx:%i,endy:%i", touchPopEnd->getPopX(), touchPopEnd->getPopY());
		return true;
	}
	else
	{
		return false;
	}

}*/

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

//检测上下左右的函数
Array* MyScene::checkPopNearBy(PopSprite* popStar)
{
	//用数组储存数据
	Array* tempArr = Array::create();
	//判断是否相同颜色
	canRemove = false;
	//获取点击位置的x，y坐标
	int y = popStar->getPopY();
	int x = popStar->getPopX();
	int yUpCount = 0;
	int yDownCount = 0;
	int xRightCount = 0;
	int xLeftCount = 0;
	//判断点击位置向上的相同色块数
	for (int up = y + 1; up < 10; up++)
	{
		if (popSquare[x][up]->getColor() == popSquare[x][y]->getColor())
		{
			yUpCount++;
		}
		else
			break;
	}
	//判断点击位置向下的相同色块数
	for (int down = y - 1; down >= 0; down--)
	{
		if (popSquare[x][down]->getColor() == popSquare[x][y]->getColor())
		{
			yDownCount++;
		}
		else
			break;
	}
	//判断点击位置向右的相同色块数
	for (int right = x + 1; right < 10; right++)
	{
		if (popSquare[right][y]->getColor() == popSquare[x][y]->getColor())
		{
			xRightCount++;
		}
		else
			break;
	}
	//判断点击位置向左的相同色块数
	for (int left = x - 1; left >= 0; left--)
	{
		if (popSquare[left][y]->getColor() == popSquare[x][y]->getColor())
		{
			xLeftCount++;
		}
		else
			break;
	}

	//大于3就可以消除
	if (yUpCount + yDownCount >= 2)
	{
		canRemove = true;
		for (int i = 1; i <= yUpCount; i++)
		{
			tempArr->addObject(popSquare[x][y + i]);
			//消除变成灰色，调试用
			popSquare[x][y + i]->setColor(-1);
		}
		for (int i = 1; i <= yDownCount; i++)
		{
			tempArr->addObject(popSquare[x][y - i]);
			//消除变成灰色，调试用
			popSquare[x][y - i]->setColor(-1);
		}
	}
	if (xRightCount + xLeftCount >= 2)
	{
		canRemove = true;
		for (int i = 1; i <= xRightCount; i++)
		{
			tempArr->addObject(popSquare[x+i][y]);
			//消除变成灰色，调试用
			popSquare[x+i][y]->setColor(-1);
		}
		for (int i = 1; i <= xLeftCount; i++)
		{
			tempArr->addObject(popSquare[x-i][y]);
			//消除变成灰色，调试用
			popSquare[x-i][y]->setColor(-1);
		}
	}
	
	if (canRemove)
	{
		//消除变成灰色，调试用
		popSquare[x][y]->setColor(-1);
		//可以消除就把该点加入；
		tempArr->addObject(popSquare[x][y]);
		
	}
	return tempArr;
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

		checkPopNearBy(popSquare[x][y]);
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