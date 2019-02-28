//////////////////////////////////////////////////////////////////////////
//	�ð��� �ٷ�� ��ƿ��Ƽ
//	����� : ������ (whitewitch@logickorea.co.kr / ljh6341@gmail.com)
//	history : 20091111-	8byte�� ������ �����ϱ� ���ٴ� untime32�� untime64�� ������ �����ϱ�� ����
//						�������̽��� ���������� �������̽� Ŭ������ ���� ����� ���ٴ� �׳� �� �ȵǴ� ó������.
//						�Ϲ������� �̸� ȥ���ؼ� ����ϴ� ���� ������..
//			  20100115- untime32�� untime���� ����. �ð� �񱳸� ���� �ϱ� ���ؼ� little endian�� �°� ���� ����. ���� �ð� �����ϱ�.

//	To do : 4byte <->8byte ������ ���
//			DB���� ����� �� �ֵ��� ��¥ ������ �پ��ϰ� ������ ��!
//

#include "common.h"
#include "time.h"

namespace nsTime
{

	union unTime32	//	little endian ������. ������ ��!
	{
		enum
		{
			eTimeFormat_YYYYMMDD_HHMMSS,	//	�⺻..
			eTimeFormat_YYYYMMDD,			//	��¥ ������
			eTimeFormat_HHMMSS,				//	�ð� ������
		};

		enum
		{
			eCompare_ALL,
			eCompare_YYYYMMDD,
			eCompare_HHMMSS,
		};

		enum eTIME_TERM_CHECK
		{
			eTIME_TERM_CHECK_YY,
			eTIME_TERM_CHECK_MM,
			eTIME_TERM_CHECK_DD,
			eTIME_TERM_CHECK_HH,
			eTIME_TERM_CHECK_MIN,
			eTIME_TERM_CHECK_SS,

			eTIME_TERM_CHECK_COUNT,
		};

		struct 
		{
			//	year�� Ȯ������. ���� 20091027 (�������� ���ӻ󿡼� 2090�� �ʿ��� ���� ������..)
			u4	second		:	6;	//	��
			u4	minute		:	6;	//	��
			u4	hour		:	5;	//	��
			u4	day			:	5;	//	��
			u4	month		:	4;	//	��
			u4	year		:	6;	//	�� �Ѱ� ��ġ 63��. 2063 ���Ŀ��� �� ����.
		};

		struct 
		{
			u4	m_value;
		};

		inline	void	reset(){	set(00,01,01,0,0,0);	}	//	2000�� 1�� 1�� 0�� �������� �ʱ�ȭ
		inline unTime32&	operator=(const unTime32& _t)
		{
			m_value = _t.m_value;
			return *this;
		}
		inline  void	set(u4 _year, u4 _month, u4 _day, u4 _hour, u4 _minute, u4 _second)
		{	year = _year; month =_month; day = _day; hour = _hour; minute = _minute; second = _second;
		}
		inline  void	setDate(u4 _year, u4 _month, u4 _day)
		{	year = _year; month =_month; day = _day;
		}
		inline  void	setTime(u4 _hour, u4 _minute, u4 _second)
		{	hour = _hour; minute = _minute; second = _second;
		}

		void setCurrentTime()
		{
			time_t tTime;	struct tm *tmTime;
			tTime = time(NULL);	tmTime = localtime(&tTime);
			set((tmTime->tm_year+1900)%1000,tmTime->tm_mon+1,tmTime->tm_mday, tmTime->tm_hour, tmTime->tm_min,tmTime->tm_sec);
		}

		inline BOOL operator==(const unTime32& _t)	{	return (m_value == _t.m_value); }
		inline BOOL operator!=(const unTime32& _t)	{	return (m_value != _t.m_value); }
		inline BOOL operator>(const unTime32& _t)		{	return (m_value > _t.m_value);	}
		inline BOOL operator>=(const unTime32& _t)	{	return (m_value >= _t.m_value); }
		inline BOOL operator<(const unTime32& _t)		{	return (m_value < _t.m_value);	}
		inline BOOL operator<=(const unTime32& _t)	{	return (m_value <= _t.m_value); }

