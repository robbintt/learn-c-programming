#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* used from stdlib: malloc */
/* used from stdio: printf */
/* used from string: strcpy */
/* used k&r implementation of strdup: kr_strdup */
/* used from ctype: toascii */



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
  printf("lookup details:");
  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
  {
    printf("%s, ", np->name);
    if (strcmp(s, np->name) == 0)
    {
      printf("\n"); // end of lookup details stdout
      return np; /* found */ 
    }
  }
  printf("\n"); // end of lookup details stdout
  printf("lookup: %s not found in hash table.\n", s);
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
    printf("%s->%s: freeing old definition. (function = lookup)\n", name, defn);
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

  // previous pointer, used to hold the previous place in the do-while check 
  void *pp;
  do {
    /* if we actually reference the hashtab then we can change it later */
    /* np is the target of 'undef' */
    printf("Traversing: %s %s\n", np.name, np.defn);
    if (strcmp(s, np.name) == 0) {
      // assumes that np.next is null initialized
      if (np.next != NULL) {
        printf("this should usually not happen.\n");
        // we can just copy np.next onto np, then free the struct at np.next
        // this sidesteps changing the reference to another struct in the hashtab array
        // i don't think these are sticking... refer to the install function
        np.next = np.next->next;
        np.name = np.next->name;
        np.defn = np.next->defn;
        // free these strings, what about the struct? where does that go?
        //free(np.next->name);
        //free(np.next->defn);
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
    pp = np.next;
    np = *np.next; // while needs to check np, not np.next
  } while (pp != NULL);

  return NULL;
}


/* from: http://stackoverflow.com/a/8465083 */
char *concat(const char *s1, const char *s2)
{
  // in real code check for errors in the malloc
  char *res = malloc(strlen(s1)+strlen(s2)+1); // +1 for the zero terminator

  strcpy(res, s1);
  strcat(res, s2);

  // wherever this goes, it must be free()'d later.
  return(res);
}


char *char2str(const char c)
{
  char *mystr = malloc(2);
  mystr[0] = c;
  mystr[1] = '\0';

  return(mystr);
}


// test the test string against the target
int testhashes(char *s, char *target)
{
    unsigned hashs, hasht;
    hashs = hash(s);
    hasht = hash(target);
    if (hashs == hasht)
    {
      printf("attempt: %s matches target: %s\n", s, target);
      install(s, target);
    }
    else
      ; //printf("attempt: %s doesn't match target: %s\n", s, target);

    // return a match or array of structs of matches or something
    // it needs to return an arbitrary number of matches though
    // probably a linked list?
    return 0;
}

/* construct strings in this ascii range */
#define CHARTABLE_SIZE 95 /* highest character is 32+(95-1) */
#define CHARTABLE_OFFSET 32 /* used ascii character offset */
static int chartable[CHARTABLE_SIZE]; /* table of possible characters */

int build_and_test_hash(char target[], char s[], int depth, int *chartable)
{
  for (int i=0; i<CHARTABLE_SIZE; i++)
  {
    char *t = char2str(chartable[i]);
    char *new_s = concat(s, t);
    if (depth > 0)
      // tests longer strings first
      build_and_test_hash(target, new_s, depth-1, chartable);

    testhashes(new_s, target);
    free(new_s); // deallocate the string
  }

  return 0;
}


/* brute force a duplicate hash for a particular string */
/* accepts an empty string or a prefix */
/* 'max' is the maximum number of letters to append onto 'prefix' */
int findhashdup(char target[], char prefix[], int max) 
{

  // build a table of characters
  for (int c = 0; c < CHARTABLE_SIZE; c++)
    chartable[c] = c + CHARTABLE_OFFSET;

  // recursively test each hash
  build_and_test_hash(target, prefix, --max, chartable);

  return 0;
}


int main()
{
  
  install("hello", "world");
  install("hello", "party");
  undef("hello");
  // returns error if hello does not exist...
  lookup("doesnotexistever");
  install("hello", "tennis");
  printf("lookup result: %s\n", lookup("hello")->defn);

  // this is currently installing all colliding hashes in this depth
  // then we can selectively undef and test if undef is working
  // we can also finally test the lookup on deeper elements
  findhashdup("hello", "", 2);
  printf("lookup result: %s\n", lookup("oo")->defn);
  undef("oo");
  printf("lookup result: %s:%s\n", "oo", lookup("oo")->defn);
  printf("lookup result: %s:%s\n", "v", lookup("v")->defn);
  printf("lookup result: %s:%s\n", "SF", lookup("SF")->defn);
}
