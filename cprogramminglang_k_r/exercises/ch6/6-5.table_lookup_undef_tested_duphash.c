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

  // IMPORTANT: standard idiom for walking along a linked list ***
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


/* install: put (name, defn) in hash table */
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


/* write a function 'undef' that will remove a name and definition from the hash table */
/* HOW: 
 * we need to remove the reference to that struct.
 * we must replace the 'next' reference from the previous nlist with the deleted nlist's 'next' pointer
 * OR replace the 'next' reference with NULL if the current nlist's 'next' is NULL
 * This implies we need a reference back to the deleted nlist's parent's 'next'
 * do we need to unallocate the struct or its contents? 
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
        strcpy(np.defn, np.next->defn);
        strcpy(np.name, np.next->name);
        // this overwrites the actual pointer with the other pointer
        *np.next = *np.next->next;
        // don't I need to free() the struct that disappeared?
        // from elsewhere: free((void *) np->defn); /* free previous defn */
        free((void *) (*np.next).defn);
        free((void *) (*np.next).name);
      }
      else {
        // don't I need to free() the struct that disappeared?
        // if at the top level, reset the hashtable index to null 
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


int test_a_hash(char *s, char *target)
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

    return 0;
}


/* construct all strings length<=depth in this ascii range */
#define CHAR_TABLE_SIZE 95 /* highest character is 32+(95-1) */
#define CHAR_TABLE_OFFSET 32 /* used ascii character offset */


static int char_table[CHAR_TABLE_SIZE]; /* table of possible characters */


int build_and_test_hash(char target[], char s[], int depth, int *char_table)
{
  for (int i=0; i<CHAR_TABLE_SIZE; i++)
  {
    char *t = char2str(char_table[i]);
    char *new_s = concat(s, t);
    if (depth > 0)
      // tests longer strings first
      build_and_test_hash(target, new_s, depth-1, char_table);

    test_a_hash(new_s, target);
    free(new_s); // deallocate the string
  }

  return 0;
}


/* brute force hash collisions for a particular string */
int find_hash_dupes(char target[], char prefix[], int max) 
{
  /* 'max' is the maximum number of letters to append 
   * accepts an empty string or a prefix
   * onto 'prefix' and is the recursion depth */

  // build a table of characters
  for (int c = 0; c < CHAR_TABLE_SIZE; c++)
    char_table[c] = c + CHAR_TABLE_OFFSET;

  // recursively test each hash
  build_and_test_hash(target, prefix, max-1, char_table);

  return 0;
}


int main()
{
  /* a bunch of what passes for tests */  
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
  find_hash_dupes("hello", "", 2);
  printf("lookup result: %s\n", lookup("oo")->defn);
  undef("oo");
  lookup("oo");
  printf("lookup result: %s:%s\n", "v", lookup("v")->defn);
  printf("lookup result: %s:%s\n", "SF", lookup("SF")->defn);
}
