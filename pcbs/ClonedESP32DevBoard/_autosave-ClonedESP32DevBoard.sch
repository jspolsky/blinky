EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
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
L ClonedESP32DevBoard-rescue:Adafruit_CP2104_Friend-Joels_KiCad_Symbol_Library J1
U 1 1 61BD45F6
P 1850 1450
F 0 "J1" H 1875 1565 50  0000 C CNN
F 1 "Adafruit_CP2104_Friend" H 1875 1474 50  0000 C CNN
F 2 "Joels KiCad Footprint Library:Adafruit_CP2104_Friend" H 1850 1550 50  0001 C CNN
F 3 "" H 1850 1550 50  0001 C CNN
	1    1850 1450
	1    0    0    -1  
$EndComp
NoConn ~ 1500 1700
NoConn ~ 1500 1900
NoConn ~ 1500 2000
NoConn ~ 1500 2100
NoConn ~ 1500 2200
NoConn ~ 1500 2300
$Comp
L power:VBUS #PWR0101
U 1 1 61BD522A
P 1150 1600
F 0 "#PWR0101" H 1150 1450 50  0001 C CNN
F 1 "VBUS" H 1165 1773 50  0000 C CNN
F 2 "" H 1150 1600 50  0001 C CNN
F 3 "" H 1150 1600 50  0001 C CNN
	1    1150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 1600 1500 1600
$Comp
L power:GND #PWR0102
U 1 1 61BD57E3
P 1150 2550
F 0 "#PWR0102" H 1150 2300 50  0001 C CNN
F 1 "GND" H 1155 2377 50  0000 C CNN
F 2 "" H 1150 2550 50  0001 C CNN
F 3 "" H 1150 2550 50  0001 C CNN
	1    1150 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 2550 1150 1800
Wire Wire Line
	1150 1800 1500 1800
Text Label 2600 1800 2    50   ~ 0
DTR
Text Label 2600 2200 2    50   ~ 0
RTS
Wire Wire Line
	2250 2200 2600 2200
Wire Wire Line
	2250 1800 2600 1800
Text Label 2600 2100 2    50   ~ 0
U0TXD
Text Label 2600 2000 2    50   ~ 0
U0RXD
NoConn ~ 2250 1600
NoConn ~ 2250 1700
NoConn ~ 2250 1900
NoConn ~ 2250 2300
Text Notes 1050 1100 0    50   ~ 0
USB CONNECTIVITY
$Comp
L Device:R R1
U 1 1 61BCEF6B
P 3750 1650
F 0 "R1" V 3543 1650 50  0000 C CNN
F 1 "10K(1%)" V 3634 1650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3680 1650 50  0001 C CNN
F 3 "~" H 3750 1650 50  0001 C CNN
	1    3750 1650
	0    1    1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 61BD0546
P 3750 2250
F 0 "R2" V 3957 2250 50  0000 C CNN
F 1 "10K(1%)" V 3866 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3680 2250 50  0001 C CNN
F 3 "~" H 3750 2250 50  0001 C CNN
	1    3750 2250
	0    -1   -1   0   
$EndComp
$Comp
L Device:Q_NPN_BEC Q1
U 1 1 61BD4337
P 4750 1650
F 0 "Q1" H 4941 1696 50  0000 L CNN
F 1 "KSC3265YMTF" H 4941 1605 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4950 1750 50  0001 C CNN
F 3 "~" H 4750 1650 50  0001 C CNN
	1    4750 1650
	1    0    0    -1  
$EndComp
Text Label 3300 1650 0    50   ~ 0
DTR
Wire Wire Line
	3300 1650 3550 1650
Text Label 3300 2250 0    50   ~ 0
RTS
Wire Wire Line
	3300 2250 3500 2250
Wire Wire Line
	3900 1650 4550 1650
Text Label 5450 1300 2    50   ~ 0
CHIP_PU
Wire Wire Line
	4850 1450 4850 1300
Wire Wire Line
	4850 1300 5450 1300
Wire Wire Line
	4850 1850 3500 1850
Wire Wire Line
	3500 1850 3500 2250
Connection ~ 3500 2250
Wire Wire Line
	3500 2250 3600 2250
$Comp
L Device:Q_NPN_BEC Q2
U 1 1 61BD61FD
P 4750 2250
F 0 "Q2" H 4941 2296 50  0000 L CNN
F 1 "KSC3265YMTF" H 4941 2205 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 4950 2350 50  0001 C CNN
F 3 "~" H 4750 2250 50  0001 C CNN
	1    4750 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2250 4550 2250
Wire Wire Line
	4850 2050 4850 1950
Wire Wire Line
	4850 1950 3550 1950
Wire Wire Line
	3550 1950 3550 1650
Connection ~ 3550 1650
Wire Wire Line
	3550 1650 3600 1650
Text Label 5450 2600 2    50   ~ 0
GPIO9
Wire Wire Line
	4850 2450 4850 2600
Wire Wire Line
	4850 2600 5450 2600
Text Notes 3300 1100 0    50   ~ 0
AUTO PROGRAM
Text Notes 1050 3150 0    50   ~ 0
NEOPIXEL
$Comp
L LED:NeoPixel_THT D1
U 1 1 61BDCFC1
P 2200 3950
F 0 "D1" H 2150 4500 50  0000 L CNN
F 1 "NeoPixel" H 1950 4400 50  0000 L CNN
F 2 "Joels KiCad Footprint Library:LED_WS2812-2020" H 2250 3650 50  0001 L TNN
F 3 "https://www.adafruit.com/product/1938" H 2300 3575 50  0001 L TNN
	1    2200 3950
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0103
U 1 1 61BDD779
P 1200 3650
F 0 "#PWR0103" H 1200 3500 50  0001 C CNN
F 1 "+3.3V" H 1215 3823 50  0000 C CNN
F 2 "" H 1200 3650 50  0001 C CNN
F 3 "" H 1200 3650 50  0001 C CNN
	1    1200 3650
	1    0    0    -1  
