/*
 * cpy.c
 *
 * Tool description: Copy / move a file's preserving attributes.
 * Copyright (c) 2017 Aleksander Djuric. All rights reserved.
 * Distributed under the GNU Lesser General Public License (LGPL).
 * The complete text of the license can be found in the LICENSE
 * file included in the distribution.
 *
 */

#include "cpy.h"
#include "copy_file.h"

void cpcb(cp_state *s);
void usage(char *name);

int main(int argc, char *argv[]) {
	cp_callback cpcb_ptr = NULL;
	char c, *src, *dst;
	int cp_func = CP_MODE_COPY;
	int nfiles, rc = 0;

	setlocale(LC_ALL, "");

	if (argc < 2) {
		usage(argv[0]);
		return 0;
	}

	while ((c = getopt(argc, argv, "rmv")) != -1)
	switch (c) {
		case 'r': // remove mode
			cp_func = CP_MODE_REMOVE;
			break;
		case 'm': // move mode
			cp_func = CP_MODE_MOVE;
			break;
		case 'v': // verbose mode
			cpcb_ptr = cpcb;
			break;
		case '?':
		default: // print help
			usage(argv[0]);
			return 0;
	}

	nfiles = argc - optind;
	if (nfiles == 2) {
		src = argv[optind++];
		dst = argv[optind++];
		rc = copy_file(src, dst, cp_func, cpcb_ptr);
	} else if (nfiles == 1 && cp_func == CP_MODE_REMOVE) {
		src = argv[optind++];
		rc = remove_file(src, cp_func, cpcb_ptr);
	} else {
		usage(argv[0]);
		return -1;
	}

	return rc;
}

void cpcb(cp_state *s) {
	int pcnt = (s->curpos * 100. / (s->size + 1));

	if ((pcnt % 10)) return;

	if (s->func == CP_MODE_REMOVE)
		printf("removing: %s %d%%\n", s->src, pcnt);
	else if (s->func == CP_MODE_MOVE)
		printf("moving: %s to %s %d%%\n", s->src, s->dst, pcnt);
	else if (s->func == CP_MODE_COPY)
		printf("copying: %s to %s %d%%\n", s->src, s->dst, pcnt);
	else return;
}

void usage(char *name) {
	printf("\rUsage:\t%s [-mv] source_file target_file\n", name);
	printf("\t%s [-mv] source_file target_directory\n", name);
	printf("\t%s [-mv] source_directory target_directory\n", name);
	printf("\t%s [-rv] file\n", name);
	printf("\t%s [-rv] directory\n\n", name);

	printf("\t-m\tmove mode\n");
	printf("\t-r\tremove mode\n");
	printf("\t-v\tbe verbose\n\n");
} // usage
