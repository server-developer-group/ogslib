#ifndef __ONLINE_GAME_SERVER_LIBRARY_STREAM_ENCODER_HEADER_FILE__
#define __ONLINE_GAME_SERVER_LIBRARY_STREAM_ENCODER_HEADER_FILE__

#include "common.h"

namespace nsStream
{

	interface IEncoder
	{
		virtual BOOL	Encode( u1* pStart, u4 nLength, u1 nKeyIndex ) = 0;
		virtual BOOL	Decode( u1* pStart, u4 nLength, u1 nKeyIndex ) = 0;
	};

}; // namespace nsStream

#endif // #ifndef __ONLINE_GAME_SERVER_LIBRARY_STREAM_ENCODER_HEADER_FILE__