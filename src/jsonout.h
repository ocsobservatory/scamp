/* write html report utilities */
#ifndef _JSONOUT_H_
#define _JSONOUT_H_

#include "fgroup.h"
#include "field.h"
#include <json.h>

/* not thread safe */
void JsonOut_set_data(fieldstruct**,int,fgroupstruct**,int);
void JsonOut_write();

#endif /* _JSONOUT_H_ */