$EndComp
NoConn ~ 2500 3950
$Comp
L power:GND #PWR0104
U 1 1 61BE0079
P 2200 4350
F 0 "#PWR0104" H 2200 4100 50  0001 C CNN
F 1 "GND" H 2205 4177 50  0000 C CNN
F 2 "" H 2200 4350 50  0001 C CNN
F 3 "" H 2200 4350 50  0001 C CNN
	1    2200 4350
	1    0    0    -1  
$EndComp
Text Label 1200 3950 0    50   ~ 0
GPIO8
$Comp
L Switch:SW_Push SW1
U 1 1 61BCF356
P 3800 3750
F 0 "SW1" V 3846 3702 50  0000 R CNN
F 1 "BOOT" V 3755 3702 50  0000 R CNN
F 2 "Joels KiCad Footprint Library:TL9320AF400QG" H 3800 3950 50  0001 C CNN
F 3 "~" H 3800 3950 50  0001 C CNN
	1    3800 3750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 61BD0211
P 3400 4300
F 0 "#PWR01" H 3400 4050 50  0001 C CNN
F 1 "GND" H 3405 4127 50  0000 C CNN
F 2 "" H 3400 4300 50  0001 C CNN
F 3 "" H 3400 4300 50  0001 C CNN
	1    3400 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 61BD0CE1
P 4000 4300
F 0 "C1" V 3748 4300 50  0000 C CNN
F 1 "0.1uF/50V(10%)(NC)" V 3839 4300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4038 4150 50  0001 C CNN
F 3 "~" H 4000 4300 50  0001 C CNN
	1    4000 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 4300 3400 3550
Wire Wire Line
	3400 3550 3800 3550
Text Label 4900 3950 2    50   ~ 0
GPIO9
Wire Wire Line
	3800 3950 4500 3950
Wire Wire Line
	3400 4300 3850 4300
Connection ~ 3400 4300
Wire Wire Line
	4150 4300 4500 4300
Wire Wire Line
	4500 4300 4500 3950
Connection ~ 4500 3950
Wire Wire Line
	4500 3950 4900 3950
$Comp
L Switch:SW_Push SW2
U 1 1 61BE1B53
P 5600 3750
F 0 "SW2" V 5646 3702 50  0000 R CNN
F 1 "RST" V 5555 3702 50  0000 R CNN
F 2 "Joels KiCad Footprint Library:TL9320AF400QG" H 5600 3950 50  0001 C CNN
F 3 "~" H 5600 3950 50  0001 C CNN
	1    5600 3750
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR02
U 1 1 61BE1B59
P 5200 4300
F 0 "#PWR02" H 5200 4050 50  0001 C CNN
F 1 "GND" H 5205 4127 50  0000 C CNN
F 2 "" H 5200 4300 50  0001 C CNN
F 3 "" H 5200 4300 50  0001 C CNN
	1    5200 4300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 61BE1B5F
P 5800 4300
F 0 "C2" V 5548 4300 50  0000 C CNN
F 1 "0.1uF/50V(10%)(NC)" V 5639 4300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5838 4150 50  0001 C CNN
F 3 "~" H 5800 4300 50  0001 C CNN
	1    5800 4300
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 4300 5200 3550
Wire Wire Line
	5200 3550 5600 3550
Text Label 6750 3950 2    50   ~ 0
CHIP_PU
Wire Wire Line
	5600 3950 6300 3950
Wire Wire Line
	5200 4300 5650 4300
Wire Wire Line
	5950 4300 6300 4300
Wire Wire Line
	6300 4300 6300 3950
Connection ~ 6300 3950
Wire Wire Line
	6300 3950 6750 3950
Connection ~ 5200 4300
Text Notes 3250 3150 0    50   ~ 0
BUTTONS
Wire Notes Line
	1050 1150 2700 1150
Wire Notes Line
	2700 1150 2700 2800
Wire Notes Line
	2700 2800 1050 2800
Wire Notes Line
	1050 2800 1050 1150
Wire Notes Line
	3250 1150 3250 2800
Wire Notes Line
	3250 2800 5600 2800
Wire Notes Line
	5600 2800 5600 1150
Wire Notes Line
	5600 1150 3250 1150
Wire Notes Line
	1050 3250 2700 3250
Wire Notes Line
	2700 3250 2700 4600
Wire Notes Line
	2700 4600 1050 4600
Wire Notes Line
	1050 4600 1050 3250
Wire Notes Line
	3250 3300 8300 3300
Wire Notes Line
	8300 3300 8300 4600
Wire Notes Line
	8300 4600 3250 4600
Wire Notes Line
	3250 4600 3250 3300
Text Notes 1050 5000 0    50   ~ 0
VOLTAGE REGULATOR - USB - HI POWER
$Comp
L Regulator_Linear:AP2112K-3.3 U1
U 1 1 61BF3C99
P 3550 5650
F 0 "U1" H 3550 5992 50  0000 C CNN
F 1 "AP2112M-3.3" H 3550 5901 50  0000 C CNN
F 2 "Joels KiCad Footprint Library:Diodes-SO-8" H 3550 5975 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/AP2112.pdf" H 3550 5750 50  0001 C CNN
	1    3550 5650
	1    0    0    -1  
