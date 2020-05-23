Сетевой сервер для работы с таблицами фиксированного формата вида: id - value
id должен иметь тип uint
value должен иметь тип string


## Список поддерживаемых команд и их формат:

1) INSERT table_name id value;
2) TRUNCATE table_name;
3) INTERSECTION left_tale_name right_table_name;
4) SYMMETRIC_DIFFERENCE left_tale_name right_table_name;

При вводе синтаксически неверной команды или команды с ошибочными
данными пользователю возвращается описание возникшей ошибки. 

## Аргументы командной строки:
```bash
--help		Подсказка о возможных аргументах
--port		Номер прослушиваемого сервером порта
```

**Примеры**: 

`join_server_--port 12345`
`INSERT_A 0 hello_world;`
`TRUNCATE_A;`
`INTERSECTION_A B;`
`SYMMETRIC_DIFFERENCE_A B;`
