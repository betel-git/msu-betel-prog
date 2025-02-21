set title "График функции sinx + sin10x + sin100x"
set xlabel "X"
set ylabel "Y"
set xrange [0:3]
set yrange [-1.5:3]
set grid
set key top right
plot sin(x) + sin(10 * x) + sin(100 * x) with lines lw 2 lc rgb "red" title "sinx + sin10x + sin100x"
set terminal pngcairo size 800,600
set output "4.png"
replot
set output