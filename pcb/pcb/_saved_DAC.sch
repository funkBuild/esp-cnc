EESchema Schematic File Version 4
LIBS:pcb-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
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
L custom:PCM5102A U9
U 1 1 5CB0C559
P 4500 2900
F 0 "U9" H 4500 3615 50  0000 C CNN
F 1 "PCM5102A" H 4500 3524 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 4450 4100 50  0001 C CNN
F 3 "" H 4450 4100 50  0001 C CNN
	1    4500 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0140
U 1 1 5CB0C603
P 5100 3500
F 0 "#PWR0140" H 5100 3250 50  0001 C CNN
F 1 "GND" H 5105 3327 50  0000 C CNN
F 2 "" H 5100 3500 50  0001 C CNN
F 3 "" H 5100 3500 50  0001 C CNN
	1    5100 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0141
U 1 1 5CB0C62F
P 5650 2050
F 0 "#PWR0141" H 5650 1900 50  0001 C CNN
F 1 "+3.3V" H 5665 2223 50  0000 C CNN
F 2 "" H 5650 2050 50  0001 C CNN
F 3 "" H 5650 2050 50  0001 C CNN
	1    5650 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0142
U 1 1 5CB0C651
P 3400 3550
F 0 "#PWR0142" H 3400 3300 50  0001 C CNN
F 1 "GND" H 3405 3377 50  0000 C CNN
F 2 "" H 3400 3550 50  0001 C CNN
F 3 "" H 3400 3550 50  0001 C CNN
	1    3400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3400 5100 3400
Wire Wire Line
	5100 3400 5100 3500
Wire Wire Line
	4000 3400 3850 3400
$Comp
L Device:C C13
U 1 1 5CB0C696
P 3400 3400
F 0 "C13" H 3515 3446 50  0000 L CNN
F 1 "0.1u" H 3515 3355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3438 3250 50  0001 C CNN
F 3 "~" H 3400 3400 50  0001 C CNN
	1    3400 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5CB0C6BE
P 3100 3400
F 0 "C11" H 3215 3446 50  0000 L CNN
F 1 "10u" H 3215 3355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3138 3250 50  0001 C CNN
F 3 "~" H 3100 3400 50  0001 C CNN
	1    3100 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3300 3650 3300
Wire Wire Line
	3650 3300 3650 3550
Wire Wire Line
	3650 3550 3400 3550
Wire Wire Line
	3400 3550 3100 3550
Connection ~ 3400 3550
Wire Wire Line
	3100 3250 3400 3250
Wire Wire Line
	3400 3250 3550 3250
Wire Wire Line
	3550 3250 3550 3200
Wire Wire Line
	3550 3200 4000 3200
Connection ~ 3400 3250
Wire Wire Line
	3850 3550 3650 3550
Wire Wire Line
	3850 3400 3850 3550
Connection ~ 3650 3550
$Comp
L Device:R R11
U 1 1 5CB0C9B7
P 2400 2750
F 0 "R11" V 2193 2750 50  0000 C CNN
F 1 "470" V 2284 2750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2330 2750 50  0001 C CNN
F 3 "~" H 2400 2750 50  0001 C CNN
	1    2400 2750
	0    1    1    0   
$EndComp
$Comp
L Device:C C7
U 1 1 5CB0CA1E
P 2250 2900
F 0 "C7" H 2365 2946 50  0000 L CNN
F 1 "2.2n" H 2365 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2288 2750 50  0001 C CNN
F 3 "~" H 2250 2900 50  0001 C CNN
	1    2250 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R14
U 1 1 5CB0CB56
P 2700 3100
F 0 "R14" V 2493 3100 50  0000 C CNN
F 1 "470" V 2584 3100 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2630 3100 50  0001 C CNN
F 3 "~" H 2700 3100 50  0001 C CNN
	1    2700 3100
	0    1    1    0   
