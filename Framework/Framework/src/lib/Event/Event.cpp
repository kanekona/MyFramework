#include "Event.h"
#include "ResourceLoad\ResourceLoad.h"
#include "WindowEvent\WindowEvent.h"
#include "ConfigInput\ConfigInputEvent.h"
CEventTask::CEventTask()
{

}
CEventTask::~CEventTask()
{

}
bool CEventTask::Load(const EEvent& eventType, const std::string& path)
{
	//もしそのファイルがほかで開かれているなら閉じる
	if (ifs.is_open())
	{
		ifs.close();
	}
	//ファイルを開く
	ifs.open(path);
	//存在しない場合終了する
	if (!ifs)
	{
		return false;
	}
	//読み込んだファイルを指定した種類のEventで実行する
	switch (eventType)
	{
	case EEvent::RESOURCE_LOAD:
	{
		//constructorで処理が終わるので生成してdeleteする
		CResourceLoad* rl = new CResourceLoad(ifs);
		delete rl;
	}
	break;
	case EEvent::WINDOW_CHANGE:
	{
		CWindowEvent* we = new CWindowEvent(ifs);
		delete we;
	}
	break;
	case EEvent::INPUT_CONFIG:
	{
		CConfigInputEvent* ci = new CConfigInputEvent(ifs);
		delete ci;
	}
	break;
		break;
	}
	return true;
}