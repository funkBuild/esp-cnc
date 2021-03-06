EESchema Schematic File Version 4
LIBS:pcb-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L pcb-rescue:74HC595-74xx U?
U 1 1 5CAC3687
P 1700 4700
AR Path="/5CAC3687" Ref="U?"  Part="1" 
AR Path="/5CAC35BA/5CAC3687" Ref="U?"  Part="1" 
F 0 "U?" H 1300 5450 50  0000 C CNN
F 1 "74HC595" H 1400 5350 50  0000 C CNN
F 2 "" H 1700 4700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 1700 4700 50  0001 C CNN
	1    1700 4700
	1    0    0    -1  
$EndComp
Text HLabel 1100 4500 0    50   Input ~ 0
BCK
Text HLabel 1100 4800 0    50   Input ~ 0
WS
Text HLabel 1100 4300 0    50   Input ~ 0
DATA
Wire Wire Line
	1300 4300 1100 4300
Wire Wire Line
	1300 4500 1100 4500
Wire Wire Line
	1300 4800 1100 4800
$Comp
L pcb-rescue:74HC595-74xx U?
U 1 1 5CAC376A
P 3450 4700
AR Path="/5CAC376A" Ref="U?"  Part="1" 
AR Path="/5CAC35BA/5CAC376A" Ref="U?"  Part="1" 
F 0 "U?" H 3050 5450 50  0000 C CNN
F 1 "74HC595" H 3150 5350 50  0000 C CNN
F 2 "" H 3450 4700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 3450 4700 50  0001 C CNN
	1    3450 4700
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:74HC595-74xx U?
U 1 1 5CAC3794
P 5300 4700
AR Path="/5CAC3794" Ref="U?"  Part="1" 
AR Path="/5CAC35BA/5CAC3794" Ref="U?"  Part="1" 
F 0 "U?" H 4900 5450 50  0000 C CNN
F 1 "74HC595" H 5000 5350 50  0000 C CNN
F 2 "" H 5300 4700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 5300 4700 50  0001 C CNN
	1    5300 4700
	1    0    0    -1  
$EndComp
$Comp
L pcb-rescue:74HC595-74xx U?
U 1 1 5CAC37E2
P 7200 4700
AR Path="/5CAC37E2" Ref="U?"  Part="1" 
AR Path="/5CAC35BA/5CAC37E2" Ref="U?"  Part="1" 
F 0 "U?" H 6800 5450 50  0000 C CNN
F 1 "74HC595" H 6900 5350 50  0000 C CNN
F 2 "" H 7200 4700 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 7200 4700 50  0001 C CNN
	1    7200 4700
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CAC3856
P 1700 4100
F 0 "#PWR?" H 1700 3950 50  0001 C CNN
F 1 "+3.3V" H 1715 4273 50  0000 C CNN
F 2 "" H 1700 4100 50  0001 C CNN
F 3 "" H 1700 4100 50  0001 C CNN
	1    1700 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CAC3890
P 3450 4100
F 0 "#PWR?" H 3450 3950 50  0001 C CNN
F 1 "+3.3V" H 3465 4273 50  0000 C CNN
F 2 "" H 3450 4100 50  0001 C CNN
F 3 "" H 3450 4100 50  0001 C CNN
	1    3450 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CAC38BF
P 5300 4100
F 0 "#PWR?" H 5300 3950 50  0001 C CNN
F 1 "+3.3V" H 5315 4273 50  0000 C CNN
F 2 "" H 5300 4100 50  0001 C CNN
F 3 "" H 5300 4100 50  0001 C CNN
	1    5300 4100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CAC38E2
P 7200 4100
F 0 "#PWR?" H 7200 3950 50  0001 C CNN
F 1 "+3.3V" H 7215 4273 50  0000 C CNN
F 2 "" H 7200 4100 50  0001 C CNN
F 3 "" H 7200 4100 50  0001 C CNN
	1    7200 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CAC3964
P 1700 5400
F 0 "#PWR?" H 1700 5150 50  0001 C CNN
F 1 "GND" H 1705 5227 50  0000 C CNN
F 2 "" H 1700 5400 50  0001 C CNN
F 3 "" H 1700 5400 50  0001 C CNN
	1    1700 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CAC397E
P 3450 5400
F 0 "#PWR?" H 3450 5150 50  0001 C CNN
F 1 "GND" H 3455 5227 50  0000 C CNN
F 2 "" H 3450 5400 50  0001 C CNN
F 3 "" H 3450 5400 50  0001 C CNN
	1    3450 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CAC39B5
