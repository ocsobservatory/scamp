/* write html report utilities */
#ifndef _JSON_H_
#define _JSON_H_

#include "fgroup.h"
#include "field.h"
#include <json.h>

/* not thread safe */
void Json_set_data(fieldstruct**,int,fgroupstruct**,int);
json_object *Json_write(char *filename);
void Json_free(json_object *obj);

#endif /* _JSON_H_ */