$EndComp
$Comp
L Device:C C8
U 1 1 5CB0CBA8
P 2550 3250
F 0 "C8" H 2665 3296 50  0000 L CNN
F 1 "2.2n" H 2665 3205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2588 3100 50  0001 C CNN
F 3 "~" H 2550 3250 50  0001 C CNN
	1    2550 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0143
U 1 1 5CB0CBDC
P 2250 3050
F 0 "#PWR0143" H 2250 2800 50  0001 C CNN
F 1 "GND" H 2255 2877 50  0000 C CNN
F 2 "" H 2250 3050 50  0001 C CNN
F 3 "" H 2250 3050 50  0001 C CNN
	1    2250 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0144
U 1 1 5CB0CBF5
P 2550 3400
F 0 "#PWR0144" H 2550 3150 50  0001 C CNN
F 1 "GND" H 2555 3227 50  0000 C CNN
F 2 "" H 2550 3400 50  0001 C CNN
F 3 "" H 2550 3400 50  0001 C CNN
	1    2550 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 3100 4000 3100
Wire Wire Line
	4000 3000 2900 3000
Wire Wire Line
	2900 3000 2900 2750
Wire Wire Line
	2900 2750 2550 2750
Text Label 2550 3100 2    50   ~ 0
DAC_OUT_R
Text Label 2250 2750 2    50   ~ 0
DAC_OUT_L
$Comp
L Device:C C10
U 1 1 5CB0D1C2
P 3100 2700
F 0 "C10" H 3215 2746 50  0000 L CNN
F 1 "2.2u" H 3215 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3138 2550 50  0001 C CNN
F 3 "~" H 3100 2700 50  0001 C CNN
	1    3100 2700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C9
U 1 1 5CB0D208
P 3100 2350
F 0 "C9" H 3215 2396 50  0000 L CNN
F 1 "10u" H 3215 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3138 2200 50  0001 C CNN
F 3 "~" H 3100 2350 50  0001 C CNN
	1    3100 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5CB0D238
P 3400 2350
F 0 "C12" H 3515 2396 50  0000 L CNN
F 1 "0.1u" H 3515 2305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3438 2200 50  0001 C CNN
F 3 "~" H 3400 2350 50  0001 C CNN
	1    3400 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2900 3100 2850
Wire Wire Line
	3100 2550 3100 2500
Wire Wire Line
	3100 2200 3100 2150
Wire Wire Line
	3100 2150 3400 2150
Wire Wire Line
	3400 2150 3400 2200
Wire Wire Line
	3400 2500 3400 2550
Wire Wire Line
	3400 2550 3100 2550
Connection ~ 3100 2550
Wire Wire Line
	3400 2550 3600 2550
Wire Wire Line
	3600 2550 3600 2700
Wire Wire Line
	3600 2700 4000 2700
Connection ~ 3400 2550
$Comp
L Device:C C14
U 1 1 5CB0E05A
P 3650 2650
F 0 "C14" H 3765 2696 50  0000 L CNN
F 1 "2.2u" H 3765 2605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3688 2500 50  0001 C CNN
F 3 "~" H 3650 2650 50  0001 C CNN
	1    3650 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2800 3650 2800
Wire Wire Line
	3650 2500 3850 2500
Wire Wire Line
	3850 2500 3850 2600
Wire Wire Line
	3850 2600 4000 2600
Wire Wire Line
	4000 2500 4000 2150
Wire Wire Line
	4000 2150 3500 2150
Connection ~ 3400 2150
$Comp
L power:+3.3V #PWR0145
U 1 1 5CB0EF1F
P 3500 2150
F 0 "#PWR0145" H 3500 2000 50  0001 C CNN
F 1 "+3.3V" H 3515 2323 50  0000 C CNN
F 2 "" H 3500 2150 50  0001 C CNN
F 3 "" H 3500 2150 50  0001 C CNN
	1    3500 2150
	1    0    0    -1  
$EndComp
Connection ~ 3500 2150
Wire Wire Line
	3500 2150 3400 2150
