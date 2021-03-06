EESchema Schematic File Version 4
LIBS:pcb-cache
EELAYER 30 0
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
L custom:PCM5102A U?
U 1 1 5CB0C559
P 4500 2900
F 0 "U?" H 4500 3615 50  0000 C CNN
F 1 "PCM5102A" H 4500 3524 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 4450 4100 50  0001 C CNN
F 3 "" H 4450 4100 50  0001 C CNN
	1    4500 2900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CB0C603
P 5100 3500
F 0 "#PWR?" H 5100 3250 50  0001 C CNN
F 1 "GND" H 5105 3327 50  0000 C CNN
F 2 "" H 5100 3500 50  0001 C CNN
F 3 "" H 5100 3500 50  0001 C CNN
	1    5100 3500
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CB0C62F
P 5650 2050
F 0 "#PWR?" H 5650 1900 50  0001 C CNN
F 1 "+3.3V" H 5665 2223 50  0000 C CNN
F 2 "" H 5650 2050 50  0001 C CNN
F 3 "" H 5650 2050 50  0001 C CNN
	1    5650 2050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CB0C651
P 3400 3550
F 0 "#PWR?" H 3400 3300 50  0001 C CNN
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
L pcb-rescue:C-Device C?
U 1 1 5CB0C696
P 3400 3400
F 0 "C?" H 3515 3446 50  0000 L CNN
F 1 "0.1u" H 3515 3355 50  0000 L CNN
F 2 "" H 3438 3250 50  0001 C CNN
F 3 "~" H 3400 3400 50  0001 C CNN
	1    3400 3400
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:C-Device C?
U 1 1 5CB0C6BE
P 3100 3400
F 0 "C?" H 3215 3446 50  0000 L CNN
F 1 "10u" H 3215 3355 50  0000 L CNN
F 2 "" H 3138 3250 50  0001 C CNN
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
L pcb-rescue:R-Device R?
U 1 1 5CB0C9B7
P 2400 2750
F 0 "R?" V 2193 2750 50  0000 C CNN
F 1 "470" V 2284 2750 50  0000 C CNN
F 2 "" V 2330 2750 50  0001 C CNN
F 3 "~" H 2400 2750 50  0001 C CNN
	1    2400 2750
	0    1    1    0   
$EndComp
$Comp
L pcb-rescue:C-Device C?
U 1 1 5CB0CA1E
P 2250 2900
F 0 "C?" H 2365 2946 50  0000 L CNN
F 1 "2.2n" H 2365 2855 50  0000 L CNN
F 2 "" H 2288 2750 50  0001 C CNN
F 3 "~" H 2250 2900 50  0001 C CNN
	1    2250 2900
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:R-Device R?
U 1 1 5CB0CB56
P 2700 3100
F 0 "R?" V 2493 3100 50  0000 C CNN
F 1 "470" V 2584 3100 50  0000 C CNN
F 2 "" V 2630 3100 50  0001 C CNN
F 3 "~" H 2700 3100 50  0001 C CNN
	1    2700 3100
	0    1    1    0   
$EndComp
$Comp
L pcb-rescue:C-Device C?
U 1 1 5CB0CBA8
P 2550 3250
F 0 "C?" H 2665 3296 50  0000 L CNN
F 1 "2.2n" H 2665 3205 50  0000 L CNN
F 2 "" H 2588 3100 50  0001 C CNN
F 3 "~" H 2550 3250 50  0001 C CNN
	1    2550 3250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CB0CBDC
P 2250 3050
F 0 "#PWR?" H 2250 2800 50  0001 C CNN
F 1 "GND" H 2255 2877 50  0000 C CNN
F 2 "" H 2250 3050 50  0001 C CNN
F 3 "" H 2250 3050 50  0001 C CNN
	1    2250 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CB0CBF5
