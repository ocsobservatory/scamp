/* write html report utilities */
#ifndef _JSON_H_
#define _JSON_H_

#include "fgroup.h"
#include "field.h"

/* not thread safe */
void Json_set_data(fieldstruct**,int,fgroupstruct**,int);
void Json_write(char *filename);

#endif /* _JSON_H_ */
