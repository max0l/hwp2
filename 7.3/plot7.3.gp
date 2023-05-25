set term png
set out "7.3.png"
set title "Dioden Spannung in Flussrichtung"
set ylabel "Strom in A"
set xlabel "Spannung gemessen in V"
set grid
plot "7.3 d1.txt" using 2:1 with lines title "D1",\
	 "7.3 d2.txt" using 2:1 with lines title "D2",\
	 "7.3 d3.txt" using 2:1 with lines title "D3",\
	 "7.3 d4.txt" using 2:1 with lines title "D4",\
	 "7.3 d5.txt" using 2:1 with lines title "D5",\
	 "7.3 d6.txt" using 2:1 with lines title "D6"
	 
	 
