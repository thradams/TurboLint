# C language extensions

Operator new, delete and destroy.

## Operator new

Syntaxe:

```cpp
Type *p = new (Type) {0};
```

The code above is equivalent of:

```cpp
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

```cpp
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
Destroy will can an special function defined with "destroy". 
(I am not sure about the best position of this function modifier - but the idea is the use the same keyword destroy in two contexts)

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
 
 