		BOOL isEqual(const unTime32& _t, s4 _option = eCompare_ALL)
		{
			switch(_option)
			{
			case eCompare_ALL:		return (m_value == _t.m_value);
			case eCompare_YYYYMMDD:	return ((m_value >> 17) == (_t.m_value >> 17));
			case eCompare_HHMMSS:	return ((m_value << 15) == (_t.m_value << 15));
			}
			return FALSE;
		}
		BOOL isNotEqual(const unTime32& _t, s4 _option = eCompare_ALL)
		{
			switch(_option)
			{
			case eCompare_ALL:		return (m_value != _t.m_value);
			case eCompare_YYYYMMDD:	return ((m_value >> 17) != (_t.m_value >> 17));
			case eCompare_HHMMSS:	return ((m_value << 15) != (_t.m_value << 15));
			}
			return FALSE;
		}

		BOOL isGreater(const unTime32& _t, s4 _option = eCompare_ALL)
		{
			switch(_option)
			{
			case eCompare_ALL:		return (m_value > _t.m_value);
			case eCompare_YYYYMMDD:	return ((m_value >> 17) > (_t.m_value >> 17));
			case eCompare_HHMMSS:	return ((m_value << 15) > (_t.m_value << 15));
			}
			return FALSE;
		}
		BOOL isGreaterEqual(const unTime32& _t, s4 _option = eCompare_ALL)
		{
			switch(_option)
			{
			case eCompare_ALL:		return (m_value >= _t.m_value);
			case eCompare_YYYYMMDD:	return ((m_value >> 17) >= (_t.m_value >> 17));
			case eCompare_HHMMSS:	return ((m_value << 15) >= (_t.m_value << 15));
			}
			return FALSE;
		}
		BOOL isLess(const unTime32& _t, s4 _option = eCompare_ALL)
		{
			switch(_option)
			{
			case eCompare_ALL:		return (m_value < _t.m_value);
			case eCompare_YYYYMMDD:	return ((m_value >> 17) < (_t.m_value >> 17));
			case eCompare_HHMMSS:	return ((m_value << 15) < (_t.m_value << 15));
			}
			return FALSE;
		}
		BOOL isLessEqual(const unTime32& _t, s4 _option = eCompare_ALL)
		{
			switch(_option)
			{
			case eCompare_ALL:		return (m_value <= _t.m_value);
			case eCompare_YYYYMMDD:	return ((m_value >> 17) <= (_t.m_value >> 17));
			case eCompare_HHMMSS:	return ((m_value << 15) <= (_t.m_value << 15));
			}
			return FALSE;
		}

		//	���� ����� class�� ���� ���� �����ϴ� ���� �� ����� ��... 091028 ����
		stdString		stringFormat(s4 _format = unTime32::eTimeFormat_YYYYMMDD_HHMMSS)
		{
			stdString strRet = _T("2000-01-01 00:00:00");
			switch(_format)
			{
			case unTime32::eTimeFormat_YYYYMMDD_HHMMSS:
				{
					TCHAR tmp[64];
					_stprintf_s(tmp, 64, _T("%04d-%02d-%02d %02d:%02d:%02d"), 2000+year, month, day, hour, minute, second);
					strRet = tmp;
				}
				break;
			case unTime32::eTimeFormat_YYYYMMDD:
				{
					TCHAR tmp[64];
					_stprintf_s(tmp, 64, _T("%04d-%02d-%02d"), 2000+year, month, day);
					strRet = tmp;
				}
				break;
			case unTime32::eTimeFormat_HHMMSS:
				{
					TCHAR tmp[64];
					_stprintf_s(tmp, 64, _T("%02d:%02d:%02d"), hour, minute, second);
					strRet = tmp;
				}
				break;
			}

			return strRet;
		}

public:
	static unTime32 currentTime() {
		unTime32 time;
		time.setCurrentTime();
		return time;
	}

	static unTime32 epochTime() {
		return unTime32(2000, 1, 1, 0, 0, 0);
	}

	static unTime32 spareTime(unsigned int value) {
		return unTime32(value);
	}

	static unTime32 cTime(time_t t) {
		tm tmLocal;
		localtime_s(&tmLocal, &t);
		return unTime32(tmLocal.tm_year, tmLocal.tm_mon + 1, tmLocal.tm_mday, tmLocal.tm_hour, tmLocal.tm_min, tmLocal.tm_sec);
	}

public:
	unTime32(unsigned int _value = 0) : m_value(_value) {}
	unTime32(const tm& tmSet) {
		set(tmSet);
	}
	unTime32(unsigned int _year, unsigned int _month, unsigned int _day, unsigned int _hour, unsigned int _minute, unsigned int _second) {
		set(_year, _month, _day, _hour, _minute, _second);
	}
	void addHour(int _value) {
		addMinute(_value * 60);
	}

