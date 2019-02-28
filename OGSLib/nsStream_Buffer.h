#ifndef __ONLINE_GAME_SERVER_LIBRARY_STREAM_BUFFER_HEADER_FILE__
#define __ONLINE_GAME_SERVER_LIBRARY_STREAM_BUFFER_HEADER_FILE__

#include "common.h"

namespace nsStream
{
	////////////////////////////////////////////////////////////////////////////////
	// ������ ũ���� ���۸� ��� Ŭ����
	class CBuffer
	{
	public:

		CBuffer();
		virtual ~CBuffer();

		// by novice
		// �ڷ��� ������ ���� �ѹ� ��������ҵ�

		// nSize : ������ ������ ũ��
		// nSize��ŭ ������ �ڿ��� �Ҵ��մϴ�.
		BOOL	Create( u4 nSize );

		// ������ �ڿ��� �����մϴ�.
		void	Destroy();

		// ������ ũ�⸦ ��ȯ�մϴ�.
		u4		Length();

		// nStartIndex	: �ּҸ� ����� �ϴ� ��ġ
		// ������ Ư�� ��ġ�� �ּҸ� ��ȯ�մϴ�.
		u1*		GetData( u4 nStartIndex );

		// ������� ���� ��ġ�� �ε����� ��ȯ�մϴ�.
		u4		GetRdPos();

		// ������� ���� ��ġ�� �ε����� ��ȯ�մϴ�.
		u4		GetWrPos();

		// ���� �б�
		// pTarget		: ���� ���
		// nSize		: ���� ũ��
		// pTarget�� nSize��ŭ �а� ���� ũ�⸸ŭ ��ġ�� �̵��մϴ�.
		BOOL Read( void* pTarget, u4 nSize );

		// ���� �б�
		// refTarget	: ���� ���
		// refTarget�� ũ�⸸ŭ �а� ���� ũ�⸸ŭ ��ġ�� �̵��մϴ�.
		template <class T>	BOOL Read( T& refTarget );
		template <> BOOL Read( std::string& refTarget );
		template <> BOOL Read( std::wstring& refTarget );

		// ���� �б�
		// pTarget		: ���� ���
		// nSize		: ���� ũ��
		// pTarget�� nSize��ŭ ������ ��ġ�� �̵����� �ʽ��ϴ�.
		BOOL Peek( void* pTarget, u4 nSize );

		// ���� �б�
		// refTarget	: ���� ���
		// refTarget�� ũ�⸸ŭ ������ ��ġ�� �̵����� �ʽ��ϴ�.
		template <class T>	BOOL Peek( T& refTarget );

		// ���� ����
		// pSource		: �� ����
		// nSize		: �� ũ��
		// pSource�� nSize��ŭ ���� �� ũ�⸸ŭ ��ġ�� �̵��մϴ�.
		BOOL Write( void* pSource, u4 nSize );

		// ���� ����
		// refSource	: �� ����
		// refSource�� ũ�⸸ŭ ���� �� ũ�⸸ŭ ��ġ�� �̵��մϴ�.
		template <class T> BOOL Write( T refSource );
		template <> BOOL Write( const std::string& refSource );
		template <> BOOL Write( const std::wstring& refSource );
		template <> BOOL Write( const char* refSource );
		template <> BOOL Write( const wchar_t* refSource );

	private:

		// ���� ����
		CBuffer( const CBuffer& );
		CBuffer& operator = ( const CBuffer& );

		u1*		Alloc( u4 nSize );
		void	Free();

		BOOL	Read( u4 nStartIndex, u1* pTarget, u4 nSize );
		BOOL	Write( u4 nStartIndex, u1* pSource, u4 nSize );

		u4		m_nSize;				// ������ ũ��
		u4		m_nRdPos;				// ������ ���� ��ġ
		u4		m_nWrPos;				// ������ �� ��ġ

		u1*		m_pBuffer;				// ������ ���� �ּ�

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
	// CBuffer �� ���� �б� / ���⸦ �����ϴ� Ŭ����
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

		// ���� ����
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