$EndComp
$Comp
L Device:D D2
U 1 1 61BF79CC
P 1650 5550
F 0 "D2" H 1650 5333 50  0000 C CNN
F 1 "SD1206S020S1R0???" H 1650 5424 50  0000 C CNN
F 2 "Diode_SMD:D_1206_3216Metric" H 1650 5550 50  0001 C CNN
F 3 "~" H 1650 5550 50  0001 C CNN
	1    1650 5550
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 61BFA290
P 3550 6100
F 0 "#PWR0105" H 3550 5850 50  0001 C CNN
F 1 "GND" H 3555 5927 50  0000 C CNN
F 2 "" H 3550 6100 50  0001 C CNN
F 3 "" H 3550 6100 50  0001 C CNN
	1    3550 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3550 6100 3550 5950
$Comp
L Device:C C3
U 1 1 61BFB1B0
P 2650 5850
F 0 "C3" H 2765 5896 50  0000 L CNN
F 1 "10uF" H 2765 5805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2688 5700 50  0001 C CNN
F 3 "~" H 2650 5850 50  0001 C CNN
	1    2650 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 61BFC144
P 2650 6100
F 0 "#PWR0106" H 2650 5850 50  0001 C CNN
F 1 "GND" H 2655 5927 50  0000 C CNN
F 2 "" H 2650 6100 50  0001 C CNN
F 3 "" H 2650 6100 50  0001 C CNN
	1    2650 6100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0107
U 1 1 61C011B5
P 2100 5550
F 0 "#PWR0107" H 2100 5400 50  0001 C CNN
F 1 "+5V" H 2115 5723 50  0000 C CNN
F 2 "" H 2100 5550 50  0001 C CNN
F 3 "" H 2100 5550 50  0001 C CNN
	1    2100 5550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 61C01F2A
P 2450 5550
F 0 "#PWR0108" H 2450 5400 50  0001 C CNN
F 1 "+5V" H 2465 5723 50  0000 C CNN
F 2 "" H 2450 5550 50  0001 C CNN
F 3 "" H 2450 5550 50  0001 C CNN
	1    2450 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 5550 2650 5550
Wire Wire Line
	1200 5550 1500 5550
$Comp
L power:VBUS #PWR0109
U 1 1 61BF6A66
P 1200 5550
F 0 "#PWR0109" H 1200 5400 50  0001 C CNN
F 1 "VBUS" H 1215 5723 50  0000 C CNN
F 2 "" H 1200 5550 50  0001 C CNN
F 3 "" H 1200 5550 50  0001 C CNN
	1    1200 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 5550 2100 5550
Wire Wire Line
	2650 5700 2650 5550
Connection ~ 2650 5550
Wire Wire Line
	2650 6000 2650 6100
$Comp
L Device:C C4
U 1 1 61C108EE
P 4100 5850
F 0 "C4" H 4215 5896 50  0000 L CNN
F 1 "10uF" H 4215 5805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4138 5700 50  0001 C CNN
F 3 "~" H 4100 5850 50  0001 C CNN
	1    4100 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0110
U 1 1 61C108F8
P 4100 6100
F 0 "#PWR0110" H 4100 5850 50  0001 C CNN
F 1 "GND" H 4105 5927 50  0000 C CNN
F 2 "" H 4100 6100 50  0001 C CNN
F 3 "" H 4100 6100 50  0001 C CNN
	1    4100 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 5700 4100 5550
Wire Wire Line
	4100 6000 4100 6100
Wire Wire Line
	3850 5550 4100 5550
$Comp
L Device:LED D3
U 1 1 61C158B7
P 2100 6150
F 0 "D3" V 2139 6032 50  0000 R CNN
F 1 "LED" V 2048 6032 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric" H 2100 6150 50  0001 C CNN
F 3 "~" H 2100 6150 50  0001 C CNN
	1    2100 6150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2100 5550 2100 5700
Connection ~ 2100 5550
$Comp
L Device:R R3
U 1 1 61C1856E
P 2100 5850
F 0 "R3" H 2170 5896 50  0000 L CNN
F 1 "5.1K" H 2170 5805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2030 5850 50  0001 C CNN
F 3 "~" H 2100 5850 50  0001 C CNN
	1    2100 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 61C19F3D
P 2100 6450
F 0 "#PWR0112" H 2100 6200 50  0001 C CNN
F 1 "GND" H 2105 6277 50  0000 C CNN
F 2 "" H 2100 6450 50  0001 C CNN
F 3 "" H 2100 6450 50  0001 C CNN
	1    2100 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 6450 2100 6300
Wire Notes Line
	1050 5100 4650 5100
Wire Notes Line
	4650 5100 4650 6750
Wire Notes Line
	4650 6750 1050 6750
Wire Notes Line
	1050 6750 1050 5100