P 5300 5400
F 0 "#PWR?" H 5300 5150 50  0001 C CNN
F 1 "GND" H 5300 5250 50  0000 C CNN
F 2 "" H 5300 5400 50  0001 C CNN
F 3 "" H 5300 5400 50  0001 C CNN
	1    5300 5400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CAC39F8
P 7200 5400
F 0 "#PWR?" H 7200 5150 50  0001 C CNN
F 1 "GND" H 7205 5227 50  0000 C CNN
F 2 "" H 7200 5400 50  0001 C CNN
F 3 "" H 7200 5400 50  0001 C CNN
	1    7200 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CAC3AE7
P 1050 4600
F 0 "#PWR?" H 1050 4450 50  0001 C CNN
F 1 "+3.3V" V 1065 4728 50  0000 L CNN
F 2 "" H 1050 4600 50  0001 C CNN
F 3 "" H 1050 4600 50  0001 C CNN
	1    1050 4600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1300 4600 1050 4600
$Comp
L power:GND #PWR?
U 1 1 5CAC3B5D
P 1150 5000
F 0 "#PWR?" H 1150 4750 50  0001 C CNN
F 1 "GND" H 1155 4827 50  0000 C CNN
F 2 "" H 1150 5000 50  0001 C CNN
F 3 "" H 1150 5000 50  0001 C CNN
	1    1150 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4900 1150 4900
Wire Wire Line
	1150 4900 1150 5000
Wire Wire Line
	2100 5200 2500 5200
Wire Wire Line
	2500 5200 2500 4300
Wire Wire Line
	2500 4300 3050 4300
Text HLabel 2850 4500 0    50   Input ~ 0
BCK
Text HLabel 2850 4800 0    50   Input ~ 0
WS
Wire Wire Line
	3050 4500 2850 4500
Wire Wire Line
	3050 4800 2850 4800
$Comp
L power:GND #PWR?
U 1 1 5CAC3CFB
P 2900 5000
F 0 "#PWR?" H 2900 4750 50  0001 C CNN
F 1 "GND" H 2905 4827 50  0000 C CNN
F 2 "" H 2900 5000 50  0001 C CNN
F 3 "" H 2900 5000 50  0001 C CNN
	1    2900 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 5000 2900 4900
Wire Wire Line
	2900 4900 3050 4900
$Comp
L power:GND #PWR?
U 1 1 5CAC3DAF
P 4700 5000
F 0 "#PWR?" H 4700 4750 50  0001 C CNN
F 1 "GND" H 4705 4827 50  0000 C CNN
F 2 "" H 4700 5000 50  0001 C CNN
F 3 "" H 4700 5000 50  0001 C CNN
	1    4700 5000
	1    0    0    -1  
$EndComp
Text HLabel 4600 4800 0    50   Input ~ 0
WS
Text HLabel 4600 4500 0    50   Input ~ 0
BCK
Wire Wire Line
	4900 4300 4300 4300
Wire Wire Line
	4300 4300 4300 5200
Wire Wire Line
	4300 5200 3850 5200
Wire Wire Line
	4600 4500 4900 4500
Wire Wire Line
	4900 4800 4600 4800
Wire Wire Line
	4900 4900 4700 4900
Wire Wire Line
	4700 4900 4700 5000
Text HLabel 6550 4500 0    50   Input ~ 0
BCK
Text HLabel 6550 4800 0    50   Input ~ 0
WS
$Comp
L power:GND #PWR?
U 1 1 5CAC42DE
P 6550 5000
F 0 "#PWR?" H 6550 4750 50  0001 C CNN
F 1 "GND" H 6555 4827 50  0000 C CNN
F 2 "" H 6550 5000 50  0001 C CNN
F 3 "" H 6550 5000 50  0001 C CNN
	1    6550 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 4900 6550 4900
Wire Wire Line
	6550 4900 6550 5000
Wire Wire Line
	6800 4800 6550 4800
Wire Wire Line
	6800 4500 6550 4500
Wire Wire Line
	5700 5200 6250 5200
Wire Wire Line
	6250 5200 6250 4300
Wire Wire Line
	6250 4300 6800 4300
