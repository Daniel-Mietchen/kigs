#include "PrecompiledHeaders.h"
#include "ModuleTimer.h"
#include "Timer.h"
#include "TimeProfiler.h"
#include "ControlledTimer.h"

IMPLEMENT_CLASS_INFO(ModuleTimer)

ModuleTimer::ModuleTimer(const kstl::string& name,CLASS_NAME_TREE_ARG) : ModuleBase(name,PASS_CLASS_NAME_TREE_ARG)
{
}

ModuleTimer::~ModuleTimer()
{
}    

void ModuleTimer::Init(KigsCore* core, const kstl::vector<CoreModifiableAttribute*>* params)
{
    BaseInit(core,"Timer",params);

	core->RegisterMainModuleList(this,TimerModuleCoreIndex);

	DECLARE_FULL_CLASS_INFO(KigsCore::Instance(), Timer, Timer, Timer);
	DECLARE_FULL_CLASS_INFO(KigsCore::Instance(), TimeProfiler,TimeProfiler,Timer);
	DECLARE_FULL_CLASS_INFO(KigsCore::Instance(), ControlledTimer, ControlledTimer, Timer);

}

void ModuleTimer::Close()
{
    BaseClose();
}    

void ModuleTimer::Update(const Timer& timer, void* addParam)
{
	BaseUpdate(timer,addParam);

	// update tickers

	kstl::map<CoreModifiable*,CoreModifiable*>::iterator	itTickers=mTickerList.begin();
	while(itTickers!=mTickerList.end())
	{
		(*itTickers).first->CallUpdate(timer,addParam);
		++itTickers;
	}
}    


bool	ModuleTimer::addItem(const CMSP& item, ItemPosition pos DECLARE_LINK_NAME)
{
	if(item->isSubType("TimeTicker"))
	{
		CoreModifiable* i = item.Pointer();
		if(mTickerList.find(i)==mTickerList.end())
		{
			mTickerList[i]=i;
		}
	}

	return CoreModifiable::addItem(item,pos PASS_LINK_NAME(linkName));
}

bool	ModuleTimer::removeItem(const CMSP& item DECLARE_LINK_NAME)
{
	if(item->isSubType("TimeTicker"))
	{
		CoreModifiable* i = item.get();
		if(mTickerList.find(i)!=mTickerList.end())
		{
			mTickerList.erase(i);
		}
	}

	return CoreModifiable::removeItem(item PASS_LINK_NAME(linkName));
}
