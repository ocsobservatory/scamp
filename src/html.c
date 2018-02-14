#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "html.h"
#include "mustache/mustache.h"

static fieldstruct  **html_fields;
static fgroupstruct **html_fgroups;
static int html_nfields;
static int html_nfgroups;

void
Html_set_data(
    fieldstruct     **fields, 
    int             nfields,
    fgroupstruct    **fgroups,
    int             nfgroups)
{

    html_fields = fields;
    html_fgroups = fgroups;
    html_nfields = nfields;
    html_nfgroups = nfgroups;
}

void
Html_write(char *filename)
{
    RessourceStore   *store;
    int              index;
    Ressource        *ressource;
    Dict             *dict;
    ExpandOutput     *exp;

    store     = Mstc_ressource_create();
    index     = Mstc_ressource_load(store, "html/index.html.mustache");
    ressource = Mstc_ressource_get(store, index);
    dict      = Mstc_dict_new();


    /* TODO populate the dict */


    exp = Mstc_expand_init(6000);
    Mstc_expand_run(ressource, dict, exp);

    FILE *out = fopen(filename, "w");
    if (!out) {
        perror(filename);
    } else {
        fwrite(exp->out, 1, strlen(exp->out), out);
    }

    Mstc_ressource_free(store);
    Mstc_dict_free(dict);
    Mstc_expand_free(exp);
}
