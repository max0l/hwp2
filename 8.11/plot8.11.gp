set term png
set out "8.6.png"
set title "Ib"
set xlabel "Ugs in V"
set ylabel "Strom Id in A"
set grid
plot "8.11-0vV.txt" using 2:1 with lines title "0V", \
	 "8.11-1vV.txt" using 2:1 with lines title "1V", \
	 "8.11-2vV.txt" using 2:1 with lines title "2V", \
	 "8.11-2.5vV.txt" using 2:1 with lines title "2.5V", \
	 "8.11-3vV.txt" using 2:1 with lines title "3V", \
	 "8.11-4vV.txt" using 2:1 with lines title "4V", \
	 "8.11-5vV.txt" using 2:1 with lines title "5V"
