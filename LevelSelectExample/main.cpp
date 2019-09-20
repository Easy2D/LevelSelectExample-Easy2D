//---------------------------------------------------------
// �������ƣ��ؿ�ѡ�񳡾�
// ���ߣ�Nomango
// ���뻷����Visual Studio 2019 / Easy2D v2.0.0-beta7
// ��Ŀ���ͣ�Win32 Console Application
//---------------------------------------------------------

#include <easy2d.h>

using namespace easy2d;


//---------------------------------------------------------
// ��������
//---------------------------------------------------------

void EnterScene();		// ��������������
void InitJungle();		// ���� Jungle �ؿ�
void InitChina();		// ���� China �ؿ�
void InitEgypt();		// ���� Egypt �ؿ�
void InitButton();		// ���ذ�ť
void MovePanel();		// �ƶ��ؿ����
void ClickLeft();		// �����ť
void ClickRight();		// ����Ұ�ť


//---------------------------------------------------------
// ȫ�ֱ�������
//---------------------------------------------------------

Scene *		g_Scene;		// ����
Node *		g_Panel;		// �ؿ����
int			g_Level;		// ��ǰѡ�еĹؿ���
Button *	g_LeftButton;	// ��ť
Button *	g_RightButton;	// �Ұ�ť


//---------------------------------------------------------
// ��������
//---------------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (Game::init(L"�ؿ�ѡ��", 320, 480))
	{
		// ���ýڵ�Ĭ�����ĵ�
		Node::setDefaultAnchor(0.5f, 0.5f);
		// ��������������
		EnterScene();

		Game::start();
	}

	Game::destroy();
	return 0;
}

void EnterScene()
{
	// ����һ���ճ���
	g_Scene = new Scene();
	// ���õ�ǰ�ؿ�Ϊ 0
	g_Level = 0;

	// ��������ͼ����
	auto background = new Sprite(L"res/LS00.png");
	// ����ͼ������ʾ
	background->setPos(Window::getSize() / 2);
	// ��С����ͼ
	background->setScale(0.5f, 0.5f);
	// ��ͼƬ��ӵ�������
	g_Scene->addChild(background);

	// �����ؿ�ͼƬ�ϲ�Ϊ panel �ڵ�
	g_Panel = new Node();
	g_Scene->addChild(g_Panel);

	// ���عؿ�ͼƬ
	InitJungle();
	InitChina();
	InitEgypt();

	// ��Ӱ�ť
	InitButton();

	// ���볡��
	SceneManager::enter(g_Scene);
}

void InitJungle()
{
	// ����ͼƬ
	auto JungleImage = new Sprite(L"res/LS13.png");
	JungleImage->setPosY(Window::getHeight() / 2 - 40);
	// ��������
	auto JungleText = new Sprite(L"res/LS10.png");
	JungleText->setPosY(Window::getHeight() - 130);
	// ͼƬ����
	JungleImage->setPosX(Window::getWidth() / 2);
	JungleText->setPosX(JungleImage->getPosX());

	// ������������ӵ� panel �ڵ�
	g_Panel->addChild(JungleImage);
	g_Panel->addChild(JungleText);
}

void InitChina()
{
	// ����ͼƬ
	auto ChinaImage = new Sprite(L"res/LS14.png");
	ChinaImage->setPosY(Window::getHeight() / 2 - 20);
	// ��������
	auto ChinaText = new Sprite(L"res/LS11.png");
	ChinaText->setPosY(Window::getHeight() - 130);
	// ͼƬ����
	ChinaImage->setPosX(Window::getWidth() / 2 + Window::getWidth());
	ChinaText->setPosX(ChinaImage->getPosX());

	// ������������ӵ� panel �ڵ�
	g_Panel->addChild(ChinaImage);
	g_Panel->addChild(ChinaText);
}

void InitEgypt()
{
	// ����ͼƬ
	auto EgyptImage = new Sprite(L"res/LS15.png");
	EgyptImage->setPosY(Window::getHeight() / 2 - 20);
	// ��������λ��
	auto EgyptText = new Sprite(L"res/LS12.png");
	EgyptText->setPosY(Window::getHeight() - 130);
	// ͼƬ����
	EgyptImage->setPosX(Window::getWidth() / 2 + Window::getWidth() * 2);
	EgyptText->setPosX(EgyptImage->getPosX());

	// ������������ӵ� panel �ڵ�
	g_Panel->addChild(EgyptImage);
	g_Panel->addChild(EgyptText);
}

void InitButton()
{
	// ������ʼ��ť
	auto startBtn = new Button();
	// ���ð�ťͼƬ
	startBtn->setNormal(new Sprite(L"res/LS07.png"));
	// ���ð�ť��ѡ��ʱ��ͼƬ
	startBtn->setSelected(new Sprite(L"res/LS08.png"));
	// ���ð�ť����ʱ��ͼƬ
	startBtn->setDisabled(new Sprite(L"res/LS09.png"));
	// ���ð�ťλ��
	startBtn->setPos(Window::getWidth() / 2, Window::getHeight() - 80);
	// ��ӿ�ʼ��ť
	g_Scene->addChild(startBtn);

	// ������ѡ��ť
	g_LeftButton = new Button();
	g_LeftButton->setNormal(new Sprite(L"res/LS01.png"));
	g_LeftButton->setSelected(new Sprite(L"res/LS02.png"));
	g_LeftButton->setDisabled(new Sprite(L"res/LS03.png"));
	g_LeftButton->setPosX(g_LeftButton->getWidth() / 2);
	g_LeftButton->setPosY((Window::getHeight() - g_LeftButton->getHeight()) / 2);
	g_LeftButton->setEnable(false);
	g_Scene->addChild(g_LeftButton);

	// �����ťִ�� ClickLeft ����
	g_LeftButton->setClickFunc(ClickLeft);

	// ������ѡ��ť
	g_RightButton = new Button();
	g_RightButton->setNormal(new Sprite(L"res/LS04.png"));
	g_RightButton->setSelected(new Sprite(L"res/LS05.png"));
	g_RightButton->setDisabled(new Sprite(L"res/LS06.png"));
	g_RightButton->setPosX(Window::getWidth() - g_RightButton->getWidth() / 2);
	g_RightButton->setPosY((Window::getHeight() - g_RightButton->getHeight()) / 2);
	g_Scene->addChild(g_RightButton);

	// ����Ұ�ťִ�� ClickRight ����
	g_RightButton->setClickFunc(ClickRight);
}

void ClickLeft()
{
	// level Ϊ 1 ʱ��������ѡ��ť
	if (g_Level == 1) {
		g_LeftButton->setEnable(false);
	}
	// ������ѡ��ť�󣬰���ѡ��ť����
	g_RightButton->setEnable(true);
	// level ��һ
	g_Level--;
	// �ƶ� panel
	MovePanel();
}

void ClickRight()
{
	// level Ϊ 1 ʱ��������ѡ��ť
	if (g_Level == 1) {
		g_RightButton->setEnable(false);
	}
	// ������ѡ��ť�󣬰���ѡ��ť����
	g_LeftButton->setEnable(true);
	// level ��һ
	g_Level++;
	// �ƶ� panel
	MovePanel();
}

void MovePanel()
{
	// ����Ŀ���
	auto point = Point(-Window::getWidth() * g_Level, 0);
	// �����ƶ�����
	auto action = new MoveTo(0.5f, point);
	// ֹͣ panel �����ж���
	g_Panel->stopAllActions();
	// ִ���¶���
	g_Panel->runAction(action);
}
