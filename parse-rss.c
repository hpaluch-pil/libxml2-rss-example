/*
 * parse-rss.c - simple libxml2 example - parsing RSS list from Debian DSA
 * Base on libxml2/example/parse*.c and others.
 * dsa.xml can be downloaded from:  https://www.debian.org/security/dsa
 */

#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


int main(int argc, char **argv) {
	xmlDocPtr doc = NULL;
	const char *filename = NULL;
	int ret = EXIT_FAILURE;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s dsa.xml\n", argv[0]);
		goto exit0;
	}
	filename = argv[1];
	doc = xmlReadFile(filename, NULL, 0);

	if (doc == NULL) {
		fprintf(stderr, "Failed to parse %s\n", filename);
		goto exit0;
	}

	ret = EXIT_SUCCESS;

	xmlFreeDoc(doc);
exit0:
	return ret;
}
