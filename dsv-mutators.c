/***************************************************************************
 *  This file is automatically generated by gen-get-set.  Be sure to keep
 *  track of any manual changes.
 *
 *  These generated functions are not expected to be perfect.  Check and
 *  edit as needed before adding to your code.
 ***************************************************************************/

#include <string.h>
#include <ctype.h>
#include <stdbool.h>        // In case of bool
#include <stdint.h>         // In case of int64_t, etc
#include "string.h"         // strlcpy() on Linux
#include "dsv-private.h"


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lxtend
 *
 *  Description:
 *      Mutator for array_size member in a xt_dsv_line_t structure.
 *      Use this function to set array_size in a xt_dsv_line_t object
 *      from non-member functions.  This function performs a direct
 *      assignment for scalar or pointer structure members.  If
 *      array_size is a pointer, data previously pointed to should
 *      be freed before calling this function to avoid memory
 *      leaks.
 *
 *  Arguments:
 *      xt_dsv_line_ptr    Pointer to the structure to set
 *      new_array_size  The new value for array_size
 *
 *  Returns:
 *      DSV_DATA_OK if the new value is acceptable and assigned
 *      DSV_DATA_OUT_OF_RANGE otherwise
 *
 *  Examples:
 *      xt_dsv_line_t      xt_dsv_line;
 *      size_t          new_array_size;
 *
 *      if ( xt_dsv_line_set_array_size(&xt_dsv_line, new_array_size)
 *              == DSV_DATA_OK )
 *      {
 *      }
 *
 *  See also:
 *      (3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-05-27  gen-get-set Auto-generated from dsv-private.h
 ***************************************************************************/

int     xt_dsv_line_set_num_fields_array_size(xt_dsv_line_t *xt_dsv_line_ptr, size_t new_array_size)

{
    if ( false )
	return DSV_DATA_OUT_OF_RANGE;
    else
    {
	xt_dsv_line_ptr->num_fields_array_size = new_array_size;
	return DSV_DATA_OK;
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lxtend
 *
 *  Description:
 *      Mutator for num_fields member in a xt_dsv_line_t structure.
 *      Use this function to set num_fields in a xt_dsv_line_t object
 *      from non-member functions.  This function performs a direct
 *      assignment for scalar or pointer structure members.  If
 *      num_fields is a pointer, data previously pointed to should
 *      be freed before calling this function to avoid memory
 *      leaks.
 *
 *  Arguments:
 *      xt_dsv_line_ptr    Pointer to the structure to set
 *      new_num_fields  The new value for num_fields
 *
 *  Returns:
 *      DSV_DATA_OK if the new value is acceptable and assigned
 *      DSV_DATA_OUT_OF_RANGE otherwise
 *
 *  Examples:
 *      xt_dsv_line_t      xt_dsv_line;
 *      size_t          new_num_fields;
 *
 *      if ( xt_dsv_line_set_num_fields(&xt_dsv_line, new_num_fields)
 *              == DSV_DATA_OK )
 *      {
 *      }
 *
 *  See also:
 *      (3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-05-27  gen-get-set Auto-generated from dsv-private.h
 ***************************************************************************/

int     xt_dsv_line_set_num_fields(xt_dsv_line_t *xt_dsv_line_ptr, size_t new_num_fields)

{
    if ( false )
	return DSV_DATA_OUT_OF_RANGE;
    else
    {
	xt_dsv_line_ptr->num_fields = new_num_fields;
	return DSV_DATA_OK;
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lxtend
 *
 *  Description:
 *      Mutator for fields member in a xt_dsv_line_t structure.
 *      Use this function to set fields in a xt_dsv_line_t object
 *      from non-member functions.  This function performs a direct
 *      assignment for scalar or pointer structure members.  If
 *      fields is a pointer, data previously pointed to should
 *      be freed before calling this function to avoid memory
 *      leaks.
 *
 *  Arguments:
 *      xt_dsv_line_ptr    Pointer to the structure to set
 *      new_fields      The new value for fields
 *
 *  Returns:
 *      DSV_DATA_OK if the new value is acceptable and assigned
 *      DSV_DATA_OUT_OF_RANGE otherwise
 *
 *  Examples:
 *      xt_dsv_line_t      xt_dsv_line;
 *      char **         new_fields;
 *
 *      if ( xt_dsv_line_set_fields(&xt_dsv_line, new_fields)
 *              == DSV_DATA_OK )
 *      {
 *      }
 *
 *  See also:
 *      (3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-05-27  gen-get-set Auto-generated from dsv-private.h
 ***************************************************************************/

int     xt_dsv_line_set_fields(xt_dsv_line_t *xt_dsv_line_ptr, char ** new_fields)

{
    if ( new_fields == NULL )
	return DSV_DATA_OUT_OF_RANGE;
    else
    {
	xt_dsv_line_ptr->fields = new_fields;
	return DSV_DATA_OK;
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lxtend
 *
 *  Description:
 *      Mutator for an array element of fields member in a xt_dsv_line_t
 *      structure. Use this function to set xt_dsv_line_ptr->fields[c]
 *      in a xt_dsv_line_t object from non-member functions.
 *
 *  Arguments:
 *      xt_dsv_line_ptr    Pointer to the structure to set
 *      c               Subscript to the fields array
 *      new_fields_element The new value for fields[c]
 *
 *  Returns:
 *      DSV_DATA_OK if the new value is acceptable and assigned
 *      DSV_DATA_OUT_OF_RANGE otherwise
 *
 *  Examples:
 *      xt_dsv_line_t      xt_dsv_line;
 *      size_t          c;
 *      char **         new_fields_element;
 *
 *      if ( xt_dsv_line_set_fields_ae(&xt_dsv_line, c, new_fields_element)
 *              == DSV_DATA_OK )
 *      {
 *      }
 *
 *  See also:
 *      DSV_LINE_SET_FIELDS_AE(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-05-27  gen-get-set Auto-generated from dsv-private.h
 ***************************************************************************/

int     xt_dsv_line_set_fields_ae(xt_dsv_line_t *xt_dsv_line_ptr, size_t c, char * new_fields_element)

{
    if ( new_fields_element == NULL )
	return DSV_DATA_OUT_OF_RANGE;
    else
    {
	xt_dsv_line_ptr->fields[c] = new_fields_element;
	return DSV_DATA_OK;
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lxtend
 *
 *  Description:
 *      Mutator for fields member in a xt_dsv_line_t structure.
 *      Use this function to set fields in a xt_dsv_line_t object
 *      from non-member functions.  This function copies the array pointed to
 *      by new_fields to xt_dsv_line_ptr->fields.
 *
 *  Arguments:
 *      xt_dsv_line_ptr    Pointer to the structure to set
 *      new_fields      The new value for fields
 *      array_size      Size of the fields array.
 *
 *  Returns:
 *      DSV_DATA_OK if the new value is acceptable and assigned
 *      DSV_DATA_OUT_OF_RANGE otherwise
 *
 *  Examples:
 *      xt_dsv_line_t      xt_dsv_line;
 *      char **         new_fields;
 *      size_t          array_size;
 *
 *      if ( xt_dsv_line_set_fields_cpy(&xt_dsv_line, new_fields, array_size)
 *              == DSV_DATA_OK )
 *      {
 *      }
 *
 *  See also:
 *      DSV_LINE_SET_FIELDS(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-05-27  gen-get-set Auto-generated from dsv-private.h
 ***************************************************************************/

int     xt_dsv_line_set_fields_cpy(xt_dsv_line_t *xt_dsv_line_ptr, char ** new_fields, size_t array_size)

{
    if ( new_fields == NULL )
	return DSV_DATA_OUT_OF_RANGE;
    else
    {
	size_t  c;
	
	// FIXME: Assuming all elements should be copied
	for (c = 0; c < array_size; ++c)
	    xt_dsv_line_ptr->fields[c] = new_fields[c];
	return DSV_DATA_OK;
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lxtend
 *
 *  Description:
 *      Mutator for delims member in a xt_dsv_line_t structure.
 *      Use this function to set delims in a xt_dsv_line_t object
 *      from non-member functions.  This function performs a direct
 *      assignment for scalar or pointer structure members.  If
 *      delims is a pointer, data previously pointed to should
 *      be freed before calling this function to avoid memory
 *      leaks.
 *
 *  Arguments:
 *      xt_dsv_line_ptr    Pointer to the structure to set
 *      new_delims      The new value for delims
 *
 *  Returns:
 *      DSV_DATA_OK if the new value is acceptable and assigned
 *      DSV_DATA_OUT_OF_RANGE otherwise
 *
 *  Examples:
 *      xt_dsv_line_t      xt_dsv_line;
 *      char *          new_delims;
 *
 *      if ( xt_dsv_line_set_delims(&xt_dsv_line, new_delims)
 *              == DSV_DATA_OK )
 *      {
 *      }
 *
 *  See also:
 *      (3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-05-27  gen-get-set Auto-generated from dsv-private.h
 ***************************************************************************/

int     xt_dsv_line_set_delims(xt_dsv_line_t *xt_dsv_line_ptr, char * new_delims)

{
    if ( new_delims == NULL )
	return DSV_DATA_OUT_OF_RANGE;
    else
    {
	xt_dsv_line_ptr->delims = new_delims;
	return DSV_DATA_OK;
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lxtend
 *
 *  Description:
 *      Mutator for an array element of delims member in a xt_dsv_line_t
 *      structure. Use this function to set xt_dsv_line_ptr->delims[c]
 *      in a xt_dsv_line_t object from non-member functions.
 *
 *  Arguments:
 *      xt_dsv_line_ptr    Pointer to the structure to set
 *      c               Subscript to the delims array
 *      new_delims_element The new value for delims[c]
 *
 *  Returns:
 *      DSV_DATA_OK if the new value is acceptable and assigned
 *      DSV_DATA_OUT_OF_RANGE otherwise
 *
 *  Examples:
 *      xt_dsv_line_t      xt_dsv_line;
 *      size_t          c;
 *      char *          new_delims_element;
 *
 *      if ( xt_dsv_line_set_delims_ae(&xt_dsv_line, c, new_delims_element)
 *              == DSV_DATA_OK )
 *      {
 *      }
 *
 *  See also:
 *      DSV_LINE_SET_DELIMS_AE(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-05-27  gen-get-set Auto-generated from dsv-private.h
 ***************************************************************************/

int     xt_dsv_line_set_delims_ae(xt_dsv_line_t *xt_dsv_line_ptr, size_t c, char  new_delims_element)

{
    if ( false )
	return DSV_DATA_OUT_OF_RANGE;
    else
    {
	xt_dsv_line_ptr->delims[c] = new_delims_element;
	return DSV_DATA_OK;
    }
}


/***************************************************************************
 *  Library:
 *      #include <xtend/dsv.h>
 *      -lxtend
 *
 *  Description:
 *      Mutator for delims member in a xt_dsv_line_t structure.
 *      Use this function to set delims in a xt_dsv_line_t object
 *      from non-member functions.  This function copies the array pointed to
 *      by new_delims to xt_dsv_line_ptr->delims.
 *
 *  Arguments:
 *      xt_dsv_line_ptr    Pointer to the structure to set
 *      new_delims      The new value for delims
 *      array_size      Size of the delims array.
 *
 *  Returns:
 *      DSV_DATA_OK if the new value is acceptable and assigned
 *      DSV_DATA_OUT_OF_RANGE otherwise
 *
 *  Examples:
 *      xt_dsv_line_t      xt_dsv_line;
 *      char *          new_delims;
 *      size_t          array_size;
 *
 *      if ( xt_dsv_line_set_delims_cpy(&xt_dsv_line, new_delims, array_size)
 *              == DSV_DATA_OK )
 *      {
 *      }
 *
 *  See also:
 *      DSV_LINE_SET_DELIMS(3)
 *
 *  History: 
 *  Date        Name        Modification
 *  2023-05-27  gen-get-set Auto-generated from dsv-private.h
 ***************************************************************************/

int     xt_dsv_line_set_delims_cpy(xt_dsv_line_t *xt_dsv_line_ptr, char * new_delims, size_t array_size)

{
    if ( new_delims == NULL )
	return DSV_DATA_OUT_OF_RANGE;
    else
    {
	// FIXME: Assuming char array is a null-terminated string
	strlcpy(xt_dsv_line_ptr->delims, new_delims, array_size);
	return DSV_DATA_OK;
    }
}
