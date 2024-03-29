EESchema Schematic File Version 4
LIBS:PonchoGateway-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Switch:SW_Push SW1
U 1 1 5CFD7D1E
P 8400 3400
F 0 "SW1" H 8400 3685 50  0000 C CNN
F 1 "SW_Push" H 8400 3594 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 8400 3600 50  0001 C CNN
F 3 "~" H 8400 3600 50  0001 C CNN
	1    8400 3400
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:HY1602E DS1
U 1 1 5CFD8F42
P 5250 6650
F 0 "DS1" V 5500 7450 50  0000 C CNN
F 1 "HY1602E" V 5400 7550 50  0000 C CNN
F 2 "Display:Display_Propio" H 5250 5750 50  0001 C CIN
F 3 "http://www.icbank.com/data/ICBShop/board/HY1602E.pdf" H 5450 6750 50  0001 C CNN
	1    5250 6650
	0    -1   -1   0   
$EndComp
$Comp
L LibreriaPropia:SD_Arduino SD1
U 1 1 5CFD9A33
P 9200 6150
F 0 "SD1" H 9628 6401 50  0000 L CNN
F 1 "SD_Arduino" H 9628 6310 50  0000 L CNN
F 2 "lib-ESP8266:SD-SHIELD-ARD" H 9200 6200 50  0001 C CNN
F 3 "" H 9200 6200 50  0001 C CNN
	1    9200 6150
	1    0    0    -1  
$EndComp
$Comp
L Poncho_Esqueleto:Conn_Poncho2P_2x_20x2 XA1
U 1 1 5CFFA1D1
P 3200 1300
F 0 "XA1" H 3550 1847 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 3550 1741 60  0000 C CNN
F 2 "Poncho_Esqueleto:Conn_Poncho_SinBorde" H 3200 1300 60  0000 C CNN
F 3 "" H 3200 1300 60  0000 C CNN
	1    3200 1300
	1    0    0    -1  
$EndComp
$Comp
L Poncho_Esqueleto:Conn_Poncho2P_2x_20x2 XA1
U 2 1 5CFFAE9D
P 3200 3600
F 0 "XA1" H 3550 4147 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 3550 4041 60  0000 C CNN
F 2 "Poncho_Esqueleto:Conn_Poncho_SinBorde" H 3200 3600 60  0000 C CNN
F 3 "" H 3200 3600 60  0000 C CNN
	2    3200 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 5200 2750 5200
Wire Wire Line
	2950 5100 2750 5100
Wire Wire Line
	2950 4600 2750 4600
Wire Wire Line
	2750 4600 2750 5100
Connection ~ 2750 5100
Wire Wire Line
	2950 4500 2750 4500
Wire Wire Line
	2750 4500 2750 4600
Connection ~ 2750 4600
Wire Wire Line
	2950 4200 2750 4200
Wire Wire Line
	2750 4200 2750 4500
Connection ~ 2750 4500
Wire Wire Line
	2950 4100 2750 4100
Wire Wire Line
	2750 4100 2750 4200
Connection ~ 2750 4200
Wire Wire Line
	2950 3900 2750 3900
Wire Wire Line
	2750 3900 2750 4100
Connection ~ 2750 4100
Wire Wire Line
	2950 3800 2750 3800
Wire Wire Line
	2750 3800 2750 3900
Connection ~ 2750 3900
Wire Wire Line
	2950 3600 2750 3600
Wire Wire Line
	2750 3600 2750 3800
Connection ~ 2750 3800
Wire Wire Line
	2950 3500 2750 3500
Wire Wire Line
	2750 3500 2750 3600
Connection ~ 2750 3600
Wire Wire Line
	2950 3400 2750 3400
Wire Wire Line
	2750 3400 2750 3500
Connection ~ 2750 3500
Wire Wire Line
	4150 1900 4350 1900
Wire Wire Line
	4150 2900 4350 2900
Wire Wire Line
	4150 2800 4350 2800
Connection ~ 4350 2800
Wire Wire Line
	4350 2800 4350 2900
Wire Wire Line
	4150 2500 4350 2500
Connection ~ 4350 2500
Wire Wire Line
	4350 2500 4350 2800
Wire Wire Line
	4150 2400 4350 2400
Connection ~ 4350 2400
Wire Wire Line
	4350 2400 4350 2500
Wire Wire Line
	4150 2300 4350 2300
Connection ~ 4350 2300
Wire Wire Line
	4350 2300 4350 2400
Wire Wire Line
	4150 2200 4350 2200
Connection ~ 4350 2200
Wire Wire Line
	4350 2200 4350 2300
Wire Wire Line
	4150 2100 4350 2100
