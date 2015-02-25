#!/usr/bin/gnuplot
reset
set terminal png
set output "plot_data.png"
set xtic auto # set xtics automatically
set ytic auto # set ytics automatically
set grid
plot "data-sinus.data" using 1:44100 title 'Briandais Tree' with linespoints