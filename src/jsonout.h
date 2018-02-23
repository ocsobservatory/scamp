/* write html report utilities */
#ifndef _JSONOUT_H_
#define _JSONOUT_H_

#include "fgroup.h"
#include "field.h"
#include <json.h>

/* not thread safe */
void JsonOut_set_data(fieldstruct**,int,fgroupstruct**,int);
json_object *JsonOut_generate();
void JsonOut_write(char *filename, json_object *js);
void JsonOut_free(json_object *obj);

#endif /* _JSONOUT_H_ */