P 2550 3400
F 0 "#PWR?" H 2550 3150 50  0001 C CNN
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
L pcb-rescue:C-Device C?
U 1 1 5CB0D1C2
P 3100 2700
F 0 "C?" H 3215 2746 50  0000 L CNN
F 1 "2.2u" H 3215 2655 50  0000 L CNN
F 2 "" H 3138 2550 50  0001 C CNN
F 3 "~" H 3100 2700 50  0001 C CNN
	1    3100 2700
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:C-Device C?
U 1 1 5CB0D208
P 3100 2350
F 0 "C?" H 3215 2396 50  0000 L CNN
F 1 "10u" H 3215 2305 50  0000 L CNN
F 2 "" H 3138 2200 50  0001 C CNN
F 3 "~" H 3100 2350 50  0001 C CNN
	1    3100 2350
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:C-Device C?
U 1 1 5CB0D238
P 3400 2350
F 0 "C?" H 3515 2396 50  0000 L CNN
F 1 "0.1u" H 3515 2305 50  0000 L CNN
F 2 "" H 3438 2200 50  0001 C CNN
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
L pcb-rescue:C-Device C?
U 1 1 5CB0E05A
P 3650 2650
F 0 "C?" H 3765 2696 50  0000 L CNN
F 1 "2.2u" H 3765 2605 50  0000 L CNN
F 2 "" H 3688 2500 50  0001 C CNN
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
L power:+3.3V #PWR?
U 1 1 5CB0EF1F
P 3500 2150
F 0 "#PWR?" H 3500 2000 50  0001 C CNN
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
L power:GND #PWR?
U 1 1 5CB0EF42
P 3400 2550
F 0 "#PWR?" H 3400 2300 50  0001 C CNN
F 1 "GND" H 3405 2377 50  0000 C CNN
F 2 "" H 3400 2550 50  0001 C CNN
F 3 "" H 3400 2550 50  0001 C CNN
	1    3400 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2900 4000 2900
$Comp
L pcb-rescue:C-Device C?
U 1 1 5CB0F338
P 5450 2250
F 0 "C?" H 5565 2296 50  0000 L CNN
F 1 "2.2u" H 5565 2205 50  0000 L CNN
F 2 "" H 5488 2100 50  0001 C CNN
F 3 "~" H 5450 2250 50  0001 C CNN
	1    5450 2250
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:C-Device C?
U 1 1 5CB0F3AE
P 5850 2250
F 0 "C?" H 5965 2296 50  0000 L CNN
F 1 "2.2u" H 5965 2205 50  0000 L CNN
F 2 "" H 5888 2100 50  0001 C CNN
F 3 "~" H 5850 2250 50  0001 C CNN
	1    5850 2250
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:C-Device C?
U 1 1 5CB0F3E4
P 5450 2600
F 0 "C?" H 5565 2646 50  0000 L CNN
F 1 "2.2u" H 5565 2555 50  0000 L CNN
F 2 "" H 5488 2450 50  0001 C CNN
F 3 "~" H 5450 2600 50  0001 C CNN
	1    5450 2600
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:C-Device C?
U 1 1 5CB0F42C
P 5850 2600
F 0 "C?" H 5965 2646 50  0000 L CNN
F 1 "2.2u" H 5965 2555 50  0000 L CNN
F 2 "" H 5888 2450 50  0001 C CNN
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
L power:GND #PWR?
U 1 1 5CB1164D
P 5850 2450
F 0 "#PWR?" H 5850 2200 50  0001 C CNN
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
L power:GND #PWR?
U 1 1 5CB13637
P 5450 2900
F 0 "#PWR?" H 5450 2650 50  0001 C CNN
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
L pcb-rescue:TL072-Amplifier_Operational U?
U 1 1 5CB17A70
P 5300 4450
F 0 "U?" H 5300 4817 50  0000 C CNN
F 1 "TL072" H 5300 4726 50  0000 C CNN
F 2 "" H 5300 4450 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 5300 4450 50  0001 C CNN
	1    5300 4450
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:TL072-Amplifier_Operational U?
U 2 1 5CB17B0F
P 5300 5950
F 0 "U?" H 5300 6317 50  0000 C CNN
F 1 "TL072" H 5300 6226 50  0000 C CNN
F 2 "" H 5300 5950 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 5300 5950 50  0001 C CNN
	2    5300 5950
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:TL072-Amplifier_Operational U?
U 3 1 5CB17BAB
P 6900 4450
F 0 "U?" H 6858 4496 50  0000 L CNN
F 1 "TL072" H 6858 4405 50  0000 L CNN
F 2 "" H 6900 4450 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/tl071.pdf" H 6900 4450 50  0001 C CNN
	3    6900 4450
	1    0    0    -1  
