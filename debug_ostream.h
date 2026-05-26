/*＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
* 
*	デバッグログ表示[debug ostream.h]
* 
* 　作成者 : Asuka Kuroda
* 　作成日 : 2025/4/25
* ----------------------------------------------------------------------------------------------------------
*	shift_JISのみ対応
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝*/
#ifndef DEBUG_OSTREAM_H
#define DEBUG_OSTREAM_H

#include <Windows.h>
#include <sstream>

namespace dOst
{
	class DebugBuf : public	std::basic_stringbuf < char, std::char_traits<char>>
{
public:

	virtual ~DebugBuf() {
		sync();
	}

protected:

	int sync() {
		OutputDebugStringA(str().c_str());
		str(std::basic_string<char>());
		return 0;
	}
};

class DebugOstream : public std::basic_ostream<char, std::char_traits<char>>
{
public:
	DebugOstream() : std::basic_ostream<char,std::char_traits<char>>(new DebugBuf()){}
	~DebugOstream() { delete rdbuf(); }
};
extern DebugOstream dout;
}

#endif // DEBUG_OSTREAM_H