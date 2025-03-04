/*
 * Copyright 2018 Scott Vokes
 *
 * See LICENCE for the full copyright terms.
 */

#ifndef RE_AST_COMPILE_H
#define RE_AST_COMPILE_H

/*
 * Compilation to FSM
 */

struct ast_expr;
struct ast_class;
struct fsm;
struct re_err;
struct ast_expr;
struct ast_class;

int
ast_compile_class(const struct ast_class *class,
	struct fsm *fsm, enum re_flags flags,
	struct re_err *err,
	struct fsm_state *x, struct fsm_state *y);

int
ast_compile_expr(struct ast_expr *n,
	struct fsm *fsm, enum re_flags flags,
	struct re_err *err,
	struct fsm_state *x, struct fsm_state *y);

struct fsm *
ast_compile(const struct ast *ast,
	enum re_flags flags,
	const struct fsm_options *opt,
	struct re_err *err);

#endif