	void addMinute(int _value) {
		addSecond(_value * 60);
	}

	void addSecond(int _value) {
		tm tmAdd = toTm();
		tmAdd.tm_sec += _value;
		const time_t timeAdd = mktime(&tmAdd);
		localtime_s(&tmAdd, &timeAdd);
		set(tmAdd);
	}

	///	���� �ð����� �󸶳� ���̰� ������ ����Ѵ�
	int calcTermFromNow(eTIME_TERM_CHECK _returnType = eTIME_TERM_CHECK_SS) const {
		return calcTerm(unTime32::currentTime(), _returnType);
	}

	int calcTerm(const unTime32& _from, eTIME_TERM_CHECK _returnType = eTIME_TERM_CHECK_SS) const {
		//	time_t�� 64bit �ü������ 64��Ʈ�� ��ȴ�.
		//	�Ʒ� �κ��� �����ؾ߸� �Ѵ�. tRetTime�� 4byte�� ���� �� ������ �ս��� �߻��� �� ����. ���� tRetTime�� ���� Ȯ���ؼ� ��ġ�� ��!
		const time_t tFrom = _from.getLocalTime();
		const time_t tSpTime = getLocalTime();
		const int tRetTime = abs((int)(tFrom - tSpTime));

		switch (_returnType) {
		case eTIME_TERM_CHECK_YY:	//	365�� ����.
			return tRetTime / 946080000/*60 / 60 / 24 / 30 / 365*/;
		case eTIME_TERM_CHECK_MM:	//	30�� ����.
			return tRetTime / 2592000/*60 / 60 / 24 / 30*/;
		case eTIME_TERM_CHECK_DD:
			return tRetTime / 86400 /*60 / 60 / 24*/;
		case eTIME_TERM_CHECK_HH:
			return tRetTime / 3600 /*60 / 60*/;
		case eTIME_TERM_CHECK_MIN:
			return tRetTime / 60;
		}
		return tRetTime;
	}

	//���� �ð� - ���� �ð� �� �ƴ� �̷� �ð� - ���� �ð��� ���� ��� ��� �Ұ�.
	int lastCalcTerm(const unTime32& _from, eTIME_TERM_CHECK _returnType = eTIME_TERM_CHECK_SS) const {
		//	time_t�� 64bit �ü������ 64��Ʈ�� ��ȴ�.
		//	�Ʒ� �κ��� �����ؾ߸� �Ѵ�. tRetTime�� 4byte�� ���� �� ������ �ս��� �߻��� �� ����. ���� tRetTime�� ���� Ȯ���ؼ� ��ġ�� ��!
		const time_t tFrom = _from.getLocalTime();
		const time_t tSpTime = getLocalTime();
		const int tRetTime = abs((int)(tSpTime - tFrom));

		switch (_returnType) {
		case eTIME_TERM_CHECK_YY:	//	365�� ����.
			return tRetTime / 946080000/*60 / 60 / 24 / 30 / 365*/;
		case eTIME_TERM_CHECK_MM:	//	30�� ����.
			return tRetTime / 2592000/*60 / 60 / 24 / 30*/;
		case eTIME_TERM_CHECK_DD:
			return tRetTime / 86400 /*60 / 60 / 24*/;
		case eTIME_TERM_CHECK_HH:
			return tRetTime / 3600 /*60 / 60*/;
		case eTIME_TERM_CHECK_MIN:
			return tRetTime / 60;
		}
		return tRetTime;
	}

public:
	void set(unsigned int _year, unsigned int _month, unsigned int _day, unsigned int _hour, unsigned int _minute, unsigned int _second) {
		year = _year % 100; month = _month; day = _day;
		hour = _hour; minute = _minute; second = _second;
	}

	void set(const tm& tmSet) {
		set(tmSet.tm_year, tmSet.tm_mon + 1, tmSet.tm_mday,
			tmSet.tm_hour, tmSet.tm_min, tmSet.tm_sec);
	}

	void setDate(unsigned int _year, unsigned int _month, unsigned int _day) {
		year = _year % 100;
		month = _month; day = _day;
	}
	void setTime(unsigned int _hour, unsigned int _minute, unsigned int _second) {
		hour = _hour; minute = _minute; second = _second;
	}

	void reset() {
		m_value = 0;
	}

	void setEpochTime() {
		this->set(2000, 1, 1, 0, 0, 0);
	}

