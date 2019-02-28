#include "nsTime.h"

SUITE(nsTime_SUITE)
{
	TEST(unTime_TEST)
	{
		nsTime::unTime	t;
		t.set( 9,10,28, 10,33,21);

		CHECK( t.year == 9);
		CHECK( t.month == 10);
		CHECK( t.second == 21);

		nsTime::unTime	t2;
		t2 = t;
		CHECK( t.year == 9);
		CHECK( t.month == 10);
		CHECK( t.second == 21);

		t2.hour = 9;
		CHECK( t != t2);
		CHECK( t.isNotEqual(t2) );

		CHECK( t.isNotEqual(t2, nsTime::unTime::eCompare_HHMMSS) );
		CHECK( t.isEqual(t2, nsTime::unTime::eCompare_YYYYMMDD) );

		stdString strTime = t.stringFormat();
		CHECK( strTime.compare( _T("2009-10-28 10:33:21")) == 0 );

		stdString strDatePart = t.stringFormat(nsTime::unTime::eTimeFormat_YYYYMMDD);
		CHECK( strDatePart.compare( _T("2009-10-28")) == 0 );

		stdString strTimePart = t.stringFormat(nsTime::unTime::eTimeFormat_HHMMSS);
		CHECK( strTimePart.compare( _T("10:33:21")) == 0 );
	}
}