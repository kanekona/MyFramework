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
	//�������̃t�@�C�����ق��ŊJ����Ă���Ȃ����
	if (ifs.is_open())
	{
		ifs.close();
	}
	//�t�@�C�����J��
	ifs.open(path);
	//���݂��Ȃ��ꍇ�I������
	if (!ifs)
	{
		return false;
	}
	//�ǂݍ��񂾃t�@�C�����w�肵����ނ�Event�Ŏ��s����
	switch (eventType)
	{
	case Event::RESOURCE_LOAD:
	{
		//constructor�ŏ������I���̂Ő�������delete����
		ResourceLoad* rl = new ResourceLoad(ifs);
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