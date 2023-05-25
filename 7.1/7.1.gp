set term png
set out "7.1.png"
set title "LED Kennlinie"
set ylabel "Spannung gemessen in V"
set xlabel "Spannung ausgegeben in V"
set grid
plot "7.1.txt" using 2:1 with lines title "Spannung in V"
	 
