EESchema Schematic File Version 4
EELAYER 30 0
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
L Joels_KiCad_Symbol_Library:ATSAMD21E18A-AF U2
U 1 1 6196BB45
P 5000 3050
F 0 "U2" H 6000 3437 60  0000 C CNN
F 1 "ATSAMD21E18A-AF" H 6000 3331 60  0000 C CNN
F 2 "Joels KiCad Footprint Library:ATSAMD21E18A-AF" H 6000 3290 60  0001 C CNN
F 3 "" H 5000 3050 60  0000 C CNN
	1    5000 3050
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AP2112K-3.3 U1
U 1 1 6196E8D9
P 2800 3050
F 0 "U1" H 2800 3392 50  0000 C CNN
F 1 "AP2112K-3.3" H 2800 3301 50  0000 C CNN
F 2 "Joels KiCad Footprint Library:Diodes-SO-8" H 2800 3375 50  0001 C CNN
F 3 "https://www.diodes.com/assets/Datasheets/AP2112.pdf" H 2800 3150 50  0001 C CNN
	1    2800 3050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 6196FBC3
P 2150 2950
F 0 "#PWR0101" H 2150 2800 50  0001 C CNN
F 1 "+5V" H 2165 3123 50  0000 C CNN
F 2 "" H 2150 2950 50  0001 C CNN
F 3 "" H 2150 2950 50  0001 C CNN
	1    2150 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 2950 2350 2950
Wire Wire Line
	2350 2950 2350 3050
Wire Wire Line
	2350 3050 2500 3050
Connection ~ 2350 2950
Wire Wire Line
	2350 2950 2500 2950
$Comp
L power:GND #PWR0102
U 1 1 6196FFD4
P 2800 3500
F 0 "#PWR0102" H 2800 3250 50  0001 C CNN
F 1 "GND" H 2805 3327 50  0000 C CNN
F 2 "" H 2800 3500 50  0001 C CNN
F 3 "" H 2800 3500 50  0001 C CNN
	1    2800 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 61970109
P 2150 3500
F 0 "#PWR0103" H 2150 3250 50  0001 C CNN
F 1 "GND" H 2155 3327 50  0000 C CNN
F 2 "" H 2150 3500 50  0001 C CNN
F 3 "" H 2150 3500 50  0001 C CNN
	1    2150 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3350 2800 3500
$Comp
L Device:C C1
U 1 1 6197047C
P 2150 3250
F 0 "C1" H 2265 3296 50  0000 L CNN
F 1 "10uF" H 2265 3205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2188 3100 50  0001 C CNN
F 3 "~" H 2150 3250 50  0001 C CNN
	1    2150 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 2950 2150 3100
Connection ~ 2150 2950
Wire Wire Line
	2150 3500 2150 3400
$Comp
L power:+3.3V #PWR0104
U 1 1 61970F71
P 3500 2950
F 0 "#PWR0104" H 3500 2800 50  0001 C CNN
F 1 "+3.3V" H 3515 3123 50  0000 C CNN
F 2 "" H 3500 2950 50  0001 C CNN
F 3 "" H 3500 2950 50  0001 C CNN
	1    3500 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2950 3350 2950
$Comp
L Device:C C2
U 1 1 61971257
P 3350 3250
F 0 "C2" H 3465 3296 50  0000 L CNN
F 1 "10uF" H 3465 3205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3388 3100 50  0001 C CNN
F 3 "~" H 3350 3250 50  0001 C CNN
	1    3350 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 2950 3350 3100
Connection ~ 3350 2950
Wire Wire Line
	3350 2950 3500 2950
$Comp
L power:GND #PWR0105
U 1 1 61971939
P 3350 3500
F 0 "#PWR0105" H 3350 3250 50  0001 C CNN
F 1 "GND" H 3355 3327 50  0000 C CNN
F 2 "" H 3350 3500 50  0001 C CNN
F 3 "" H 3350 3500 50  0001 C CNN
	1    3350 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3400 3350 3500