$Comp
L power:+3.3V #PWR?
U 1 1 5CAC59F9
P 2900 4600
F 0 "#PWR?" H 2900 4450 50  0001 C CNN
F 1 "+3.3V" V 2915 4728 50  0000 L CNN
F 2 "" H 2900 4600 50  0001 C CNN
F 3 "" H 2900 4600 50  0001 C CNN
	1    2900 4600
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CAC5A0C
P 4700 4600
F 0 "#PWR?" H 4700 4450 50  0001 C CNN
F 1 "+3.3V" V 4715 4728 50  0000 L CNN
F 2 "" H 4700 4600 50  0001 C CNN
F 3 "" H 4700 4600 50  0001 C CNN
	1    4700 4600
	0    -1   -1   0   
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5CAC5A3B
P 6650 4600
F 0 "#PWR?" H 6650 4450 50  0001 C CNN
F 1 "+3.3V" V 6665 4728 50  0000 L CNN
F 2 "" H 6650 4600 50  0001 C CNN
F 3 "" H 6650 4600 50  0001 C CNN
	1    6650 4600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3050 4600 2900 4600
Wire Wire Line
	4900 4600 4700 4600
Wire Wire Line
	6800 4600 6650 4600
Entry Wire Line
	2200 4300 2300 4400
Entry Wire Line
	2200 4400 2300 4500
Entry Wire Line
	2200 4500 2300 4600
Entry Wire Line
	2200 4600 2300 4700
Entry Wire Line
	2200 4700 2300 4800
Entry Wire Line
	2200 4800 2300 4900
Entry Wire Line
	2200 4900 2300 5000
Entry Wire Line
	2200 5000 2300 5100
Wire Wire Line
	2200 4300 2100 4300
Wire Wire Line
	2200 4400 2100 4400
Wire Wire Line
	2200 4500 2100 4500
Wire Wire Line
	2200 4600 2100 4600
Wire Wire Line
	2200 4700 2100 4700
Wire Wire Line
	2200 4800 2100 4800
Wire Wire Line
	2200 4900 2100 4900
Wire Wire Line
	2200 5000 2100 5000
Text Label 2200 4300 2    50   ~ 0
D0
Text Label 2200 4400 2    50   ~ 0
D1
Text Label 2200 4500 2    50   ~ 0
D2
Text Label 2200 4600 2    50   ~ 0
D3
Text Label 2200 4700 2    50   ~ 0
D4
Text Label 2200 4800 2    50   ~ 0
D5
Text Label 2200 4900 2    50   ~ 0
D6
Text Label 2200 5000 2    50   ~ 0
D7
Entry Wire Line
	3950 4300 4050 4400
Entry Wire Line
	3950 4400 4050 4500
Entry Wire Line
	3950 4500 4050 4600
Entry Wire Line
	3950 4600 4050 4700
Entry Wire Line
	3950 4700 4050 4800
Entry Wire Line
	3950 4800 4050 4900
Entry Wire Line
	3950 4900 4050 5000
Entry Wire Line
	3950 5000 4050 5100
Wire Wire Line
	3950 4300 3850 4300
Wire Wire Line
	3950 4400 3850 4400
Wire Wire Line
	3950 4500 3850 4500
Wire Wire Line
	3950 4600 3850 4600
Wire Wire Line
	3950 4700 3850 4700
Wire Wire Line
	3950 4800 3850 4800
Wire Wire Line
	3950 4900 3850 4900
Wire Wire Line
	3950 5000 3850 5000
Text Label 3950 4300 2    50   ~ 0
D8
Text Label 3950 4400 2    50   ~ 0
D9
Text Label 3950 4500 2    50   ~ 0
D10
Text Label 3950 4600 2    50   ~ 0
D11
Text Label 3950 4700 2    50   ~ 0
D12
Text Label 3950 4800 2    50   ~ 0
D13
Text Label 3950 4900 2    50   ~ 0
D14
Text Label 3950 5000 2    50   ~ 0
D15
$Comp
L Connector:Conn_01x08_Male J?
U 1 1 5CAD04DB
P 3000 2900
F 0 "J?" V 2835 2827 50  0000 C CNN
F 1 "Conn_01x08_Male" V 2926 2827 50  0000 C CNN
F 2 "" H 3000 2900 50  0001 C CNN
F 3 "~" H 3000 2900 50  0001 C CNN
	1    3000 2900
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_01x08_Male J?
U 1 1 5CAD0553
P 4100 2900
F 0 "J?" V 3935 2827 50  0000 C CNN
F 1 "Conn_01x08_Male" V 4026 2827 50  0000 C CNN
F 2 "" H 4100 2900 50  0001 C CNN
F 3 "~" H 4100 2900 50  0001 C CNN
	1    4100 2900
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_01x08_Male J?
U 1 1 5CAD058B
P 5250 2900
F 0 "J?" V 5085 2827 50  0000 C CNN
F 1 "Conn_01x08_Male" V 5176 2827 50  0000 C CNN
F 2 "" H 5250 2900 50  0001 C CNN
F 3 "~" H 5250 2900 50  0001 C CNN
	1    5250 2900
	0    -1   1    0   