Connection ~ 4350 2100
Wire Wire Line
	4350 2100 4350 2200
Wire Wire Line
	4150 2000 4350 2000
Wire Wire Line
	4350 1900 4350 2000
Connection ~ 4350 2000
Wire Wire Line
	4350 2000 4350 2100
Wire Wire Line
	4150 1100 4350 1100
Wire Wire Line
	4350 1100 4350 1900
Connection ~ 4350 1900
Text GLabel 7800 1400 2    50   Input ~ 0
GND
Wire Wire Line
	7800 1400 7500 1400
Text GLabel 7800 2400 2    50   Input ~ 0
GND
Text GLabel 7800 2300 2    50   Input ~ 0
GND
Text GLabel 6150 2000 0    50   Input ~ 0
GND
Text GLabel 6150 1700 0    50   Input ~ 0
GND
Wire Wire Line
	6550 1700 6150 1700
Wire Wire Line
	6150 2000 6550 2000
Wire Wire Line
	7800 2300 7500 2300
Wire Wire Line
	7500 2400 7800 2400
Text GLabel 10300 2100 2    50   Input ~ 0
GND
Text GLabel 8700 1400 0    50   Input ~ 0
GND
Wire Wire Line
	8700 1400 9000 1400
Wire Wire Line
	10300 2100 9950 2100
Text GLabel 6150 1500 0    50   Input ~ 0
RESET-MOTE
Wire Wire Line
	6550 1500 6150 1500
Text GLabel 6150 1600 0    50   Input ~ 0
+3.3V
Wire Wire Line
	6550 1600 6150 1600
Text GLabel 10300 2200 2    50   Input ~ 0
+3.3V
Wire Wire Line
	10300 2200 9950 2200
Text GLabel 8800 2100 0    50   Input ~ 0
UART-MOTE-TX
Text GLabel 8800 2200 0    50   Input ~ 0
UART-MOTE-RX
Wire Wire Line
	9000 2100 8800 2100
Wire Wire Line
	8800 2200 9000 2200
Text GLabel 4450 4700 2    50   Input ~ 0
LCD1
Text GLabel 4450 4600 2    50   Input ~ 0
LCD2
Text GLabel 4450 4500 2    50   Input ~ 0
LCD3
Text GLabel 4450 4400 2    50   Input ~ 0
LCD-RS
Text GLabel 4450 4300 2    50   Input ~ 0
LCD4
Wire Wire Line
	4450 4300 4150 4300
Wire Wire Line
	4450 4400 4150 4400
Wire Wire Line
	4450 4500 4150 4500
Wire Wire Line
	4450 4600 4150 4600
Wire Wire Line
	4450 4700 4150 4700
Text GLabel 4450 4200 2    50   Input ~ 0
CIAA-SCK
Text GLabel 4450 4100 2    50   Input ~ 0
CIAA-MISO
Text GLabel 2600 4300 0    50   Input ~ 0
CIAA-MOSI
Text GLabel 2600 4400 0    50   Input ~ 0
LCD-EN
Wire Wire Line
	4450 4100 4150 4100
Wire Wire Line
	4150 4200 4450 4200
Wire Wire Line
	2950 4300 2600 4300
Wire Wire Line
	2600 4400 2950 4400
Text GLabel 2850 2100 0    50   Input ~ 0
CIAA-UART1-RX
Text GLabel 2850 2200 0    50   Input ~ 0
CIAA-UART1-TX
Wire Wire Line
	2950 2100 2850 2100
Wire Wire Line
	2950 2200 2850 2200
Text GLabel 4450 1100 2    50   Input ~ 0
GND
Wire Wire Line
	2550 5200 2750 5200
Text GLabel 4450 1000 2    50   Input ~ 0
+5V
Text GLabel 2650 1000 0    50   Input ~ 0
+3.3V
Wire Wire Line
	4450 1000 4150 1000
Wire Wire Line
	4450 1100 4350 1100
Connection ~ 4350 1100
Text GLabel 2600 3300 0    50   Input ~ 0
+3.3V
Wire Wire Line
	2600 3300 2950 3300
Text GLabel 4450 3300 2    50   Input ~ 0
+5V
Wire Wire Line
	4150 3300 4450 3300
Wire Wire Line
	2950 1000 2650 1000
Text GLabel 7950 3400 0    50   Input ~ 0
RESET-MOTE
Text GLabel 8850 3400 2    50   Input ~ 0
GND
Wire Wire Line
	8850 3400 8600 3400
Wire Wire Line
	8200 3400 7950 3400
Text GLabel 2550 5200 0    50   Input ~ 0
GND
Connection ~ 2750 5200
Wire Wire Line
	2750 5100 2750 5200
