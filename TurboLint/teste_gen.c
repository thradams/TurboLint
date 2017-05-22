/*external files*/

 typedef struct Point {
 int x /* = 1 */;
 int y /* = 1 */;
} Point;

 typedef struct Line {
 Point pt;
 Point* pt2;
} Line;

 typedef union s {
 Point;
 Line;
};

 int main()
{
 Line line = {{1,1},NULL};
 Line* line = NULL;
 int* p = NULL, p2 = 0;
}


