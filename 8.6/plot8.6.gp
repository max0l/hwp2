set term png
set out "8.6.png"
set title "Id = f(Ugs)"
set xlabel "Ugs in V"
set ylabel "Id in A"
set grid
plot "8.6-2vV.txt" using 2:1 with lines title "2v", \
	 "8.6-3vV.txt" using 2:1 with lines title "3v", \
	 "8.6-4vV.txt" using 2:1 with lines title "4v", \
	 "8.6-5vV.txt" using 2:1 with lines title "5v"