$EndComp
$Comp
L Connector:Conn_01x08_Male J?
U 1 1 5CAD05EB
P 6300 2900
F 0 "J?" V 6135 2827 50  0000 C CNN
F 1 "Conn_01x08_Male" V 6226 2827 50  0000 C CNN
F 2 "" H 6300 2900 50  0001 C CNN
F 3 "~" H 6300 2900 50  0001 C CNN
	1    6300 2900
	0    -1   1    0   
$EndComp
Entry Wire Line
	2700 3350 2800 3450
Entry Wire Line
	2800 3350 2900 3450
Entry Wire Line
	2900 3350 3000 3450
Entry Wire Line
	3000 3350 3100 3450
Entry Wire Line
	3100 3350 3200 3450
Entry Wire Line
	3200 3350 3300 3450
Entry Wire Line
	3300 3350 3400 3450
Entry Wire Line
	3400 3350 3500 3450
Wire Wire Line
	3400 3350 3400 3100
Wire Wire Line
	3300 3100 3300 3350
Wire Wire Line
	3200 3350 3200 3100
Wire Wire Line
	3100 3100 3100 3350
Wire Wire Line
	3000 3350 3000 3100
Wire Wire Line
	2900 3100 2900 3350
Wire Wire Line
	2800 3350 2800 3100
Wire Wire Line
	2700 3100 2700 3350
Text Label 2700 3350 1    50   ~ 0
D0
Text Label 2800 3350 1    50   ~ 0
D1
Text Label 2900 3350 1    50   ~ 0
D2
Text Label 3000 3350 1    50   ~ 0
D3
Text Label 3100 3350 1    50   ~ 0
D4
Text Label 3200 3350 1    50   ~ 0
D5
Text Label 3300 3350 1    50   ~ 0
D6
Text Label 3400 3350 1    50   ~ 0
D7
Entry Wire Line
	3800 3350 3900 3450
Entry Wire Line
	3900 3350 4000 3450
Entry Wire Line
	4000 3350 4100 3450
Entry Wire Line
	4100 3350 4200 3450
Entry Wire Line
	4200 3350 4300 3450
Entry Wire Line
	4300 3350 4400 3450
Entry Wire Line
	4400 3350 4500 3450
Entry Wire Line
	4500 3350 4600 3450
Wire Wire Line
	3800 3350 3800 3100
Wire Wire Line
	3900 3100 3900 3350
Wire Wire Line
	4000 3350 4000 3100
Wire Wire Line
	4100 3100 4100 3350
Wire Wire Line
	4200 3350 4200 3100
Wire Wire Line
	4300 3100 4300 3350
Wire Wire Line
	4400 3350 4400 3100
Wire Wire Line
	4500 3100 4500 3350
Text Label 3800 3350 1    50   ~ 0
D8
Text Label 3900 3350 1    50   ~ 0
D9
Text Label 4000 3350 1    50   ~ 0
D10
Text Label 4100 3350 1    50   ~ 0
D11
Text Label 4200 3350 1    50   ~ 0
D12
Text Label 4300 3350 1    50   ~ 0
D13
Text Label 4400 3350 1    50   ~ 0
D14
Text Label 4500 3350 1    50   ~ 0
D15
Connection ~ 4050 3450
Connection ~ 6000 3450
Entry Wire Line
	5900 4300 6000 4400
Entry Wire Line
	5900 4400 6000 4500
Entry Wire Line
	5900 4500 6000 4600
Entry Wire Line
	5900 4600 6000 4700
Entry Wire Line
	5900 4700 6000 4800
Entry Wire Line
	5900 4800 6000 4900
Entry Wire Line
	5900 4900 6000 5000
Entry Wire Line
	5900 5000 6000 5100
Wire Wire Line
	5900 4300 5700 4300
Wire Wire Line
	5900 4400 5700 4400
Wire Wire Line
	5900 4500 5700 4500
Wire Wire Line
	5900 4600 5700 4600
Wire Wire Line
	5900 4700 5700 4700
Wire Wire Line
	5900 4800 5700 4800
Wire Wire Line
	5900 4900 5700 4900
Wire Wire Line
	5900 5000 5700 5000
Text Label 5900 4300 2    50   ~ 0
D16
Text Label 5900 4400 2    50   ~ 0
D17
Text Label 5900 4500 2    50   ~ 0
D18
Text Label 5900 4600 2    50   ~ 0
D19
Text Label 5900 4700 2    50   ~ 0
D20
Text Label 5900 4800 2    50   ~ 0
D21
Text Label 5900 4900 2    50   ~ 0
D22
Text Label 5900 5000 2    50   ~ 0
D23
Entry Wire Line
	7800 4300 7900 4400
