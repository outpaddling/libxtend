
/*
 *  Generated by /home/bacon/auto-gen-get-set-opaque
 *
 *  Mutator functions for setting with no sanity checking.  Use these to
 *  set structure members from functions outside the xt_ff_dsv_line_t
 *  class.  These macros perform no data validation.  Hence, they achieve
 *  maximum performance where data are guaranteed correct by other means.
 *  Use the mutator functions (same name as the macro, but lower case)
 *  for more robust code with a small performance penalty.
 *
 *  These generated macros are not expected to be perfect.  Check and edit
 *  as needed before adding to your code.
 */

/* temp-dsv-mutators.c */
int xt_ff_dsv_line_set_array_size(xt_ff_dsv_line_t *xt_ff_dsv_line_ptr, size_t new_array_size);
int xt_ff_dsv_line_set_num_fields(xt_ff_dsv_line_t *xt_ff_dsv_line_ptr, size_t new_num_fields);
int xt_ff_dsv_line_set_fields(xt_ff_dsv_line_t *xt_ff_dsv_line_ptr, char **new_fields);
int xt_ff_dsv_line_set_fields_ae(xt_ff_dsv_line_t *xt_ff_dsv_line_ptr, size_t c, char *new_fields_element);
int xt_ff_dsv_line_set_fields_cpy(xt_ff_dsv_line_t *xt_ff_dsv_line_ptr, char **new_fields, size_t array_size);
int xt_ff_dsv_line_set_delims(xt_ff_dsv_line_t *xt_ff_dsv_line_ptr, char *new_delims);
int xt_ff_dsv_line_set_delims_ae(xt_ff_dsv_line_t *xt_ff_dsv_line_ptr, size_t c, char new_delims_element);
int xt_ff_dsv_line_set_delims_cpy(xt_ff_dsv_line_t *xt_ff_dsv_line_ptr, char *new_delims, size_t array_size);
