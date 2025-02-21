set title "График функции th100x"
set xlabel "X"
set ylabel "Y"
set xrange [0:0.2]
set yrange [0:1.1]
set grid
set key top right
plot tanh(100 * x) with lines lw 2 lc rgb "red" title "th100x"
set terminal pngcairo size 800,600
set output "3.png"
replot
set output