$Comp
L ClonedESP32DevBoard-rescue:MIC5225-3.3YM5-Joels_KiCad_Symbol_Library U2
U 1 1 61C1FF3E
P 6750 5550
F 0 "U2" H 7300 5815 50  0000 C CNN
F 1 "MIC5225-3.3YM5" H 7300 5724 50  0000 C CNN
F 2 "Joels KiCad Footprint Library:MIC5225-SOT23-5LD" H 6750 5950 50  0001 L CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/mic5225.pdf" H 6750 6050 50  0001 L CNN
F 4 "1%" H 6750 6150 50  0001 L CNN "accuracy percentage"
F 5 "No" H 6750 6250 50  0001 L CNN "automotive"
F 6 "IC" H 6750 6350 50  0001 L CNN "category"
F 7 "Integrated Circuits (ICs)" H 6750 6450 50  0001 L CNN "device class L1"
F 8 "Power Management ICs" H 6750 6550 50  0001 L CNN "device class L2"
F 9 "Voltage Regulators - Linear" H 6750 6650 50  0001 L CNN "device class L3"
F 10 "IC REG LINEAR 3.3V 150MA SOT23-5" H 6750 6750 50  0001 L CNN "digikey description"
F 11 "576-2980-1-ND" H 6750 6850 50  0001 L CNN "digikey part number"
F 12 "310mV" H 6750 6950 50  0001 L CNN "dropout voltage"
F 13 "1.45mm" H 6750 7050 50  0001 L CNN "height"
F 14 "Yes" H 6750 7150 50  0001 L CNN "lead free"
F 15 "4928afa3c5097de1" H 6750 7250 50  0001 L CNN "library id"
F 16 "Microchip Technology" H 6750 7350 50  0001 L CNN "manufacturer"
F 17 "+125??C" H 6750 7450 50  0001 L CNN "max junction temp"
F 18 "16V" H 6750 7550 50  0001 L CNN "max supply voltage"
F 19 "2.3V" H 6750 7650 50  0001 L CNN "min supply voltage"
F 20 "LDO Voltage Regulators High Vin, Low Iq Regulator (Lead Free)\\n\\n" H 6750 7750 50  0001 L CNN "mouser description"
F 21 "998-MIC5225-3.3YM5TR" H 6750 7850 50  0001 L CNN "mouser part number"
F 22 "29-3000uA" H 6750 7950 50  0001 L CNN "nominal supply current"
F 23 "1" H 6750 8050 50  0001 L CNN "number of outputs"
F 24 "150mA" H 6750 8150 50  0001 L CNN "output current"
F 25 "Fixed" H 6750 8250 50  0001 L CNN "output type"
F 26 "3.3V" H 6750 8350 50  0001 L CNN "output voltage"
F 27 "SOT23-5" H 6750 8450 50  0001 L CNN "package"
F 28 "Yes" H 6750 8550 50  0001 L CNN "rohs"
F 29 "0mm" H 6750 8650 50  0001 L CNN "standoff height"
F 30 "+125??C" H 6750 8750 50  0001 L CNN "temperature range high"
F 31 "-40??C" H 6750 8850 50  0001 L CNN "temperature range low"
	1    6750 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 61C2ACF1
P 6500 5800
F 0 "C5" H 6615 5846 50  0000 L CNN
F 1 "1uF" H 6615 5755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6538 5650 50  0001 C CNN
F 3 "~" H 6500 5800 50  0001 C CNN
	1    6500 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 5650 6500 5550
$Comp
L power:GND #PWR0113
U 1 1 61C2EE97
P 6500 6200
F 0 "#PWR0113" H 6500 5950 50  0001 C CNN
F 1 "GND" H 6505 6027 50  0000 C CNN
F 2 "" H 6500 6200 50  0001 C CNN
F 3 "" H 6500 6200 50  0001 C CNN
	1    6500 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 6200 6500 6050
Connection ~ 6500 6050
Wire Wire Line
	6500 6050 6500 5950
$Comp
L power:GND #PWR0114
U 1 1 61C31BFB
P 7900 6150
F 0 "#PWR0114" H 7900 5900 50  0001 C CNN
F 1 "GND" H 7905 5977 50  0000 C CNN
F 2 "" H 7900 6150 50  0001 C CNN
F 3 "" H 7900 6150 50  0001 C CNN
	1    7900 6150
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 6150 7900 5950
Wire Wire Line
	7900 5950 7750 5950
$Comp
L Device:C C6
U 1 1 61C353F6
P 7900 5750
F 0 "C6" H 8015 5796 50  0000 L CNN
F 1 "2.2uF" H 8015 5705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 7938 5600 50  0001 C CNN
F 3 "~" H 7900 5750 50  0001 C CNN
	1    7900 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 5600 7900 5550
Wire Wire Line
	7900 5900 7900 5950
Connection ~ 7900 5950
NoConn ~ 7750 5750
Text Notes 5200 5000 0    50   ~ 0
VOLTAGE REGULATOR - EXTERNAL BATTERY
Wire Notes Line
	5200 5100 8600 5100
Wire Notes Line
	8600 5100 8600 6750
Wire Notes Line
	8600 6750 5200 6750
Wire Notes Line
	5200 6750 5200 5100
Wire Wire Line
	2650 5550 2900 5550
Wire Wire Line
	2900 5650 2900 5550
Connection ~ 2900 5550
Wire Wire Line
	2900 5550 3250 5550
Wire Wire Line
	2200 4250 2200 4350
Wire Wire Line
	1200 3650 1550 3650
Wire Wire Line
	1200 3950 1550 3950
$Comp
L Device:R R6
U 1 1 61C7A8DE
P 1550 3800
F 0 "R6" H 1620 3846 50  0000 L CNN
F 1 "10K(1%)" H 1620 3755 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1480 3800 50  0001 C CNN
F 3 "~" H 1550 3800 50  0001 C CNN
	1    1550 3800
	1    0    0    -1  
$EndComp
Connection ~ 1550 3650
Wire Wire Line
	1550 3650 2200 3650
Connection ~ 1550 3950
Wire Wire Line
	1550 3950 1900 3950
Wire Wire Line
	2900 5650 3250 5650
$Comp
L Device:C C7
U 1 1 61C7F196
P 5900 5800
F 0 "C7" H 6015 5846 50  0000 L CNN
F 1 "100uF 6.3V" H 6015 5755 50  0000 L CNN
F 2 "Capacitor_SMD:C_1210_3225Metric" H 5938 5650 50  0001 C CNN
F 3 "~" H 5900 5800 50  0001 C CNN
	1    5900 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 5550 6750 5550
