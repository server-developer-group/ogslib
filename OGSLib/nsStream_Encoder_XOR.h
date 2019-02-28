#ifndef __ONLINE_GAME_SERVER_LIBRARY_STREAM_ENCODER_XOR_HEADER_FILE__
#define __ONLINE_GAME_SERVER_LIBRARY_STREAM_ENCODER_XOR_HEADER_FILE__

#include "nsStream_Encoder.h"

namespace nsStream
{
	class CEncoderXOR : public IEncoder
	{
	public:
		virtual BOOL	Encode( u1* pStart, u4 nLength, u1 nKeyIndex );
		virtual BOOL	Decode( u1* pStart, u4 nLength, u1 nKeyIndex );

	private:

#ifdef _W64
		typedef u8	XORKeyType;
#else
		typedef u4	XORKeyType;
#endif // #ifdef _W64

		static const u4			cnEncodeTableSize = 128;
		static const XORKeyType	m_arrEncodeTable[cnEncodeTableSize];
	};

};	// end namespace nsStream

#endif // #ifndef __ONLINE_GAME_SERVER_LIBRARY_STREAM_ENCODER_XOR_HEADER_FILE__