$Comp
L power:GND #PWR0146
U 1 1 5CB0EF42
P 3400 2550
F 0 "#PWR0146" H 3400 2300 50  0001 C CNN
F 1 "GND" H 3405 2377 50  0000 C CNN
F 2 "" H 3400 2550 50  0001 C CNN
F 3 "" H 3400 2550 50  0001 C CNN
	1    3400 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2900 4000 2900
$Comp
L Device:C C15
U 1 1 5CB0F338
P 5450 2250
F 0 "C15" H 5565 2296 50  0000 L CNN
F 1 "2.2u" H 5565 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5488 2100 50  0001 C CNN
F 3 "~" H 5450 2250 50  0001 C CNN
	1    5450 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C17
U 1 1 5CB0F3AE
P 5850 2250
F 0 "C17" H 5965 2296 50  0000 L CNN
F 1 "2.2u" H 5965 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5888 2100 50  0001 C CNN
F 3 "~" H 5850 2250 50  0001 C CNN
	1    5850 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:C C16
U 1 1 5CB0F3E4
P 5450 2600
F 0 "C16" H 5565 2646 50  0000 L CNN
F 1 "2.2u" H 5565 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5488 2450 50  0001 C CNN
F 3 "~" H 5450 2600 50  0001 C CNN
	1    5450 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C18
U 1 1 5CB0F42C
P 5850 2600
F 0 "C18" H 5965 2646 50  0000 L CNN
F 1 "2.2u" H 5965 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5888 2450 50  0001 C CNN
F 3 "~" H 5850 2600 50  0001 C CNN
	1    5850 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2450 5850 2400
Wire Wire Line
	5850 2450 5450 2450
Connection ~ 5850 2450
Wire Wire Line
	5450 2450 5450 2400
Connection ~ 5450 2450
Wire Wire Line
	5450 2100 5450 2050
Wire Wire Line
	5450 2050 5650 2050
Wire Wire Line
	5850 2050 5850 2100
Connection ~ 5650 2050
Wire Wire Line
	5650 2050 5850 2050
Wire Wire Line
	5450 2750 5450 2800
Wire Wire Line
	5450 2800 5850 2800
Wire Wire Line
	5850 2800 5850 2750
$Comp
L power:GND #PWR0147
U 1 1 5CB1164D
P 5850 2450
F 0 "#PWR0147" H 5850 2200 50  0001 C CNN
F 1 "GND" V 5855 2322 50  0000 R CNN
F 2 "" H 5850 2450 50  0001 C CNN
F 3 "" H 5850 2450 50  0001 C CNN
	1    5850 2450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5450 2450 5250 2450
Wire Wire Line
	5250 2450 5250 2600
Wire Wire Line
	5250 2600 5000 2600
Wire Wire Line
	5000 2500 5100 2500
Wire Wire Line
	5100 2500 5100 2050
Wire Wire Line
	5100 2050 5450 2050
Connection ~ 5450 2050
Wire Wire Line
	5000 2700 5250 2700
Wire Wire Line
	5250 2700 5250 2800
Wire Wire Line
	5250 2800 5450 2800
Connection ~ 5450 2800
Text HLabel 5450 3300 2    50   Input ~ 0
SCK
Text HLabel 5450 3200 2    50   Input ~ 0
BCK
Text HLabel 5450 3100 2    50   Input ~ 0
DIN
Text HLabel 5450 3000 2    50   Input ~ 0
LRCK
$Comp
L power:GND #PWR0148
U 1 1 5CB13637
P 5450 2900
F 0 "#PWR0148" H 5450 2650 50  0001 C CNN
F 1 "GND" V 5455 2772 50  0000 R CNN
F 2 "" H 5450 2900 50  0001 C CNN
F 3 "" H 5450 2900 50  0001 C CNN
	1    5450 2900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5450 2900 5000 2900
Wire Wire Line
	5450 3000 5000 3000
Wire Wire Line
	5450 3100 5000 3100
Wire Wire Line
	5000 3200 5450 3200