Connection ~ 6500 5550
Wire Wire Line
	6750 5550 6750 5950
Wire Wire Line
	6750 5950 6850 5950
Connection ~ 6750 5550
Wire Wire Line
	6750 5550 6850 5550
Wire Wire Line
	5900 5550 5900 5650
Connection ~ 5900 5550
Wire Wire Line
	5900 5550 6500 5550
Wire Wire Line
	5900 5950 5900 6050
Connection ~ 5900 6050
Wire Wire Line
	5900 6050 6500 6050
Text Label 4500 5550 2    50   ~ 0
USB3v
Wire Wire Line
	4100 5550 4500 5550
Connection ~ 4100 5550
Text Label 8350 5550 2    50   ~ 0
BAT3V
Wire Wire Line
	7750 5550 7900 5550
Connection ~ 7900 5550
Wire Wire Line
	7900 5550 8350 5550
$Comp
L Switch:SW_Push_DPDT SW3
U 1 1 61CAE00D
P 7650 3950
F 0 "SW3" H 7650 3425 50  0000 C CNN
F 1 "JS202011JCQN" H 7650 3516 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_DPDT_CK_JS202011JCQN" H 7650 3950 50  0001 C CNN
F 3 "~" H 7650 3950 50  0001 C CNN
	1    7650 3950
	-1   0    0    1   
$EndComp
Text Label 7050 3650 0    50   ~ 0
USB3v
Text Label 7050 3850 0    50   ~ 0
BAT3V
Wire Wire Line
	7050 3850 7300 3850
$Comp
L power:+3.3V #PWR0111
U 1 1 61CB8F8A
P 8100 3750
F 0 "#PWR0111" H 8100 3600 50  0001 C CNN
F 1 "+3.3V" H 8115 3923 50  0000 C CNN
F 2 "" H 8100 3750 50  0001 C CNN
F 3 "" H 8100 3750 50  0001 C CNN
	1    8100 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 3750 7850 3750
$Comp
L ClonedESP32DevBoard-rescue:ESP32-C3-MINI-1-H4-Joels_KiCad_Symbol_Library IC1
U 1 1 61D1A13C
P 11400 1650
F 0 "IC1" H 12050 1915 50  0000 C CNN
F 1 "ESP32-C3-MINI-1-H4" H 12050 1824 50  0000 C CNN
F 2 "Joels KiCad Footprint Library:ESP32-C3-MINI-1" H 12550 1750 50  0001 L CNN
F 3 "https://www.mouser.es/datasheet/2/891/Espressif_ESP32_C3_MINI_1_Datasheet-2006822.pdf" H 12550 1650 50  0001 L CNN
F 4 "SMD MODULE, ESP32-C3FH4, PCB ANT" H 12550 1550 50  0001 L CNN "Description"
F 5 "2.55" H 12550 1450 50  0001 L CNN "Height"
F 6 "Espressif Systems" H 12550 1350 50  0001 L CNN "Manufacturer_Name"
F 7 "ESP32-C3-MINI-1-H4" H 12550 1250 50  0001 L CNN "Manufacturer_Part_Number"
F 8 "356-ESP32-C3-MINI1H4" H 12550 1150 50  0001 L CNN "Mouser Part Number"
F 9 "https://www.mouser.co.uk/ProductDetail/Espressif-Systems/ESP32-C3-MINI-1-H4?qs=stqOd1AaK78JkwNX13Q9hQ%3D%3D" H 12550 1050 50  0001 L CNN "Mouser Price/Stock"
F 10 "" H 12550 950 50  0001 L CNN "Arrow Part Number"
F 11 "" H 12550 850 50  0001 L CNN "Arrow Price/Stock"
	1    11400 1650
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0115
U 1 1 61D1E684
P 9100 1600
F 0 "#PWR0115" H 9100 1450 50  0001 C CNN
F 1 "+3.3V" H 9115 1773 50  0000 C CNN
F 2 "" H 9100 1600 50  0001 C CNN
F 3 "" H 9100 1600 50  0001 C CNN
	1    9100 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	11400 1850 10150 1850
Wire Wire Line
	9100 1850 9100 1600
$Comp
L Device:C C8
U 1 1 61D21B77
P 9100 2150
F 0 "C8" H 9215 2196 50  0000 L CNN
F 1 "10uF" H 9215 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9138 2000 50  0001 C CNN
F 3 "~" H 9100 2150 50  0001 C CNN
	1    9100 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 61D22A0D
P 9600 2150
F 0 "C9" H 9715 2196 50  0000 L CNN
F 1 "0.1uF" H 9715 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9638 2000 50  0001 C CNN
F 3 "~" H 9600 2150 50  0001 C CNN
	1    9600 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 1850 9100 2000
Connection ~ 9100 1850
Wire Wire Line
	9600 2000 9600 1850
Connection ~ 9600 1850
Wire Wire Line
	9600 1850 9100 1850
$Comp
L power:GND #PWR0116
U 1 1 61D275B7
P 9100 3000
F 0 "#PWR0116" H 9100 2750 50  0001 C CNN
F 1 "GND" H 9105 2827 50  0000 C CNN
F 2 "" H 9100 3000 50  0001 C CNN
F 3 "" H 9100 3000 50  0001 C CNN
	1    9100 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 2300 9100 2650
Wire Wire Line
	9600 2300 9600 2650
Wire Wire Line
	9600 2650 9100 2650
