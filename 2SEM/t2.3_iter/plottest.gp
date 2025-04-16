set terminal pngcairo enhanced font 'Verdana,10'
set output 'data0.png'
set title 'Сходимость метода простой итерации'
set xlabel 'Итерация'
set ylabel 'Норма невязки'
set grid
plot 'data0.txt' with lines title 'Норма невязки'
exit
