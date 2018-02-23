/* write html report utilities */
#ifndef _HTML_H_
#define _HTML_H_

#include "fgroup.h"
#include "field.h"
#include <json.h>

/* not thread safe */
void Html_set_data(fieldstruct**,int,fgroupstruct**,int);
void Html_write(char *filename, json_object *obj);

#endif /* _HTML_H_ */