Connection ~ 9100 2650
Wire Wire Line
	9100 2650 9100 3000
$Comp
L Device:R R4
U 1 1 61D2C595
P 10150 2150
F 0 "R4" H 10220 2196 50  0000 L CNN
F 1 "10K(1%)" H 10220 2105 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10080 2150 50  0001 C CNN
F 3 "~" H 10150 2150 50  0001 C CNN
	1    10150 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 1850 10150 2000
Connection ~ 10150 1850
Wire Wire Line
	10150 1850 9600 1850
Wire Wire Line
	10150 2350 10150 2300
Text Label 10600 2350 0    50   ~ 0
CHIP_PU
Wire Wire Line
	10150 2350 11400 2350
$Comp
L Device:C C10
U 1 1 61D41B79
P 10150 2650
F 0 "C10" H 10265 2696 50  0000 L CNN
F 1 "1uF" H 10265 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 10188 2500 50  0001 C CNN
F 3 "~" H 10150 2650 50  0001 C CNN
	1    10150 2650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 61D429E9
P 10150 3000
F 0 "#PWR0117" H 10150 2750 50  0001 C CNN
F 1 "GND" H 10155 2827 50  0000 C CNN
F 2 "" H 10150 3000 50  0001 C CNN
F 3 "" H 10150 3000 50  0001 C CNN
	1    10150 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 3000 10150 2800
Wire Wire Line
	10150 2500 10150 2350
Connection ~ 10150 2350
Text Label 11050 2050 0    50   ~ 0
GPIO2
Wire Wire Line
	11050 2050 11400 2050
Text Label 11050 2150 0    50   ~ 0
GPIO3
Wire Wire Line
	11050 2150 11400 2150
NoConn ~ 11400 1950
NoConn ~ 11400 2250
$Comp
L power:GND #PWR0118
U 1 1 61D51F25
P 10950 1350
F 0 "#PWR0118" H 10950 1100 50  0001 C CNN
F 1 "GND" V 10955 1222 50  0000 R CNN
F 2 "" H 10950 1350 50  0001 C CNN
F 3 "" H 10950 1350 50  0001 C CNN
	1    10950 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	10950 1350 11400 1350
Wire Wire Line
	11400 1350 11400 1650
Wire Wire Line
	11400 1650 11400 1750
Connection ~ 11400 1650
NoConn ~ 11400 2450
NoConn ~ 11400 2550
Text Label 11050 2750 0    50   ~ 0
GPIO0
Text Label 11050 2850 0    50   ~ 0
GPIO1
Text Label 11050 3150 0    50   ~ 0
GPIO10
Text Label 11050 3350 0    50   ~ 0
GPIO4
Text Label 11050 3450 0    50   ~ 0
GPIO5
Text Label 11050 3550 0    50   ~ 0
GPIO6
Text Label 11050 3650 0    50   ~ 0
GPIO7
Text Label 11050 3750 0    50   ~ 0
GPIO8
Text Label 11050 3850 0    50   ~ 0
GPIO9
NoConn ~ 11400 3050
NoConn ~ 11400 3250
NoConn ~ 11400 3950
NoConn ~ 11400 4050
Text Label 11050 4150 0    50   ~ 0
GPIO18
Text Label 11050 4250 0    50   ~ 0
GPIO19
Wire Wire Line
	11050 2750 11400 2750
Wire Wire Line
	11050 2850 11400 2850
Wire Wire Line
	11050 3150 11400 3150
Wire Wire Line
	11400 3350 11050 3350
Wire Wire Line
	11050 3450 11400 3450
Wire Wire Line
	11050 3550 11400 3550
Wire Wire Line
	11050 3650 11400 3650
Wire Wire Line
	11400 3750 11050 3750
Wire Wire Line
	11050 3850 11400 3850
Wire Wire Line
	11400 4150 11050 4150
Wire Wire Line
	11050 4250 11400 4250
NoConn ~ 11400 4350
NoConn ~ 11400 4450
Text Label 11050 4550 0    50   ~ 0
U0RXD
Wire Wire Line
	11050 4550 11400 4550
Text Label 11050 4650 0    50   ~ 0
U0TXD
Wire Wire Line
	11050 4650 11400 4650
NoConn ~ 12700 1650
NoConn ~ 12700 1750
NoConn ~ 12700 1850
NoConn ~ 12700 1950
$Comp
L power:GND #PWR0119
U 1 1 61DA6983
P 13100 4550
F 0 "#PWR0119" H 13100 4300 50  0001 C CNN
F 1 "GND" H 13105 4377 50  0000 C CNN
F 2 "" H 13100 4550 50  0001 C CNN
F 3 "" H 13100 4550 50  0001 C CNN
	1    13100 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	13100 4550 12700 4550
Wire Wire Line
	13100 4550 13100 4450
Wire Wire Line
	13100 4450 12700 4450
Connection ~ 13100 4550
Wire Wire Line
	12700 2050 13100 2050
Wire Wire Line
	13100 2050 13100 2150
Connection ~ 13100 4450
Wire Wire Line
	12700 2150 13100 2150
Connection ~ 13100 2150
Wire Wire Line
	13100 2150 13100 2250
Wire Wire Line
	13100 2250 12700 2250
Connection ~ 13100 2250
Wire Wire Line
	13100 2250 13100 2350
Wire Wire Line
	12700 2350 13100 2350
Connection ~ 13100 2350
Wire Wire Line
	13100 2350 13100 2450
Wire Wire Line
	12700 2450 13100 2450
Connection ~ 13100 2450
Wire Wire Line
	13100 2450 13100 2550
Wire Wire Line
	12700 2550 13100 2550
