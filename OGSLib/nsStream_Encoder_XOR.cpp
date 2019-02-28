#include "nsStream_Encoder_XOR.h"

namespace nsStream
{

	// by novice
	// XOR 를 위한 Table 을 만드는데
	// x64와 x86에 대한 #ifdef 이런걸 안해보기 위해서
	const CEncoderXOR::XORKeyType CEncoderXOR::m_arrEncodeTable[] = {
		static_cast<XORKeyType>(0x1D4BB8BCE9B90666),	static_cast<XORKeyType>(0x3DDB79C1940CD238),
		static_cast<XORKeyType>(0x845AF00B0BB7CC00),	static_cast<XORKeyType>(0x285E00250BD2DB05),
		static_cast<XORKeyType>(0x21507011F3C3F4FD),	static_cast<XORKeyType>(0x3D004289E7899365),
		static_cast<XORKeyType>(0x8B7D892B073D90FE),	static_cast<XORKeyType>(0xBBC94DDE7BD4A048),
		static_cast<XORKeyType>(0x4F10FCC5466D636A),	static_cast<XORKeyType>(0x29B30DEA11A9AB3A),
		static_cast<XORKeyType>(0x001BF2D73E8E4725),	static_cast<XORKeyType>(0x2B65505FDCBF4203),
		static_cast<XORKeyType>(0x871CC845DFA2912B),	static_cast<XORKeyType>(0x03C5AEF090AD82DF),
		static_cast<XORKeyType>(0x0BECF36BCD35152F),	static_cast<XORKeyType>(0xFF3B4EC655801139),
		static_cast<XORKeyType>(0x1FF75A167CE47393),	static_cast<XORKeyType>(0x26D7970031457485),
		static_cast<XORKeyType>(0xD8920947655B3FF4),	static_cast<XORKeyType>(0x7ADEC79B0A7F58CE),
		static_cast<XORKeyType>(0xDC02DA374B81B840),	static_cast<XORKeyType>(0xC4BD515E52F3DFD3),
		static_cast<XORKeyType>(0x9130933464473623),	static_cast<XORKeyType>(0x11B4C4C579FDE200),
		static_cast<XORKeyType>(0xE1F84F4F6A7C67CD),	static_cast<XORKeyType>(0x38F38911161B0094),
		static_cast<XORKeyType>(0x0BFC83A499584173),	static_cast<XORKeyType>(0x70832472E0510109),
		static_cast<XORKeyType>(0x56C0BF071215E987),	static_cast<XORKeyType>(0x018BF3B916A24546),
		static_cast<XORKeyType>(0xFFC72205DFBDBCC6),	static_cast<XORKeyType>(0x903FEDCFE4A84932),
		static_cast<XORKeyType>(0x7B7BD63C9EB4B991),	static_cast<XORKeyType>(0x00EF1E18BC35C0CD),
		static_cast<XORKeyType>(0x576B5A3BADBAC3C2),	static_cast<XORKeyType>(0x91573E14CB4CB5DB),
		static_cast<XORKeyType>(0x386F01F09CBCB786),	static_cast<XORKeyType>(0x3AFDF906159331E5),
		static_cast<XORKeyType>(0x3A6D69248D2AFE16),	static_cast<XORKeyType>(0xC6C39535F7CF720D),
		static_cast<XORKeyType>(0x926AA17A19B1A3DB),	static_cast<XORKeyType>(0x62D6B51566B43FD3),
		static_cast<XORKeyType>(0xEF12806D4137ED0E),	static_cast<XORKeyType>(0x34159E4DB72588DE),
		static_cast<XORKeyType>(0xAF6E0385024C003F),	static_cast<XORKeyType>(0xF5837C5898651DDD),
		static_cast<XORKeyType>(0xA25C80723ED7F17F),	static_cast<XORKeyType>(0x255A85D141FB9B3F),
		static_cast<XORKeyType>(0xA59D6861344DAA07),	static_cast<XORKeyType>(0x793F2024473A18DC),
		static_cast<XORKeyType>(0x49EB1274C71D051B),	static_cast<XORKeyType>(0x5589AC6853356C6B),
		static_cast<XORKeyType>(0x3FD9949AA28226ED),	static_cast<XORKeyType>(0x93ACB63E46FC9BDC),
		static_cast<XORKeyType>(0x96BE01E9D7BBC915),	static_cast<XORKeyType>(0x00C0DE40907A4108),
		static_cast<XORKeyType>(0x0392F2EEBF230B63),	static_cast<XORKeyType>(0xED25DE46F8CB4FD3),
		static_cast<XORKeyType>(0x69C610D30ACA683F),	static_cast<XORKeyType>(0xF9B159E5CC861EA4),
		static_cast<XORKeyType>(0xB76757488DC44340),	static_cast<XORKeyType>(0x35E0BA75662D24DF),
		static_cast<XORKeyType>(0x991DCC9D0A2987BF),	static_cast<XORKeyType>(0xCCEC7508AA27CE17),
		static_cast<XORKeyType>(0x6676ED4D75B3F8A8),	static_cast<XORKeyType>(0x0087502F1E4A3E9A),
		static_cast<XORKeyType>(0xFAAF938C2BDEB16C),	static_cast<XORKeyType>(0x105DDBBE8261E84C),
		static_cast<XORKeyType>(0x8B156C30DC97152E),	static_cast<XORKeyType>(0x393C1EDA4E4AC9C9),
		static_cast<XORKeyType>(0x61B530FD1938DB75),	static_cast<XORKeyType>(0xCF250BEBB73D886E),
		static_cast<XORKeyType>(0x304995C143B4CE94),	static_cast<XORKeyType>(0xF2DBC09BAF5C5A9F),
		static_cast<XORKeyType>(0xB1F9D1EB689044FA),	static_cast<XORKeyType>(0xFEAD8ACD90D3411F),
		static_cast<XORKeyType>(0x1041EEB21AC97E33),	static_cast<XORKeyType>(0x8D97144A55C483AF),
		static_cast<XORKeyType>(0x2C9BC78024BE799C),	static_cast<XORKeyType>(0x968A732599662AEE),
		static_cast<XORKeyType>(0xD97754D607067815),	static_cast<XORKeyType>(0x86DF6113FC565FC1),
		static_cast<XORKeyType>(0x61AC56543288CBD2),	static_cast<XORKeyType>(0x1B513C0E2EC17834),
		static_cast<XORKeyType>(0xDD164910FE2E09D5),	static_cast<XORKeyType>(0x78CCC9BDFC3C8B17),
		static_cast<XORKeyType>(0x0047DECCD0B8B5B5),	static_cast<XORKeyType>(0xA45301DED95F0141),
		static_cast<XORKeyType>(0x9FD3DB7A2AF9D296),	static_cast<XORKeyType>(0x2C97E6AA8A22A78C),
		static_cast<XORKeyType>(0xB03F00624A4754CD),	static_cast<XORKeyType>(0x594380A78690A52E),
		static_cast<XORKeyType>(0xA0E9C3242BDBA8DF),	static_cast<XORKeyType>(0xDCF22A2768EF126B),
		static_cast<XORKeyType>(0xA5A9B117579DA8D2),	static_cast<XORKeyType>(0x6DD8A09EC5928BFE),
		static_cast<XORKeyType>(0xC6A43019DBFF1C55),	static_cast<XORKeyType>(0x7FC04830F36AD9F0),
		static_cast<XORKeyType>(0x09C2FC715F0A4900),	static_cast<XORKeyType>(0x04906F230323EA60),
		static_cast<XORKeyType>(0x2234963E03F17563),	static_cast<XORKeyType>(0x93EEB00BDFE9C211),
		static_cast<XORKeyType>(0x11882420343200EB),	static_cast<XORKeyType>(0xFDD35324EDA30AAA),
		static_cast<XORKeyType>(0x44AE94653C5DFEFB),	static_cast<XORKeyType>(0xACCFA0B669E4001A),
		static_cast<XORKeyType>(0x2588A4A535005DBD),	static_cast<XORKeyType>(0xC000855DBC4EC7DC),
		static_cast<XORKeyType>(0x59BEED7BEE4C21ED),	static_cast<XORKeyType>(0xA0A486313BBF9A92),
		static_cast<XORKeyType>(0x657202085254CC33),	static_cast<XORKeyType>(0x32C18DE2957143E1),
		static_cast<XORKeyType>(0x41949E978403F2C4),	static_cast<XORKeyType>(0xBCDF2EB61C6D152B),
		static_cast<XORKeyType>(0x00D64672FBBF7308),	static_cast<XORKeyType>(0x041CC3468F304285),
		static_cast<XORKeyType>(0xBADB5253846F66F0),	static_cast<XORKeyType>(0x3B7EE6F0292BF01C),
		static_cast<XORKeyType>(0x1ECCE67CEFA68D16),	static_cast<XORKeyType>(0xB23052875B69C54A),
		static_cast<XORKeyType>(0xD07DEF53F59F8ABA),	static_cast<XORKeyType>(0xD051F8F70523D5E9),
		static_cast<XORKeyType>(0x2E97B24B321FDD99),	static_cast<XORKeyType>(0xC4C46488383AADF8),
		static_cast<XORKeyType>(0x1116C9A53D0900F4),	static_cast<XORKeyType>(0xEF02721320AF43A3),
		static_cast<XORKeyType>(0xD341B7A78969D745),	static_cast<XORKeyType>(0xA5A41BD998F4519E),
	};

