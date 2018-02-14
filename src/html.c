#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "html.h"
#include "mustache/mustache.h"
#include "prefs.h"

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
    int i, j;
    char buff[MAXCHAR];

    int naxis, lng, lat;
    if (html_nfields) {
        naxis = html_fields[0]->naxis;
        lng = html_fields[0]->lng;
        lat = html_fields[0]->lat;
    } else {
        naxis = lng = lat = 0;
    }

    double deg2arcsec, deg2arcmin;
    deg2arcsec = (lng!=lat) ? (DEG/ARCSEC) : 1.0;
    deg2arcmin = (lng!=lat) ? (DEG/ARCMIN) : 1.0;

    store     = Mstc_ressource_create();
    /*index     = Mstc_ressource_load(store, HTML_TPL);*/
    index     = Mstc_ressource_load(store, "html/scamp_report.html.tpl");
    ressource = Mstc_ressource_get(store, index);
    dict      = Mstc_dict_new();

    if (prefs.match_flag)
        Mstc_dict_setShowSection(dict, "prefs_match_flag", true);

    Dict *sub;
    /* table_summary */
    fieldstruct *field;
    for (i=0; i<html_nfields; i++) {
        field = html_fields[i];
        sub = Mstc_dict_addSectionItem(dict, "table_summary");

        snprintf(buff, MAXCHAR, "%d", field->fieldindex+1);
        Mstc_dict_setValue(sub, "num", buff);
        Mstc_dict_setValue(sub, "filename", field->rfilename);
        Mstc_dict_setValue(sub, "id", field->ident);
        snprintf(buff, MAXCHAR, "%d", field->nset);
        Mstc_dict_setValue(sub, "next", buff);
        snprintf(buff, MAXCHAR, "%d", field->nsample);
        Mstc_dict_setValue(sub, "ndet", buff);
        snprintf(buff, MAXCHAR, "%d", field->fgroup->no);
        Mstc_dict_setValue(sub, "g", buff);
        snprintf(buff, MAXCHAR, "A%d", field->astromlabel+1);
        Mstc_dict_setValue(sub, "a", buff);
        snprintf(buff, MAXCHAR, "P%d", field->photomlabel+1);
        Mstc_dict_setValue(sub, "p", buff);
        snprintf(buff, MAXCHAR, "%0.9f", field->epoch);
        Mstc_dict_setValue(sub, "date", buff);
        snprintf(buff, MAXCHAR, "%0.3f", field->expotime);
        Mstc_dict_setValue(sub, "exp_time", buff);
        snprintf(buff, MAXCHAR, "%0.2f", field->airmass);
        Mstc_dict_setValue(sub, "air_mass", buff);

        int pos = 0;
        for (j=0; j<field->naxis; j++) {
            snprintf(&buff[pos], MAXCHAR, "%.10g", field->meanwcspos[j]);
            pos += strlen(buff);
            snprintf(&buff[pos], MAXCHAR, " ");
            pos ++;
        }
        buff[pos-1] = '\0';
        Mstc_dict_setValue(sub, "right_asc", buff);
    
        pos = 0;
        for (j=0; j<field->naxis; j++) {
            pos += snprintf(&buff[pos], MAXCHAR - pos, "%.6g", field->meanwcsscale[j]*deg2arcsec);
            snprintf(&buff[pos], MAXCHAR - pos, " ");
            pos ++;
        }
        buff[pos-1] = '\0';
        Mstc_dict_setValue(sub, "dec", buff);
        
        snprintf(buff, MAXCHAR, "%0.6g", field->maxradius*deg2arcmin);
        Mstc_dict_setValue(sub, "radius", buff);
        snprintf(buff, MAXCHAR, "%0.6g", field->dmagzero);
        Mstc_dict_setValue(sub, "pix_scale", buff);
        
        if (prefs.match_flag) {
            snprintf(buff, MAXCHAR, "%0.6g", field->match_dscale);
            Mstc_dict_setValue(sub, "delta_pix_scale", buff);
            snprintf(buff, MAXCHAR, "%0.6g", field->match_dangle);
            Mstc_dict_setValue(sub, "delta_pos_angle", buff);
            snprintf(buff, MAXCHAR, "%0.6g", field->match_asig);
            Mstc_dict_setValue(sub, "a_on_s_contrast", buff);
            snprintf(buff, MAXCHAR, "%0.6g", field->match_dlng);
            Mstc_dict_setValue(sub, "delta_x", buff);
            snprintf(buff, MAXCHAR, "%0.6g", field->match_dlat);
            Mstc_dict_setValue(sub, "delta_y", buff);
            snprintf(buff, MAXCHAR, "%0.6g", field->match_sig);
            Mstc_dict_setValue(sub, "x_on_y_contrast", buff);
        }
    }

    /* astrometric instruments */
    for (i=0; i<prefs.nphotinstrustr; i++) {
        int len = fitsfind(prefs.astrinstrustr[i],  "END     ");
        int f2  = 0;

        for (j=0; j<html_nfgroups; j++) {
            int k;
            for (k=0; k<html_fgroups[j]->nfield;k++) {
                if (html_fgroups[j]->field[k]->astromlabel == i)
                    f2++;
            }
        }

        sub = Mstc_dict_addSectionItem(dict, "astrometric_instruments");

        snprintf(buff, MAXCHAR, "A%d", i+1);
        Mstc_dict_setValue(sub, "name", buff);

        snprintf(buff, MAXCHAR, "%d", i+1);
        Mstc_dict_setValue(sub, "id", buff);

        snprintf(buff, MAXCHAR, "%d", f2);
        Mstc_dict_setValue(sub, "nfields", buff);

        snprintf(buff, MAXCHAR, "%d", len);
        Mstc_dict_setValue(sub, "nkeywords", buff);

        int pos = 0;
        for (j=0; j<len; j++) {
            pos += snprintf(&buff[pos], MAXCHAR - pos, "%32.32s", prefs.astrinstrustr[i]+j*80);
            snprintf(&buff[pos], MAXCHAR - pos, ", ");
            pos+=2;
        }
        buff[pos] = '\0';
        Mstc_dict_setValue(sub, "keywords", buff);
    }


    /* photometric instruments */
    for (i=0; i<prefs.nphotinstrustr; i++) {
        int len = fitsfind(prefs.photinstrustr[i], "END     ");
        int f2 = 0;

        for (j=0; j < html_nfgroups; j++) {
            int k;
            for (k=0; k < html_fgroups[j]->nfield; k++) {
                if (html_fgroups[j]->field[k]->photomlabel == i)
                    f2++;
            }
        }

        sub = Mstc_dict_addSectionItem(dict, "photometric_instruments");
        snprintf(buff, MAXCHAR, "P%d", i+1);
        Mstc_dict_setValue(sub, "name", buff);
        snprintf(buff, MAXCHAR, "%d", i+1);
        Mstc_dict_setValue(sub, "index", buff);
        snprintf(buff, MAXCHAR, "%d", f2);
        Mstc_dict_setValue(sub, "nfields", buff);
        snprintf(buff, MAXCHAR, "%.6g", prefs.magzero_out[i]);
        Mstc_dict_setValue(sub, "out_ZP", buff);
        snprintf(buff, MAXCHAR, "%d", len);
        Mstc_dict_setValue(sub, "nkeywords", buff);

        int pos = 0;
        for (j=0; j<len; j++) {
            pos += snprintf(&buff[pos], MAXCHAR - pos, "%32.32s", prefs.photinstrustr[i]+j*80);
            snprintf(&buff[pos], MAXCHAR - pos, ", ");
            pos+=2;
        }
        buff[pos] = '\0';
        Mstc_dict_setValue(sub, "keywords", buff);

    }
    
    /* command line */
    int cpos = 0;
    for (i=0; i<prefs.ncommand_line; i++) {
        cpos += snprintf(&buff[cpos], MAXCHAR - cpos, "%s", prefs.command_line[i]);
        snprintf(&buff[cpos], MAXCHAR - cpos, " ");
        cpos++;
    }
    buff[cpos] = '\0';
    Mstc_dict_setValue(dict, "command_line", buff);

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