$Comp
L LibreriaPropia:MOTEDRESDENGAT_v1 MDG1
U 1 1 5D0056C5
P 8200 2000
F 0 "MDG1" H 8225 2965 50  0000 C CNN
F 1 "MOTEDRESDENGAT_v1" H 8225 2874 50  0000 C CNN
F 2 "Connector_Samtec_HLE_SMD:SAMTEC-EDU-CIAA" H 7450 2300 50  0001 C CNN
F 3 "" H 7450 2300 50  0001 C CNN
	1    8200 2000
	1    0    0    -1  
$EndComp
Text GLabel 8100 5600 0    50   Input ~ 0
GND
Text GLabel 8100 5700 0    50   Input ~ 0
+3.3V
Text GLabel 8100 5800 0    50   Input ~ 0
+5V
Text GLabel 8100 6000 0    50   Input ~ 0
CIAA-MOSI
Text GLabel 8100 6200 0    50   Input ~ 0
CIAA-MISO
Text GLabel 8100 6100 0    50   Input ~ 0
CIAA-SCK
Text GLabel 8100 6300 0    50   Input ~ 0
GND
Text GLabel 2600 4700 0    50   Input ~ 0
GPIO0-CS
Wire Wire Line
	2950 4700 2600 4700
Text GLabel 8100 5900 0    50   Input ~ 0
GPIO0-CS
Wire Wire Line
	8100 5600 8450 5600
Wire Wire Line
	8100 5700 8450 5700
Wire Wire Line
	8100 5800 8450 5800
Wire Wire Line
	8100 5900 8450 5900
Wire Wire Line
	8100 6000 8450 6000
Wire Wire Line
	8100 6100 8450 6100
Wire Wire Line
	8100 6200 8450 6200
Wire Wire Line
	8100 6300 8450 6300
Text GLabel 6250 6650 2    50   Input ~ 0
GND
Text GLabel 4000 6650 0    50   Input ~ 0
+5V
Wire Wire Line
	6050 6650 6150 6650
Connection ~ 6150 6650
Wire Wire Line
	6150 6650 6250 6650
Text GLabel 4950 7350 3    50   Input ~ 0
LCD-RS
Wire Wire Line
	4950 7050 4950 7350
Text GLabel 4850 7350 3    50   Input ~ 0
GND
Wire Wire Line
	4850 7050 4850 7350
Text GLabel 4650 7350 3    50   Input ~ 0
LCD-EN
Wire Wire Line
	4650 7050 4650 7350
Text GLabel 5550 7350 3    50   Input ~ 0
LCD1
Text GLabel 5650 7350 3    50   Input ~ 0
LCD2
Text GLabel 5750 7350 3    50   Input ~ 0
LCD3
Text GLabel 5850 7350 3    50   Input ~ 0
LCD4
Wire Wire Line
	5550 7050 5550 7350
Wire Wire Line
	5650 7050 5650 7350
Wire Wire Line
	5750 7050 5750 7350
Wire Wire Line
	5850 7050 5850 7350
$Comp
L Device:Jumper JP1
U 1 1 5D0B78D0
P 4700 5900
F 0 "JP1" H 4700 6164 50  0000 C CNN
F 1 "Jumper" H 4700 6073 50  0000 C CNN
F 2 "lib-ESP8266:JUMPER-PONCHO-EDU-CIAA" H 4700 5900 50  0001 C CNN
F 3 "~" H 4700 5900 50  0001 C CNN
	1    4700 5900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 6250 6150 6250
Wire Wire Line
	6150 6250 6150 6650
Text GLabel 4650 6200 1    50   Input ~ 0
GND
Text GLabel 4450 4800 2    50   Input ~ 0
UART-MOTE-RX
Wire Wire Line
	4450 4800 4150 4800
Text GLabel 2600 4800 0    50   Input ~ 0
UART-MOTE-TX
Wire Wire Line
	2950 4800 2600 4800
$Comp
L Misc_Poncho_Grande:+3.3V #PWR0101
U 1 1 5D064E9F
P 1750 6150
F 0 "#PWR0101" H 1750 6110 30  0001 C CNN
F 1 "+3.3V" H 1759 6288 30  0000 C CNN
F 2 "" H 1750 6150 60  0000 C CNN
F 3 "" H 1750 6150 60  0000 C CNN
	1    1750 6150
	1    0    0    -1  
$EndComp
$Comp
L Misc_Poncho_Grande:+5V #PWR0102
U 1 1 5D06553A
P 2100 6150
F 0 "#PWR0102" H 2100 6240 20  0001 C CNN
F 1 "+5V" H 2096 6278 30  0000 C CNN
F 2 "" H 2100 6150 60  0000 C CNN
F 3 "" H 2100 6150 60  0000 C CNN
	1    2100 6150
	1    0    0    -1  
