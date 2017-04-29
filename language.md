# C language extensions

Operator new, delete and destroy.

## Operator new

Syntaxe:

```cpp
Type *p = new (Type) {0};
```

The code above is equivalent of:

```c
//Equivalent code in C
Type* Type_OperatorNew()
{
  Type* p = malloc (sizeof (Type));
  if (p)
  {
    *p = (Type){0};
   }
  return p;
 } 
 
 Type *p = Type_OperatorNew();
```

Let´s say I want my custon allocator for Type

```cpp

Type* new TypeAllocator()
{
  return malloc(sizeof Type);
}
```
This especial function will be called if present: (default is malloc)

```c
//Equivalent code in C
Type* Type_OperatorNew()
{
  Type* p = TypeAllocator();
  if (p)
  {
    *p = (Type){0};
   }
  return p;
 } 
 
 Type *p = Type_OperatorNew();
```

## Operator destroy

Syntaxe:

```cpp
Type p;
destroy p;
```
Destroy will call an special function defined with "destroy". 
If no function is defined there is no effect.


```cpp
void destroy Type_OperatorDestroy(Type* p)
{
  //...
 }   
 
 Type p;
 Type_OperatorDestroy(&p);

```

## Operator delete

Syntaxe:

```cpp
Type *p = ...
delete p;
```

The code above is equivalent of:

```cpp

Type *p = ...

destroy p; free(p);
```
Let´s say you have used your custon allocator for new:
Now you can define the deallocator

```cpp
void delete Type_Deallocator(Type* p)
{
  free(p);
} 
```
 
 
Obs:
I tried to use the same keyword (whaterer it is) to define the operator and 
the especial function modifiers. But i am not sure the best position to put for "especial" functions.

