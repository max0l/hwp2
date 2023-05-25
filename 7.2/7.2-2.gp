set term png
set out "7.2.png"
set title "LED"
set xlabel "Spannung über die LED gemessen in V"
set ylabel "Strom in mA und Spannung in V"
set grid
plot "7.2.txt" using 2:1 with lines title "Strom", \
	"7.1.txt" using 2:1 with lines title "Spannung"
	 
