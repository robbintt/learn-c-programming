#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* used from stdlib: malloc */
/* used from stdio: printf */
/* used from string: strcpy */
/* used k&r implementation of strdup: kr_strdup */


struct nlist {   /* table entry: */
  struct nlist *next;  /* next entry in chain */
  char *name; /* defined name */
  char *defn; /* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
  struct nlist *np;

  // standard idiom for walking along a linked list
  // for (ptr = head; ptr != NULL; ptr = ptr->next)
  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np; /* found */
  return NULL; /* not found */
}

// this function really goes in a library included in this program
// you can use the strdup function in the stdlib, i think it is in string.h
char *kr_strdup(char *s) /* make a duplicate of s */
{
  char *p;

  p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
  if (p != NULL)
    strcpy(p, s);
  return p;
}


struct nlist *lookup(char *);

/* this is either a semicolon or it's part of the definition on 143 and needed a ... */
/* my belief is that the line shouldn't exist at all on this page */
/* char *kr_strdup(char *); */

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) { /* not found */
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = kr_strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else /* already there */
    free((void *) np->defn); /* free previous defn */
  if ((np->defn = kr_strdup(defn)) == NULL)
    return NULL;
  return np;
}

int main()
{
  
  install("hello", "world");
  install("hello", "party");
  printf("%s", lookup("hello")->defn);

}
