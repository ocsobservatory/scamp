/*
 * Generate scamp metadata report output
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "html.h"
#include "mustache/mustache_api.h"
#include "prefs.h"
#include "key.h"

extern pkeystruct key[];

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
    Template        *template;
    Dict             *dict;
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

    template  = Mstc_template_open("html/scamp_report.html.tpl");
    dict      = Mstc_dict_new();

    if (prefs.match_flag)
        Mstc_dict_setShowSection(dict, "prefs_match_flag", true);

    Dict *sub;

    /* table_summary */
    fieldstruct *field;
    for (i=0; i<html_nfields; i++) {
        field = html_fields[i];
        sub = Mstc_dict_addSectionItem(dict, "table_summary");

        Mstc_dict_setFValue(sub, "num", "%d", field->fieldindex+1);
        Mstc_dict_setValue(sub, "filename", field->rfilename);
        Mstc_dict_setValue(sub, "id", field->ident);
        Mstc_dict_setFValue(sub, "next", "%d", field->nset);
        Mstc_dict_setFValue(sub, "ndet", "%d", field->nsample);
        Mstc_dict_setFValue(sub, "g", "%d", field->fgroup->no);
        Mstc_dict_setFValue(sub, "a", "A%d", field->astromlabel+1);
        Mstc_dict_setFValue(sub, "p", "P%d", field->photomlabel+1);
        Mstc_dict_setFValue(sub, "date", "%0.9f", field->epoch);
        Mstc_dict_setFValue(sub, "exp_time", "%0.3f", field->expotime);
        Mstc_dict_setFValue(sub, "air_mass", "%0.2f", field->airmass);

        int pos = 0;
        for (j=0; j<field->naxis; j++)
            pos += snprintf(&buff[pos], MAXCHAR - pos, "%.10g ",
                                                         field->meanwcspos[j]);
        buff[pos-1] = '\0';

        Mstc_dict_setValue(sub, "right_asc", buff);
    
        pos = 0;
        for (j=0; j<field->naxis; j++)
            pos += snprintf(&buff[pos], MAXCHAR - pos, "%.6g ", 
                                            field->meanwcsscale[j]*deg2arcsec);
        buff[pos-1] = '\0';

        Mstc_dict_setValue(sub, "dec", buff);
        
        Mstc_dict_setFValue(sub, "radius", "%0.6g", field->maxradius*deg2arcmin);
        Mstc_dict_setFValue(sub, "pix_scale", "%0.6g", field->dmagzero);
        
        if (prefs.match_flag) {
            Mstc_dict_setFValue(sub, "delta_pix_scale", "%0.6g", field->match_dscale);
            Mstc_dict_setFValue(sub, "delta_pos_angle", "%0.6g", field->match_dangle);
            Mstc_dict_setFValue(sub, "a_on_s_contrast", "%0.6g", field->match_asig);
            Mstc_dict_setFValue(sub, "delta_x", "%0.6g", field->match_dlng);
            Mstc_dict_setFValue(sub, "delta_y", "%0.6g", field->match_dlat);
            Mstc_dict_setFValue(sub, "x_on_y_contrast", "%0.6g", field->match_sig);
        }
    }


    /* group properties */
    for (i=0; i<html_nfgroups; i++) {
        fgroupstruct *fgroup = html_fgroups[i];
        sub = Mstc_dict_addSectionItem(dict, "group_properties");
        Mstc_dict_setFValue(sub, "gname", "G%d", i+1);
        Mstc_dict_setFValue(sub, "id", "%d", i+1);
        Mstc_dict_setFValue(sub, "nfields", "%d", fgroup->nfield);
/*
        Mstc_dict_setFValue(sub, "r_asc", "h");
        Mstc_dict_setFValue(sub, "dec", "h");
        Mstc_dict_setFValue(sub, "pix_scale", "h");
        Mstc_dict_setFValue(sub, "max_radius", "h");
        Mstc_dict_setFValue(sub, "astr_ref_cat", "h");
        Mstc_dict_setFValue(sub, "astr_ref_band", "h");
        Mstc_dict_setFValue(sub, "astr_qint", "h");
        Mstc_dict_setFValue(sub, "astr_pint", "h");
        Mstc_dict_setFValue(sub, "astr_x2int", "h");
        Mstc_dict_setFValue(sub, "astr_nint", "h");
        Mstc_dict_setFValue(sub, "astr_qint_hSN", "h");
        Mstc_dict_setFValue(sub, "astr_pint_hSH", "h");
        Mstc_dict_setFValue(sub, "astr_x2int_hSN", "h");
        Mstc_dict_setFValue(sub, "astr_nint_hSH", "h");
        Mstc_dict_setFValue(sub, "astr_dRAref_dDECref", "h");
        Mstc_dict_setFValue(sub, "astr_qref", "h");
        Mstc_dict_setFValue(sub, "astr_pref", "h");
        Mstc_dict_setFValue(sub, "astr_x2ref", "h");
        Mstc_dict_setFValue(sub, "astr_nref", "h");
        Mstc_dict_setFValue(sub, "astr_dRAref_dDECref_hSN", "h");
        Mstc_dict_setFValue(sub, "astr_qref_hSN", "h");
        Mstc_dict_setFValue(sub, "astr_pref_hSN", "h");
        Mstc_dict_setFValue(sub, "astr_x2ref_hSN", "h");
        Mstc_dict_setFValue(sub, "astr_Nref_hSN", "h");
        Mstc_dict_setFValue(sub, "pht_instru", "h");
        Mstc_dict_setFValue(sub, "pht_qint", "h");
        Mstc_dict_setFValue(sub, "pht_x2int", "h");
        Mstc_dict_setFValue(sub, "pht_qint_hSN", "h");
        Mstc_dict_setFValue(sub, "pht_x2int_hSN", "h");
        Mstc_dict_setFValue(sub, "pht_Nint_hSN", "h");
        Mstc_dict_setFValue(sub, "pht_qref", "h");
        Mstc_dict_setFValue(sub, "pht_x2ref", "h");
        Mstc_dict_setFValue(sub, "pht_Nref", "h");
        Mstc_dict_setFValue(sub, "pht_qref_hSN", "h");
        Mstc_dict_setFValue(sub, "pht_x2ref_hSN", "h");
        Mstc_dict_setFValue(sub, "pht_Nref_hSN", "h");
*/
        
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

        Mstc_dict_setFValue(sub, "name", "A%d", i+1);
        Mstc_dict_setFValue(sub, "id", "%d", i+1);
        Mstc_dict_setFValue(sub, "nfields", "%d", f2);
        Mstc_dict_setFValue(sub, "nkeywords", "%d", len);

        int pos = 0;
        for (j=0; j<len; j++)
            pos += snprintf(&buff[pos], MAXCHAR - pos, "%32.32s, ", 
                                                  prefs.astrinstrustr[i]+j*80);
        buff[pos - 2] = '\0';
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
        Mstc_dict_setFValue(sub, "name", "P%d", i+1);
        Mstc_dict_setFValue(sub, "index", "%d", i+1);
        Mstc_dict_setFValue(sub, "nfields", "%d", f2);
        Mstc_dict_setFValue(sub, "out_ZP", "%.6g", prefs.magzero_out[i]);
        Mstc_dict_setFValue(sub, "nkeywords", "%d", len);

        int pos = 0;
        for (j=0; j<len; j++)
            pos += snprintf(&buff[pos], MAXCHAR - pos, "%32.32s, ", 
                                                  prefs.photinstrustr[i]+j*80);
        buff[pos-2] = '\0';
        Mstc_dict_setValue(sub, "keywords", buff);

    }
    

    /* command line */
    int cpos = 0;
    for (i=0; i<prefs.ncommand_line; i++)
        cpos += snprintf(&buff[cpos], MAXCHAR - cpos, "%s ", 
                                                        prefs.command_line[i]);
    buff[cpos - 1] = '\0';

    Mstc_dict_setValue(dict, "command_line", buff);

    Mstc_dict_setValue(dict, "config_file_name", prefs.prefs_name);

    /* configuration */
    for (i=0; key[i].name[0]; i++) {
        sub = Mstc_dict_addSectionItem(dict, "scamp_config");
        Mstc_dict_setValue(sub, "key", key[i].name);
        switch (key[i].type) {
            case P_FLOAT:
                Mstc_dict_setFValue(sub, "value", "%f", *((float*)key[i].ptr));
                break;
            case P_INT:
                Mstc_dict_setFValue(sub, "value", "%i", *((int*)key[i].ptr));
                break;
            case P_STRING:
                Mstc_dict_setValue(sub, "value", key[i].ptr);
                break;
            case P_BOOL:
                Mstc_dict_setFValue(sub, "value", "%c", 
                                              *((int*)key[i].ptr) ? 'T' : 'F');
                break;
            case P_KEY:
                Mstc_dict_setValue(sub, "value", 
                                          key[i].keylist[*((int*)key[i].ptr)]);
                break;
            case P_FLOATLIST:
                cpos = 0;
                for (j=0; j< *(key[i].nlistptr); j++)
                    cpos += snprintf(&buff[cpos], MAXCHAR - cpos, "%f, ", 
                                ((double*)key[i].ptr)[j]);
                buff[cpos-2] = '\0';
                Mstc_dict_setValue(sub, "value", buff);
                break;
            case P_INTLIST:
                cpos = 0;
                for (j=0; j< *(key[i].nlistptr); j++)
                    cpos += snprintf(&buff[cpos], MAXCHAR - cpos, "%i, ", 
                                ((int*)key[i].ptr)[j]);
                buff[cpos-2] = '\0';
                Mstc_dict_setValue(sub, "value", buff);
                break;
            case P_BOOLLIST:
                cpos = 0;
                for (j=0; j< *(key[i].nlistptr); j++)
                    cpos += snprintf(&buff[cpos], MAXCHAR - cpos, "%c, ", 
                                ((int*)key[i].ptr)[j] ? 'T' : 'F');
                buff[cpos-2] = '\0';
                Mstc_dict_setValue(sub, "value", buff);
                break;
            case P_STRINGLIST:
                cpos = 0;
                for (j=0; j< *(key[i].nlistptr); j++)
                    cpos += snprintf(&buff[cpos], MAXCHAR - cpos, "%s, ", 
                                ((char**)key[i].ptr)[j]);
                buff[cpos-2] = '\0';
                Mstc_dict_setValue(sub, "value", buff);
                break;
            case P_KEYLIST:
                cpos = 0;
                for (j=0; j< *(key[i].nlistptr); j++)
                    cpos += snprintf(&buff[cpos], MAXCHAR - cpos, "%s, ", 
                                key[i].keylist[((int*)key[i].ptr)[j]]);
                buff[cpos-2] = '\0';
                Mstc_dict_setValue(sub, "value", buff);
                break;

        }
        
    }
    
    
    char *output = Mstc_expand(template, dict);

    FILE *fd = fopen(filename, "w");
    if (!fd) {
        perror(filename);
    } else {
        fwrite(output, 1, strlen(output), fd);
        fclose(fd);
    }

    free(output);
    Mstc_template_close(template);
    Mstc_dict_free(dict);
}
