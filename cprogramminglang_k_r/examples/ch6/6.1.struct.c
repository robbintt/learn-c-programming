/* Chapter 6: Structures */

int main()
{

  /* declaring a struct */
  struct point {
    int x;
    int y;
  };

  /* this will allocate structs for the variables 
   * following the declaration */
  struct point_ {
    int x;
    int y;
  } point_a1, point_a2, point_a3, point_an;


  /* same as any other declaration and definition */
  struct point pt;
  struct point maxpt = { 320, 200 };

  /* what values are default? probably follows the 
   * rules of the types in the struct */
  printf("%d\t%d\n", pt.x, pt.y);
  printf("%d\t%d\n", maxpt.x, maxpt.y);

  /* what is going on here? i don't get this declaration */
  double dist, sqrt(double);
  /* what is going on here? I don't understand the use of (double) */
  dist = sqrt((double)pt.x * pt.x + (double)pt.y * pt.y);

  /* nesting structs */
  struct rect {
    struct point pt1;
    struct point pt2;
  };

  struct rect screen;
  printf("%i\t\n", screen.pt1.x);

}
