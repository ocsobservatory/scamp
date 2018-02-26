/*
 * Generate scamp metadata report output
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "htmlout.h"
#include "mustache/mustache.h"
#include "prefs.h"
#include "key.h"

extern pkeystruct key[];

static fieldstruct  **html_fields;
static fgroupstruct **html_fgroups;
static int html_nfields;
static int html_nfgroups;

void
HtmlOut_set_data(
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
HtmlOut_write(char *filename, json_object *main) 
{
	json_object *table, *val, *item, *elem;
	Template *template;
	FILE *fd;
	char *strval, *output;
    	Dict *dict, *sub;
	int i, j, tlen, ilen;

    	dict = Mstc_dict_new();
	if (json_object_object_get_ex(main, "AstroInstruments", &table)) {

		tlen  = json_object_array_length(table);
		for (i=0; i<tlen; i++) {
			item = json_object_array_get_idx(table, i);
			sub = Mstc_dict_addSectionItem(dict, "AstroInstruments");

			ilen = json_object_array_length(item);
			for (j=0; j<ilen; j++) {
				elem = json_object_array_get_idx(item, j);

				json_object_object_get_ex(elem, "name", &val);
				if (val == NULL)
					continue;

				strval = (char*) json_object_get_string(val);
				if (strcmp(strval, "Name")) {
					printf("have %s\n", strval);
					Mstc_dict_setValue(sub, "Name", "juju");
				} else if (strcmp(strval, "Index")) {
					printf("have %s\n", strval);
					Mstc_dict_setValue(sub, "Index", "juju");
				} else if (strcmp(strval, "NFields")) {
					printf("have %s\n", strval);
					Mstc_dict_setValue(sub, "NFields", "juju");
				} else if (strcmp(strval, "MagZeroPoint_Output")) {
					printf("have %s\n", strval);
					Mstc_dict_setValue(sub, "MagZeroPoint_Output", "juju");
				} else if (strcmp(strval, "NKeys")) {
					printf("have %s\n", strval);
					Mstc_dict_setValue(sub, "NKeys", "juju");
				} else if (strcmp(strval, "Keys")) {
					printf("have %s\n", strval);
					Mstc_dict_setValue(sub, "Keys", "juju");
				} else if (strcmp(strval, "DistPlot")) {
					printf("have %s\n", strval);
					Mstc_dict_setValue(sub, "DistPlot", "juju");
				} else {
					printf("have %s\n", strval);
				}
			}
		}
	}
 

	fd = fopen(filename, "w");
	if (!fd) {
		perror(filename);
	} else {
		template = Mstc_template_open("html/scamp_report.html.tpl");
		output = Mstc_expand(template, dict);
		fwrite(output, 1, strlen(output), fd);
		fclose(fd);
	}

	free(output);
	Mstc_template_close(template);
	Mstc_dict_free(dict);

}

void
HtmlOut_write2(char *filename)
{
    int i, j, k;
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

    Dict *dict = Mstc_dict_new();

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
        Mstc_dict_setFValue(sub, "flags", "%c%c", 
            field->headflag   == 1 ? 'H' : '-',
            field->photomflag == 1 ? 'P' : '-');
        Mstc_dict_setFValue(sub, "right_asc", "%.0f:%.0f:%.2f", 
            floor(field->meanwcspos[0] / 15),
            floor(fmod(field->meanwcspos[0]*4,   60)),
            floor(fmod(field->meanwcspos[0]*240, 60)));
    
        double dec = field->meanwcspos[1];
        char sign = '+';
        if (dec < 0) {
            sign = '-';
            dec = 0 - dec;
        }
        Mstc_dict_setFValue(sub, "dec", "%c%.0f:%.0f:%.1f", 
            sign,
            floor(dec),
            floor(fmod(dec * 60, 60)),
            floor(fmod(dec * 3600, 60)));
        
        Mstc_dict_setFValue(sub, "pix_scale", "%.4f''", 
            (field->meanwcsscale[0]*deg2arcsec + 
             field->meanwcsscale[1]*deg2arcsec) / 2);
        Mstc_dict_setFValue(sub, "radius", "%0.6g'", 
                                                field->maxradius*deg2arcmin);
        
        if (prefs.match_flag) {
            /* TODO MUSTACHE should find it in parent context */
            Mstc_dict_setShowSection(sub, "prefs_match_flag", true);
            Mstc_dict_setFValue(sub, "delta_pix_scale", "%0.4f",
                                                        field->match_dscale);
            Mstc_dict_setFValue(sub, "delta_pos_angle", "%0.6g°", 
                                                        field->match_dangle);
            Mstc_dict_setFValue(sub, "a_on_s_contrast", "%0.1f", 
                                                        field->match_asig);
            Mstc_dict_setFValue(sub, "delta_x", "%0.6g°",   field->match_dlng);
            Mstc_dict_setFValue(sub, "delta_y", "%0.6g°",   field->match_dlat);
            Mstc_dict_setFValue(sub, "x_on_y_contrast", "%0.1f", 
                                                            field->match_sig);
        }
        Mstc_dict_setFValue(sub, "x_2_int", "%.2f", (double) field->chi2_int);
        Mstc_dict_setFValue(sub, "x_2_int_h_s_on_n", "%.2f", (double)
                                                          field->chi2_int_hsn);
        Mstc_dict_setFValue(sub, "x_2_ref", "%.2f", (double) field->chi2_ref);
        Mstc_dict_setFValue(sub, "x_2_ref_h_s_on_n", "%.2f", 
                                                (double) field->chi2_ref_hsn);
        Mstc_dict_setFValue(sub, "mag_delta_zp", "%.3f", field->dmagzero);
    }


    if (html_nfgroups) {
        naxis   = html_fgroups[0]->naxis;
        lng     = html_fgroups[0]->lng;
        lat     = html_fgroups[0]->lat;
    } else {
        naxis = lng = lat = 0;
    }

    deg2arcsec = (lng!=lat) ? (DEG/ARCSEC) : 1.0;
    deg2arcmin = (lng!=lat) ? (DEG/ARCMIN) : 1.0;

    /* check if PNG plots are being produced */
#ifdef HAVE_PLPLOT
    char plotfilename[MAXCHAR];
    char *pstr;
    int nplot , pnplot, pngflag, pngindex;
    int *cp;
    QCALLOC(cp, int, prefs.ncplot_type);
    nplot = pnplot = pngflag = 0;
    for (i=0; i<prefs.ncplot_device; i++) {
        if (prefs.cplot_device[i] == CPLOT_PNG) {
            pngflag = 1;
            break;
        }
    }

    if (pngflag && (pngindex=cplot_check(CPLOT_ALLSKY)) != RETURN_ERROR) {
        /*
        strcpy(plotfilename, prefs.cplot_name[pngindex]);
        if (!(pstr = strrchr(plotfilename, '.')))
            pstr = plotfilename + strlen(plotfilename);
        sprintf(pstr, "_1.png");
        fprintf(file, "   <PARAM name=\"AllSkyPlot\" datatype=\"char\""
                " ucd=\"meta.id;meta.dataset\" value=\"%s\"/>\n",
                plotfilename);
        */
        cp[nplot++] = pngindex;
    }

    if (pngflag)
        Mstc_dict_setShowSection(dict, "have_plots", true);
#endif /* HAVE_PLPLOT */


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
    
    
    Template *template  = Mstc_template_open("html/scamp_report.html.tpl");
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