$Comp
L power:+3.3V #PWR0106
U 1 1 61974C81
P 4200 3850
F 0 "#PWR0106" H 4200 3700 50  0001 C CNN
F 1 "+3.3V" H 4215 4023 50  0000 C CNN
F 2 "" H 4200 3850 50  0001 C CNN
F 3 "" H 4200 3850 50  0001 C CNN
	1    4200 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3850 5000 3850
$Comp
L power:+3.3V #PWR0107
U 1 1 6197536C
P 8150 3150
F 0 "#PWR0107" H 8150 3000 50  0001 C CNN
F 1 "+3.3V" H 8165 3323 50  0000 C CNN
F 2 "" H 8150 3150 50  0001 C CNN
F 3 "" H 8150 3150 50  0001 C CNN
	1    8150 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 6197598C
P 7800 3500
F 0 "C4" H 7915 3546 50  0000 L CNN
F 1 "1uF" H 7915 3455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7838 3350 50  0001 C CNN
F 3 "~" H 7800 3500 50  0001 C CNN
	1    7800 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3350 7800 3350
$Comp
L power:GND #PWR0108
U 1 1 619769EF
P 7800 3750
F 0 "#PWR0108" H 7800 3500 50  0001 C CNN
F 1 "GND" H 7805 3577 50  0000 C CNN
F 2 "" H 7800 3750 50  0001 C CNN
F 3 "" H 7800 3750 50  0001 C CNN
	1    7800 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 3750 7800 3650
$Comp
L power:GND #PWR0109
U 1 1 6197733E
P 4200 3950
F 0 "#PWR0109" H 4200 3700 50  0001 C CNN
F 1 "GND" H 4205 3777 50  0000 C CNN
F 2 "" H 4200 3950 50  0001 C CNN
F 3 "" H 4200 3950 50  0001 C CNN
	1    4200 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3950 5000 3950
$Comp
L power:GND #PWR0110
U 1 1 619778E8
P 7550 3500
F 0 "#PWR0110" H 7550 3250 50  0001 C CNN
F 1 "GND" H 7555 3327 50  0000 C CNN
F 2 "" H 7550 3500 50  0001 C CNN
F 3 "" H 7550 3500 50  0001 C CNN
	1    7550 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3500 7550 3450
Wire Wire Line
	7550 3450 7000 3450
$Comp
L power:GND #PWR0111
U 1 1 61977F19
P 8150 3750
F 0 "#PWR0111" H 8150 3500 50  0001 C CNN
F 1 "GND" H 8155 3577 50  0000 C CNN
F 2 "" H 8150 3750 50  0001 C CNN
F 3 "" H 8150 3750 50  0001 C CNN
	1    8150 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 61978399
P 8150 3500
F 0 "C5" H 8265 3546 50  0000 L CNN
F 1 "100nF" H 8265 3455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8188 3350 50  0001 C CNN
F 3 "~" H 8150 3500 50  0001 C CNN
	1    8150 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 3250 8150 3350
Wire Wire Line
	8150 3650 8150 3750
$Comp
L Device:C C3
U 1 1 61985953
P 7850 4950
F 0 "C3" H 7965 4996 50  0000 L CNN
F 1 "100nF" H 7965 4905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7888 4800 50  0001 C CNN
F 3 "~" H 7850 4950 50  0001 C CNN
	1    7850 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3650 7600 3650
Wire Wire Line
	7600 3650 7600 4650
Wire Wire Line
	7600 4650 7850 4650
$Comp
L power:GND #PWR0112
U 1 1 61986553
P 7850 5250
F 0 "#PWR0112" H 7850 5000 50  0001 C CNN
F 1 "GND" H 7855 5077 50  0000 C CNN
F 2 "" H 7850 5250 50  0001 C CNN
F 3 "" H 7850 5250 50  0001 C CNN
	1    7850 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 4650 7850 4800
$Comp
L Device:R R2
U 1 1 61987EAF
P 8300 4650
F 0 "R2" V 8093 4650 50  0000 C CNN
F 1 "330Ω" V 8184 4650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8230 4650 50  0001 C CNN
F 3 "~" H 8300 4650 50  0001 C CNN
	1    8300 4650
	0    1    1    0   
