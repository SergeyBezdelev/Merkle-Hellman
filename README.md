алгоритм Меркла-Хеллмана:
Генерируем 2 ключа:
Первый приватный ключ (супервозрастающая последовательность целых чисел, где каждый последующий элемент больше суммы предыдущих).
Далее мы должны выбрать 2 числа q - должно быть больше суммы последовательности и r - взаимно простое к q.
Второй ключ будет публичным (r*w(элемент последовательности) mod q)
Для шифрования:
1) переводим сообщение в байткод
2) делим на блоки, размером равным с размером последовательности ключа
3) перебираем блок сообщения, если встречается 1, смотрим какое число в публичном ключе стоит на этой позиции и делаем sum += это число
Для расшифровки:
1) переводим сообщение в байткод
2) делим на блоки, размером равным с размером последовательности ключа
3) находим обратное число для r по модулю q
4) берем элемент зашифрованного сообщения c * обратное r mod q
5) ищем самый большой элемент в твоем приватном ключе и вычитаем его и продолжаем так пока не дойдем до конца, потом те элементы которые мы вычитали подставляем 1, которые не вычитал 0