	BOOL CEncoderXOR::Encode( u1* pStart, u4 nLength, u1 nKeyIndex )
	{
		u4			nEncodedLength	= 0;
		XORKeyType	EncodeKey		= 0;
		XORKeyType*	pEncodeAddr		= reinterpret_cast<XORKeyType*>(pStart);

		for ( ; nLength > nEncodedLength; ++nKeyIndex )
		{
			EncodeKey = m_arrEncodeTable[nKeyIndex % cnEncodeTableSize];

			// 최대한 큰 Byte 단위로 Encoding 을 시도하고
			// 여의치 않을때에만 1바이트 단위로 Encoding 한다
			if ( nLength - nEncodedLength >= sizeof(XORKeyType) )
			{
				(*pEncodeAddr)	^=	EncodeKey;
				nEncodedLength	+=	sizeof(XORKeyType);
				++pEncodeAddr;
			}
			else
			{
				u1* pEncodedByteAddr	= reinterpret_cast<u1*>(pEncodeAddr);
				u1* pEncodeKeyByteAddr	= reinterpret_cast<u1*>(&EncodeKey);

				for ( ; nLength > nEncodedLength; )
				{
					(*pEncodedByteAddr)	^= (*pEncodeKeyByteAddr);
					nEncodedLength	+=	sizeof(u1);
					++pEncodedByteAddr;
					++pEncodeKeyByteAddr;
				}
			}
		}

		return TRUE;
	}

	BOOL CEncoderXOR::Decode( u1 *pStart, u4 nLength, u1 nKeyIndex )
	{
		return Encode( pStart, nLength, nKeyIndex );
	}

}; // namespace nsStream