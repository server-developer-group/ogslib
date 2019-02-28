#ifndef __ONLINE_GAME_SERVER_LIBRARY_STREAM_BUFFER_HEADER_FILE__
#define __ONLINE_GAME_SERVER_LIBRARY_STREAM_BUFFER_HEADER_FILE__

#include "common.h"

namespace nsStream
{
	////////////////////////////////////////////////////////////////////////////////
	// 정해진 크기의 버퍼를 담는 클래스
	class CBuffer
	{
	public:

		CBuffer();
		virtual ~CBuffer();

		// by novice
		// 자료형 사용법에 대해 한번 여쭤봐야할듯

		// nSize : 생성할 버퍼의 크기
		// nSize만큼 버퍼의 자원을 할당합니다.
		BOOL	Create( u4 nSize );

		// 버퍼의 자원을 해제합니다.
		void	Destroy();

		// 버퍼의 크기를 반환합니다.
		u4		Length();

		// nStartIndex	: 주소를 얻고자 하는 위치
		// 버퍼의 특정 위치의 주소를 반환합니다.
		u1*		GetData( u4 nStartIndex );

		// 현재까지 읽힌 위치의 인덱스를 반환합니다.
		u4		GetRdPos();

		// 현재까지 쓰인 위치의 인덱스를 반환합니다.
		u4		GetWrPos();

		// 버퍼 읽기
		// pTarget		: 읽을 대상
		// nSize		: 읽을 크기
		// pTarget을 nSize만큼 읽고 읽은 크기만큼 위치를 이동합니다.
		BOOL Read( void* pTarget, u4 nSize );

		// 버퍼 읽기
		// refTarget	: 읽을 대상
		// refTarget의 크기만큼 읽고 읽은 크기만큼 위치를 이동합니다.
		template <class T>	BOOL Read( T& refTarget );
		template <> BOOL Read( std::string& refTarget );
		template <> BOOL Read( std::wstring& refTarget );

		// 버퍼 읽기
		// pTarget		: 읽을 대상
		// nSize		: 읽을 크기
		// pTarget을 nSize만큼 읽지만 위치는 이동하지 않습니다.
		BOOL Peek( void* pTarget, u4 nSize );

		// 버퍼 읽기
		// refTarget	: 읽을 대상
		// refTarget의 크기만큼 읽지만 위치는 이동하지 않습니다.
		template <class T>	BOOL Peek( T& refTarget );

		// 버퍼 쓰기
		// pSource		: 쓸 내용
		// nSize		: 쓸 크기
		// pSource를 nSize만큼 쓰고 쓴 크기만큼 위치를 이동합니다.
		BOOL Write( void* pSource, u4 nSize );

		// 버퍼 쓰기
		// refSource	: 쓸 내용
		// refSource의 크기만큼 쓰고 쓴 크기만큼 위치를 이동합니다.
		template <class T> BOOL Write( T refSource );
		template <> BOOL Write( const std::string& refSource );
		template <> BOOL Write( const std::wstring& refSource );
		template <> BOOL Write( const char* refSource );
		template <> BOOL Write( const wchar_t* refSource );

	private:

		// 복사 금지
		CBuffer( const CBuffer& );
		CBuffer& operator = ( const CBuffer& );

		u1*		Alloc( u4 nSize );
		void	Free();

		BOOL	Read( u4 nStartIndex, u1* pTarget, u4 nSize );
		BOOL	Write( u4 nStartIndex, u1* pSource, u4 nSize );

		u4		m_nSize;				// 버퍼의 크기
		u4		m_nRdPos;				// 버퍼의 읽을 위치
		u4		m_nWrPos;				// 버퍼의 쓸 위치

		u1*		m_pBuffer;				// 버퍼의 시작 주소

		friend class CBufferProxy;
	};

	template <class T> BOOL CBuffer::Read( T& refTarget )
	{
		return Read( reinterpret_cast<void*>(&refTarget), sizeof(refTarget) );
	}

