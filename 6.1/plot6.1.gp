set term png
set out "6.1.png"
set title "Widerstand/Spannungs verhalten"
set ylabel "Gemessen an AE0"
set xlabel "Spannung ausgegeben"
set grid
plot "6.1.txt" using 2:1 with lines title "Resistor 1k Ohm"
