set title "График функции exp(-x^2)"
set xlabel "X"
set ylabel "Y"
set xrange [-3:3]
set yrange [0:1]
set grid
set key top right
plot exp(- x * x) with lines lw 2 lc rgb "red" title "exp(-x^2)"
set terminal pngcairo size 800,600
set output "2.png"
replot
set output