	template <> BOOL CBuffer::Read( std::string& refTarget )
	{
		u2 nLen = 0;
		BOOL bRet = Read( &nLen, sizeof(u2) );
		if ( FALSE == bRet )
		{
			return FALSE;
		}

		refTarget.resize( nLen );
		return Read( const_cast<char*>(refTarget.data()), nLen );
	}

	template <> BOOL CBuffer::Read( std::wstring& refTarget )
	{
		u2 nLen = 0;
		BOOL bRet = Read( &nLen, sizeof(u2) );
		if ( FALSE == bRet )
		{
			return FALSE;
		}

		refTarget.resize( nLen );
		return Read( const_cast<wchar_t*>(refTarget.data()), nLen * sizeof(wchar_t) );
	}

	template <class T> BOOL CBuffer::Peek( T& refTarget )
	{
		return Peek( reinterpret_cast<void*>(&refTarget), sizeof(refTarget) );
	}

	template <class T> BOOL CBuffer::Write( T refSource )
	{
		return Write( reinterpret_cast<void*>(&refSource), sizeof(refSource) );
	}

	template <> BOOL CBuffer::Write( const std::string& refSource )
	{
		u2 nLen = static_cast<u2>(refSource.length());
		BOOL bRet = Write( &nLen, sizeof(u2) );
		if ( FALSE == bRet )
		{
			return FALSE;
		}

		return Write( const_cast<char*>(refSource.c_str()), nLen );
	}

	template <> BOOL CBuffer::Write( const std::wstring& refSource )
	{
		u2 nLen = static_cast<u2>(refSource.length());
		BOOL bRet = Write( &nLen, sizeof(u2) );
		if ( FALSE == bRet )
		{
			return FALSE;
		}

		return Write( const_cast<wchar_t*>(refSource.c_str()), nLen * sizeof(wchar_t) );
	}

	template <> BOOL CBuffer::Write( const char* refSource )
	{
		u2 nLen = static_cast<u2>(strlen( reinterpret_cast<const char*>(refSource) ));
		BOOL bRet = Write( &nLen, sizeof(u2) );
		if ( FALSE == bRet )
		{
			return FALSE;
		}

		return Write( const_cast<char*>(refSource), nLen );
	}

	template <> BOOL CBuffer::Write( const wchar_t* refSource )
	{
		u2 nLen = static_cast<u2>(wcslen( reinterpret_cast<const wchar_t*>(refSource) ));
		BOOL bRet = Write( &nLen, sizeof(u2) );
		if ( FALSE == bRet )
		{
			return FALSE;
		}

		return Write( const_cast<wchar_t*>(refSource), nLen * sizeof(wchar_t) );
	}
	////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////
	// CBuffer 에 대해 읽기 / 쓰기를 대행하는 클래스
	class CBufferProxy
	{
	public:

		explicit CBufferProxy( CBuffer& refBuffer );
		virtual ~CBufferProxy();

		BOOL Read( void* pTarget, u4 nSize );
		template <class T>	BOOL Read( T& refTarget );

		BOOL Peek( void* pTarget, u4 nSize );
		template <class T>	BOOL Peek( T& refTarget );

		BOOL Write( void* pSource, u4 nSize );
		template <class T> BOOL Write( T refSource );

	private:

		// 복사 금지
		CBufferProxy( const CBufferProxy& );
		CBufferProxy& operator = ( const CBufferProxy& );

		u4			m_nRdPos;
		u4			m_nWrPos;
		CBuffer&	m_refBuffer;
	};

	template <class T> BOOL CBufferProxy::Read( T& refTarget )
	{
		return Read( reinterpret_cast<void*>(&refTarget), sizeof(refTarget) );
	}

	template <class T> BOOL CBufferProxy::Peek( T& refTarget )
	{
		return Peek( reinterpret_cast<void*>(&refTarget), sizeof(refTarget) );
	}

	template <class T> BOOL CBufferProxy::Write( T refSource )
	{
		return Write( reinterpret_cast<void*>(&refSource), sizeof(refSource) );
	}
	////////////////////////////////////////////////////////////////////////////////

}; // namespace nsStream

#endif // #ifndef __ONLINE_GAME_SERVER_LIBRARY_STREAM_BUFFER_HEADER_FILE__