Connection ~ 13100 2550
Wire Wire Line
	13100 2550 13100 2650
Wire Wire Line
	12700 2650 13100 2650
Connection ~ 13100 2650
Wire Wire Line
	13100 2650 13100 2750
Wire Wire Line
	12700 2750 13100 2750
Connection ~ 13100 2750
Wire Wire Line
	13100 2750 13100 2850
Wire Wire Line
	12700 2850 13100 2850
Connection ~ 13100 2850
Wire Wire Line
	13100 2850 13100 2950
Wire Wire Line
	12700 2950 13100 2950
Connection ~ 13100 2950
Wire Wire Line
	13100 2950 13100 3050
Wire Wire Line
	12700 3050 13100 3050
Connection ~ 13100 3050
Wire Wire Line
	13100 3050 13100 3150
Wire Wire Line
	12700 3150 13100 3150
Connection ~ 13100 3150
Wire Wire Line
	13100 3150 13100 3250
Wire Wire Line
	12700 3250 13100 3250
Connection ~ 13100 3250
Wire Wire Line
	13100 3250 13100 3350
Wire Wire Line
	12700 3350 13100 3350
Connection ~ 13100 3350
Wire Wire Line
	13100 3350 13100 3450
Wire Wire Line
	12700 3450 13100 3450
Connection ~ 13100 3450
Wire Wire Line
	13100 3450 13100 3550
Wire Wire Line
	12700 3550 13100 3550
Connection ~ 13100 3550
Wire Wire Line
	13100 3550 13100 3650
Wire Wire Line
	12700 3650 13100 3650
Connection ~ 13100 3650
Wire Wire Line
	13100 3650 13100 3750
Wire Wire Line
	12700 3750 13100 3750
Connection ~ 13100 3750
Wire Wire Line
	13100 3750 13100 3850
Wire Wire Line
	12700 3850 13100 3850
Connection ~ 13100 3850
Wire Wire Line
	13100 3850 13100 3950
Wire Wire Line
	12700 3950 13100 3950
Connection ~ 13100 3950
Wire Wire Line
	13100 3950 13100 4050
Wire Wire Line
	12700 4050 13100 4050
Connection ~ 13100 4050
Wire Wire Line
	13100 4050 13100 4150
Wire Wire Line
	12700 4150 13100 4150
Connection ~ 13100 4150
Wire Wire Line
	13100 4150 13100 4250
Wire Wire Line
	12700 4250 13100 4250
Connection ~ 13100 4250
Wire Wire Line
	13100 4250 13100 4350
Wire Wire Line
	12700 4350 13100 4350
Connection ~ 13100 4350
Wire Wire Line
	13100 4350 13100 4450
Wire Wire Line
	11400 2650 10750 2650
Wire Wire Line
	10750 2650 10750 2950
Wire Wire Line
	10750 2950 11400 2950
$Comp
L power:GND #PWR0120
U 1 1 61E22E0C
P 10750 3000
F 0 "#PWR0120" H 10750 2750 50  0001 C CNN
F 1 "GND" H 10755 2827 50  0000 C CNN
F 2 "" H 10750 3000 50  0001 C CNN
F 3 "" H 10750 3000 50  0001 C CNN
	1    10750 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10750 3000 10750 2950
Connection ~ 10750 2950
Wire Notes Line
	8900 1100 13300 1100
Wire Notes Line
	13300 1100 13300 4900
Wire Notes Line
	13300 4900 8900 4900
Wire Notes Line
	8900 4900 8900 1100
Text Notes 8900 1050 0    50   ~ 0
ESP32-C3-MINI-1
$Comp
L Connector:Conn_01x16_Female J3
U 1 1 61E633D5
P 10900 6250
F 0 "J3" H 10750 7200 50  0000 L CNN
F 1 "HDR1" H 10700 5250 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x16_P2.54mm_Vertical" H 10900 6250 50  0001 C CNN
F 3 "~" H 10900 6250 50  0001 C CNN
	1    10900 6250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x16_Female J4
U 1 1 61E65567
P 11200 6250
F 0 "J4" H 11150 7200 50  0000 C CNN
F 1 "HDR2" H 11050 5250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x16_P2.54mm_Vertical" H 11200 6250 50  0001 C CNN
F 3 "~" H 11200 6250 50  0001 C CNN
	1    11200 6250
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR0121
U 1 1 61E887BA
P 9800 7050
F 0 "#PWR0121" H 9800 6800 50  0001 C CNN
F 1 "GND" H 9805 6877 50  0000 C CNN
F 2 "" H 9800 7050 50  0001 C CNN
F 3 "" H 9800 7050 50  0001 C CNN
	1    9800 7050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0122
U 1 1 61E88D23
P 12250 7050
F 0 "#PWR0122" H 12250 6800 50  0001 C CNN
F 1 "GND" H 12255 6877 50  0000 C CNN
F 2 "" H 12250 7050 50  0001 C CNN
F 3 "" H 12250 7050 50  0001 C CNN
	1    12250 7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10700 5550 9800 5550
Wire Wire Line
	10700 6050 9800 6050
Wire Wire Line
	9800 5550 9800 6050
Connection ~ 9800 6050
Wire Wire Line
	9800 6050 9800 6250
Wire Wire Line
	10700 6250 9800 6250
Connection ~ 9800 6250
Wire Wire Line
	9800 6250 9800 6650
Wire Wire Line
	10700 6650 9800 6650
Connection ~ 9800 6650
Wire Wire Line
	9800 6650 9800 6950
Wire Wire Line
	10700 6950 9800 6950