Entry Wire Line
	7800 4400 7900 4500
Entry Wire Line
	7800 4500 7900 4600
Entry Wire Line
	7800 4600 7900 4700
Entry Wire Line
	7800 4700 7900 4800
Entry Wire Line
	7800 4800 7900 4900
Entry Wire Line
	7800 4900 7900 5000
Entry Wire Line
	7800 5000 7900 5100
Wire Wire Line
	7800 4300 7600 4300
Wire Wire Line
	7600 4400 7800 4400
Wire Wire Line
	7800 4500 7600 4500
Wire Wire Line
	7800 4600 7600 4600
Wire Wire Line
	7800 4700 7600 4700
Wire Wire Line
	7800 4800 7600 4800
Wire Wire Line
	7800 4900 7600 4900
Wire Wire Line
	7800 5000 7600 5000
NoConn ~ 7600 5200
Text Label 7800 4300 2    50   ~ 0
D24
Text Label 7800 4400 2    50   ~ 0
D25
Text Label 7800 4500 2    50   ~ 0
D26
Text Label 7800 4600 2    50   ~ 0
D27
Text Label 7800 4700 2    50   ~ 0
D28
Text Label 7800 4800 2    50   ~ 0
D29
Text Label 7800 4900 2    50   ~ 0
D30
Text Label 7800 5000 2    50   ~ 0
D31
Entry Wire Line
	4950 3350 5050 3450
Entry Wire Line
	5050 3350 5150 3450
Entry Wire Line
	5150 3350 5250 3450
Entry Wire Line
	5250 3350 5350 3450
Entry Wire Line
	5350 3350 5450 3450
Entry Wire Line
	5450 3350 5550 3450
Entry Wire Line
	5550 3350 5650 3450
Entry Wire Line
	5650 3350 5750 3450
Entry Wire Line
	6000 3350 6100 3450
Entry Wire Line
	6100 3350 6200 3450
Entry Wire Line
	6200 3350 6300 3450
Entry Wire Line
	6300 3350 6400 3450
Entry Wire Line
	6400 3350 6500 3450
Entry Wire Line
	6500 3350 6600 3450
Entry Wire Line
	6600 3350 6700 3450
Entry Wire Line
	6700 3350 6800 3450
Wire Wire Line
	6700 3350 6700 3100
Wire Wire Line
	6600 3100 6600 3350
Wire Wire Line
	6500 3350 6500 3100
Wire Wire Line
	6400 3100 6400 3350
Wire Wire Line
	6300 3350 6300 3100
Wire Wire Line
	6200 3100 6200 3350
Wire Wire Line
	6100 3350 6100 3100
Wire Wire Line
	6000 3100 6000 3350
Wire Wire Line
	5650 3100 5650 3350
Wire Wire Line
	5550 3350 5550 3100
Wire Wire Line
	5450 3100 5450 3350
Wire Wire Line
	5350 3350 5350 3100
Wire Wire Line
	5250 3100 5250 3350
Wire Wire Line
	5150 3350 5150 3100
Wire Wire Line
	5050 3100 5050 3350
Wire Wire Line
	4950 3350 4950 3100
Text Label 4950 3350 1    50   ~ 0
D16
Text Label 5050 3350 1    50   ~ 0
D17
Text Label 5150 3350 1    50   ~ 0
D18
Text Label 5250 3350 1    50   ~ 0
D19
Text Label 5350 3350 1    50   ~ 0
D20
Text Label 5450 3350 1    50   ~ 0
D21
Text Label 5550 3350 1    50   ~ 0
D22
Text Label 5650 3350 1    50   ~ 0
D23
Text Label 6000 3350 1    50   ~ 0
D24
Text Label 6100 3350 1    50   ~ 0
D25
Text Label 6200 3350 1    50   ~ 0
D26
Text Label 6300 3350 1    50   ~ 0
D27
Text Label 6400 3350 1    50   ~ 0
D28
Text Label 6500 3350 1    50   ~ 0
D29
Text Label 6600 3350 1    50   ~ 0
D30
Text Label 6700 3350 1    50   ~ 0
D31
Wire Bus Line
	6000 3450 7900 3450
Wire Bus Line
	7900 3450 7900 5100
Wire Bus Line
	6000 3450 6000 5100
Wire Bus Line
	2300 3450 2300 5100
Wire Bus Line
	4050 3450 4050 5100
Wire Bus Line
	2300 3450 4050 3450
Wire Bus Line
	4050 3450 6000 3450
$EndSCHEMATC
