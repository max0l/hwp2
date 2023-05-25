set term png
set out "7.5.png"
set title "Dioden Spannung in Sperrrichtung"
set ylabel "Strom in A"
set xlabel "Spannung über Diode gemessen in V"
set grid
plot "7.5.txt" using 1:2 with lines title "Zehnerdiode D6",
	 
