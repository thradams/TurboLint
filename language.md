# C language extensions

## initializers

```c
struct Point
{
   int x = 0;
};

Point pt = {};
```

## new expression


```c

Point* p = new (Point){};
Point* p = new (Point){.x=2};

```

## delete
```c

Point* p = new (Point){};
delete p;
```


## destroy

```c
struct Line
{
  Point^ p;
}

Line line;

destroy line;
```

## custon destroy

```c
void operator destroy(Type * p)
{
}

```

