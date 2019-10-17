#pragma once
#include <string>
#include <unordered_map>
#include "Engine\EngineTypedef.h"
#include "NonCopyable\NonCopyable.hpp"

class CStrID;
class CStrIDSystem;

class CStrIDSystem : private CNonCopyable
{
	std::unordered_map<std::string, uint32> strIDData;
	std::vector<std::string> strData;
	static CStrIDSystem* instance;
	explicit CStrIDSystem();
	virtual ~CStrIDSystem();
	void AddData(const std::string& str);
public:
	static uint32 GetID(const std::string& str);
	static uint32 GetID(const std::string* str);
	static const std::string& GetStr(const CStrID& CStrID);
	static const std::string& GetStr(const CStrID* CStrID);
	static void Create();
	static void Delete();
};

class CStrID
{
	uint32 id;
public:
	CStrID();
	CStrID(const std::string& str);
	CStrID(const char* str);
	CStrID(const CStrID& CStrID);
	const std::string& ToString() const;
	bool operator==(const CStrID& CStrID);
	bool operator<(const CStrID& CStrID);
	operator uint32() const;
	static const std::string defaultID;
};


namespace std
{
	template<> class hash<CStrID>
	{
	public:
		std::size_t operator()(const CStrID& CStrID) const { return (uint32)CStrID; }
	};
}
