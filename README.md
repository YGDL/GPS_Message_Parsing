# GPS_Message_Parsing
 使用STM32 UART+DMA接收GPS数据，该数据格式符合NMEA0183标准。由于接收不会自动隔断字符串，所以需要使用下面程序将收到的字符串进行分析，找出各条指令的位置。之后使用NMEA Library 0.5.3对该数据进行解析，最后存储进入结构体中。
