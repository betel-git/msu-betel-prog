set title "График функции e^{-x} * sin{1000x}"
set xlabel "X"
set ylabel "Y"
set xrange [0:3]
set yrange [-1.5:1.5]
set grid
set key top right
plot exp(-x) * sin(1000 * x) with lines lw 2 lc rgb "red" title "e^{-x} * sin{1000x}"
set terminal pngcairo size 800,600
set output "7.png"
replot
set output