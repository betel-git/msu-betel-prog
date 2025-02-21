set title "График функций sin(x) и cos(x)"
set xlabel "Ось X"
set ylabel "Ось Y"
set xrange [0:2*pi]
set yrange [-1:1]
set grid
set key top right
plot sin(x) with lines lw 2 lc rgb "blue" title "sin(x)", \
     cos(x) with lines lw 2 lc rgb "red" title "cos(x)"
set terminal pngcairo size 800,600
set output "graph.png"
replot
set output