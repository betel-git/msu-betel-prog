set title "График функции 1/ \sqrt(1 - x^2)"
set xlabel "X"
set ylabel "Y"
set xrange [-1.5:1.5]
set yrange [0:4]
set grid
set key top right
plot 1 / sqrt(1 - (x * x)) with lines lw 2 lc rgb "red" title "\frac{1}{\sqrt{1 - x^2}}"
set terminal pngcairo size 800,600
set output "6.png"
replot
set output