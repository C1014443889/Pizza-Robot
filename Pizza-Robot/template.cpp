// Includes, namespace and prototypes
#include "template.h"
using namespace AGK;
app App;

//�ƶ������˳Ե�������ֵ�����

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
//ͼ������
const int ROBOT_IMAGE=1;
const int PIZZA_IMAGE=2;
const int YUM_IMAGE=3;
//��������
const int ROBOT_INDEX=1;
const int PIZZA_INDEX=2;
const int YUM_INDEX=3;
//����֡
const int FRAME_WIDTH=128;
const int FRAME_HEIGHT=128;
const int FRAME_COUNT=3;

//�������ƶ�����
const float robotMove=4;
const int HALF_SECOND=500;

void generatePizza();
void updateRoot();
void detectCollision();
void showYum();

// Begin app, called once at the start
void app::Begin( void )
{
	//���ñ��⡢��Ļ
	agk::SetWindowTitle("PizzaBot");
	agk::SetVirtualResolution(SCREEN_WIDTH,SCREEN_HEIGHT);

	//����ͼ��
	agk::LoadImage(ROBOT_IMAGE,"PizzaBot/Robot.png");
	agk::LoadImage(PIZZA_IMAGE,"PizzaBot/Pizza.png");
	agk::LoadImage(YUM_IMAGE,"PizzaBot/Yum.png");

	//��������
	agk::CreateSprite(ROBOT_INDEX,ROBOT_IMAGE);
	agk::CreateSprite(PIZZA_INDEX,PIZZA_IMAGE);
	agk::CreateSprite(YUM_INDEX,YUM_IMAGE);

	//���ö���֡
	agk::SetSpriteAnimation(ROBOT_INDEX,FRAME_WIDTH,FRAME_HEIGHT,FRAME_COUNT);

	//���û����˵�λ��
	agk::SetSpritePosition(ROBOT_INDEX,0,SCREEN_HEIGHT-FRAME_HEIGHT);

	//���Ŷ���֡
	agk::PlaySprite(ROBOT_INDEX);

	//��������
	generatePizza();
}

// Main loop, called every frame
void app::Loop ( void )
{
	//���»����˵�λ��
	updateRoot();
	//�������˺������Ƿ��ͻ
	detectCollision();
	//ˢ����Ļ
	agk::Sync();
}

// Called when the app ends
void app::End ( void )
{
}


//��������
void generatePizza()
{
	//��ȡ�����Ŀ���
	float pizzaWidth=agk::GetSpriteWidth(PIZZA_INDEX);
	float pizzaHeight=agk::GetSpriteHeight(PIZZA_INDEX);

	//�������������λ�ã���һ���ķ�Χ��
	float maxX=SCREEN_WIDTH-pizzaWidth;
	float maxY=SCREEN_HEIGHT-pizzaHeight;
	float x=(float)(agk::Random(0,(int)maxX));
	float y=(float)(agk::Random(0,(int)maxY));

	//����Yumͼ
	agk::SetSpriteVisible(YUM_INDEX,0);

	//����������Yumͼ����λ�ã�������Yumͼ��ͬһλ�ã�
	agk::SetSpritePosition(PIZZA_INDEX,x,y);
	agk::SetSpritePosition(YUM_INDEX,x,y);

	//�������ӻ�
	agk::SetSpriteVisible(PIZZA_INDEX,1);
}


//���»����˵�λ��
void updateRoot()
{
	//��ȡ�����˵�λ��
	float rootX=agk::GetSpriteX(ROBOT_INDEX);
	float rootY=agk::GetSpriteY(ROBOT_INDEX);

	//�ж��Ƿ���down����up����left����right��
	if(agk::GetRawKeyState(AGK_KEY_DOWN))
	{
		rootY+=robotMove;
	}
	if(agk::GetRawKeyState(AGK_KEY_UP))
	{
		rootY-=robotMove;
	}

	if(agk::GetRawKeyState(AGK_KEY_LEFT))
	{
		rootX-=robotMove;
	}

	if(agk::GetRawKeyState(AGK_KEY_RIGHT))
	{
		rootX+=robotMove;
	}

	//���»����˵�λ��
	agk::SetSpritePosition(ROBOT_INDEX,rootX,rootY);
}

//��ʾYum
void showYum()
{
	//����pizza,��ʾYum
	agk::SetSpriteVisible(PIZZA_INDEX,0);
	agk::SetSpriteVisible(YUM_INDEX,1);
	agk::Sync();//ˢ����Ļ
	agk::Sleep(HALF_SECOND);//�ӳٰ���
}


//�����˺������Ƿ��ͻ
void detectCollision()
{
	//���
	if(agk::GetSpriteCollision(ROBOT_INDEX,PIZZA_INDEX))
	{
		//��ʾYum
	     showYum();
		 //�����µ�����
		 generatePizza();
	}

}