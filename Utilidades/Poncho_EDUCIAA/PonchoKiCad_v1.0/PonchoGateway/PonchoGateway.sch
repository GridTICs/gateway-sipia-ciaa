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
P 8650 3700
F 0 "SW1" H 8650 3985 50  0000 C CNN
F 1 "SW_Push" H 8650 3894 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 8650 3900 50  0001 C CNN
F 3 "~" H 8650 3900 50  0001 C CNN
	1    8650 3700
	1    0    0    -1  
$EndComp
$Comp
L Display_Character:HY1602E DS1
U 1 1 5CFD8F42
P 3600 6650
F 0 "DS1" H 3600 7631 50  0000 C CNN
F 1 "HY1602E" H 3600 7540 50  0000 C CNN
F 2 "Display:HY1602E" H 3600 5750 50  0001 C CIN
F 3 "http://www.icbank.com/data/ICBShop/board/HY1602E.pdf" H 3800 6750 50  0001 C CNN
	1    3600 6650
	0    -1   -1   0   
$EndComp
$Comp
L LibreriaPropia:ESP8266_ARDUINO ESP1
U 1 1 5CFD86D6
P 6900 5450
F 0 "ESP1" H 6900 5965 50  0000 C CNN
F 1 "ESP8266_ARDUINO" H 6900 5874 50  0000 C CNN
F 2 "" H 7150 5100 50  0001 C CNN
F 3 "" H 7150 5100 50  0001 C CNN
	1    6900 5450
	1    0    0    -1  
$EndComp
$Comp
L LibreriaPropia:SD_Arduino SD1
U 1 1 5CFD9A33
P 9900 5600
F 0 "SD1" H 10328 5851 50  0000 L CNN
F 1 "SD_Arduino" H 10328 5760 50  0000 L CNN
F 2 "" H 9900 5650 50  0001 C CNN
F 3 "" H 9900 5650 50  0001 C CNN
	1    9900 5600
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
P 3200 3700
F 0 "XA1" H 3550 4247 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 3550 4141 60  0000 C CNN
F 2 "Poncho_Esqueleto:Conn_Poncho_SinBorde" H 3200 3700 60  0000 C CNN
F 3 "" H 3200 3700 60  0000 C CNN
	2    3200 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 5300 2750 5300
Wire Wire Line
	2950 5200 2750 5200
Wire Wire Line
	2950 4700 2750 4700
Wire Wire Line
	2750 4700 2750 5200
Connection ~ 2750 5200
Wire Wire Line
	2950 4600 2750 4600
Wire Wire Line
	2750 4600 2750 4700
Connection ~ 2750 4700
Wire Wire Line
	2950 4300 2750 4300
Wire Wire Line
	2750 4300 2750 4600
Connection ~ 2750 4600
Wire Wire Line
	2950 4200 2750 4200
Wire Wire Line
	2750 4200 2750 4300
Connection ~ 2750 4300
Wire Wire Line
	2950 4000 2750 4000
Wire Wire Line
	2750 4000 2750 4200
Connection ~ 2750 4200
Wire Wire Line
	2950 3900 2750 3900
Wire Wire Line
	2750 3900 2750 4000
Connection ~ 2750 4000
Wire Wire Line
	2950 3700 2750 3700
Wire Wire Line
	2750 3700 2750 3900
Connection ~ 2750 3900
Wire Wire Line
	2950 3600 2750 3600
Wire Wire Line
	2750 3600 2750 3700
Connection ~ 2750 3700
Wire Wire Line
	2950 3500 2750 3500
Wire Wire Line
	2750 3500 2750 3600
Connection ~ 2750 3600
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
Text GLabel 8250 1500 2    50   Input ~ 0
GND
Wire Wire Line
	8250 1500 7950 1500
Text GLabel 8250 2500 2    50   Input ~ 0
GND
Text GLabel 8250 2400 2    50   Input ~ 0
GND
Text GLabel 6600 2100 0    50   Input ~ 0
GND
Text GLabel 6600 1800 0    50   Input ~ 0
GND
Wire Wire Line
	7000 1800 6600 1800
Wire Wire Line
	6600 2100 7000 2100
Wire Wire Line
	8250 2400 7950 2400
Wire Wire Line
	7950 2500 8250 2500
Text GLabel 10750 2200 2    50   Input ~ 0
GND
Text GLabel 9150 1500 0    50   Input ~ 0
GND
Wire Wire Line
	9150 1500 9450 1500
Wire Wire Line
	10750 2200 10400 2200
Text GLabel 6600 1600 0    50   Input ~ 0
RESET-MOTE
Wire Wire Line
	7000 1600 6600 1600
Text GLabel 6600 1700 0    50   Input ~ 0
+3.3V
Wire Wire Line
	7000 1700 6600 1700
