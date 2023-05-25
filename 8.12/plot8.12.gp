set term png
set out "8.12.png"
set title "Strom"
set ylabel "Ic in A"
set xlabel "Ib in A"
set grid
plot "8.12-5vV.txt" using 2:1 with lines title "5v", \
	 "8.12-4vV.txt" using 2:1 with lines title "4v", \
	 "8.12-3vV.txt" using 2:1 with lines title "3v", \
	 "8.12-2vV.txt" using 2:1 with lines title "2v"
	
