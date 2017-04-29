# C language extensions

```cpp

 typedef struct   {
 int x = 1;
 int y = 2;
} Point;

Point* new PointAllocate()
{
  return *malloc(sizeof (Point))
}

void delete PointDeallocate(Point* p)
{
   free(p);
}

void destroy PointPtr_Destroy(Point** p)
{
}

void destroy Point_Destroy(Point* p)
{
  
}

  int main()
{
 /*auto*/ Point p = {};
 /*auto*/Point* p2 = new (Point){};
 //p.~Point();
 destroy p2;
 delete p2;
}


//~p;
```


