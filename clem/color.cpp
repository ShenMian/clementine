
#include "color.h"

using std::string;
using std::to_string;
using std::vector;
using std::unordered_map;

unordered_map<ushort, string> Color::index;
vector<const string*> Color::stack;

Color::Color()
{
}

Color::Color(ushort attr)
{
	const auto it = index.find(attr);
	if(it == index.end())
	{
		auto pair = index.insert({attr, compile(attr)});
		pString = &pair.first->second;
	}
	else
		pString = &it->second;
}

void Color::on() const
{
	printf("%s", pString->c_str());
}

void Color::off() const
{
	printf("%s", "\x1b[0m");
}

void Color::push()
{
	printf("%s", pString->c_str());
	stack.push_back(pString);
}

void Color::pop()
{
	stack.pop_back();
	if(stack.empty())
		printf("%s", "\x1b[0m");
	else
		printf("%s", stack.back()->c_str());
}

const string& Color::getString() const
{
	return *pString;
}

string Color::compile(ushort attr) const
{
	const auto fore  = attr & fore_mask;
	const auto back  = (attr & back_mask) >> 4;
	const auto style = (attr & style_mask) >> 8;

	string str = "\x1b[";

	if(fore)
		str += '3' + to_string(fore - 1) + ';';
	if(back)
		str += '4' + to_string(back - 1) + ';';
	
	str.pop_back();
	str += 'm';
	return str;
}

