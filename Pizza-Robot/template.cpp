// Includes, namespace and prototypes
#include "template.h"
using namespace AGK;
app App;

//移动机器人吃掉随机出现的披萨

const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
//图像索引
const int ROBOT_IMAGE=1;
const int PIZZA_IMAGE=2;
const int YUM_IMAGE=3;
//精灵索引
const int ROBOT_INDEX=1;
const int PIZZA_INDEX=2;
const int YUM_INDEX=3;
//动画帧
const int FRAME_WIDTH=128;
const int FRAME_HEIGHT=128;
const int FRAME_COUNT=3;

//机器人移动距离
const float robotMove=4;
const int HALF_SECOND=500;

void generatePizza();
void updateRoot();
void detectCollision();
void showYum();

// Begin app, called once at the start
void app::Begin( void )
{
	//设置标题、屏幕
	agk::SetWindowTitle("PizzaBot");
	agk::SetVirtualResolution(SCREEN_WIDTH,SCREEN_HEIGHT);

	//加载图像
	agk::LoadImage(ROBOT_IMAGE,"PizzaBot/Robot.png");
	agk::LoadImage(PIZZA_IMAGE,"PizzaBot/Pizza.png");
	agk::LoadImage(YUM_IMAGE,"PizzaBot/Yum.png");

	//创建精灵
	agk::CreateSprite(ROBOT_INDEX,ROBOT_IMAGE);
	agk::CreateSprite(PIZZA_INDEX,PIZZA_IMAGE);
	agk::CreateSprite(YUM_INDEX,YUM_IMAGE);

	//设置动画帧
	agk::SetSpriteAnimation(ROBOT_INDEX,FRAME_WIDTH,FRAME_HEIGHT,FRAME_COUNT);

	//设置机器人的位置
	agk::SetSpritePosition(ROBOT_INDEX,0,SCREEN_HEIGHT-FRAME_HEIGHT);

	//播放动画帧
	agk::PlaySprite(ROBOT_INDEX);

	//产生披萨
	generatePizza();
}

// Main loop, called every frame
void app::Loop ( void )
{
	//更新机器人的位置
	updateRoot();
	//检查机器人和披萨是否冲突
	detectCollision();
	//刷新屏幕
	agk::Sync();
}

// Called when the app ends
void app::End ( void )
{
}


//产生披萨
void generatePizza()
{
	//获取披萨的宽、高
	float pizzaWidth=agk::GetSpriteWidth(PIZZA_INDEX);
	float pizzaHeight=agk::GetSpriteHeight(PIZZA_INDEX);

	//计算披萨的随机位置（有一定的范围）
	float maxX=SCREEN_WIDTH-pizzaWidth;
	float maxY=SCREEN_HEIGHT-pizzaHeight;
	float x=(float)(agk::Random(0,(int)maxX));
	float y=(float)(agk::Random(0,(int)maxY));

	//隐藏Yum图
	agk::SetSpriteVisible(YUM_INDEX,0);

	//设置披萨、Yum图的新位置（披萨、Yum图在同一位置）
	agk::SetSpritePosition(PIZZA_INDEX,x,y);
	agk::SetSpritePosition(YUM_INDEX,x,y);

	//披萨可视化
	agk::SetSpriteVisible(PIZZA_INDEX,1);
}


//更新机器人的位置
void updateRoot()
{
	//获取机器人的位置
	float rootX=agk::GetSpriteX(ROBOT_INDEX);
	float rootY=agk::GetSpriteY(ROBOT_INDEX);

	//判断是否按下down键、up键、left键、right键
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

	//更新机器人的位置
	agk::SetSpritePosition(ROBOT_INDEX,rootX,rootY);
}

//显示Yum
void showYum()
{
	//隐藏pizza,显示Yum
	agk::SetSpriteVisible(PIZZA_INDEX,0);
	agk::SetSpriteVisible(YUM_INDEX,1);
	agk::Sync();//刷新屏幕
	agk::Sleep(HALF_SECOND);//延迟半秒
}


//机器人和披萨是否冲突
void detectCollision()
{
	//检测
	if(agk::GetSpriteCollision(ROBOT_INDEX,PIZZA_INDEX))
	{
		//显示Yum
	     showYum();
		 //产生新的披萨
		 generatePizza();
	}

}