$EndComp
$Comp
L Misc_Poncho_Grande:GND #PWR0103
U 1 1 5D065BF0
P 2450 6150
F 0 "#PWR0103" H 2450 6150 30  0001 C CNN
F 1 "GND" H 2450 6080 30  0001 C CNN
F 2 "" H 2450 6150 60  0000 C CNN
F 3 "" H 2450 6150 60  0000 C CNN
	1    2450 6150
	-1   0    0    1   
$EndComp
Text GLabel 2450 6650 3    50   Input ~ 0
GND
Text GLabel 2100 6650 3    50   Input ~ 0
+5V
Text GLabel 1750 6650 3    50   Input ~ 0
+3.3V
Wire Wire Line
	1750 6650 1750 6150
Wire Wire Line
	2100 6650 2100 6150
Wire Wire Line
	2450 6150 2450 6650
Wire Notes Line
	5500 650  11050 650 
Wire Notes Line
	11050 650  11050 3650
Wire Notes Line
	11050 3650 5500 3650
Wire Notes Line
	5500 3650 5500 650 
Wire Notes Line
	6750 3850 10700 3850
Wire Notes Line
	10700 3850 10700 5200
Wire Notes Line
	10700 5200 6750 5200
Wire Notes Line
	6750 5200 6750 3850
Wire Notes Line
	6750 5300 10700 5300
Wire Notes Line
	10700 5300 10700 6450
Wire Notes Line
	6750 6450 6750 5300
Wire Notes Line
	6750 6450 10700 6450
Wire Notes Line
	6550 5500 6550 7750
Wire Notes Line
	6550 7750 3650 7750
Wire Notes Line
	3650 7750 3650 5500
Wire Notes Line
	3650 5500 6550 5500
Wire Wire Line
	4650 6200 4650 6250
Wire Wire Line
	5000 5900 5250 5900
Wire Wire Line
	5250 5900 5250 6250
Wire Wire Line
	4000 6650 4100 6650
Wire Wire Line
	4400 5900 4100 5900
Wire Wire Line
	4100 5900 4100 6650
Connection ~ 4100 6650
Wire Wire Line
	4100 6650 4450 6650
Wire Notes Line
	1050 650  1050 5400
Wire Notes Line
	1050 5400 5400 5400
Wire Notes Line
	5400 5400 5400 650 
Wire Notes Line
	1050 650  5400 650 
Wire Notes Line
	3550 5500 1050 5500
Wire Notes Line
	1050 5500 1050 7750
Wire Notes Line
	1050 7750 3550 7750
Wire Notes Line
	3550 7750 3550 5500
Text Notes 9550 3600 0    118  ~ 24
MOTES DRESDEN\n
Text Notes 10300 5150 0    118  ~ 24
WIFI
Text Notes 10400 6400 0    118  ~ 24
SD
Text Notes 6150 7700 0    118  ~ 24
LCD
Text Notes 2900 7700 0    118  ~ 24
POWER
Text Notes 1050 850  0    118  ~ 24
EDU-CIAA
Text Notes 7340 7510 0    79   ~ 16
Poncho EDU-CIAA
Text Notes 10590 7640 0    59   ~ 12
1.0
Text Notes 8130 7640 0    59   ~ 12
15/06/19
Text GLabel 9900 4350 2    50   Input ~ 0
GND
Wire Wire Line
	9550 4350 9900 4350
Text GLabel 7450 4450 0    50   Input ~ 0
+3.3V
Text GLabel 7450 4650 0    50   Input ~ 0
+3.3V
Wire Wire Line
	7650 4450 7450 4450
Wire Wire Line
	7650 4650 7450 4650
Text GLabel 7450 4350 0    50   Input ~ 0
CIAA-UART1-RX
$Comp
L ESP8266:ESP-01v090 U1
U 1 1 5D11C3EC
P 8600 4500
F 0 "U1" H 8600 5015 50  0000 C CNN
F 1 "ESP-01v090" H 8600 4924 50  0000 C CNN
F 2 "lib-ESP8266:ESP-01" H 8600 4500 50  0001 C CNN
F 3 "http://l0l.org.uk/2014/12/esp8266-modules-hardware-guide-gotta-catch-em-all/" H 8600 4500 50  0001 C CNN
	1    8600 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7650 4350 7450 4350
Text GLabel 9900 4650 2    50   Input ~ 0
CIAA-UART1-TX
Wire Wire Line
	9900 4650 9550 4650
Text GLabel 8800 2300 0    50   Input ~ 0
GND
Wire Wire Line
	9000 2300 8800 2300
$EndSCHEMATC