Wire Wire Line
	5450 3300 5000 3300
$Comp
L Amplifier_Operational:TL072 U8
U 1 1 5CB17A70
P 2450 4600
F 0 "U8" H 2450 4967 50  0000 C CNN
F 1 "TL072" H 2450 4876 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 2450 4600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 2450 4600 50  0001 C CNN
	1    2450 4600
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL072 U8
U 2 1 5CB17B0F
P 2450 6100
F 0 "U8" H 2450 6467 50  0000 C CNN
F 1 "TL072" H 2450 6376 50  0000 C CNN
F 2 "" H 2450 6100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 2450 6100 50  0001 C CNN
	2    2450 6100
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL072 U8
U 3 1 5CB17BAB
P 6900 4450
F 0 "U8" H 6858 4496 50  0000 L CNN
F 1 "TL072" H 6858 4405 50  0000 L CNN
F 2 "" H 6900 4450 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 6900 4450 50  0001 C CNN
	3    6900 4450
	1    0    0    -1  
$EndComp
Text Label 1800 4500 2    50   ~ 0
DAC_OUT_L
$Comp
L Device:R R12
U 1 1 5CB17EF0
P 2450 5000
F 0 "R12" V 2243 5000 50  0000 C CNN
F 1 "4k" V 2334 5000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2380 5000 50  0001 C CNN
F 3 "~" H 2450 5000 50  0001 C CNN
	1    2450 5000
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 5CB17F86
P 2000 5150
F 0 "R9" H 1930 5104 50  0000 R CNN
F 1 "1k" H 1930 5195 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1930 5150 50  0001 C CNN
F 3 "~" H 2000 5150 50  0001 C CNN
	1    2000 5150
	-1   0    0    1   
$EndComp
Wire Wire Line
	2750 4600 2850 4600
Wire Wire Line
	2850 4600 2850 5000
Wire Wire Line
	2850 5000 2600 5000
Wire Wire Line
	2300 5000 2000 5000
Wire Wire Line
	2000 5000 2000 4700
Wire Wire Line
	2000 4700 2150 4700
Connection ~ 2000 5000
Wire Wire Line
	2150 4500 1800 4500
$Comp
L power:GND #PWR0149
U 1 1 5CB1C173
P 2000 5300
F 0 "#PWR0149" H 2000 5050 50  0001 C CNN
F 1 "GND" H 2005 5127 50  0000 C CNN
F 2 "" H 2000 5300 50  0001 C CNN
F 3 "" H 2000 5300 50  0001 C CNN
	1    2000 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 4600 3050 4600
Connection ~ 2850 4600
$Comp
L Device:R R13
U 1 1 5CB1D896
P 2450 6500
F 0 "R13" V 2243 6500 50  0000 C CNN
F 1 "4k" V 2334 6500 50  0000 C CNN
F 2 "" V 2380 6500 50  0001 C CNN
F 3 "~" H 2450 6500 50  0001 C CNN
	1    2450 6500
	0    1    1    0   
$EndComp
$Comp
L Device:R R10
U 1 1 5CB1D926
P 2000 6650
F 0 "R10" H 1930 6604 50  0000 R CNN
F 1 "1k" H 1930 6695 50  0000 R CNN
F 2 "" V 1930 6650 50  0001 C CNN
F 3 "~" H 2000 6650 50  0001 C CNN
	1    2000 6650
	-1   0    0    1   
$EndComp
Text Label 1800 6000 2    50   ~ 0
DAC_OUT_R
Wire Wire Line
	2150 6000 1800 6000
Wire Wire Line
	2150 6200 2000 6200
Wire Wire Line
	2000 6200 2000 6500
Wire Wire Line
	2000 6500 2300 6500
Connection ~ 2000 6500
Wire Wire Line
	2600 6500 2850 6500
Wire Wire Line
	2850 6500 2850 6100
Wire Wire Line
	2850 6100 2750 6100
