set title "График функции sinx + 0.01 * sin1000x"
set xlabel "X"
set ylabel "Y"
set xrange [0:3]
set yrange [0:1]
set grid
set key top right
set samples 1000
plot sin(x) + 0.01 * sin(1000 * x) with lines lw 1 lc rgb "red" title "sinx + 0.01 * sin1000x"
set terminal pngcairo size 800,600
set output "5.png"
replot
set output