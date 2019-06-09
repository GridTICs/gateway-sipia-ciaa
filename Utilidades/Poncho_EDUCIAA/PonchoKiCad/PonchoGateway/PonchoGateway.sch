EESchema Schematic File Version 4
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
P 1800 1350
F 0 "SW1" H 1800 1635 50  0000 C CNN
F 1 "SW_Push" H 1800 1544 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 1800 1550 50  0001 C CNN
F 3 "~" H 1800 1550 50  0001 C CNN
	1    1800 1350
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:HY1602E DS1
U 1 1 5CFD8F42
P 4650 1700
F 0 "DS1" H 4650 2681 50  0000 C CNN
F 1 "HY1602E" H 4650 2590 50  0000 C CNN
F 2 "Display:HY1602E" H 4650 800 50  0001 C CIN
F 3 "http://www.icbank.com/data/ICBShop/board/HY1602E.pdf" H 4850 1800 50  0001 C CNN
	1    4650 1700
	1    0    0    -1  
$EndComp
$Comp
L LibreriaPropia:ESP8266_ARDUINO ESP1
U 1 1 5CFD86D6
P 7200 1450
F 0 "ESP1" H 7200 1965 50  0000 C CNN
F 1 "ESP8266_ARDUINO" H 7200 1874 50  0000 C CNN
F 2 "" H 7450 1100 50  0001 C CNN
F 3 "" H 7450 1100 50  0001 C CNN
	1    7200 1450
	1    0    0    -1  
$EndComp
$Comp
L LibreriaPropia:SD_Arduino SD1
U 1 1 5CFD9A33
P 9900 1600
F 0 "SD1" H 10328 1851 50  0000 L CNN
F 1 "SD_Arduino" H 10328 1760 50  0000 L CNN
F 2 "" H 9900 1650 50  0001 C CNN
F 3 "" H 9900 1650 50  0001 C CNN
	1    9900 1600
	1    0    0    -1  
$EndComp
$Comp
L Poncho_Esqueleto:Conn_Poncho2P_2x_20x2 XA1
U 1 1 5CFFA1D1
P 1700 5850
F 0 "XA1" H 2050 6397 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 2050 6291 60  0000 C CNN
F 2 "Poncho_Esqueleto:Conn_Poncho_SinBorde" H 1700 5850 60  0000 C CNN
F 3 "" H 1700 5850 60  0000 C CNN
	1    1700 5850
	1    0    0    -1  
$EndComp
$Comp
L Poncho_Esqueleto:Conn_Poncho2P_2x_20x2 XA1
U 2 1 5CFFAE9D
P 4750 5850
F 0 "XA1" H 5100 6397 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 5100 6291 60  0000 C CNN
F 2 "Poncho_Esqueleto:Conn_Poncho_SinBorde" H 4750 5850 60  0000 C CNN
F 3 "" H 4750 5850 60  0000 C CNN
	2    4750 5850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
