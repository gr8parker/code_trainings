#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct nlist { /* table element */
    struct nlist *next; /* pointer to next element */
    char *name; /* define name */ 
    char *defn; /* inplace text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE]; /* table of pointers */

/* hash: returns hash for string */
unsigned hash(char* s)
{
    unsigned hashval;

    for( hashval = 0; *s != '\0'; s++)
	hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
	if (strcmp(s, np->name) == 0)
	    return np; /* found */
    return NULL;
}

/* install */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
	    np = (struct nlist *) malloc(sizeof(*np));
	    if (np == NULL || (np->name = strdup(name)) == NULL)
		return NULL;
	    hashval = hash(name);
	    np->next = hashtab[hashval];
	    hashtab[hashval] = np;
	} else /* we already have one */
	      free((void*)np->defn);
	if ((np->defn = strdup(defn)) == NULL)
	    return NULL;
	return np;
}


typedef struct tnode* Treeptr;
typedef struct tnode {
    char * word;
    int count;
    Treeptr left;
    Treeptr right;
} Treenode;

int main () {
    install("ab", "ab");
    install("dd", "dd");
    install("ba", "ba");
    for(int i = 0; i < HASHSIZE; ++i) {
	if( hashtab[i] != 0 )
	    printf("%s\n", hashtab[i]->name);
    }
}


			  
		
