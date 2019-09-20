//---------------------------------------------------------
// 程序名称：关卡选择场景
// 作者：Nomango
// 编译环境：Visual Studio 2019 / Easy2D v2.0.0-beta7
// 项目类型：Win32 Console Application
//---------------------------------------------------------

#include <easy2d.h>

using namespace easy2d;


//---------------------------------------------------------
// 函数声明
//---------------------------------------------------------

void EnterScene();		// 创建场景并进入
void InitJungle();		// 加载 Jungle 关卡
void InitChina();		// 加载 China 关卡
void InitEgypt();		// 加载 Egypt 关卡
void InitButton();		// 加载按钮
void MovePanel();		// 移动关卡面板
void ClickLeft();		// 点击左按钮
void ClickRight();		// 点击右按钮


//---------------------------------------------------------
// 全局变量声明
//---------------------------------------------------------

Scene *		g_Scene;		// 场景
Node *		g_Panel;		// 关卡面板
int			g_Level;		// 当前选中的关卡数
Button *	g_LeftButton;	// 左按钮
Button *	g_RightButton;	// 右按钮


//---------------------------------------------------------
// 函数定义
//---------------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (Game::init(L"关卡选择", 320, 480))
	{
		// 设置节点默认中心点
		Node::setDefaultAnchor(0.5f, 0.5f);
		// 创建场景并进入
		EnterScene();

		Game::start();
	}

	Game::destroy();
	return 0;
}

void EnterScene()
{
	// 创建一个空场景
	g_Scene = new Scene();
	// 设置当前关卡为 0
	g_Level = 0;

	// 创建背景图对象
	auto background = new Sprite(L"res/LS00.png");
	// 背景图居中显示
	background->setPos(Window::getSize() / 2);
	// 缩小背景图
	background->setScale(0.5f, 0.5f);
	// 将图片添加到场景中
	g_Scene->addChild(background);

	// 三个关卡图片合并为 panel 节点
	g_Panel = new Node();
	g_Scene->addChild(g_Panel);

	// 加载关卡图片
	InitJungle();
	InitChina();
	InitEgypt();

	// 添加按钮
	InitButton();

	// 进入场景
	SceneManager::enter(g_Scene);
}

void InitJungle()
{
	// 创建图片
	auto JungleImage = new Sprite(L"res/LS13.png");
	JungleImage->setPosY(Window::getHeight() / 2 - 40);
	// 创建文字
	auto JungleText = new Sprite(L"res/LS10.png");
	JungleText->setPosY(Window::getHeight() - 130);
	// 图片居中
	JungleImage->setPosX(Window::getWidth() / 2);
	JungleText->setPosX(JungleImage->getPosX());

	// 将两个精灵添加到 panel 节点
	g_Panel->addChild(JungleImage);
	g_Panel->addChild(JungleText);
}

void InitChina()
{
	// 创建图片
	auto ChinaImage = new Sprite(L"res/LS14.png");
	ChinaImage->setPosY(Window::getHeight() / 2 - 20);
	// 创建文字
	auto ChinaText = new Sprite(L"res/LS11.png");
	ChinaText->setPosY(Window::getHeight() - 130);
	// 图片居中
	ChinaImage->setPosX(Window::getWidth() / 2 + Window::getWidth());
	ChinaText->setPosX(ChinaImage->getPosX());

	// 将两个精灵添加到 panel 节点
	g_Panel->addChild(ChinaImage);
	g_Panel->addChild(ChinaText);
}

void InitEgypt()
{
	// 创建图片
	auto EgyptImage = new Sprite(L"res/LS15.png");
	EgyptImage->setPosY(Window::getHeight() / 2 - 20);
	// 设置文字位置
	auto EgyptText = new Sprite(L"res/LS12.png");
	EgyptText->setPosY(Window::getHeight() - 130);
	// 图片居中
	EgyptImage->setPosX(Window::getWidth() / 2 + Window::getWidth() * 2);
	EgyptText->setPosX(EgyptImage->getPosX());

	// 将两个精灵添加到 panel 节点
	g_Panel->addChild(EgyptImage);
	g_Panel->addChild(EgyptText);
}

void InitButton()
{
	// 创建开始按钮
	auto startBtn = new Button();
	// 设置按钮图片
	startBtn->setNormal(new Sprite(L"res/LS07.png"));
	// 设置按钮被选中时的图片
	startBtn->setSelected(new Sprite(L"res/LS08.png"));
	// 设置按钮禁用时的图片
	startBtn->setDisabled(new Sprite(L"res/LS09.png"));
	// 设置按钮位置
	startBtn->setPos(Window::getWidth() / 2, Window::getHeight() - 80);
	// 添加开始按钮
	g_Scene->addChild(startBtn);

	// 创建左选按钮
	g_LeftButton = new Button();
	g_LeftButton->setNormal(new Sprite(L"res/LS01.png"));
	g_LeftButton->setSelected(new Sprite(L"res/LS02.png"));
	g_LeftButton->setDisabled(new Sprite(L"res/LS03.png"));
	g_LeftButton->setPosX(g_LeftButton->getWidth() / 2);
	g_LeftButton->setPosY((Window::getHeight() - g_LeftButton->getHeight()) / 2);
	g_LeftButton->setEnable(false);
	g_Scene->addChild(g_LeftButton);

	// 点击左按钮执行 ClickLeft 函数
	g_LeftButton->setClickFunc(ClickLeft);

	// 创建右选按钮
	g_RightButton = new Button();
	g_RightButton->setNormal(new Sprite(L"res/LS04.png"));
	g_RightButton->setSelected(new Sprite(L"res/LS05.png"));
	g_RightButton->setDisabled(new Sprite(L"res/LS06.png"));
	g_RightButton->setPosX(Window::getWidth() - g_RightButton->getWidth() / 2);
	g_RightButton->setPosY((Window::getHeight() - g_RightButton->getHeight()) / 2);
	g_Scene->addChild(g_RightButton);

	// 点击右按钮执行 ClickRight 函数
	g_RightButton->setClickFunc(ClickRight);
}

void ClickLeft()
{
	// level 为 1 时，禁用左选按钮
	if (g_Level == 1) {
		g_LeftButton->setEnable(false);
	}
	// 按下左选按钮后，把右选按钮启动
	g_RightButton->setEnable(true);
	// level 减一
	g_Level--;
	// 移动 panel
	MovePanel();
}

void ClickRight()
{
	// level 为 1 时，禁用右选按钮
	if (g_Level == 1) {
		g_RightButton->setEnable(false);
	}
	// 按下右选按钮后，把左选按钮启动
	g_LeftButton->setEnable(true);
	// level 加一
	g_Level++;
	// 移动 panel
	MovePanel();
}

void MovePanel()
{
	// 创建目标点
	auto point = Point(-Window::getWidth() * g_Level, 0);
	// 创建移动动画
	auto action = new MoveTo(0.5f, point);
	// 停止 panel 的所有动画
	g_Panel->stopAllActions();
	// 执行新动画
	g_Panel->runAction(action);
}