	void setCurrentTime() {
		const time_t tTime = time(NULL);
		tm tmTime;
		localtime_s(&tmTime, &tTime);
		set(tmTime);
	}

public:
	time_t getLocalTime() const {
		tm tmt = toTm();
		return mktime(&tmt);
	}

	tm toTm() const {
		tm tmTo;
		tmTo.tm_year = year + 100;
		tmTo.tm_mon = month - 1;
		tmTo.tm_mday = day;
		tmTo.tm_hour = hour;
		tmTo.tm_min = minute;
		tmTo.tm_sec = second;
		tmTo.tm_wday = 0;
		tmTo.tm_yday = 0;
		tmTo.tm_isdst = 0;
		return tmTo;
	}

	std::wstring toString(int _format = unTime32::eTimeFormat_YYYYMMDD_HHMMSS) const {
		//assertEx(isDateTimeType(), "precondition");
		std::wstring strRet;
		__wchar_t str[64];
		switch (_format) {
		case unTime32::eTimeFormat_YYYYMMDD_HHMMSS:
			swprintf_s(str, _T("%04d-%02d-%02d %02d:%02d:%02d"), 2000 + year, month, day, hour, minute, second);
			strRet = str;
			break;
		case unTime32::eTimeFormat_YYYYMMDD:
			swprintf_s(str, _T("%04d-%02d-%02d"), 2000 + year, month, day);
			strRet = str;
			break;
		case unTime32::eTimeFormat_HHMMSS:
			swprintf_s(str, _T("%02d:%02d:%02d"), hour, minute, second);
			strRet = str;
			break;
		default:
			strRet = _T("2000-01-01 00:00:00");
			break;
		}
		return strRet;
	}

public:
	/// @return true: �Ϲ� ��¥ ����, false: ���� �ð��� üũ�ϴ� ����(year���� 0)
	bool isDateTimeType() const {
		return year > 0;
	}

	bool isPassed() const {
		return isLess(unTime32::currentTime());
	}

	bool isEqual(const unTime32& _t, int _option = eCompare_ALL) const {
		switch (_option) {
		case eCompare_ALL:		return (m_value == _t.m_value);
		case eCompare_YYYYMMDD:	return ((m_value >> 17) == (_t.m_value >> 17));
		case eCompare_HHMMSS:	return ((m_value << 15) == (_t.m_value << 15));
		}
		return false;
	}

	bool isGreater(const unTime32& _t, int _option = eCompare_ALL) const {
		switch (_option) {
		case eCompare_ALL:		return (m_value > _t.m_value);
		case eCompare_YYYYMMDD:	return ((m_value >> 17) > (_t.m_value >> 17));
		case eCompare_HHMMSS:	return ((m_value << 15) > (_t.m_value << 15));
		}
		return false;
	}

	bool isGreaterEqual(const unTime32& _t, int _option = eCompare_ALL) const {
		switch (_option) {
		case eCompare_ALL:		return (m_value >= _t.m_value);
		case eCompare_YYYYMMDD:	return ((m_value >> 17) >= (_t.m_value >> 17));
		case eCompare_HHMMSS:	return ((m_value << 15) >= (_t.m_value << 15));
		}
		return false;
	}

	bool isLess(const unTime32& _t, int _option = eCompare_ALL) const {
		switch (_option) {
		case eCompare_ALL:		return (m_value < _t.m_value);
		case eCompare_YYYYMMDD:	return ((m_value >> 17) < (_t.m_value >> 17));
		case eCompare_HHMMSS:	return ((m_value << 15) < (_t.m_value << 15));
		}
		return false;
	}

	bool isLessEqual(const unTime32& _t, int _option = eCompare_ALL) const {
		switch (_option) {
		case eCompare_ALL:		return (m_value <= _t.m_value);
		case eCompare_YYYYMMDD:	return ((m_value >> 17) <= (_t.m_value >> 17));
		case eCompare_HHMMSS:	return ((m_value << 15) <= (_t.m_value << 15));
		}
		return false;
	}

public:
	bool operator==(const unTime32& _t) const {
		return isEqual(_t);
	}
	bool operator!=(const unTime32& _t) const {
		return !isEqual(_t);
	}
	bool operator>(const unTime32& _t) const {
		return isGreater(_t);
	}
	bool operator>=(const unTime32& _t) const {
		return isGreaterEqual(_t);
	}
	bool operator<(const unTime32& _t) const {
		return isLess(_t);
	}
	bool operator<=(const unTime32& _t) const {
		return isLessEqual(_t);
	}
	
	};

};	//	end namespace