$EndComp
Text Label 4650 4350 2    50   ~ 0
DAC_OUT_L
$Comp
L pcb-rescue:R-Device R?
U 1 1 5CB17EF0
P 5300 4850
F 0 "R?" V 5093 4850 50  0000 C CNN
F 1 "4k" V 5184 4850 50  0000 C CNN
F 2 "" V 5230 4850 50  0001 C CNN
F 3 "~" H 5300 4850 50  0001 C CNN
	1    5300 4850
	0    1    1    0   
$EndComp
$Comp
L pcb-rescue:R-Device R?
U 1 1 5CB17F86
P 4850 5000
F 0 "R?" H 4780 4954 50  0000 R CNN
F 1 "1k" H 4780 5045 50  0000 R CNN
F 2 "" V 4780 5000 50  0001 C CNN
F 3 "~" H 4850 5000 50  0001 C CNN
	1    4850 5000
	-1   0    0    1   
$EndComp
Wire Wire Line
	5600 4450 5700 4450
Wire Wire Line
	5700 4450 5700 4850
Wire Wire Line
	5700 4850 5450 4850
Wire Wire Line
	5150 4850 4850 4850
Wire Wire Line
	4850 4850 4850 4550
Wire Wire Line
	4850 4550 5000 4550
Connection ~ 4850 4850
Wire Wire Line
	5000 4350 4650 4350
$Comp
L power:GND #PWR?
U 1 1 5CB1C173
P 4850 5150
F 0 "#PWR?" H 4850 4900 50  0001 C CNN
F 1 "GND" H 4855 4977 50  0000 C CNN
F 2 "" H 4850 5150 50  0001 C CNN
F 3 "" H 4850 5150 50  0001 C CNN
	1    4850 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 4450 5900 4450
Connection ~ 5700 4450
$Comp
L pcb-rescue:R-Device R?
U 1 1 5CB1D896
P 5300 6350
F 0 "R?" V 5093 6350 50  0000 C CNN
F 1 "4k" V 5184 6350 50  0000 C CNN
F 2 "" V 5230 6350 50  0001 C CNN
F 3 "~" H 5300 6350 50  0001 C CNN
	1    5300 6350
	0    1    1    0   
$EndComp
$Comp
L pcb-rescue:R-Device R?
U 1 1 5CB1D926
P 4850 6500
F 0 "R?" H 4780 6454 50  0000 R CNN
F 1 "1k" H 4780 6545 50  0000 R CNN
F 2 "" V 4780 6500 50  0001 C CNN
F 3 "~" H 4850 6500 50  0001 C CNN
	1    4850 6500
	-1   0    0    1   
$EndComp
Text Label 4650 5850 2    50   ~ 0
DAC_OUT_R
Wire Wire Line
	5000 5850 4650 5850
Wire Wire Line
	5000 6050 4850 6050
Wire Wire Line
	4850 6050 4850 6350
Wire Wire Line
	4850 6350 5150 6350
Connection ~ 4850 6350
Wire Wire Line
	5450 6350 5700 6350
Wire Wire Line
	5700 6350 5700 5950
Wire Wire Line
	5700 5950 5600 5950