$EndComp
Connection ~ 7850 4650
$Comp
L power:GND #PWR0113
U 1 1 6198AE52
P 8550 6050
F 0 "#PWR0113" H 8550 5800 50  0001 C CNN
F 1 "GND" H 8555 5877 50  0000 C CNN
F 2 "" H 8550 6050 50  0001 C CNN
F 3 "" H 8550 6050 50  0001 C CNN
	1    8550 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 5100 7850 5250
Wire Wire Line
	8450 4650 8550 4650
Wire Wire Line
	7950 4650 7850 4650
Connection ~ 7950 4650
Wire Wire Line
	8150 4650 7950 4650
Wire Wire Line
	7950 4500 7950 4650
$Comp
L power:+3.3V #PWR0114
U 1 1 61991AC3
P 7950 4200
F 0 "#PWR0114" H 7950 4050 50  0001 C CNN
F 1 "+3.3V" H 7965 4373 50  0000 C CNN
F 2 "" H 7950 4200 50  0001 C CNN
F 3 "" H 7950 4200 50  0001 C CNN
	1    7950 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 61991025
P 7950 4350
F 0 "R1" H 8020 4396 50  0000 L CNN
F 1 "10kΩ" H 8020 4305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7880 4350 50  0001 C CNN
F 3 "~" H 7950 4350 50  0001 C CNN
	1    7950 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3250 8150 3250
Wire Wire Line
	8150 3250 8150 3150
Connection ~ 8150 3250
Text Label 7600 4900 2    50   ~ 0
*RESET
Wire Wire Line
	7600 4650 7600 4900
Connection ~ 7600 4650
Wire Wire Line
	7400 3150 7000 3150
Text Label 7400 3150 2    50   ~ 0
SWCLK
Wire Wire Line
	7000 3050 7400 3050
Text Label 7400 3050 2    50   ~ 0
SWDIO
Entry Wire Line
	12000 5350 12100 5450
$Comp
L power:+5V #PWR0117
U 1 1 619A57B3
P 9450 4700
F 0 "#PWR0117" H 9450 4550 50  0001 C CNN
F 1 "+5V" H 9465 4873 50  0000 C CNN
F 2 "" H 9450 4700 50  0001 C CNN
F 3 "" H 9450 4700 50  0001 C CNN
	1    9450 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0118
U 1 1 619A5AAE
P 9350 4100
F 0 "#PWR0118" H 9350 3850 50  0001 C CNN
F 1 "GND" H 9355 3927 50  0000 C CNN
F 2 "" H 9350 4100 50  0001 C CNN
F 3 "" H 9350 4100 50  0001 C CNN
	1    9350 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 4100 9750 4100
Wire Wire Line
	9750 4700 9450 4700
$Comp
L Connector:Conn_01x14_Female J3
U 1 1 619AE0FA
P 9950 5300
F 0 "J3" H 9978 5276 50  0000 L CNN
F 1 "Conn_01x14_Female" H 9978 5185 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x14_P2.54mm_Vertical" H 9950 5300 50  0001 C CNN
F 3 "~" H 9950 5300 50  0001 C CNN
	1    9950 5300
	1    0    0    -1  
$EndComp
Text Label 4700 3050 0    50   ~ 0
PA00
Text Label 4700 3150 0    50   ~ 0
PA01
Text Label 4700 3250 0    50   ~ 0
PA02
Text Label 4700 3350 0    50   ~ 0
PA03
Text Label 4700 3450 0    50   ~ 0
PA04
Text Label 4700 3550 0    50   ~ 0
PA05
Text Label 4700 3650 0    50   ~ 0
PA06
Text Label 4700 3750 0    50   ~ 0
PA07
Text Label 4700 4050 0    50   ~ 0
PA08
Text Label 4700 4150 0    50   ~ 0
PA09
Text Label 4700 4250 0    50   ~ 0
PA10
Text Label 4700 4350 0    50   ~ 0
PA11
Text Label 9350 2900 0    50   ~ 0
PA00
Text Label 9350 3000 0    50   ~ 0
PA01
Text Label 9350 3100 0    50   ~ 0
PA02
Text Label 9350 3200 0    50   ~ 0
PA03
Text Label 9350 3300 0    50   ~ 0
PA04
Text Label 9350 3400 0    50   ~ 0
PA05
Text Label 9350 3500 0    50   ~ 0
PA06
Text Label 9350 3600 0    50   ~ 0
PA07
Text Label 9350 3700 0    50   ~ 0
PA08
Text Label 9350 3800 0    50   ~ 0
PA09
Text Label 9350 3900 0    50   ~ 0
PA10
Text Label 9350 4000 0    50   ~ 0
PA11
Wire Wire Line
	4700 3050 5000 3050
