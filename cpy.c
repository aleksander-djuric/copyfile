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

#include "copy_file.h"

void cpcb(cp_state *s);
void usage(char *name);

int main(int argc, char *argv[]) {
	cp_callback cpcb_ptr = NULL;
	char c, *src, *dst;
	int move_flag = 0;
	int rc = 0;

	setlocale(LC_ALL, "");

	if (argc > 2) {
		src = argv[argc-2];
		dst = argv[argc-1];
		argc -= 2;
	} else {
		usage(argv[0]);
		return 0;
	}

	while ((c = getopt(argc, argv, "hmv")) != -1)
	switch (c) {
		case 'm': // move mode
			move_flag = 1;
			break;
		case 'v': // verbose mode
			cpcb_ptr = cpcb;
			break;
		case '?':
		default: // print help
			usage(argv[0]);
			return 0;
	}

	if ((rc = copy_file(src, dst, move_flag, cpcb_ptr)) < 0)
		printf("copy file error %s\n", strerror(errno));

	return rc;
}

void cpcb(cp_state *s) {
	int pcnt = (s->cp_cur * 100. / (s->cp_top + 1));

	if (!(pcnt % 10))
		printf("%s %s to %s %d%%\n", s->move_flag ? "moving" : "copying",
			s->src, s->dst, pcnt);
}

void usage(char *name) {
	printf("\rUsage:\t%s [-mv] source_file target_file\n", name);
	printf("\t%s [-mv] source_file target_directory\n", name);
	printf("\t%s [-mv] source_directory target_directory\n\n", name);

	printf("\t-m\tmove mode\n");
	printf("\t-v\tbe verbose\n\n");
} // usage