$Comp
L power:GND #PWR0150
U 1 1 5CB22C5C
P 2000 6800
F 0 "#PWR0150" H 2000 6550 50  0001 C CNN
F 1 "GND" H 2005 6627 50  0000 C CNN
F 2 "" H 2000 6800 50  0001 C CNN
F 3 "" H 2000 6800 50  0001 C CNN
	1    2000 6800
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 6100 2850 6100
Connection ~ 2850 6100
Text Label 3050 4600 0    50   ~ 0
OUT_L+
Text Label 3050 6100 0    50   ~ 0
OUT_R+
$Comp
L Regulator_Linear:L78L12_SOT89 U11
U 1 1 5CB245C2
P 7950 1550
F 0 "U11" H 7950 1792 50  0000 C CNN
F 1 "L78L12_SOT89" H 7950 1701 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 7950 1750 50  0001 C CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/15/55/e5/aa/23/5b/43/fd/CD00000446.pdf/files/CD00000446.pdf/jcr:content/translations/en.CD00000446.pdf" H 7950 1500 50  0001 C CNN
	1    7950 1550
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:L79L12_SOT89 U12
U 1 1 5CB247DA
P 7950 2550
F 0 "U12" H 7950 2400 50  0000 C CNN
F 1 "L79L12_SOT89" H 7950 2309 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 7950 2350 50  0001 C CIN
F 3 "http://www.farnell.com/datasheets/1827870.pdf" H 7950 2550 50  0001 C CNN
	1    7950 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 2250 7950 2000
$Comp
L power:GND #PWR0151
U 1 1 5CB25F60
P 8100 2050
F 0 "#PWR0151" H 8100 1800 50  0001 C CNN
F 1 "GND" H 8105 1877 50  0000 C CNN
F 2 "" H 8100 2050 50  0001 C CNN
F 3 "" H 8100 2050 50  0001 C CNN
	1    8100 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 2050 8100 2000
Wire Wire Line
	8100 2000 7950 2000
Connection ~ 7950 2000
Wire Wire Line
	7950 2000 7950 1850
$Comp
L power:+12V #PWR0152
U 1 1 5CB27901
P 8450 1550
F 0 "#PWR0152" H 8450 1400 50  0001 C CNN
F 1 "+12V" V 8465 1678 50  0000 L CNN
F 2 "" H 8450 1550 50  0001 C CNN
F 3 "" H 8450 1550 50  0001 C CNN
	1    8450 1550
	0    1    1    0   
$EndComp
$Comp
L power:-12V #PWR0153
U 1 1 5CB279B4
P 8450 2550
F 0 "#PWR0153" H 8450 2650 50  0001 C CNN
F 1 "-12V" V 8465 2678 50  0000 L CNN
F 2 "" H 8450 2550 50  0001 C CNN
F 3 "" H 8450 2550 50  0001 C CNN
	1    8450 2550
	0    1    1    0   
$EndComp
Wire Wire Line
	8450 1550 8250 1550
Wire Wire Line
	8250 2550 8450 2550
$Comp
L power:+15V #PWR0154
U 1 1 5CB2AF29
P 7450 1550
F 0 "#PWR0154" H 7450 1400 50  0001 C CNN
F 1 "+15V" V 7465 1678 50  0000 L CNN
F 2 "" H 7450 1550 50  0001 C CNN
F 3 "" H 7450 1550 50  0001 C CNN
	1    7450 1550
	0    -1   -1   0   
$EndComp
$Comp
L power:-15V #PWR0155
U 1 1 5CB2B00C
P 7450 2550
F 0 "#PWR0155" H 7450 2650 50  0001 C CNN
F 1 "-15V" V 7465 2678 50  0000 L CNN
F 2 "" H 7450 2550 50  0001 C CNN
F 3 "" H 7450 2550 50  0001 C CNN
	1    7450 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7650 1550 7450 1550
Wire Wire Line
	7450 2550 7650 2550
