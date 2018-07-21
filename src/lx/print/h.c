/*
 * Copyright 2008-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stdio.h>

#include <fsm/print.h>
#include <fsm/options.h>

#include <print/esc.h>

#include "lx/ast.h"
#include "lx/print.h"

static void
print_tokens(FILE *f, const struct ast *ast)
{
	struct ast_token *t;

	assert(f != NULL);
	assert(ast != NULL);

	fprintf(f, "enum %stoken {\n", prefix.api);

	/* TODO: the token prefix needs to be configurable */
	for (t = ast->tl; t != NULL; t = t->next) {
		fprintf(f, "\t%s", prefix.tok);
		esctok(f, t->s);
		fprintf(f, ",\n");
	}

	fprintf(f, "\t%sEOF,\n", prefix.tok);
	fprintf(f, "\t%sERROR,\n", prefix.tok);
	fprintf(f, "\t%sUNKNOWN\n", prefix.tok);

	fprintf(f, "};\n");
}

void
lx_print_h(FILE *f, const struct ast *ast)
{
	assert(f != NULL);
	assert(ast != NULL);

	fprintf(f, "/* Generated by lx */\n");	/* TODO: date, input etc */
	fprintf(f, "\n");

	/* TODO: this guard macro needs to be configurable */
	fprintf(f, "#ifndef LX_H\n");
	fprintf(f, "#define LX_H\n");
	fprintf(f, "\n");

	print_tokens(f, ast);
	fprintf(f, "\n");

	if (~api_exclude & API_POS) {
		fprintf(f, "/*\n");
		fprintf(f, " * .byte is 0-based.\n");
		fprintf(f, " * .line, .col, and .saved_col are 1-based; 0 means unknown.\n");
		fprintf(f, " */\n");
		fprintf(f, "struct lx_pos {\n");
		fprintf(f, "\tunsigned byte;\n");
		fprintf(f, "\tunsigned line;\n");
		fprintf(f, "\tunsigned col;\n");
		fprintf(f, "\tunsigned saved_col;\n");
		fprintf(f, "};\n");
		fprintf(f, "\n");
	}

	fprintf(f, "struct %slx {\n", prefix.lx);

	switch (opt.io) {
	case FSM_IO_GETC:
		fprintf(f, "\tint (*lgetc)(struct %slx *lx);\n", prefix.lx);
		fprintf(f, "\tvoid *getc_opaque;\n");
		fprintf(f, "\n");
		fprintf(f, "\tint c; /* %sungetc buffer */\n", prefix.api);
		fprintf(f, "\n");
		break;

	case FSM_IO_STR:
		fprintf(f, "\tconst char *p; /* input string */\n");
		fprintf(f, "\n");
		break;

	case FSM_IO_PAIR:
		fprintf(f, "\tconst char *p; /* input string */\n");
		fprintf(f, "\tconst char *e; /* one past end of input */\n");
		fprintf(f, "\n");
		break;
	}

	if (~api_exclude & API_POS) {
		fprintf(f, "\tstruct lx_pos start;\n");
		fprintf(f, "\tstruct lx_pos end;\n");
		fprintf(f, "\n");
	}
	if (~api_exclude & API_BUF) {
		fprintf(f, "\tvoid *buf_opaque;\n");
		fprintf(f, "\tint  (*push) (void *buf_opaque, char c);\n");
		fprintf(f, "\tint  (*clear)(void *buf_opaque);\n");
		fprintf(f, "\tvoid (*free) (void *buf_opaque);\n");
		fprintf(f, "\n");
	}

	fprintf(f, "\tenum %stoken (*z)(struct %slx *lx);\n", prefix.api, prefix.lx);

	fprintf(f, "};\n");
	fprintf(f, "\n");

	if (api_tokbuf & API_DYNBUF) {
		fprintf(f, "/*\n");
		fprintf(f, " * The initial buffer size; this ought to be over the typical token length,\n");
		fprintf(f, " * so as to avoid a run-up of lots of resizing.\n");
		fprintf(f, " */\n");
		fprintf(f, "#ifndef LX_DYN_LOW\n");
		fprintf(f, "#define LX_DYN_LOW 1 << 10\n");
		fprintf(f, "#endif\n");
		fprintf(f, "\n");

		fprintf(f, "/*\n");
		fprintf(f, " * High watermark; if the buffer grows over this, it will resize back down\n");
		fprintf(f, " * by LX_DYN_FACTOR when no longer in use.\n");
		fprintf(f, " */\n");
		fprintf(f, "#ifndef LX_DYN_HIGH\n");
		fprintf(f, "#define LX_DYN_HIGH 1 << 13\n");
		fprintf(f, "#endif\n");
		fprintf(f, "\n");

		fprintf(f, "/*\n");
		fprintf(f, " * Andrew Koenig said the growth factor should be less than phi, (1 + sqrt(5)) / 2\n");
		fprintf(f, " * P.J. Plauger said 1.5 works well in practice. (Perhaps because of internal\n");
		fprintf(f, " * bookkeeping data stored by the allocator.)\n");
		fprintf(f, " *\n");
		fprintf(f, " * Non-integer factors here add the constraint that LX_DYN_LOW > 1 because\n");
		fprintf(f, " * because conversion to size_t truncates, and e.g. 1 * 1.5 == 1 is no good\n");
		fprintf(f, " * as the requirement is to *increase* a buffer.\n");
		fprintf(f, " */\n");
		fprintf(f, "#ifndef LX_DYN_FACTOR\n");
		fprintf(f, "#define LX_DYN_FACTOR 2\n");
		fprintf(f, "#endif\n");
		fprintf(f, "\n");

		fprintf(f, "/* dynamic token buffer */\n");
		fprintf(f, "struct lx_dynbuf {\n");
		fprintf(f, "\tchar *p;\n");
		fprintf(f, "\tsize_t len;\n");
		fprintf(f, "\tchar *a;\n");
		fprintf(f, "};\n");
		fprintf(f, "\n");
	}

	if (api_tokbuf & API_FIXEDBUF) {
		fprintf(f, "/* fixed-size token buffer */\n");
		fprintf(f, "struct lx_fixedbuf {\n");
		fprintf(f, "\tchar *p;\n");
		fprintf(f, "\tsize_t len;\n");
		fprintf(f, "#ifdef LX_FIXED_SIZE\n");
		fprintf(f, "\tchar a[LX_FIXED_SIZE];\n");
		fprintf(f, "#else\n");
		fprintf(f, "\tchar *a; /* could be flexible member */\n");
		fprintf(f, "#endif\n");
		fprintf(f, "};\n");
		fprintf(f, "\n");
	}

	if (api_getc & API_AGETC) {
		fprintf(f, "/* opaque for %sagetc */\n", prefix.api);
		fprintf(f, "struct lx_arr {\n");
		fprintf(f, "\tchar *p;\n");
		fprintf(f, "\tsize_t len;\n");
		fprintf(f, "};\n");
		fprintf(f, "\n");
	}

	if (api_getc & API_FDGETC) {
		/* TODO: posix only */
		fprintf(f, "/* opaque for %sfdgetc */\n", prefix.api);
		fprintf(f, "struct lx_fd {\n");
		fprintf(f, "\tchar *p;\n");
		fprintf(f, "\tsize_t len;\n");
		fprintf(f, "\n");
		fprintf(f, "\tint fd;\n");
		fprintf(f, "\tchar *buf;\n");
		fprintf(f, "\tsize_t bufsz;\n");
		fprintf(f, "};\n");
		fprintf(f, "\n");
	}

	if (~api_exclude & API_NAME) {
		fprintf(f, "const char *%sname(enum %stoken t);\n", prefix.api, prefix.api);
	}
	if (~api_exclude & API_EXAMPLE) {
		fprintf(f, "const char *%sexample(enum %stoken (*z)(struct %slx *), enum %stoken t);\n",
			prefix.api, prefix.api, prefix.lx, prefix.api);
	}
	fprintf(f, "\n");

	fprintf(f, "void %sinit(struct %slx *lx);\n", prefix.api, prefix.lx);
	fprintf(f, "enum %stoken %snext(struct %slx *lx);\n", prefix.api, prefix.api, prefix.lx);
	fprintf(f, "\n");

	if (api_getc & API_FGETC) {
		fprintf(f, "int %sfgetc(struct %slx *lx);\n", prefix.api, prefix.lx); /* TODO: stdio only */
	}
	if (api_getc & API_SGETC) {
		fprintf(f, "int %ssgetc(struct %slx *lx);\n", prefix.api, prefix.lx);
	}
	if (api_getc & API_AGETC) {
		fprintf(f, "int %sagetc(struct %slx *lx);\n", prefix.api, prefix.lx);
	}
	if (api_getc & API_FDGETC) {
		fprintf(f, "int %sdgetc(struct %slx *lx);\n", prefix.api, prefix.lx);
	}
	if (api_getc) {
		fprintf(f, "\n");
	}

	if (api_tokbuf & API_DYNBUF) {
		fprintf(f, "int  %sdynpush(void *buf_opaque, char c);\n", prefix.api);
		fprintf(f, "int  %sdynclear(void *buf_opaque);\n", prefix.api);
		fprintf(f, "void %sdynfree(void *buf_opaque);\n", prefix.api);
		fprintf(f, "\n");
	}

	if (api_tokbuf & API_FIXEDBUF) {
		fprintf(f, "int  %sfixedpush(void *buf_opaque, char c);\n", prefix.api);
		fprintf(f, "int  %sfixedclear(void *buf_opaque);\n", prefix.api);
		fprintf(f, "\n");
	}

        if (opt.io == FSM_IO_STR) {
		fprintf(f, "void %sinput_str(struct %slx *lx, const char *p);\n", prefix.api, prefix.lx);
		fprintf(f, "\n");
        }

	fprintf(f, "#endif\n");
	fprintf(f, "\n");
}