Connection ~ 9800 6950
Wire Wire Line
	9800 6950 9800 7050
Wire Wire Line
	10700 7050 9800 7050
Connection ~ 9800 7050
Wire Wire Line
	11400 5550 12250 5550
Wire Wire Line
	11400 5850 12250 5850
Wire Wire Line
	12250 5550 12250 5850
Connection ~ 12250 5850
Wire Wire Line
	11400 6650 12250 6650
Connection ~ 12250 6650
Wire Wire Line
	12250 6650 12250 6950
Wire Wire Line
	11400 6950 12250 6950
Connection ~ 12250 6950
Wire Wire Line
	12250 6950 12250 7050
Wire Wire Line
	11400 7050 12250 7050
Connection ~ 12250 7050
$Comp
L power:+3.3V #PWR0123
U 1 1 61EE5517
P 9500 5550
F 0 "#PWR0123" H 9500 5400 50  0001 C CNN
F 1 "+3.3V" H 9515 5723 50  0000 C CNN
F 2 "" H 9500 5550 50  0001 C CNN
F 3 "" H 9500 5550 50  0001 C CNN
	1    9500 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10700 5650 9500 5650
Wire Wire Line
	9500 5650 9500 5550
Wire Wire Line
	9500 5650 9500 5750
Wire Wire Line
	9500 5750 10700 5750
Connection ~ 9500 5650
Wire Wire Line
	9250 6750 10700 6750
$Comp
L power:+5V #PWR0126
U 1 1 61F13E08
P 9250 6650
F 0 "#PWR0126" H 9250 6500 50  0001 C CNN
F 1 "+5V" H 9265 6823 50  0000 C CNN
F 2 "" H 9250 6650 50  0001 C CNN
F 3 "" H 9250 6650 50  0001 C CNN
	1    9250 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 6650 9250 6750
Wire Wire Line
	9250 6850 10700 6850
Text Label 10250 5850 0    50   ~ 0
GPIO2
Text Label 10250 5950 0    50   ~ 0
GPIO3
Text Label 10250 6150 0    50   ~ 0
CHIP_PU
Text Label 10250 6350 0    50   ~ 0
GPIO0
Text Label 10250 6450 0    50   ~ 0
GPIO1
Text Label 10250 6550 0    50   ~ 0
GPIO10
Wire Wire Line
	10250 6550 10700 6550
Wire Wire Line
	10700 6450 10250 6450
Wire Wire Line
	10250 6350 10700 6350
Wire Wire Line
	10700 6150 10250 6150
Wire Wire Line
	10250 5950 10700 5950
Wire Wire Line
	10250 5850 10700 5850
Text Label 11850 5650 2    50   ~ 0
U0TXD
Text Label 11850 5750 2    50   ~ 0
U0RXD
Text Label 11850 5950 2    50   ~ 0
GPIO9
Text Label 11850 6050 2    50   ~ 0
GPIO8
Wire Wire Line
	11400 6150 12250 6150
Wire Wire Line
	12250 5850 12250 6150
Connection ~ 12250 6150
Wire Wire Line
	12250 6150 12250 6650
Text Label 11850 6250 2    50   ~ 0
GPIO7
Text Label 11850 6350 2    50   ~ 0
GPIO6
Text Label 11850 6450 2    50   ~ 0
GPIO5
Text Label 11850 6550 2    50   ~ 0
GPIO4
Text Label 11850 6750 2    50   ~ 0
GPIO18
Text Label 11850 6850 2    50   ~ 0
GPIO19
Wire Wire Line
	11850 5650 11400 5650
Wire Wire Line
	11400 5750 11850 5750
Wire Wire Line
	11850 5950 11400 5950
Wire Wire Line
	11400 6050 11850 6050
Wire Wire Line
	11850 6250 11400 6250
Wire Wire Line
	11400 6350 11850 6350
Wire Wire Line
	11850 6450 11400 6450
Wire Wire Line
	11850 6550 11400 6550
Wire Wire Line
	11850 6750 11400 6750
Wire Wire Line
	11850 6850 11400 6850
Wire Notes Line
	9150 5150 12400 5150
Wire Notes Line
	12400 5150 12400 7400
Wire Notes Line
	12400 7400 9150 7400
Wire Notes Line
	9150 7400 9150 5150
Text Notes 9150 5050 0    50   ~ 0
CONNECTORS
Wire Wire Line
	2250 2000 2600 2000
Wire Wire Line
	2250 2100 2600 2100
$Comp
L Device:Battery_Cell BT1
U 1 1 61FFFC19
P 5300 5850
F 0 "BT1" H 5418 5946 50  0000 L CNN
F 1 "Battery_Cell" H 5418 5855 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" V 5300 5910 50  0001 C CNN
F 3 "~" V 5300 5910 50  0001 C CNN
	1    5300 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 5550 5900 5550
Wire Wire Line
	5300 5950 5300 6050
Wire Wire Line
	5300 6050 5900 6050
Wire Wire Line
	5300 5550 5300 5650
Wire Wire Line
	7050 3650 7350 3650
Wire Wire Line
	7850 4150 7850 3750
Connection ~ 7850 3750
Wire Wire Line
	7450 4050 7350 4050
Wire Wire Line
	7350 4050 7350 3650
Connection ~ 7350 3650
Wire Wire Line
	7350 3650 7450 3650
Wire Wire Line
	7450 4250 7300 4250
Wire Wire Line
	7300 4250 7300 3850
Connection ~ 7300 3850
Wire Wire Line
	7300 3850 7450 3850
Connection ~ 9250 6750
Wire Wire Line
	9250 6750 9250 6850
$EndSCHEMATC
