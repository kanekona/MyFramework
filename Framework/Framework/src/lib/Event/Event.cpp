#include "Event.h"
#include "ResourceLoad\ResourceLoad.h"
#include "WindowEvent\WindowEvent.h"
#include "ConfigInput\ConfigInputEvent.h"
EventTask::EventTask()
{

}
EventTask::~EventTask()
{

}
bool EventTask::Load(const Event& eventType, const std::string& path)
{
	//もしそのファイルがほかで開かれているなら閉じる
	if (this->ifs.is_open())
	{
		this->ifs.close();
	}
	//ファイルを開く
	this->ifs.open(path);
	//存在しない場合終了する
	if (!this->ifs)
	{
		return false;
	}
	//読み込んだファイルを指定した種類のEventで実行する
	switch (eventType)
	{
	case Event::RESOURCE_LOAD:
	{
		//constructorで処理が終わるので生成してdeleteする
		ResourceLoad* rl = new ResourceLoad(this->ifs);
		delete rl;
	}
	break;
	case Event::WINDOW_CHANGE:
	{
		WindowEvent* we = new WindowEvent(ifs);
		delete we;
	}
	break;
	case Event::INPUT_CONFIG:
	{
		ConfigInputEvent* ci = new ConfigInputEvent(ifs);
		delete ci;
	}
	break;
		break;
	}
	return true;
}