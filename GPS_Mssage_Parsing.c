#include "stdio.h"
#include "string.h"
#include "stdint.h"

// extern void nmea_parser_destroy(nmeaPARSER *parser);
// extern int nmea_parse(nmeaPARSER *parser, const char *buff, int buff_sz, nmeaINFO *info);

const uint8_t GPS[] = {
	"$GNGGA,115911.000,2504.04042,N,11017.85653,E,1,10,2.7,197.8,M ,-20.0,M,,*68\r\n$GNGLL,2504.04042,N,11017.85653,E,115911.000,A,A*41\r\n$GNGSA,A,3,07,09,,,,,,,,,,,3.8,2.7,2.6,1*35\r\n$GNGSA,A,3,19,22,36,40,46,,,,,,,,3.8,2.7,2.6,4*35\r\n$GNGSA,A,3,75,65,72,,,,,,,,,,3.8,2.7,2.6,2*3C\r\n$GPGSV,1,1,04,07,13,314,32,08,,,20,09,40,298,37,31,12,114,,0*56\r\n$BDGSV,2,1,06,19,27,246,26,22,13,298,37,36,29,312,31,40,72,336,36,0*73\r\n$BDGSV,2,2,06,42,,,22,46,55,016,32,0*40\r\n$GLGSV,3,1,09,74,38,348,27,73,33,047,,75,09,299,33,65,10,322,31,0*7D\r\n$GLGSV,3,2,09,84,47,118,,83,24,043,,85,12,177,,71,28,217,,0*7B\r\n$GLGSV,3,3,09,72,35,276,31,0*42\r\n$GNRMC,115911.000,A,2504.04042,N,11017.85653,E,0.00,306.10,041122,,,A,V*0C\r\n$GNVTG,306.10,T,,M,0.00,N,0.00,K,A*27\r\n$GNZDA,115911.000,04,11,2022,00,00*42\r\n$GPTXT,01,01,01,ANTENNA OK*35\r\n$GPTXT,01,01,01,$NTENNA OK*35\r\n"
};

uint8_t main(void)
{
	void * Now_Pointer = NULL;
	void * Last_Pointer = (void *)GPS;
	uint16_t GPS_Info_List[18][2] = {0};
	uint16_t GPS_Data_Size = 803U;

	// nmeaINFO info;
    // nmeaPARSER parser;

	for(uint8_t Symbol_Count = 0U; ; Symbol_Count ++)
	{
		Now_Pointer = (void *)memchr(Last_Pointer + 1, '$', 801);		//查找最近的一个$符号
		GPS_Info_List[Symbol_Count][0] = Symbol_Count;
		if((GPS_Data_Size <= (uint16_t)(Now_Pointer - (void *)GPS)) || NULL == Now_Pointer)		//防止越界
		{
			GPS_Info_List[Symbol_Count][1] = GPS_Data_Size - (uint16_t)(Last_Pointer - (void *)GPS);
			GPS_Info_List[Symbol_Count+1][0] = Symbol_Count +1;
			GPS_Info_List[Symbol_Count+1][1] = 0;
			break;		//调成循环
		}
		GPS_Info_List[Symbol_Count][1] = (uint16_t)(Now_Pointer - Last_Pointer);	//计算最近的$符号偏移
		Last_Pointer = Now_Pointer;			//重新开始
	}

	// for(uint8_t Parse_Count = 0U; 0 == GPS_Info_List[Parse_Count][1]; Parse_Count ++)
	// {
	// 	nmea_parse(&parser, GPS+((0 == Parse_Count) ? 0 : GPS_Info_List[Parse_Count-1][0]), GPS_Info_List[Parse_Count][1], &info);
	// }
	// nmea_parser_destroy(&parser);

	return 0;
}