Text GLabel 10750 2300 2    50   Input ~ 0
+3.3V
Wire Wire Line
	10750 2300 10400 2300
Text GLabel 9250 2200 0    50   Input ~ 0
UART-MOTE-TX
Text GLabel 9250 2300 0    50   Input ~ 0
UART-MOTE-RX
Wire Wire Line
	9450 2200 9250 2200
Wire Wire Line
	9250 2300 9450 2300
Text GLabel 4450 4800 2    50   Input ~ 0
LCD1
Text GLabel 4450 4700 2    50   Input ~ 0
LCD2
Text GLabel 4450 4600 2    50   Input ~ 0
LCD3
Text GLabel 4450 4500 2    50   Input ~ 0
LCD-RS
Text GLabel 4450 4400 2    50   Input ~ 0
LCD4
Wire Wire Line
	4450 4400 4150 4400
Wire Wire Line
	4450 4500 4150 4500
Wire Wire Line
	4450 4600 4150 4600
Wire Wire Line
	4450 4700 4150 4700
Wire Wire Line
	4450 4800 4150 4800
Text GLabel 4450 4300 2    50   Input ~ 0
CIAA-SCK
Text GLabel 4450 4200 2    50   Input ~ 0
CIAA-MISO
Text GLabel 2600 4400 0    50   Input ~ 0
CIAA-MOSI
Text GLabel 2600 4500 0    50   Input ~ 0
LCD-EN
Wire Wire Line
	4450 4200 4150 4200
Wire Wire Line
	4150 4300 4450 4300
Wire Wire Line
	2950 4400 2600 4400
Wire Wire Line
	2600 4500 2950 4500
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
	2550 5300 2750 5300
Text GLabel 4450 1000 2    50   Input ~ 0
+5V
Text GLabel 2650 1000 0    50   Input ~ 0
+3.3V
Wire Wire Line
	4450 1000 4150 1000
Wire Wire Line
	4450 1100 4350 1100
Connection ~ 4350 1100
Text GLabel 2600 3400 0    50   Input ~ 0
+3.3V
Wire Wire Line
	2600 3400 2950 3400
Text GLabel 4450 3400 2    50   Input ~ 0
+5V
Wire Wire Line
	4150 3400 4450 3400
Wire Wire Line
	2950 1000 2650 1000
Text GLabel 8200 3700 0    50   Input ~ 0
RESET-MOTE
Text GLabel 9100 3700 2    50   Input ~ 0
GND
Wire Wire Line
	9100 3700 8850 3700
Wire Wire Line
	8450 3700 8200 3700
Text GLabel 2550 5300 0    50   Input ~ 0
GND
Connection ~ 2750 5300
Wire Wire Line
	2750 5200 2750 5300
$Comp
L LibreriaPropia:MOTEDRESDENGAT_v1 MDG1
U 1 1 5D0056C5
P 8650 2100
F 0 "MDG1" H 8675 3065 50  0000 C CNN
F 1 "MOTEDRESDENGAT_v1" H 8675 2974 50  0000 C CNN
F 2 "" H 7900 2400 50  0001 C CNN
F 3 "" H 7900 2400 50  0001 C CNN
	1    8650 2100
	1    0    0    -1  
$EndComp
Text GLabel 8800 5050 0    50   Input ~ 0
GND
Text GLabel 8800 5150 0    50   Input ~ 0
+3.3V
Text GLabel 8800 5250 0    50   Input ~ 0
+5V
Text GLabel 8800 5450 0    50   Input ~ 0
CIAA-MOSI
Text GLabel 8800 5650 0    50   Input ~ 0
CIAA-MISO
Text GLabel 8800 5550 0    50   Input ~ 0
CIAA-SCK
Text GLabel 8800 5750 0    50   Input ~ 0
GND
Text GLabel 2600 4800 0    50   Input ~ 0
GPIO0-CS
Wire Wire Line
	2950 4800 2600 4800
Text GLabel 8800 5350 0    50   Input ~ 0
GPIO0-CS
Wire Wire Line
	8800 5050 9150 5050
Wire Wire Line
	8800 5150 9150 5150
Wire Wire Line
	8800 5250 9150 5250
Wire Wire Line
	8800 5350 9150 5350
Wire Wire Line
	8800 5450 9150 5450
Wire Wire Line
	8800 5550 9150 5550
Wire Wire Line
	8800 5650 9150 5650
Wire Wire Line
	8800 5750 9150 5750
Text GLabel 7600 5650 2    50   Input ~ 0
+3.3V
Text GLabel 6150 5650 0    50   Input ~ 0
GND
Wire Wire Line
	7600 5650 7300 5650
Wire Wire Line
	6150 5650 6500 5650
$EndSCHEMATC
