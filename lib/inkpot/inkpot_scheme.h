/* $Id$ $Revision$ */
/* vim:set shiftwidth=4 ts=8: */

/***********************************************************
 *      This software is part of the graphviz package      *
 *                http://www.graphviz.org/                 *
 *                                                         *
 *            Copyright (c) 1994-2008 AT&T Corp.           *
 *                and is licensed under the                *
 *            Common Public License, Version 1.0           *
 *                      by AT&T Corp.                      *
 *                                                         *
 *        Information and Software Systems Research        *
 *              AT&T Research, Florham Park NJ             *
 **********************************************************/

#ifndef INKPOT_STRUCTS_H
#define INKPOT_STRUCTS_H

typedef unsigned char IDX_MRU_CACHE;
#define SZT_MRU_CACHE 4

typedef struct inkpot_scheme_name_s {
	IDX_SCHEME_STRINGS
	     string_idx;        /* The scheme name in TAB_STRINGS.  (e.g. "x11") */
} inkpot_scheme_name_t;

typedef struct inkpot_scheme_index_s { 
	IDX_SCHEME_STRINGS
	     string_idx;        /* The indexed scheme name in TAB_STRINGS. 
				 * e.g "blues7" from Brewer */
	IDX_IXVALUES
	    first_value_idx;	/* The first index to the color values in
				 * TAB_IXVALUES. Terminated by the
				 * first_value_idx of the next
				 * inkpot_scheme_index_t in TAB_SCHEMES_INDEX
				 * or by SZT_SCHEMES_INDEX */
} inkpot_scheme_index_t;

typedef struct inkpot_name_s {	/* Color_name used by one or more
				 * inkpot_scheme_name_t. Each instance has
				 * just one color string and one index_value_t
				 * but another instance may use the same
				 * color string for a different inkpot_value_t.
				 * inkpot_names_t are alpha sorted in
				 * TAB_NAMES[] */

	IDX_COLOR_STRINGS
	    string_idx;         /* The color name in TAB_COLOR_STRINGS.
				 * (e.g. "green") */

	IDX_VALUES
	    value_idx;		/* An index into TAB_VALUE for this
				 * inkpot_name_t */

	MSK_SCHEMES
	    scheme_bits;	/* A bit for each inkpot_scheme_name_t
				 * that includes this inkpot_name_t  */
} inkpot_name_t;

typedef struct inkpot_cache_element_s {
	IDX_MRU_CACHE
	    next_recently_used_idx;
	MSK_SCHEMES
	    scheme_bits;
	IDX_NAMES
	    name_idx;
} inkpot_cache_element_t;

/* typedef struct inkpot_s inkpot_t; */  /* public opaque type in inkpot.h */

struct inkpot_s {		/* The Ink Pot */
	MSK_SCHEMES
	    scheme_bits,	/* One bit per inkpot_scheme_name_t */
	    out_scheme_bit;     /* One scheme only for output. */

	IDX_IXVALUES
	    index,		/* The index for the current value in active_schemes_index */
	    out_index;		/* The index for the current value in active_out_schemes_index */

	IDX_SCHEMES_INDEX
	    active_schemes,                 /* The number of active index schemes. */
	    scheme_list[SZT_SCHEMES_INDEX], /* The list of active index schemes. */
	    active_out_schemes,             /* The number of active index schemes. */
	    out_scheme_list[1];             /* The list of active index schemes. */

	inkpot_name_t
	    *out_name;		/* The current output name, or NULL. */

	char *canon;		/* malloc'ed, reused storage for canonicalizing color request strings */
	int canon_alloc;
	
	inkpot_values_t values; /* The values store */
	inkpot_value_t value;	/* The current value of the inkpot */

	inkpot_cache_element_t
	    cache[SZT_MRU_CACHE];/* MRU chache of successful color lookups */
	IDX_MRU_CACHE
	    most_recently_used_idx;

	inkpot_write_disc_t
	    write_disc;		/* User changeable function for writing output
				 *    Defaults to an internal function that writes
				 *    to FILE* streams */
	void
	    *write_closure;	/* A parameter to pass to the writer function.
				 *    Defaults to (FILE*)stdout */

	inkpot_status_t
	    status;		/* The status after the last operation */
};

#endif /* INKPOT_STRUCTS_H */
