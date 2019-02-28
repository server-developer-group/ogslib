#pragma once 

#include <windows.h>
#include <string>

//////////////////////////////////////////////////////////////////////////
//	typedef
typedef signed	 char	s1;
typedef unsigned char	u1;
typedef signed	 short	s2;
typedef unsigned short	u2;
typedef signed	 int	s4;
typedef unsigned int	u4;
typedef signed long		sl4;
typedef unsigned long	ul4;
typedef __int64				s8;
typedef unsigned __int64	u8;

#ifdef UNICODE
	typedef std::wstring	stdString;
#else
	typedef std::string		stdString;
#endif

//////////////////////////////////////////////////////////////////////////
//	define
#ifndef dMAX
#define dMAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef dMIN
#define dMIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX_PATH
#define MAX_PATH	512
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       if(p) { delete (p);     (p)=NULL; }
#endif    

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) if(p) { delete[] (p);   (p)=NULL; }
#endif    

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      if(p) { (p)->release(); (p)=NULL; }
#endif

#ifndef	pKILL
#define pKILL(p) {if (p) {delete [] p	;p=NULL;}	}
#endif

#ifndef	KILL
#define KILL(p)	{if (p) {delete p		;p=NULL;}	}
#endif

//////////////////////////////////////////////////////////////////////////
//	template
template <class A> inline void Swap(A &a, A &b)
{
	A   c;

	c = a;
	a = b;
	b = c;
}

//	패턴은 따로 모으는게 좋을 듯.. 패턴 담당자를 찾아보자. 20091027 지현
template<class T>
class cSinglton			
{
public:
	static T & GetInstance()	{	
		static T cMng;	return cMng;
	}
};


//////////////////////////////////////////////////////////////////////////
//	class
