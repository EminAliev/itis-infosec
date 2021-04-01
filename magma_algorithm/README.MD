<h1><b>Алгоритм шифрования - Магма</b></h1>

<h2>Использование:</h2>
```console
magma_algorithm [-h|--help - вызов описание команд<br>
magma_algorithm [--ecb|--ctr|--ofb|--cbc|--cfb] {-e|-d} -k <key file> [operations] - вызов алгоритма в различных режимах, -e,d - шифрование/расшифрование, -k - файл с бинарным ключом, [operations] - опции в виде исходного/входного файла.<br>
 magma_algoritm --mac -k <key file> [operations] - вызов алгоритма в режиме mac
[operations]:<br>
-i <input file> - входной файл<br>
-o <output file> - выходной файл
```


<h2>Пример использования:</h2>
```console
magma_algorithm --ecb -e -i C:\Users\aliev\Desktop\input.txt -o C:\Users\aliev\Desktop\encode.txt -k C:\Users\aliev\Desktop\key.txt(пример шифрования)<br>
magma_algorithm --ecb -d -i C:\Users\aliev\Desktop\encode.txt -o C:\Users\aliev\Desktop\decode.txt -k C:\Users\aliev\Desktop\key.txt(пример расшифрования)<br>
magma_algorithm --mac -k file.key -i file.in -o file.out
```
