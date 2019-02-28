#include "nsStream_Buffer.h"

namespace nsStream
{

	CBuffer::CBuffer()
		: m_pBuffer(NULL)
		, m_nSize(0)
		, m_nRdPos(0)
		, m_nWrPos(0)
	{
	}
	
	CBuffer::~CBuffer()
	{
	}

	BOOL CBuffer::Create( u4 nSize )
	{
		if ( 0 == nSize )
		{
			return FALSE;
		}

		m_nSize = nSize;

		if ( NULL == Alloc( m_nSize ) )
		{
			return FALSE;
		}

		return TRUE;
	}
	
	void CBuffer::Destroy()
	{
		Free();

		m_nSize = 0;
	}

	u4 CBuffer::Length()
	{
		return m_nSize;
	}

	u1* CBuffer::GetData( u4 nStartIndex )
	{
		if ( nStartIndex >= m_nSize )
		{
			return NULL;
		}

		return &(m_pBuffer[nStartIndex]);
	}

	u4 CBuffer::GetRdPos()
	{
		return m_nRdPos;
	}

	u4 CBuffer::GetWrPos()
	{
		return m_nWrPos;
	}

	BOOL CBuffer::Peek( void* pTarget, u4 nSize )
	{
		return Read( m_nRdPos, reinterpret_cast<u1*>(pTarget), nSize );
	}

	BOOL CBuffer::Read( void* pTarget, u4 nSize )
	{
		BOOL bRet = Peek( pTarget, nSize );

		if ( TRUE == bRet )
		{
			m_nRdPos += nSize;
		}

		return bRet;
	}

	BOOL CBuffer::Write( void* pSource, u4 nSize )
	{
		BOOL bRet = Write( m_nWrPos, reinterpret_cast<u1*>(pSource), nSize );

		if ( TRUE == bRet )
		{
			m_nWrPos += nSize;
		}

		return bRet;
	}


	CBuffer::CBuffer( const CBuffer& )
	{
	}

	CBuffer& CBuffer::operator = ( const CBuffer& )
	{
		return (*this);
	}

	u1* CBuffer::Alloc( u4 nSize )
	{
		// 나중에 Custom Allocator 를 끼우자
		if ( NULL != m_pBuffer )
		{
			return NULL;
		}

		m_pBuffer = new u1[nSize];

		return m_pBuffer;
	}

	void CBuffer::Free()
	{
		// 나중에 Custom Allocator 를 끼우자
		if ( NULL != m_pBuffer )
		{
			delete [] m_pBuffer;
			m_pBuffer = NULL;
		}
	}

	BOOL CBuffer::Read( u4 nStartIndex, u1* pTarget, u4 nSize )
	{
		if ( nStartIndex + nSize > m_nSize )
		{
			return FALSE;
		}

		if ( NULL == memcpy(	reinterpret_cast<void*>(pTarget), 
								reinterpret_cast<void*>(&m_pBuffer[nStartIndex]), 
								nSize )		)
		{
			return FALSE;
		}

		return TRUE;
	}

	BOOL CBuffer::Write( u4 nStartIndex, u1* pSource, u4 nSize )
	{
		if ( nStartIndex + nSize > m_nSize )
		{
			return FALSE;
		}

		if ( NULL == memcpy(	reinterpret_cast<void*>(&m_pBuffer[nStartIndex]), 
								reinterpret_cast<void*>(pSource), 
								nSize )		)
		{
			return FALSE;
		}

		return TRUE;
	}



	////////////////////////////////////////////////////////////////////////////////


	CBufferProxy::CBufferProxy( CBuffer& refBuffer )
		: m_refBuffer( refBuffer )
		, m_nRdPos(0)
		, m_nWrPos(0)
	{
	}

	CBufferProxy::~CBufferProxy()
	{
	}

	BOOL CBufferProxy::Peek( void* pTarget, u4 nSize )
	{
		if ( nSize + m_nRdPos > m_refBuffer.Length() )
		{
			return FALSE;
		}

		return m_refBuffer.Read( m_nRdPos, reinterpret_cast<u1*>(pTarget), nSize );
	}

	BOOL CBufferProxy::Read( void* pTarget, u4 nSize )
	{
		BOOL bRet = Peek( pTarget, nSize );

		if ( TRUE == bRet )
		{
			m_nRdPos += nSize;
		}

		return bRet;
	}

	CBufferProxy& CBufferProxy::operator = ( const CBufferProxy& )
	{
		return (*this);
	}

	BOOL CBufferProxy::Write( void* pSource, u4 nSize )
	{
		if ( nSize + m_nWrPos > m_refBuffer.Length() )
		{
			return FALSE;
		}

		BOOL bRet = m_refBuffer.Write( m_nWrPos, reinterpret_cast<u1*>(pSource), nSize );

		if ( TRUE == bRet )
		{
			m_nWrPos += nSize;
		}

		return bRet;
	}

}; // namespace nsStream