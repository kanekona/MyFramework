#pragma once
#include <string>
#include <unordered_map>
#include "NonCopyable\NonCopyable.hpp"

class StrID;
class StrIDSystem;

class StrIDSystem : private NonCopyable
{
	std::unordered_map<std::string, int> strIDData;
	std::vector<std::string> strData;
	static StrIDSystem* instance;
	explicit StrIDSystem();
	virtual ~StrIDSystem();
	void AddData(const std::string& str);
public:
	static int GetID(const std::string& str);
	static int GetID(const std::string* str);
	static const std::string& GetStr(const StrID& strID);
	static const std::string& GetStr(const StrID* strID);
	static void Create();
	static void Delete();
};

class StrID
{
	int id;
public:
	StrID();
	StrID(const std::string& str);
	StrID(const StrID& strID);
	const std::string& ToString() const;
	bool operator==(const StrID& strID);
	bool operator<(const StrID& strID);
	operator int() const;
	static const std::string defaultID;
};


namespace std
{
	template<> class hash<StrID>
	{
	public:
		std::size_t operator()(const StrID& strID) const { return (int)strID; }
	};
}
