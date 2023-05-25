set term png
set out "8.4.png"
set title "Kennlinie Id"
set xlabel "Spannung an AE0 in Volt"
set ylabel "Id in Ampere"
set grid
plot "8.4-5vV.txt" using 2:1 with lines title "5V", \
	 "8.4-4vV.txt" using 2:1 with lines title "4V", \
	 "8.4-3vV.txt" using 2:1 with lines title "3V", \
	 "8.4-2.5vV.txt" using 2:1 with lines title "2.5V", \
	 "8.4-2vV.txt" using 2:1 with lines title "2V", \
	 "8.4-1vV.txt" using 2:1 with lines title "1V", \
	 "8.4-0vV.txt" using 2:1 with lines title "0V", \
	
