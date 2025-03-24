set terminal pngcairo size 3840,2160 enhanced font 'Verdana,20'
set output 'output.png'

set title "Графики по точкам и функция"

set xlabel "X"
set ylabel "Y"

set grid

plot \
  'out1.txt' with lines title 'Интерполяционный многочлен Лагранжа', \
  'out2.txt' with lines title 'Кусочно-линейная интерполяция', \
  'out3.txt' with lines title 'Кусочно-квадратичная интерполяция', \
  'out4.txt' with lines title 'Эрмитова интерполяция', \
  'out5.txt' with lines title 'Наилучшее среднеквадратическое приближение линейной функции', \
  'input.txt' with lines title 'Изначальный набор', \
  x**3 + 3 * x**2 + 3 * x + 3 with lines title 'f(x) = x^3 + 3x^2 + 3x + 3'