$Comp
L power:+12V #PWR0156
U 1 1 5CB2E88D
P 6800 4150
F 0 "#PWR0156" H 6800 4000 50  0001 C CNN
F 1 "+12V" H 6815 4323 50  0000 C CNN
F 2 "" H 6800 4150 50  0001 C CNN
F 3 "" H 6800 4150 50  0001 C CNN
	1    6800 4150
	1    0    0    -1  
$EndComp
$Comp
L power:-12V #PWR0157
U 1 1 5CB2E9A0
P 6800 4750
F 0 "#PWR0157" H 6800 4850 50  0001 C CNN
F 1 "-12V" H 6815 4923 50  0000 C CNN
F 2 "" H 6800 4750 50  0001 C CNN
F 3 "" H 6800 4750 50  0001 C CNN
	1    6800 4750
	-1   0    0    1   
$EndComp
$Comp
L Amplifier_Operational:TL072 U10
U 1 1 5CD92F9F
P 4800 4600
F 0 "U10" H 4800 4967 50  0000 C CNN
F 1 "TL072" H 4800 4876 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4800 4600 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 4800 4600 50  0001 C CNN
	1    4800 4600
	1    0    0    -1  
$EndComp
$Comp
L Amplifier_Operational:TL072 U10
U 2 1 5CD93020
P 4800 6100
F 0 "U10" H 4800 6467 50  0000 C CNN
F 1 "TL072" H 4800 6376 50  0000 C CNN
F 2 "" H 4800 6100 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 4800 6100 50  0001 C CNN
	2    4800 6100
	1    0    0    -1  
$EndComp
$Comp
L Device:R R18
U 1 1 5CD930FA
P 4800 5050
F 0 "R18" V 4593 5050 50  0000 C CNN
F 1 "4k" V 4684 5050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4730 5050 50  0001 C CNN
F 3 "~" H 4800 5050 50  0001 C CNN
	1    4800 5050
	0    1    1    0   
$EndComp
$Comp
L Device:R R15
U 1 1 5CD931AC
P 4150 4700
F 0 "R15" H 4080 4654 50  0000 R CNN
F 1 "1k" H 4080 4745 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4080 4700 50  0001 C CNN
F 3 "~" H 4150 4700 50  0001 C CNN
	1    4150 4700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R16
U 1 1 5CD932F4
P 4200 6200
F 0 "R16" H 4130 6154 50  0000 R CNN
F 1 "1k" H 4130 6245 50  0000 R CNN
F 2 "" V 4130 6200 50  0001 C CNN
F 3 "~" H 4200 6200 50  0001 C CNN
	1    4200 6200
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R17
U 1 1 5CD93422
P 4750 6600
F 0 "R17" V 4543 6600 50  0000 C CNN
F 1 "4k" V 4634 6600 50  0000 C CNN
F 2 "" V 4680 6600 50  0001 C CNN
F 3 "~" H 4750 6600 50  0001 C CNN
	1    4750 6600
	0    1    1    0   
$EndComp
Text Label 3900 4700 2    50   ~ 0
DAC_OUT_L
Text Label 3950 6200 2    50   ~ 0
DAC_OUT_R
Wire Wire Line
	4050 6200 3950 6200
Wire Wire Line
	4350 6200 4450 6200
Wire Wire Line
	4450 6200 4450 6600
Wire Wire Line
	4450 6600 4600 6600
Connection ~ 4450 6200
Wire Wire Line
	4450 6200 4500 6200
Wire Wire Line
	4900 6600 5250 6600
Wire Wire Line
	5250 6600 5250 6100
Wire Wire Line
	5250 6100 5100 6100
Wire Wire Line
	4950 5050 5200 5050
Wire Wire Line
	5200 5050 5200 4600
Wire Wire Line
	5200 4600 5100 4600
Wire Wire Line
	4650 5050 4400 5050
Wire Wire Line
	4400 5050 4400 4700
Wire Wire Line
	4400 4700 4500 4700
Wire Wire Line
	4400 4700 4300 4700
