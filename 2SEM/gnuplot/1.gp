set title "График функции sin(1000x)"
set xlabel "X"
set ylabel "Y"
set xrange [0:0.05]
set yrange [-1:1]
set grid
set key top right
plot sin(1000 * x) with lines lw 2 lc rgb "red" title "sin(1000x)"
set terminal pngcairo size 800,600
set output "1.png"
replot
set output