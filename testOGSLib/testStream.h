#include "nsStream.h"

SUITE(nsStream_SUITE)
{
	TEST(Buffer_TEST)
	{
		u8	Read8 = 0;
		u4	Read4 = 0;
		u2	Read2 = 0;
		u1	Read1 = 0;

		{
			// ���� ����
			nsStream::CBuffer buffer;
			CHECK( FALSE	== buffer.Create( 0 )	);
			CHECK( TRUE		== buffer.Create( 10 )	);					// 10����Ʈ¥�� ����

			// ���� ���Ͻ� ����
			nsStream::CBufferProxy proxy(buffer);	

			// ���� �׽�Ʈ
			CHECK( TRUE		== buffer.Write( (u4) 0x10203040 ) );			// 4����Ʈ ���� (4)
			CHECK( FALSE	== buffer.Write( (u8) 0x1020304050607080 ) );	// 8����Ʈ ���� (���� �뷮 �������� ����)
			CHECK( TRUE		== buffer.Write( (u2) 0x5060 ) );				// 2����Ʈ ���� (6)
			CHECK( TRUE		== buffer.Write( (u2) 0x7080 ) );				// 2����Ʈ ���� (8)
			CHECK( TRUE		== buffer.Write( (u1) 0x90 ) );					// 1����Ʈ ���� (9)
			CHECK( TRUE		== buffer.Write( (u1) 0xA0 ) );					// 1����Ʈ ���� (10)
			CHECK( FALSE	== buffer.Write( (u1) 0xB0 ) );					// 1����Ʈ ���� (���� �뷮 �������� ����)

			// �б� �׽�Ʈ
			CHECK( TRUE					== buffer.Read( Read4 ) );			// 4����Ʈ �б� (4)
			CHECK( 0x10203040			== Read4				);			// 
			CHECK( FALSE				== buffer.Read( Read8 ) );			// 8����Ʈ �б� (���� �뷮 �������� ����)
			//CHECK( 0x0000000000000000	== Read8				);			// �� �� �ǹ� ����
			CHECK( TRUE					== buffer.Peek( Read2 ) );			// 2����Ʈ �б� (4) (Peek)
			CHECK( 0x5060				== Read2				);			//
			CHECK( TRUE					== buffer.Read( Read2 ) );			// 2����Ʈ �б� (6)
			CHECK( 0x5060				== Read2				);			//
			CHECK( TRUE					== buffer.Read( Read2 ) );			// 2����Ʈ �б� (8)
			CHECK( 0x7080				== Read2				);			//
			CHECK( TRUE					== buffer.Read( Read1 ) );			// 1����Ʈ �б� (9)
			CHECK( 0x90					== Read1				);			//
			CHECK( TRUE					== buffer.Read( Read1 ) );			// 1����Ʈ �б� (10)
			CHECK( 0xA0					== Read1				);			//
			CHECK( FALSE				== buffer.Read( Read1 ) );			// 1����Ʈ �б� (���� �뷮 �������� ����)

			// �б� �׽�Ʈ (�������Ͻ�)
			CHECK( TRUE					== proxy.Read( Read4 )	);			// 4����Ʈ �б� (4)
			CHECK( 0x10203040			== Read4				);			// 
			CHECK( FALSE				== proxy.Read( Read8 )	);			// 8����Ʈ �б� (���� �뷮 �������� ����)
			//CHECK( 0x0000000000000000	== Read8				);			// �� �� �ǹ� ����
			CHECK( TRUE					== proxy.Peek( Read2 )	);			// 2����Ʈ �б� (4) (Peek)
			CHECK( 0x5060				== Read2				);			//
			CHECK( TRUE					== proxy.Read( Read2 )	);			// 2����Ʈ �б� (6)
			CHECK( 0x5060				== Read2				);			//
			CHECK( TRUE					== proxy.Read( Read2 )	);			// 2����Ʈ �б� (8)
			CHECK( 0x7080				== Read2				);			//
			CHECK( TRUE					== proxy.Read( Read1 )	);			// 1����Ʈ �б� (9)
			CHECK( 0x90					== Read1				);			//
			CHECK( TRUE					== proxy.Read( Read1 )	);			// 1����Ʈ �б� (10)
			CHECK( 0xA0					== Read1				);			//
			CHECK( FALSE				== proxy.Read( Read1 )	);			// 1����Ʈ �б� (���� �뷮 �������� ����)


			
			// ���� �Ҹ�
			buffer.Destroy();
			CHECK( 0 == buffer.Length() );
		}

		{
			struct _StructTest1
			{
				u8	nValue1;
				u2	nValue2;
				u1	nValue3;
			};

#pragma pack (push, 1)
			struct _StructTest2
			{
				u8	nValue1;
				u2	nValue2;
				u1	nValue3;
			};
#pragma pack (pop)

			nsStream::CBuffer buffer;
			CHECK( TRUE	== buffer.Create( 32 )	);					// 32����Ʈ¥�� ����

			_StructTest1 st1;
			memset( &st1, 0, sizeof(_StructTest1) );

			st1.nValue1 = 0x1010101010101010;
			st1.nValue2 = 0x2020;
			st1.nValue3 = 0x30;

			_StructTest2 st2;
			memset( &st2, 0, sizeof(_StructTest2) );

			st2.nValue1 = 0x4040404040404040;
			st2.nValue2 = 0x5050;
			st2.nValue3 = 0x60;

			CHECK( 11 <  sizeof(st1) );								// �е������� 11���ٴ� ũ�� ���ð��̴�
			CHECK( 11 == sizeof(st2) );								// 11����Ʈ¥�� ����ü

			CHECK( TRUE		== buffer.Write( &st1, sizeof(st1)) );
			CHECK( TRUE		== buffer.Write( &st2, sizeof(st2)) );
			CHECK( FALSE	== buffer.Write( &st1, sizeof(st1)) );

			_StructTest1 st1Read;
			_StructTest2 st2Read;
			CHECK( TRUE		== buffer.Read( &st1Read, sizeof(st1Read)) );
			CHECK( 0x1010101010101010	== st1Read.nValue1 );
			CHECK( 0x2020				== st1Read.nValue2 );
			CHECK( 0x30					== st1Read.nValue3 );

			CHECK( TRUE		== buffer.Peek( &st2Read, sizeof(st2Read)) );
			CHECK( 0x4040404040404040	== st2Read.nValue1 );
			CHECK( 0x5050				== st2Read.nValue2 );
			CHECK( 0x60					== st2Read.nValue3 );

			CHECK( TRUE		== buffer.Read( &st2Read, sizeof(st2Read)) );
			CHECK( 0x4040404040404040	== st2Read.nValue1 );
			CHECK( 0x5050				== st2Read.nValue2 );
			CHECK( 0x60					== st2Read.nValue3 );

			CHECK( FALSE	== buffer.Peek( &st1Read, sizeof(st1Read)) );
			CHECK( FALSE	== buffer.Read( &st1Read, sizeof(st1Read)) );

			buffer.Destroy();

			CHECK( 0 == buffer.Length() );
		}
	}

	TEST(Encoding_TEST)
	{
		nsStream::CEncoderXOR myEncoder;

		nsStream::CBuffer buffer;
		buffer.Create( 300 );

		LPCTSTR lpszWritingData = _T("1234567890123456789012345678901234567890");

		CHECK( TRUE == buffer.Write( lpszWritingData ) );
		CHECK( _tcslen(lpszWritingData) == *((u2*)buffer.GetData(0)) );

		CHECK( TRUE == myEncoder.Encode( buffer.GetData(0), buffer.GetWrPos(), 0 ) );
		CHECK( TRUE == myEncoder.Decode( buffer.GetData(0), buffer.GetWrPos(), 0 ) );

		CHECK( TRUE == myEncoder.Encode( buffer.GetData(0), buffer.GetWrPos(), 1 ) );
		CHECK( TRUE == myEncoder.Decode( buffer.GetData(0), buffer.GetWrPos(), 1 ) );

		stdString strWrittenValue;
		CHECK( TRUE == buffer.Read( strWrittenValue ) );

		CHECK( 0 == _tcscmp( lpszWritingData, reinterpret_cast<LPCTSTR>(strWrittenValue.c_str()) ) );

		buffer.Destroy();
	}
}