Wire Wire Line
	4700 3150 5000 3150
Wire Wire Line
	4700 3250 5000 3250
Wire Wire Line
	4700 3350 5000 3350
Wire Wire Line
	4700 3450 5000 3450
Wire Wire Line
	4700 3550 5000 3550
Wire Wire Line
	4700 3650 5000 3650
Wire Wire Line
	4700 3750 5000 3750
Wire Wire Line
	4700 4050 5000 4050
Wire Wire Line
	4700 4150 5000 4150
Wire Wire Line
	4700 4250 5000 4250
Wire Wire Line
	4700 4350 5000 4350
Wire Wire Line
	9350 2900 9750 2900
Wire Wire Line
	9350 3000 9750 3000
Wire Wire Line
	9350 3100 9750 3100
Wire Wire Line
	9350 3200 9750 3200
Wire Wire Line
	9350 3300 9750 3300
Wire Wire Line
	9350 3400 9750 3400
Wire Wire Line
	9350 3500 9750 3500
Wire Wire Line
	9350 3600 9750 3600
Wire Wire Line
	9350 3700 9750 3700
Wire Wire Line
	9350 3800 9750 3800
Wire Wire Line
	9350 3900 9750 3900
Wire Wire Line
	9350 4000 9750 4000
Text Label 4700 4450 0    50   ~ 0
PA14
Text Label 4700 4550 0    50   ~ 0
PA15
Wire Wire Line
	4700 4450 5000 4450
Wire Wire Line
	4700 4550 5000 4550
Text Label 7300 4550 2    50   ~ 0
PA16
Text Label 7300 4450 2    50   ~ 0
PA17
Text Label 7300 4350 2    50   ~ 0
PA18
Text Label 7300 4250 2    50   ~ 0
PA19
Text Label 7300 4150 2    50   ~ 0
PA22
Text Label 7300 4050 2    50   ~ 0
PA23
Text Label 7300 3950 2    50   ~ 0
PA24
Text Label 7300 3850 2    50   ~ 0
PA25
Text Label 7300 3750 2    50   ~ 0
PA27
Text Label 7300 3550 2    50   ~ 0
PA28
Wire Wire Line
	7300 3550 7000 3550
Wire Wire Line
	7300 3750 7000 3750
Wire Wire Line
	7000 3850 7300 3850
Wire Wire Line
	7300 3950 7000 3950
Wire Wire Line
	7000 4050 7300 4050
Wire Wire Line
	7300 4150 7000 4150
Wire Wire Line
	7000 4250 7300 4250
Wire Wire Line
	7300 4350 7000 4350
Wire Wire Line
	7000 4450 7300 4450
Wire Wire Line
	7300 4550 7000 4550
Text Label 9350 4800 0    50   ~ 0
PA14
Text Label 9350 4900 0    50   ~ 0
PA15
Text Label 9350 5000 0    50   ~ 0
PA16
Text Label 9350 5100 0    50   ~ 0
PA17
Text Label 9350 5200 0    50   ~ 0
PA18
Text Label 9350 5300 0    50   ~ 0
PA19
Text Label 9350 5400 0    50   ~ 0
PA22
Text Label 9350 5500 0    50   ~ 0
PA23
Text Label 9350 5600 0    50   ~ 0
PA24
Text Label 9350 5700 0    50   ~ 0
PA25
Text Label 9350 5800 0    50   ~ 0
PA27
Text Label 9350 5900 0    50   ~ 0
PA28
Wire Wire Line
	9350 4800 9750 4800