Connection ~ 4400 4700
Wire Wire Line
	4000 4700 3900 4700
$Comp
L power:GND #PWR0158
U 1 1 5CDA6B51
P 4500 4500
F 0 "#PWR0158" H 4500 4250 50  0001 C CNN
F 1 "GND" H 4505 4327 50  0000 C CNN
F 2 "" H 4500 4500 50  0001 C CNN
F 3 "" H 4500 4500 50  0001 C CNN
	1    4500 4500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0159
U 1 1 5CDA6C35
P 4500 6000
F 0 "#PWR0159" H 4500 5750 50  0001 C CNN
F 1 "GND" H 4505 5827 50  0000 C CNN
F 2 "" H 4500 6000 50  0001 C CNN
F 3 "" H 4500 6000 50  0001 C CNN
	1    4500 6000
	0    1    1    0   
$EndComp
Text Label 5450 4600 0    50   ~ 0
OUT_L-
Text Label 5450 6100 0    50   ~ 0
OUT_R-
Wire Wire Line
	5450 4600 5200 4600
Connection ~ 5200 4600
Wire Wire Line
	5450 6100 5250 6100
Connection ~ 5250 6100
$Comp
L Amplifier_Operational:TL072 U10
U 3 1 5CDACDAB
P 7500 4500
F 0 "U10" H 7458 4546 50  0000 L CNN
F 1 "TL072" H 7458 4455 50  0000 L CNN
F 2 "" H 7500 4500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 7500 4500 50  0001 C CNN
	3    7500 4500
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0160
U 1 1 5CDACF0B
P 7400 4200
F 0 "#PWR0160" H 7400 4050 50  0001 C CNN
F 1 "+12V" H 7415 4373 50  0000 C CNN
F 2 "" H 7400 4200 50  0001 C CNN
F 3 "" H 7400 4200 50  0001 C CNN
	1    7400 4200
	1    0    0    -1  
$EndComp
$Comp
L power:-12V #PWR0161
U 1 1 5CDACF56
P 7400 4800
F 0 "#PWR0161" H 7400 4900 50  0001 C CNN
F 1 "-12V" H 7415 4973 50  0000 C CNN
F 2 "" H 7400 4800 50  0001 C CNN
F 3 "" H 7400 4800 50  0001 C CNN
	1    7400 4800
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J9
U 1 1 5CDAD167
P 9750 2050
F 0 "J9" H 9723 1980 50  0000 R CNN
F 1 "Conn_01x03_Male" H 9723 2071 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 9750 2050 50  0001 C CNN
F 3 "~" H 9750 2050 50  0001 C CNN
	1    9750 2050
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR0162
U 1 1 5CDAD28B
P 9450 1950
F 0 "#PWR0162" H 9450 1800 50  0001 C CNN
F 1 "+12V" V 9465 2078 50  0000 L CNN
F 2 "" H 9450 1950 50  0001 C CNN
F 3 "" H 9450 1950 50  0001 C CNN
	1    9450 1950
	0    -1   -1   0   
$EndComp
$Comp
L power:-12V #PWR0163
U 1 1 5CDAD316
P 9450 2150
F 0 "#PWR0163" H 9450 2250 50  0001 C CNN
F 1 "-12V" V 9465 2278 50  0000 L CNN
F 2 "" H 9450 2150 50  0001 C CNN
F 3 "" H 9450 2150 50  0001 C CNN
	1    9450 2150
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0164
U 1 1 5CDAD40B
P 9450 2050
F 0 "#PWR0164" H 9450 1800 50  0001 C CNN
F 1 "GND" H 9455 1877 50  0000 C CNN
F 2 "" H 9450 2050 50  0001 C CNN
F 3 "" H 9450 2050 50  0001 C CNN
	1    9450 2050
	0    1    1    0   
$EndComp
Wire Wire Line
	9550 1950 9450 1950
Wire Wire Line
	9550 2050 9450 2050
Wire Wire Line
	9550 2150 9450 2150
$EndSCHEMATC
