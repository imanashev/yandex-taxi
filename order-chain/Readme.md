**D. Заказы по цепочке**

 - Ограничение времени:	1 секунда
 - Ограничение памяти:	64Mb
 - Ввод:	стандартный ввод или input.txt
 - Вывод:	стандартный вывод или output.txt
 
Водитель выбирает заказы на день. Он может выбирать из 
N≤1000 заказов. Для каждого заказа известны время начала 
Ai и время окончания Bi, причём 0≤A<sub>i</sub><B<sub>i</sub>≤20000. Водитель также знает стоимость каждого заказа W<sub>i</sub>, причём 1≤W<sub>i</sub>≤10<sup>5</sup>. Нужно найти последовательность заказов с наибольшей суммарной стоимостью. В каждый момент времени водитель может выполнять только один заказ.

**Формат ввода**

В первой строчки задано целое положительное число N — количество заказов. Далее следует N строк. В i-й строке содержится 3 целых числа, разделённых пробелами: A<sub>i</sub>, B<sub>i</sub> и W<sub>i</sub>.

**Формат вывода**

Требуется вывести одно число — наибольший заработок водителя.

**Пример 1**
```
Ввод:       Вывод:	
2           10
0 1 2 
2 3 8
```
**Пример 2**
```
Ввод:	    Вывод:
3           40
1 3 15
3 7 25
2 6 30
```
