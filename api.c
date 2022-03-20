#include "parser.h"
#include "annexe.h"
#include "tree.h"

/*
	getRootTree(), purgeTree(),
	définies dans tree.h
*/

/*
 *      Search for all the nodes matching the tag = name
 */
_Token *searchTree(void *start, char *name) {
        node *tmp = start;
        if (tmp == NULL)
            tmp = getRootTree();
        _Token *r = NULL;
        _searchTree(tmp, name, &r);
        return r;
}

/*
 *      Returns the pointer to the tag (name of the rulename) of the pointed node and stores its length
 */
char *getElementTag(void *node, int *len) {
    struct node *tmp = node;
    *len = strlen(tmp->tag);
    return tmp->tag;
}

/*
 *      Returns the pointer to the value (rulename) of the pointed node and stores its length
 */
char *getElementValue(void *node, int *len) {
    struct node *tmp = node;
    *len = tmp->len_value;
    return tmp->value;
}

/*
 *      Free the linked list of the response of searchTree
 */
void purgeElement(_Token **r) {
    if (*r == NULL) // empty _Token list
        return;

    _Token *tmp;
    while (*r) {
        tmp = (*r)->next;
        free(*r);
        *r = tmp;
    }
}


/*
*	Parse a request $req (of length $len) mapped in the memory
*/
int parseur(char *req, int len) {
    mem = req;
    no_go_zone = mem + len;
	createRoot(FIRST_TAG, req, len);
    int r = construire(FIRST_TAG, getRootTree());

	FIX_FINAL_NE_PAS_TOUCHER();

    printf("Valid:");
    truth(r);

	if (!r)
		purgeTree(getRootTree());
	#if DISPLAY_TREE
	else
		display_tree(getRootTree(), 0);
	#endif
    return r;
}
