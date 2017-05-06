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

/* i don't think this should exist here either.... it is the first line of the lookup function definition */
struct nlist *lookup(char *);

/* this is either a semicolon or it's part of the definition on p 143 and needed a ... */
/* my belief is that the line shouldn't exist at all on p 143 */
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
  } else { /* already there */
    printf("Freeing old definition. (function = lookup)");
    free((void *) np->defn); /* free previous defn */
  }
  if ((np->defn = kr_strdup(defn)) == NULL)
    return NULL;
  return np;
}

/* write a function 'undef' that will remove a name and definition from the table
 * maintained by 'lookup' and 'install' */
/* HOW: 
 * we need to remove the reference to that struct.
 * we must replace the 'next' reference from the previous nlist with the deleted nlist's 'next' pointer
 * OR replace the 'next' reference with NULL if the current nlist's 'next' is NULL
 * This implies we need a reference back to the deleted nlist's parent's 'next'
 * do we need to unallocate the struct? 
 * Also, the pointer that is altered is quite possibly in hashtab, rather than an nlist struct's 'next' pointer
 * */
/* pull traversal logic from lookup */
struct nlist *undef(char *s)
{
  struct nlist np;
  unsigned hashval;

  /* get initial np */
  hashval = hash(s);
  np = *hashtab[hashval];
  
  /* if undef occurs at the top level, reset the hash table index to NULL */
  int RESET_HASHTABLE = 1;

  do {
    /* if we actually reference the hashtab then we can change it later */
    /* np is the target of 'undef' */
    if (strcmp(s, np.name) == 0) {
      printf("%s\n", np.name);
      printf("%s\n", np.defn);
      // assumes that np.next is null initialized
      if (np.next != NULL) {
        printf("this should usually not happen.\n");
        // we can just copy np.next onto np, then free the struct at np.next
        // this sidesteps changing the reference to another struct in the hashtab array
        np.next = np.next->next;
        np.name = np.next->name;
        np.defn = np.next->defn;
        // free struct at *np.next (do i need to dereference np.next then?
        free(np.next);
      }
      else {
        printf("This usually should happen.\n");
        // if at the top level, reset the hashtable index to null 
        // no need to free the struct in this array
        if (RESET_HASHTABLE == 1) {
          hashtab[hashval] = NULL;
        }
      }
      break;
    }
    RESET_HASHTABLE = 0;
  } while (np.next != NULL);

  return NULL;
}

int main()
{
  
  install("hello", "world");
  install("hello", "party");
  undef("hello");
  // returns error if hello does not exist...
  //printf("lookup result: %s\n", lookup("doesnotexistever")->defn);
  install("hello", "tennis");
  printf("lookup result: %s\n", lookup("hello")->defn);

}
