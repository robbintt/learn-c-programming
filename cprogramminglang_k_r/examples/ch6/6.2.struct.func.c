/* Chapter 6: Structures */
/* 6.2 Structures and Functions */
#include <stdio.h>


#define XMAX 320
#define YMAX 200
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))


struct point {
  int x;
  int y;
};

struct rect {
  struct point pt1;
  struct point pt2;
};


/* makepoint: make a point from x and y components */
struct point makepoint(int x, int y)
{
  struct point temp;
  
  temp.x = x;
  temp.y = y;
  return temp;
}

/* canonrect: canonicalize coordinates of rectangle */
struct rect canonrect(struct rect r)
{
  struct rect temp;

  temp.pt1.x = min(r.pt1.x, r.pt2.x);
  temp.pt1.y = min(r.pt1.y, r.pt2.y);
  
  temp.pt2.x = max(r.pt1.x, r.pt2.x);
  temp.pt2.y = max(r.pt1.y, r.pt2.y);

  return temp;
}

/* addpoint: add two points */
struct point addpoint(struct point p1, struct point p2)
{
  p1.x += p2.x;
  p1.y += p2.y;
  return p1;
}

/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
  return p.x >= r.pt1.x && p.x < r.pt2.x
     && p.y >= r.pt1.y && p.y < r.pt2.y;
}


int main() {

  struct rect screen;
  struct point middle;
  struct point makepoint(int, int);

  screen.pt1 = makepoint(0, 0);
  screen.pt2 = makepoint(XMAX, YMAX);

  /* aside: note that the second line has an odd number of leading spaces */
  /*        compromises are made to align text in 'continued lines' */
  middle = makepoint((screen.pt1.x + screen.pt2.x)/2,
                     (screen.pt1.y + screen.pt2.y)/2);

  /* a pointer to a struct shaped like point */
  /* anything stopping this from working on identical struct same_as_point? */
  struct point origin, *pp;

  /* set the pp pointer to the referenced origin memory location */
  pp = &origin;

  /* use the dereference, `*`, to get origin.x and origin.y with pp */ 
  /* the parentheses are necessary because the precedence 
   * of member operator, `.`, is higher than `*` */
  printf("origin is (%d,%d)\n", (*pp).x, (*pp).y);
  /* there's an easier way because this is so common */
  printf("origin is (%d,%d)\n", pp->x, pp->y);

}

