/* write html report utilities */
#ifndef _HTMLOUT_H_
#define _HTMLOUT_H_

#include "fgroup.h"
#include "field.h"
#include <json.h>

/* not thread safe */
void HtmlOut_set_data(fieldstruct**,int,fgroupstruct**,int);
void HtmlOut_write(char *filename, json_object *obj);

#endif /* _HTMLOUT_H_ */
