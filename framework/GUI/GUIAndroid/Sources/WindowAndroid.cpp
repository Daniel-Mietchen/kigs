#include "PrecompiledHeaders.h"

#include "WindowAndroid.h"

#include "ModuleGUIAndroid.h"

#include "RenderingScreen.h"

#include "Core.h"

IMPLEMENT_CLASS_INFO(WindowAndroid)

//! constructor
WindowAndroid::WindowAndroid(const kstl::string& name,CLASS_NAME_TREE_ARG) : Window(name,PASS_CLASS_NAME_TREE_ARG)
{
   mScreen=0;
   // on android only one fullscreen window
   mPositionX = 0;
   mPositionY = 0;
   
}

//! destructor
WindowAndroid::~WindowAndroid()
{  
	//! destroy rendering screen
	if(mScreen)
		mScreen->Destroy();

}    

//! init the window, and if OK, show it
void WindowAndroid::ProtectedInit()
{
	Show();
}

//! show window
void  WindowAndroid::Show()
{
	if(mScreen && !mScreen->IsInit())
	{
		mScreen->setValue("ParentWindowName",getName());
		mScreen->Init();
	}
}    

//! update window
void  WindowAndroid::Update(const Timer&  timer, void* addParam)
{
	//! call screen update
	if(mScreen)
		mScreen->CallUpdate(timer,addParam);
}    


void	WindowAndroid::GetMousePosInWindow(int posx,int posy,kfloat& wposx,kfloat& wposy)
{
	posx -= (int)mPositionX;
	posy -= (int)mPositionY;
	wposx = (kfloat)posx;
	wposy = (kfloat)posy;
	return;

	posx -= (int)mPositionX;
	if(posx >= (int)mSizeX)
		posx = ((int)mSizeX)-1;
	if(posx < 0)
		posx = 0;

	posy -= (int)mPositionY;
	if(posy>=(int)mSizeY)
		posy = ((int)mSizeY)-1;
	if(posy < 0)
		posy = 0;

	if(mScreen)
	{
		mScreen->GetMousePosInScreen(posx,posy,wposx,wposy);
	}
	else
	{
		wposx=(kfloat)posx;
		wposy=(kfloat)posy;
	}
}

void	WindowAndroid::GetMousePosInDesignWindow(int posx,int posy,kfloat& wposx,kfloat& wposy)
{
	posx -= (int)mPositionX;
	if(posx >= (int)mSizeX)
		posx = ((int)mSizeX)-1;
	if(posx < 0)
		posx = 0;

	posy -= (int)mPositionY;
	if(posy>=(int)mSizeY)
		posy = ((int)mSizeY)-1;
	if(posy < 0)
		posy = 0;

	if(mScreen)
	{
		mScreen->GetMousePosInDesignScreen(posx,posy,wposx,wposy);
	}
	else
	{
		wposx=(kfloat)posx;
		wposy=(kfloat)posy;
	}
}

void WindowAndroid::ShowMouse(bool bOn)
{
}