$Comp
L power:GND #PWR?
U 1 1 5CB22C5C
P 4850 6650
F 0 "#PWR?" H 4850 6400 50  0001 C CNN
F 1 "GND" H 4855 6477 50  0000 C CNN
F 2 "" H 4850 6650 50  0001 C CNN
F 3 "" H 4850 6650 50  0001 C CNN
	1    4850 6650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 5950 5700 5950
Connection ~ 5700 5950
Text Label 5900 4450 0    50   ~ 0
OUT_L
Text Label 5900 5950 0    50   ~ 0
OUT_R
$Comp
L pcb-rescue:L78L12_SOT89-Regulator_Linear U?
U 1 1 5CB245C2
P 7950 1550
F 0 "U?" H 7950 1792 50  0000 C CNN
F 1 "L78L12_SOT89" H 7950 1701 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 7950 1750 50  0001 C CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/15/55/e5/aa/23/5b/43/fd/CD00000446.pdf/files/CD00000446.pdf/jcr:content/translations/en.CD00000446.pdf" H 7950 1500 50  0001 C CNN
	1    7950 1550
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:L79L12_SOT89-Regulator_Linear U?
U 1 1 5CB247DA
P 7950 2550
F 0 "U?" H 7950 2400 50  0000 C CNN
F 1 "L79L12_SOT89" H 7950 2309 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3" H 7950 2350 50  0001 C CIN
F 3 "http://www.farnell.com/datasheets/1827870.pdf" H 7950 2550 50  0001 C CNN
	1    7950 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 2250 7950 2000
$Comp
L power:GND #PWR?
U 1 1 5CB25F60
P 8100 2050
F 0 "#PWR?" H 8100 1800 50  0001 C CNN
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
L power:+12V #PWR?
U 1 1 5CB27901
P 8450 1550
F 0 "#PWR?" H 8450 1400 50  0001 C CNN
F 1 "+12V" V 8465 1678 50  0000 L CNN
F 2 "" H 8450 1550 50  0001 C CNN
F 3 "" H 8450 1550 50  0001 C CNN
	1    8450 1550
	0    1    1    0   
$EndComp
$Comp
L power:-12V #PWR?
U 1 1 5CB279B4
P 8450 2550
F 0 "#PWR?" H 8450 2650 50  0001 C CNN
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
L power:+15V #PWR?
U 1 1 5CB2AF29
P 7450 1550
F 0 "#PWR?" H 7450 1400 50  0001 C CNN
F 1 "+15V" V 7465 1678 50  0000 L CNN
F 2 "" H 7450 1550 50  0001 C CNN
F 3 "" H 7450 1550 50  0001 C CNN
	1    7450 1550
	0    -1   -1   0   
$EndComp
$Comp
L power:-15V #PWR?
U 1 1 5CB2B00C
P 7450 2550
F 0 "#PWR?" H 7450 2650 50  0001 C CNN
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
L power:+12V #PWR?
U 1 1 5CB2E88D
P 6800 4150
F 0 "#PWR?" H 6800 4000 50  0001 C CNN
F 1 "+12V" H 6815 4323 50  0000 C CNN
F 2 "" H 6800 4150 50  0001 C CNN
F 3 "" H 6800 4150 50  0001 C CNN
	1    6800 4150
	1    0    0    -1  
$EndComp
$Comp
L power:-12V #PWR?
U 1 1 5CB2E9A0
P 6800 4750
F 0 "#PWR?" H 6800 4850 50  0001 C CNN
F 1 "-12V" H 6815 4923 50  0000 C CNN
F 2 "" H 6800 4750 50  0001 C CNN
F 3 "" H 6800 4750 50  0001 C CNN
	1    6800 4750
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x03_Male J?
U 1 1 5CB2ECD1
P 10300 2000
F 0 "J?" H 10273 1930 50  0000 R CNN
F 1 "Conn_01x03_Male" H 10273 2021 50  0000 R CNN
F 2 "" H 10300 2000 50  0001 C CNN
F 3 "~" H 10300 2000 50  0001 C CNN
	1    10300 2000
	-1   0    0    1   
$EndComp
$EndSCHEMATC
