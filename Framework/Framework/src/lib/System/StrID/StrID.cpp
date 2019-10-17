#include "StrID.h"
#include <tuple>
CStrIDSystem::CStrIDSystem()
{
	strIDData.clear();
	AddData(CStrID::defaultID);
}
CStrIDSystem::~CStrIDSystem()
{
	strData.clear();
	strIDData.clear();
}
void CStrIDSystem::AddData(const std::string & str)
{
	strIDData.insert(std::make_pair(str, static_cast<uint32>(strData.size())));
	strData.emplace_back(str);
}
uint32 CStrIDSystem::GetID(const std::string & str)
{
	if (instance->strIDData.count(str) == 0)
	{
		instance->AddData(str);
	}
	return instance->strIDData[str];
}

uint32 CStrIDSystem::GetID(const std::string * str)
{
	return GetID(*str);
}

const std::string & CStrIDSystem::GetStr(const CStrID & CStrID)
{
	return instance->strData[(uint32)CStrID];
}

const std::string & CStrIDSystem::GetStr(const CStrID * CStrID)
{
	return GetStr(*CStrID);
}

void CStrIDSystem::Create()
{
	if (!instance)
	{
		instance = new CStrIDSystem();
	}
}
void CStrIDSystem::Delete()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}
CStrIDSystem* CStrIDSystem::instance = nullptr;

CStrID::CStrID()
{
	id = CStrIDSystem::GetID(defaultID);
}

CStrID::CStrID(const std::string & str)
{
	id = CStrIDSystem::GetID(str);
}

CStrID::CStrID(const char * str)
{
	id = CStrIDSystem::GetID(str);
}

CStrID::CStrID(const CStrID & CStrID)
{
	id = CStrID.id;
}

const std::string & CStrID::ToString() const
{
	return CStrIDSystem::GetStr(this);
}

bool CStrID::operator==(const CStrID& CStrID)
{
	return id == CStrID.id;
}

bool CStrID::operator<(const CStrID& CStrID)
{
	return std::tie(id) < std::tie(CStrID.id);
}

CStrID::operator uint32() const
{
	return id;
}

const std::string CStrID::defaultID = "None";