Сетевой сервер для работы с таблицами фиксированного формата вида: id - value. Id должен иметь тип uint,
value должен иметь тип string.


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

```bash
join_server --port 12345
INSERT A 0 hello_world;
TRUNCATE A;
INTERSECTION A B;
SYMMETRIC_DIFFERENCE A B;
```
