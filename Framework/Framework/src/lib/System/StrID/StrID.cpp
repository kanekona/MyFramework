#include "StrID.h"
#include <tuple>
StrIDSystem::StrIDSystem()
{
	strIDData.clear();
	AddData(StrID::defaultID);
}
StrIDSystem::~StrIDSystem()
{
	strData.clear();
	strIDData.clear();
}
void StrIDSystem::AddData(const std::string & str)
{
	strIDData.insert(std::make_pair(str, static_cast<int>(strData.size())));
	strData.emplace_back(str);
}
int StrIDSystem::GetID(const std::string & str)
{
	if (instance->strIDData.count(str) == 0)
	{
		instance->AddData(str);
	}
	return instance->strIDData[str];
}

int StrIDSystem::GetID(const std::string * str)
{
	return GetID(*str);
}

const std::string & StrIDSystem::GetStr(const StrID & strID)
{
	return instance->strData[(int)strID];
}

const std::string & StrIDSystem::GetStr(const StrID * strID)
{
	return GetStr(*strID);
}

void StrIDSystem::Create()
{
	if (!instance)
	{
		instance = new StrIDSystem();
	}
}
void StrIDSystem::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
StrIDSystem* StrIDSystem::instance = nullptr;

StrID::StrID()
{
	id = StrIDSystem::GetID(defaultID);
}

StrID::StrID(const std::string & str)
{
	id = StrIDSystem::GetID(str);
}

StrID::StrID(const StrID & strID)
{
	id = strID.id;
}

const std::string & StrID::ToString() const
{
	return StrIDSystem::GetStr(this);
}

bool StrID::operator==(const StrID& strID)
{
	return id == strID.id;
}

bool StrID::operator<(const StrID& strID)
{
	return std::tie(id) < std::tie(strID.id);
}

StrID::operator int() const
{
	return id;
}

const std::string StrID::defaultID = "None";