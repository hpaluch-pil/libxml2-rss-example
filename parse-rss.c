/*
 * parse-rss.c - simple libxml2 example - parsing RSS list from Debian DSA
 * Base on libxml2/example/parse*.c and others.
 * dsa.xml can be downloaded from:  https://www.debian.org/security/dsa
 */

#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


// Macro similar to Linux kernel
#define pr_err(fmt,...) printf("ERROR: at %s:%d: " fmt "\n",__FUNCTION__,__LINE__,##__VA_ARGS__)

#define checkNodeName(nm,lb) \
	if (cur == NULL){ pr_err("Node is null, but '%s' expected",nm); goto lb;} \
	if (xmlStrcmp(cur->name, (const xmlChar *) nm)) { \
		pr_err("Node name is '%s', but '%s' expected", cur->name, nm); goto lb;}


static const char *CHANNEL_PRINTABLE_ELEMS[] = {
		"title","link","date","description",NULL
};
static const char *ITEM_PRINTABLE_ELEMS[] = {
		"title","link","date",NULL
};


int handleSpecificElem(xmlNodePtr cur, const char **PRINTABLE_CHILDREN)
{
	int ret = EXIT_FAILURE;

	printf("- %s:\n", cur->name);
	cur = cur->xmlChildrenNode;
	while(cur != NULL){
		//printf("Node: '%s' (type: %d)\n", cur->name, cur->type);
		// we parse only Elements at this level - ignoring anything else
		if (cur->type == XML_ELEMENT_NODE){
			const char **p = NULL;
			//printf("Elem under: '%s'\n", cur->name);

			// look for printable element
			for(p = PRINTABLE_CHILDREN;*p!=NULL;p++){
				if (xmlStrcmp(cur->name, (const xmlChar *) *p) == 0){
					xmlChar *txt = xmlNodeGetContent(cur);
					printf("  - %s: '%s'\n", cur->name, txt);
					if (txt != NULL){
						xmlFree(txt); txt = NULL;
					}
				}
			}
		}
		cur = cur->next;
	}
	ret = EXIT_SUCCESS;
	return ret;
}

int main(int argc, char **argv) {
	xmlDocPtr doc = NULL;
	xmlNodePtr cur = NULL;
	const char *filename = NULL;
	int ret = EXIT_FAILURE;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s dsa.xml\n", argv[0]);
		goto exit0;
	}
	filename = argv[1];
	doc = xmlReadFile(filename, NULL, 0);

	if (doc == NULL) {
		pr_err("Failed to parse %s", filename);
		goto exit0;
	}

	cur = xmlDocGetRootElement(doc);

	checkNodeName("RDF",exit1);

	cur = cur->xmlChildrenNode;
	while(cur != NULL){
		// printf("Node: '%s' (type: %d)\n", cur->name, cur->type);
		// we parse only Elements at this level - ignoring anything else
		if (cur->type == XML_ELEMENT_NODE){
			//printf("Elem: '%s'\n", cur->name);
			if (xmlStrcmp(cur->name, (const xmlChar *) "channel") == 0){
				if (handleSpecificElem(cur, CHANNEL_PRINTABLE_ELEMS))
					goto exit1;
			}
			if (xmlStrcmp(cur->name, (const xmlChar *) "item") == 0){
				if (handleSpecificElem(cur, ITEM_PRINTABLE_ELEMS))
					goto exit1;
			}
		}
		cur = cur->next;
	}

	ret = EXIT_SUCCESS;
exit1:
	xmlFreeDoc(doc);
exit0:
	return ret;
}
