<h1><b>Алгоритм шифрования - Магма</b></h1>



<h2>Использование:</h2>


```console
magma_algorithm [-h|--help - вызов описание команд
magma_algorithm [--ecb|--ctr|--ofb|--cbc|--cfb] {-e|-d} -k <key file> [operations] - вызов алгоритма в различных режимах
-e,d - шифрование/расшифрование
-k - файл с бинарным ключом
[operations] - опции в виде исходного/входного файла
 magma_algoritm --mac -k <key file> [operations] - вызов алгоритма в режиме mac
[operations]:
-i <input file> - входной файл
-o <output file> - выходной файл
```



<h2>Пример использования:</h2>



```console
magma_algorithm --ecb -e -i C:\Users\aliev\Desktop\input.txt -o C:\Users\aliev\Desktop\encode.txt -k C:\Users\aliev\Desktop\key.txt  (пример шифрования)
magma_algorithm --ecb -d -i C:\Users\aliev\Desktop\encode.txt -o C:\Users\aliev\Desktop\decode.txt -k C:\Users\aliev\Desktop\key.txt (пример расшифрования)
magma_algorithm --mac -k file.key -i file.in -o file.out
```

<h2>Приведены файлы, которые можно использовать для теста алгоритма:</h2><br>
-code.txt - текст, который мы хотим шифровать<br>
-encode.txt - зашифрованный текст<br>
-decode.txt - расшифрованный текст<br>
-key.txt - ключ