Wire Wire Line
	9750 4900 9350 4900
Wire Wire Line
	9350 5000 9750 5000
Wire Wire Line
	9750 5100 9350 5100
Wire Wire Line
	9750 5200 9350 5200
Wire Wire Line
	9750 5300 9350 5300
Wire Wire Line
	9750 5400 9350 5400
Wire Wire Line
	9750 5500 9350 5500
Wire Wire Line
	9750 5600 9350 5600
Wire Wire Line
	9750 5700 9350 5700
Wire Wire Line
	9750 5800 9350 5800
Wire Wire Line
	9750 5900 9350 5900
$Comp
L power:+3.3V #PWR0119
U 1 1 61A0A7CF
P 9450 2800
F 0 "#PWR0119" H 9450 2650 50  0001 C CNN
F 1 "+3.3V" H 9465 2973 50  0000 C CNN
F 2 "" H 9450 2800 50  0001 C CNN
F 3 "" H 9450 2800 50  0001 C CNN
	1    9450 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9450 2800 9750 2800
$Comp
L Connector:Conn_01x14_Female J2
U 1 1 619A7539
P 9950 3400
F 0 "J2" H 9978 3376 50  0000 L CNN
F 1 "Conn_01x14_Female" H 9978 3285 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x14_P2.54mm_Vertical" H 9950 3400 50  0001 C CNN
F 3 "~" H 9950 3400 50  0001 C CNN
	1    9950 3400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0120
U 1 1 61A29A0A
P 9350 6000
F 0 "#PWR0120" H 9350 5750 50  0001 C CNN
F 1 "GND" H 9355 5827 50  0000 C CNN
F 2 "" H 9350 6000 50  0001 C CNN
F 3 "" H 9350 6000 50  0001 C CNN
	1    9350 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 6000 9750 6000
Wire Wire Line
	9350 1700 9750 1700
Wire Wire Line
	9350 1600 9750 1600
Text Label 9350 1700 0    50   ~ 0
SWCLK
Text Label 9350 1600 0    50   ~ 0
SWDIO
Wire Wire Line
	9200 1500 9750 1500
$Comp
L power:GND #PWR0115
U 1 1 6199D9E2
P 9200 1500
F 0 "#PWR0115" H 9200 1250 50  0001 C CNN
F 1 "GND" H 9205 1327 50  0000 C CNN
F 2 "" H 9200 1500 50  0001 C CNN
F 3 "" H 9200 1500 50  0001 C CNN
	1    9200 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 1400 9750 1400
$Comp
L power:+3.3V #PWR0116
U 1 1 6199CF35
P 9200 1400
F 0 "#PWR0116" H 9200 1250 50  0001 C CNN
F 1 "+3.3V" H 9215 1573 50  0000 C CNN
F 2 "" H 9200 1400 50  0001 C CNN
F 3 "" H 9200 1400 50  0001 C CNN
	1    9200 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 1300 9750 1300
Text Label 9350 1300 0    50   ~ 0
*RESET
$Comp
L Connector:Conn_01x05_Female J1
U 1 1 61999956
P 9950 1500
F 0 "J1" H 9978 1526 50  0000 L CNN
F 1 "DEBUG" H 9978 1435 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 9950 1500 50  0001 C CNN
F 3 "~" H 9950 1500 50  0001 C CNN
	1    9950 1500
	1    0    0    -1  
$EndComp
NoConn ~ 8450 4900
NoConn ~ 8450 5800
Wire Wire Line
	8550 4650 8550 4900
Wire Wire Line
	8550 6050 8550 5800
$Comp
L Joels_KiCad_Symbol_Library:Tactile_SW SWRESET
U 1 1 6198A164
P 8500 4500
F 0 "SWRESET" V 9304 4648 50  0000 L CNN
F 1 "SW_Push" V 9395 4648 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 8500 4700 50  0001 C CNN
F 3 "~" H 8500 4700 50  0001 C CNN
	1    8500 4500
	0    1    1    0   
$EndComp
$EndSCHEMATC
