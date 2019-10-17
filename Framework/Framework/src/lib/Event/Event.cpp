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
	case EEvent::RESOURCE_LOAD:
	{
		//constructor�ŏ������I���̂Ő�������delete����
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