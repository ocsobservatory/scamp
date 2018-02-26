/*
 * Generate scamp metadata report output
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "key.h"
#include "prefs.h"
#include "jsonout.h"

extern pkeystruct key[];

static fieldstruct  **json_fields;
static fgroupstruct **json_fgroups;
static int json_nfields;
static int json_nfgroups;

void
JsonOut_set_data(
        fieldstruct  **fields,
        int          nfields,
        fgroupstruct **fgroups,
        int          nfgroups)
{

    json_fields   = fields;
    json_fgroups  = fgroups;
    json_nfields  = nfields;
    json_nfgroups = nfgroups;
}

static json_object*
new_json_object(
        char *name,
        char *type,
        char *unit,
        char *ucd)
{
    json_object *o = json_object_new_object();
    json_object_object_add(o, "name", json_object_new_string(name));
    json_object_object_add(o, "datatype", json_object_new_string(type));
    json_object_object_add(o, "ucd",  json_object_new_string(ucd));
    if (unit)
        json_object_object_add(o, "unit", json_object_new_string(unit));

    return o;
}

#ifdef HAVE_PLPLOT
static char *plplot_astrinst_names[] = {
    "DistPlot",
    "RefSysPlot",
    "PixErr1DimPlot",
    "SubPixErr1DimPlot",
    "ShearPlot"
};
static cplotenum next_astrinst_plot = CPLOT_DISTORT;
static int
get_next_astrinst_plot(char**name) {
    int index;
    switch (next_astrinst_plot) {
        case CPLOT_DISTORT:
            next_astrinst_plot = CPLOT_REFSYSMAP2D;
            if ((index=cplot_check(CPLOT_DISTORT)) != RETURN_ERROR) {
                *name = plplot_astrinst_names[0];
                return index;
            } else {
                return get_next_astrinst_plot(name);
            }
        case CPLOT_REFSYSMAP2D:
            next_astrinst_plot = CPLOT_PIXERROR1D;
            if ((index=cplot_check(CPLOT_REFSYSMAP2D)) != RETURN_ERROR) {
                *name = plplot_astrinst_names[1];
                return index;
            } else {
                return get_next_astrinst_plot(name);
            }

        case CPLOT_PIXERROR1D:
            next_astrinst_plot = CPLOT_SUBPIXERROR1D;
            if ((index=cplot_check(CPLOT_PIXERROR1D)) != RETURN_ERROR) {
                *name = plplot_astrinst_names[2];
                return index;
            } else {
                return get_next_astrinst_plot(name);
            }
        case CPLOT_SUBPIXERROR1D:
            next_astrinst_plot = CPLOT_SHEAR;
            if ((index=cplot_check(CPLOT_SUBPIXERROR1D)) != RETURN_ERROR) {
                *name = plplot_astrinst_names[3];
                return index;
            } else {
                return get_next_astrinst_plot(name);
            }
        case CPLOT_SHEAR:
            next_astrinst_plot = CPLOT_NONE;
            if ((index=cplot_check(CPLOT_SHEAR)) != RETURN_ERROR) {
                *name = plplot_astrinst_names[4];
                return index;
            } else {
                return get_next_astrinst_plot(name);
            }
        default:
            return -1;
     }
}

static char *plplot_fgroup_names[] = {
    "FgroupsPlot",
    "Chi2Plot",
    "IntErr1DimPlot",
    "IntErr2DimPlot",
    "RefErr1DimPlot",
    "RefErr2DimPlot",
    "PhotErrPlot",
    "PhotErrMagPlot",
    "PhotZPPlot",
    "PhotZP3Plot",
    "ColShiftPlot",
    "RefPropPlot"
};
static cplotenum next_fgroup_plot = CPLOT_FGROUPS;
static int
get_next_fgroup_plot(char**name) {
    int index;
    switch (next_fgroup_plot) {
        case CPLOT_FGROUPS:
            next_fgroup_plot = CPLOT_CHI2;
            if ((index=cplot_check(CPLOT_FGROUPS)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[0];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_CHI2:
            next_fgroup_plot = CPLOT_ADERROR1D;
            if ((index=cplot_check(CPLOT_CHI2)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[1];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }

        case CPLOT_ADERROR1D:
            next_fgroup_plot = CPLOT_ADERROR2D;
            if ((index=cplot_check(CPLOT_ADERROR1D)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[2];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_ADERROR2D:
            next_fgroup_plot = CPLOT_REFERROR1D;
            if ((index=cplot_check(CPLOT_ADERROR2D)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[3];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_REFERROR1D:
            next_fgroup_plot = CPLOT_REFERROR2D;
            if ((index=cplot_check(CPLOT_REFERROR1D)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[4];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_REFERROR2D:
            next_fgroup_plot = CPLOT_PHOTERROR;
            if ((index=cplot_check(CPLOT_REFERROR2D)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[5];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_PHOTERROR:
            next_fgroup_plot = CPLOT_PHOTERRORVSMAG;
            if ((index=cplot_check(CPLOT_PHOTERROR)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[6];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_PHOTERRORVSMAG:
            next_fgroup_plot = CPLOT_PHOTZP;
            if ((index=cplot_check(CPLOT_PHOTERRORVSMAG)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[7];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_PHOTZP:
            next_fgroup_plot = CPLOT_PHOTZP3D;
            if ((index=cplot_check(CPLOT_PHOTZP)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[8];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_PHOTZP3D:
            next_fgroup_plot = CPLOT_ASTRCOLSHIFT1D;
            if ((index=cplot_check(CPLOT_PHOTZP3D)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[9];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_ASTRCOLSHIFT1D:
            next_fgroup_plot = CPLOT_REFPROP;
            if ((index=cplot_check(CPLOT_ASTRCOLSHIFT1D)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[10];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        case CPLOT_REFPROP:
            next_fgroup_plot = CPLOT_NONE;
            if ((index=cplot_check(CPLOT_REFPROP)) != RETURN_ERROR) {
                *name = plplot_fgroup_names[11];
                return index;
            } else {
                return get_next_fgroup_plot(name);
            }
        default:
            return -1;
    }
}
#endif /* HAVE_PLPLOT */

json_object*
JsonOut_generate()
{
    json_object *main_obj = json_object_new_object();
    json_object *tables = json_object_new_object();

    json_object *o, *p, *item;
    int i, j;

    char strbuff[MAXCHAR];

    char *psuser, *pshost, *pspath;
    psuser = pshost = pspath = NULL;
#ifdef HAVE_GETENV
    if (!(psuser=getenv("USERNAME")))   /* Cygwin,... */
        psuser = getenv("LOGNAME");     /* Linux,... */
    pspath = getenv("PWD");
    pshost = getenv("HOSTNAME");
#endif /* HAVE_GETENV */

    /* soft meta */
    json_object *soft = json_object_new_array();

    o = new_json_object("Name", "string", NULL, "meta.title;meta.software");
    json_object_object_add(o, "value", json_object_new_string(BANNER));
    json_object_array_add(soft, o);

    o = new_json_object("Version", "string", NULL, "meta.version;meta.software");
    json_object_object_add(o, "value", json_object_new_string(MYVERSION));
    json_object_array_add(soft, o);

    o = new_json_object("Url", "string", NULL, "meta.ref.url;meta.software");
    json_object_object_add(o, "value", json_object_new_string(WEBSITE));
    json_object_array_add(soft, o);

    o = new_json_object("Author", "string", NULL, "meta.bib.author;meta.software");
    json_object_object_add(o, "value", json_object_new_string("Emmanuel Bertin"));
    json_object_array_add(soft, o);

    o = new_json_object("Ref", "string", NULL, "meta.bib.bibcode;meta.software");
    json_object_object_add(o, "value", json_object_new_string("2006ASPC..351..112B"));
    json_object_array_add(soft, o);

    o = new_json_object("NThreads", "int", NULL, "meta.number;meta.software");
    json_object_object_add(o, "value", json_object_new_int(prefs.nthreads));
    json_object_array_add(soft, o);

    o = new_json_object("Date", "string", NULL, "time.end;meta.software");
    json_object_object_add(o, "value", json_object_new_string(prefs.sdate_end));
    json_object_array_add(soft, o);

    o = new_json_object("Time", "string", NULL, "time.end;meta.software");
    json_object_object_add(o, "value", json_object_new_string(prefs.stime_end));
    json_object_array_add(soft, o);

    o = new_json_object("Duration", "float", NULL, "time.duration;meta.software");
    json_object_object_add(o, "value", json_object_new_double(prefs.time_diff));
    json_object_array_add(soft, o);

    if (psuser) {
        o = new_json_object("User", "string", NULL, "meta.curation");
        json_object_object_add(o, "value", json_object_new_string(psuser));
        json_object_array_add(soft, o);
    }

    if (pshost) {
        o = new_json_object("Host", "string", NULL, "meta.curation");
        json_object_object_add(o, "value", json_object_new_string(pshost));
        json_object_array_add(soft, o);
    }

    if (pspath) {
        o = new_json_object("Path", "string", NULL, "meta.dataset");
        json_object_object_add(o, "value", json_object_new_string(pspath));
        json_object_array_add(soft, o);
    }

    json_object_object_add(main_obj, "Software", soft);

    /* fields */
    int naxis, lng, lat;
    if (json_nfields) {
        naxis = json_fields[0]->naxis;
        lng = json_fields[0]->lng;
        lat = json_fields[0]->lat;
    } else {
        naxis = lng = lat = 0;
    }

    double deg2arcsec = (lng!=lat) ? (DEG/ARCSEC) : 1.0;
    double deg2arcmin = (lng!=lat) ? (DEG/ARCMIN) : 1.0;

#ifdef HAVE_PLPLOT
    int nplot, pnplot, pngflag, pngindex;
    int *cp;
    char **cp_names;
    char plotfilename[MAXCHAR];
    char *pstr;
    nplot = pnplot = pngflag = 0;
    QCALLOC(cp,         int,    prefs.ncplot_type);
    QCALLOC(cp_names,   char*,  prefs.ncplot_type);
    for (i=0; i<prefs.ncplot_device; i++) {
        if ((prefs.cplot_device[i] == CPLOT_PNG)) {
            pngflag = 1;
            break;
        }
    }

    /* Check-plots */
    if (pngflag && (pngindex=cplot_check(CPLOT_ALLSKY)) != RETURN_ERROR)
    {
        strcpy(plotfilename, prefs.cplot_name[pngindex]);
        if (!(pstr = strrchr(plotfilename, '.')))
            pstr = plotfilename+strlen(plotfilename);
        sprintf(pstr, "_1.png");

        o = new_json_object("AllSkyPlot", "string", NULL, "meta.id;meta.dataset");
        json_object_object_add(o, "value", json_object_new_string(plotfilename));
        json_object_object_add(main_obj, "AllSkyPlot", o);

        cp[nplot++] = pngindex;
    }
#endif /* HAVE_PLPLOT */

    json_object *field_array = json_object_new_array();
    for (i=0; i<json_nfields; i++) {
        fieldstruct *field = json_fields[i];
        json_object *field_row = json_object_new_array();

        o = new_json_object("Catalog_Number", "int", NULL, "meta.record;meta.table;meta.file");
        json_object_object_add(o, "value", json_object_new_int(field->fieldindex + 1));
        json_object_array_add(field_row, o);

        o = new_json_object("Catalog_Name", "string", NULL, "meta.id;meta.table;meta.file");
        json_object_object_add(o, "value", json_object_new_string(field->rfilename));
        json_object_array_add(field_row, o);

        o = new_json_object("Image_Ident", "string", NULL, "meta.id;obs.field");
        json_object_object_add(o, "value", json_object_new_string(field->ident));
        json_object_array_add(field_row, o);

        o = new_json_object("NExtensions", "int", NULL, "meta.record");
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_array_add(field_row, o);

        o = new_json_object("NAxis", "int", NULL, "pos.wcs.naxis");
        json_object_object_add(o, "value", json_object_new_int(field->naxis));
        json_object_array_add(field_row, o);

        o = new_json_object("Lng_Axis", "int", NULL, "meta.id;pos.eq.ra");
        json_object_object_add(o, "value", json_object_new_int(field->lng));
        json_object_array_add(field_row, o);

        o = new_json_object("Lat_Axis", "int", NULL, "meta.id;pos.eq.dec");
        json_object_object_add(o, "value", json_object_new_int(field->lat));
        json_object_array_add(field_row, o);

        o = new_json_object("Ext_Header", "boolean", NULL, "meta.code");
        json_object_object_add(o, "value", json_object_new_boolean(field->headflag));
        json_object_array_add(field_row, o);

        o = new_json_object("NDetect", "int", NULL, "meta.number;src");
        json_object_object_add(o, "value", json_object_new_int(field->nsample));
        json_object_array_add(field_row, o);

        o = new_json_object("Group", "int", NULL, "meta.id.parent;meta.dataset");
        json_object_object_add(o, "value", json_object_new_int(field->fgroup->no));
        json_object_array_add(field_row, o);

        o = new_json_object("Astr_Instrum", "string", NULL, "meta.id.parent;meta.dataset");
        snprintf(strbuff, MAXCHAR, "A%d", field->astromlabel+1);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_row, o);

        o = new_json_object("Phot_Instrum", "string", NULL, "meta.id.parent;meta.dataset");
        snprintf(strbuff, MAXCHAR, "P%d", field->photomlabel+1);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_row, o);

        o = new_json_object("Photom_Flag", "boolean", NULL, "meta.code;phot");
        json_object_object_add(o, "value", json_object_new_boolean(field->photomflag));
        json_object_array_add(field_row, o);

        o = new_json_object("Photom_Link", "boolean", NULL, "meta.code;phot");
        json_object_object_add(o, "value", json_object_new_boolean(field->photomflag));
        json_object_array_add(field_row, o);

        o = new_json_object("Observation_Date", "double", "yr", "time.epoch;obs.field");
        json_object_object_add(o, "value", json_object_new_double(field->epoch));
        json_object_array_add(field_row, o);

        o = new_json_object("Exposure_Time", "float", NULL, "time.duration;obs.exposure");
        json_object_object_add(o, "value", json_object_new_double(field->expotime));
        json_object_array_add(field_row, o);

        o = new_json_object("AirMass", "float", NULL, "obs.airMass");
        json_object_object_add(o, "value", json_object_new_double(field->airmass));
        json_object_array_add(field_row, o);

        o = new_json_object("Field_Coordinates", "double array", "%s", "pos.eq.ra;pos.eq.dec;obs.field");
        p = json_object_new_array();
        for (j=0; j<field->naxis; j++)
            json_object_array_add(p, json_object_new_double(field->meanwcspos[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(field_row, o);

        o = new_json_object("Pixel_Scale", "float array", "%s", "instr.scale;instr.pixel;stat.mean");
        p = json_object_new_array();
        for (j=1; j<field->naxis; j++)
            json_object_array_add(p, json_object_new_double(field->meanwcsscale[j] * deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(field_row, o);

        o = new_json_object("Max_Radius", "float", "%s", "phys.size.radius");
        json_object_object_add(o, "value", json_object_new_double(field->maxradius*deg2arcmin));
        json_object_array_add(field_row, o);

        o = new_json_object("ZeroPoint_Corr", "float", "mag", "phot.mag;phot.calib;arith.zp");
        json_object_object_add(o, "value", json_object_new_double(field->dmagzero));
        json_object_array_add(field_row, o);

        if (prefs.match_flag) {
            o = new_json_object("DPixelScale", "float", NULL, "instr.scale;instr.pixel;arith.ratio");
            json_object_object_add(o, "value", json_object_new_double(field->match_dscale));
            json_object_array_add(field_row, o);

            o = new_json_object("DPosAngle", "float", "deg", "pos.posAng;obs.image;arith.diff");
            json_object_object_add(o, "value", json_object_new_double(field->match_dangle));
            json_object_array_add(field_row, o);

            o = new_json_object("AS_Contrast", "float", NULL, "stat.correlation;arith.ratio");
            json_object_object_add(o, "value", json_object_new_double(field->match_asig));
            json_object_array_add(field_row, o);

            o = new_json_object("DX", "float", "deg", "pos.eq.ra;arith.diff");
            json_object_object_add(o, "value", json_object_new_double(field->match_dlng));
            json_object_array_add(field_row, o);

            o = new_json_object("DY", "float", "deg", "pos.eq.dec;arith.diff");
            json_object_object_add(o, "value", json_object_new_double(field->match_dlat));
            json_object_array_add(field_row, o);

            o = new_json_object("XY_Contrast", "float", NULL, "stat.correlation;arith.ratio");
            json_object_object_add(o, "value", json_object_new_double(field->match_sig));
            json_object_array_add(field_row, o);

            o = new_json_object("Shear", "float", NULL, "phys.size.axisRatio;obs.image");
            json_object_object_add(o, "value", json_object_new_double(field->match_shear));
            json_object_array_add(field_row, o);

            o = new_json_object("Shear_PosAngle", "float", "deg", "pos.posAng;obs.image");
            json_object_object_add(o, "value", json_object_new_double(field->match_sangle));
            json_object_array_add(field_row, o);
        }

        o = new_json_object("Chi2_Internal", "float", NULL, "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(field->chi2_int));
        json_object_array_add(field_row, o);

        o = new_json_object("NDeg_Internal", "int", NULL, "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(field->nchi2_int));
        json_object_array_add(field_row, o);

        o = new_json_object("Chi2_Internal_HighSN", "float", NULL, "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(field->chi2_int_hsn));
        json_object_array_add(field_row, o);

        o = new_json_object("NDeg_Internal_HighSN", "int", NULL, "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(field->nchi2_int_hsn));
        json_object_array_add(field_row, o);

        o = new_json_object("AstromOffset_Reference", "float array", "%s", "pos.eq.ra;pos.eq.dec;arith.diff;obs.field");
        p = json_object_new_array();
        for (j=0; j<field->naxis; j++)
            json_object_array_add(p, json_object_new_double(field->offset_ref[j] * deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(field_row, o);

        o = new_json_object("AstromSigma_Reference", "float array", "%s", "stat.stdev;pos.eq;obs.field");
        p = json_object_new_array();
        for (j=0; j<field->naxis; j++)
            json_object_array_add(p, json_object_new_double(field->sig_referr[j] * deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(field_row, o);

        o = new_json_object("AstromCorr_Reference", "float", NULL, "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(field->sig_corr_ref));
        json_object_array_add(field_row, o);

        o = new_json_object("Chi2_Reference", "float", NULL, "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(field->chi2_ref));
        json_object_array_add(field_row, o);

        o = new_json_object("NDeg_Reference", "int", NULL, "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(field->nchi2_ref));
        json_object_array_add(field_row, o);

        o = new_json_object("AstromOffset_Reference_HighSN", "float array", "%s", "pos.eq.ra;pos.eq.dec;arith.diff;obs.field");
        p = json_object_new_array();
        for (j=0; j<field->naxis; j++)
            json_object_array_add(p, json_object_new_double(field->offset_ref_hsn[j] * deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(field_row, o);

        o = new_json_object("AstromSigma_Reference_HighSN", "float array", "%s", "stat.stdev;pos.eq;obs.field");
        p = json_object_new_array();
        for (j=0; j<field->naxis; j++)
            json_object_array_add(p, json_object_new_double(field->sig_referr_hsn[j] * deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(field_row, o);

        o = new_json_object("AstromCorr_Reference_HighSN", "float", NULL, "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double((double)field->sig_corr_ref_hsn));
        json_object_array_add(field_row, o);

        o = new_json_object("Chi2_Reference_HighSN", "float", NULL, "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(field->chi2_ref_hsn));
        json_object_array_add(field_row, o);

        o = new_json_object("NDeg_Reference_HighSN", "int", NULL, "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(field->nchi2_ref_hsn));
        json_object_array_add(field_row, o);

        json_object_array_add(field_array, field_row);
    }

    json_object_object_add(main_obj, "Fields", field_array);


    /* fgroups */

#ifdef HAVE_PLPLOT
    int plot_index;
    pnplot = i = nplot;

    while ((plot_index = get_next_fgroup_plot(&cp_names[i])) >= 0) {
        cp[nplot++] = plot_index;
        i++;
    }
#endif /* HAVE_PLPLOT */

    if (json_nfgroups) {
        naxis = json_fgroups[0]->naxis;
        lng = json_fgroups[0]->lng;
        lat = json_fgroups[0]->lat;
    } else {
        naxis = lng = lat = 0;
    }
    deg2arcsec = (lng!=lat) ? (DEG/ARCSEC) : 1.0;
    deg2arcmin = (lng!=lat) ? (DEG/ARCMIN) : 1.0;

    json_object *fgroup_array = json_object_new_array();
    for (i=0; i<json_nfgroups; i++) {
        fgroupstruct *fgroup = json_fgroups[i];
        json_object *fgroup_row = json_object_new_array();
        json_object *o;

        o = new_json_object("Name", "string", NULL, "meta.id;meta.dataset");
        snprintf(strbuff, MAXCHAR, "G%d", i+1);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("Index", "int", NULL, "meta.record;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(i+1));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("NFields", "int", NULL, "meta.number;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(fgroup->nfield));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("NAxis", "int", NULL, "pos.wcs.naxis");
        json_object_object_add(o, "value", json_object_new_double(fgroup->naxis));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("Lng_Axis", "int", NULL, "meta.id;pos.eq.ra");
        json_object_object_add(o, "value", json_object_new_double(fgroup->lng));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("Lat_Axis", "int", NULL, "meta.id;pos.eq.de");
        json_object_object_add(o, "value", json_object_new_double(fgroup->lat));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("Field_Coordinates", "double array", NULL, "pos.eq.ra;pos.eq.dec;obs.field");
        p = json_object_new_array();
        for (j=0; j<fgroup->naxis; j++)
            json_object_array_add(p, json_object_new_double(fgroup->meanwcspos[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("Pixel_Scale", "float array", NULL, "instr.pixel;obs.field;stat.mean");
        p = json_object_new_array();
        for (j=0; j<fgroup->naxis; j++)
            json_object_array_add(p, json_object_new_double(fgroup->meanwcsscale[j]*deg2arcmin));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("Max_Radius", "float", NULL, "phys.size.radius;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->maxradius*deg2arcmin));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstRef_Catalog", "string", NULL, "meta.id;meta.dataset");
        json_object_object_add(o, "value", json_object_new_string(astrefcats[(int)prefs.astrefcat].name));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstRef_Band", "string", NULL, "instr.bandpass");
        json_object_object_add(o, "value", json_object_new_string(
            astrefcats[(int)prefs.astrefcat].bandname ? astrefcats[(int)prefs.astrefcat].bandname : "" ));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromSigma_Internal", "float array", NULL, "stat.stdev;pos.eq;obs.field");
        p = json_object_new_array();
        for (j=0; j<fgroup->naxis; j++)
            json_object_array_add(p, json_object_new_double(fgroup->sig_interr[j]*deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromCorr_Internal", "float", NULL, "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->sig_corr_int));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromChi2_Internal", "float", NULL, "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(fgroup->chi2_int));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromNDets_Internal", "int", NULL, "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(fgroup->nintmatch));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromSigma_Internal_HighSN", "float array", NULL, "stat.stdev;pos.eq;obs.field");
        p = json_object_new_array();
        for (j=0; j<fgroup->naxis; j++)
            json_object_array_add(p, json_object_new_double(fgroup->sig_interr_hsn[j]*deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromCorr_Internal_HighSN", "float", NULL, "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->sig_corr_int_hsn));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromChi2_Internal_HighSN", "float", NULL, "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(fgroup->chi2_int_hsn));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromNDets_Internal_HighSN", "int", NULL, "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(fgroup->nintmatch_hsn));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromOffset_Reference", "float array", NULL, "arith.diff;pos.eq;obs.field");
        p = json_object_new_array();
        for (j=0; j<fgroup->naxis; j++)
            json_object_array_add(p, json_object_new_double(fgroup->offset_ref[j]*deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromSigma_Reference", "float array", NULL, "stat.stdev;pos.eq;obs.field");
        p = json_object_new_array();
        for (j=0; j<fgroup->naxis; j++)
            json_object_array_add(p, json_object_new_double(fgroup->sig_referr[j]*deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromCorr_Reference", "float", NULL, "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->sig_corr_ref));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromChi2_Reference", "float", NULL, "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(fgroup->chi2_ref));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromNDets_Reference", "int", NULL, "meta.number;src");
        json_object_object_add(o, "value", json_object_new_int(fgroup->nrefmatch));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromOffset_Reference_HighSN", "float array", NULL, "arith.diff;pos.eq;obs.field");
        p = json_object_new_array();
        for (j=0; j<fgroup->naxis; j++)
            json_object_array_add(p, json_object_new_double(fgroup->offset_ref_hsn[j]*deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromSigma_Reference_HighSN", "float array", NULL, "stat.stDev;pos.eq;obs.field");
        p = json_object_new_array();
        for (j=0; j<fgroup->naxis; j++)
            json_object_array_add(p, json_object_new_double(fgroup->sig_referr_hsn[j]*deg2arcsec));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromCorr_Reference_HighSN", "float", NULL, "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->sig_corr_ref_hsn));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromChi2_Reference_HighSN", "float", NULL, "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(fgroup->chi2_ref_hsn));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("AstromNDets_Reference_HighSN", "int", NULL, "meta.number;src");
        json_object_object_add(o, "value", json_object_new_int(fgroup->nrefmatch_hsn));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("NPhotInstru", "int", NULL, "meta.number;meta.em");
        json_object_object_add(o, "value", json_object_new_int(prefs.nphotinstrustr));
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotInstru_Name", "string array", NULL, "meta.id;instr.bandpass");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++) {
            snprintf(strbuff, MAXCHAR , "P%d", j+1);
            json_object_array_add(p, json_object_new_string(strbuff));
        }
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotSigma_Internal", "float array", NULL, "stat.error;phot.mag");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_double(fgroup->sig_intmagerr[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotChi2_Internal", "float array", NULL, "stat.chi2;phot.mag");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_double(fgroup->chi2_intmag[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotNDets_Internal", "int array", NULL, "meta.number;src");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_int(fgroup->nintmagmatch[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotSigma_Internal_HighSN", "float array", NULL, "stat.error;phot.mag");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_double(fgroup->sig_intmagerr_hsn[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotChi2_Internal_HighSN", "float array", NULL, "stat.chi2;phot.mag");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_double(fgroup->chi2_intmag_hsn[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotNDets_Internal_HighSN", "int array", NULL, "meta.number;src");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_int(fgroup->nintmagmatch_hsn[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotSigma_Reference", "float array", NULL, "stat.error;phot.mag");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_double(fgroup->sig_refmagerr[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotChi2_Reference", "float array", NULL, "stat.chi2;phot.mag");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_double(fgroup->chi2_refmag[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotNDets_Reference", "int array", NULL, "meta.number;src");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_double(fgroup->nrefmagmatch[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotSigma_Reference_HighSN", "float array", NULL, "stat.error;phot.mag");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_double(fgroup->sig_refmagerr_hsn[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotChi2_Reference_HighSN", "float array", NULL, "stat.chi2;phot.mag");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_double(fgroup->chi2_refmag_hsn[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

        o = new_json_object("PhotNDets_Reference_HighSN", "int array", NULL, "meta.number;src");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++)
            json_object_array_add(p, json_object_new_int(fgroup->nrefmagmatch_hsn[j]));
        json_object_object_add(o, "value", p);
        json_object_array_add(fgroup_row, o);

#ifdef HAVE_PLPLOT
        if (pngflag) {
            for (j=pnplot; j<nplot; j++) {
                o = new_json_object(cp_names[j], "string", NULL, "meta.id;meta.dataset");
                strcpy(plotfilename, prefs.cplot_name[cp[j]]);
                if (!(pstr = strrchr(plotfilename, '.')))
                    pstr = plotfilename + strlen(plotfilename);
                sprintf(pstr, "_%d.png", i+1);

                json_object_object_add(o, "value", json_object_new_string(plotfilename));
                json_object_array_add(fgroup_row, o);
            }
        }
#endif /* HAVE_PLPLOT */

        json_object_array_add(fgroup_array, fgroup_row);

    }

    json_object_object_add(main_obj, "Fgroups", fgroup_array);


    /* astro instru */
#ifdef HAVE_PLPLOT
    pnplot = i = nplot;
    while ((plot_index = get_next_astrinst_plot(&cp_names[i])) >= 0) {
        cp[nplot++] = plot_index;
        i++;
    }
#endif /* HAVE_PLPLOT */

    json_object *astr_instru_array = json_object_new_array();
    for (i=0; i<prefs.nastrinstrustr; i++) {
        int len = fitsfind(prefs.astrinstrustr[i], "END     ");
        int f2 = 0;
        for (j=0; j<json_nfgroups; j++) {
            int k;
            for (k=0; k<json_fgroups[j]->nfield; k++) {
                if (json_fgroups[j]->field[k]->astromlabel==i)
                    f2++;
            }
        }

        json_object *astr_instru_row = json_object_new_array();

        o = new_json_object("Name", "string", NULL, "meta.id;meta.dataset");
        snprintf(strbuff, MAXCHAR, "A%d", i+1);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(astr_instru_row, o);

        o = new_json_object("Index", "int", NULL, "meta.record;meta.dataset");
        json_object_object_add(o, "value", json_object_new_int(i+1));
        json_object_array_add(astr_instru_row, o);

        o = new_json_object("NFields", "int", NULL, "meta.number;meta.dataset");
        json_object_object_add(o, "value", json_object_new_int(f2));
        json_object_array_add(astr_instru_row, o);

        o = new_json_object("MagZeroPoint_Output", "float", NULL, "astr.mag;astr.calib;arith.zp");
        json_object_object_add(o, "value", json_object_new_double(prefs.nastrinstruext[i]));
        json_object_array_add(astr_instru_row, o);

        o = new_json_object("NKeys", "int", NULL, "meta.number");
        json_object_object_add(o, "value", json_object_new_int(len));
        json_object_array_add(astr_instru_row, o);

        o = new_json_object("Keys", "string array", NULL, "meta.note");
        p = json_object_new_array();
        for (j=0; j<len; j++) {
            snprintf(strbuff, MAXCHAR, "%32.32s ", prefs.astrinstrustr[i] + (j*80));
            json_object_array_add(p, json_object_new_string(strbuff));
        }
        json_object_object_add(o, "value", p);
        json_object_array_add(astr_instru_row, o);

#ifdef HAVE_PLPLOT
        if (pngflag) {
            for (j=pnplot; j<nplot; j++) {
                o = new_json_object(cp_names[j], "string", NULL, "meta.id;meta.dataset");
                strcpy(plotfilename, prefs.cplot_name[cp[j]]);
                if (!(pstr = strrchr(plotfilename, '.')))
                    pstr = plotfilename + strlen(plotfilename);
                sprintf(pstr, "_%d.png", i+1);

                json_object_object_add(o, "value", json_object_new_string(plotfilename));
                json_object_array_add(astr_instru_row, o);
            }
        }
#endif /* HAVE_PLPLOT */

        json_object_array_add(astr_instru_array, astr_instru_row);

    }

    json_object_object_add(main_obj, "AstroInstruments", astr_instru_array);



    /* phot instru */
    json_object *phot_instru_array = json_object_new_array();
    for (i=0; i<prefs.nphotinstrustr; i++) {

        int len = fitsfind(prefs.photinstrustr[i], "END     ");
        int f2 = 0;
        for (j=0; j<json_nfgroups; j++) {
            int k;
            for (k=0; k<json_fgroups[j]->nfield; k++) {
                if (json_fgroups[j]->field[k]->photomlabel==i)
                    f2++;
            }
        }

        json_object *phot_instru_row = json_object_new_array();

        o = new_json_object("Name", "string", NULL, "meta.id;meta.dataset");
        snprintf(strbuff, MAXCHAR, "P%d", i+1);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(phot_instru_row, o);

        o = new_json_object("Index", "int", NULL, "meta.record;meta.dataset");
        json_object_object_add(o, "value", json_object_new_int(i+1));
        json_object_array_add(phot_instru_row, o);

        o = new_json_object("NFields", "int", NULL, "meta.number;meta.dataset");
        json_object_object_add(o, "value", json_object_new_int(f2));
        json_object_array_add(phot_instru_row, o);

        o = new_json_object("MagZeroPoint_Output", "float", NULL, "phot.mag;phot.calib;arith.zp");
        json_object_object_add(o, "value", json_object_new_double(prefs.magzero_out[i]));
        json_object_array_add(phot_instru_row, o);

        o = new_json_object("NKeys", "int", NULL, "meta.number");
        json_object_object_add(o, "value", json_object_new_int(len));
        json_object_array_add(phot_instru_row, o);

        o = new_json_object("Keys", "string array", NULL, "meta.note");
        p = json_object_new_array();
        for (j=0; j<prefs.nphotinstrustr; j++) {
            snprintf(strbuff, MAXCHAR, "%32.32s ", prefs.photinstrustr[i] + (j*80));
            json_object_array_add(p, json_object_new_string(strbuff));
        }
        json_object_object_add(o, "value", p);
        json_object_array_add(phot_instru_row, o);

        json_object_array_add(phot_instru_array, phot_instru_row);

    }

    json_object_object_add(main_obj, "PhotInstruments", phot_instru_array);

    /* warnings */

    json_object *warn_array = json_object_new_array();
    char *warnstr;
    for (warnstr = warning_history(), i=0; *warnstr; warnstr = warning_history(), i++) {
        json_object *warn_row = json_object_new_array();

        o = new_json_object("Date", "string", NULL, "meta;time.end");
        strncpy(strbuff, &warnstr[0], 10);
        strbuff[10] = '\0';
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(warn_row, o);

        o = new_json_object("Time", "string", NULL, "meta;time.end");
        strncpy(strbuff, &warnstr[11], 8);
        strbuff[8] = '\0';
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(warn_row, o);

        o = new_json_object("Text", "string", NULL, "meta");
        strncpy(strbuff, &warnstr[22], MAXCHAR);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(warn_row, o);

        json_object_array_add(warn_array, warn_row);

    }

    json_object_object_add(main_obj, "Warnings", warn_array);


    /* command line */
    strbuff[0] = '\0';
    int pos = 0;
    for (i=0; i<prefs.ncommand_line; i++)
        pos += snprintf(&strbuff[pos], MAXCHAR - strlen(strbuff), "%s ", prefs.command_line[i]);
    json_object_object_add(main_obj, "CommandLine", json_object_new_string(strbuff));


    /* config file */
    json_object *conf_array = json_object_new_array();
    int cpos;
    for (i=0; key[i].name[0]; i++) {
        o = json_object_new_object();
        char strtype[30];
        json_object *val;
        switch (key[i].type) {
            case P_FLOAT:
                strcpy(strtype, "float");
                val = json_object_new_double(*((float*)key[i].ptr));
                break;
            case P_INT:
                strcpy(strtype, "int");
                val = json_object_new_int(*((int*)key[i].ptr));
                break;
            case P_BOOL:
                strcpy(strtype, "boolean");
                val = json_object_new_boolean(*((int*)key[i].ptr));
                break;
            case P_STRING:
                strcpy(strtype, "string");
                val = json_object_new_string(((char*)key[i].ptr));
                break;
            case P_KEY:
                strcpy(strtype, "string");
                val = json_object_new_string(key[i].keylist[*((int*)key[i].ptr)]);
                break;
            case P_FLOATLIST:
                strcpy(strtype, "float array");
                val = json_object_new_array();
                for (j=0; j< *(key[i].nlistptr); j++)
                    json_object_array_add(val, json_object_new_double(((double*)key[i].ptr)[j]));
                break;
            case P_INTLIST:
                strcpy(strtype, "int array");
                val = json_object_new_array();
                for (j=0; j< *(key[i].nlistptr); j++)
                    json_object_array_add(val, json_object_new_int(((int*)key[i].ptr)[j]));
                break;
            case P_BOOLLIST:
                strcpy(strtype, "boolean array");
                val = json_object_new_array();
                for (j=0; j< *(key[i].nlistptr); j++)
                    json_object_array_add(val, json_object_new_boolean(((int*)key[i].ptr)[j]));
                break;
            case P_STRINGLIST:
                strcpy(strtype, "string array");
                val = json_object_new_array();
                for (j=0; j< *(key[i].nlistptr); j++)
                    json_object_array_add(val, json_object_new_string(((char**)key[i].ptr)[j]));
                break;
            case P_KEYLIST:
                strcpy(strtype, "string array");
                val = json_object_new_array();
                for (j=0; j< *(key[i].nlistptr); j++)
                    json_object_array_add(val, json_object_new_string(key[i].keylist[((int*)key[i].ptr)[j]]));
                break;
        }

        json_object_object_add(o, "type", json_object_new_string(strtype));
        json_object_object_add(o, "key", json_object_new_string(key[i].name));
        json_object_object_add(o, "value", val);
        json_object_array_add(conf_array, o);

    }
    json_object_object_add(main_obj, "Configuration", conf_array);

    return main_obj;
}

void
JsonOut_write(char *filename, json_object *js)
{

    FILE *fd = fopen(filename, "w");
    if (!fd) {
        perror(filename);
    } else {
        char *output = (char*) json_object_to_json_string(js);
        fwrite(output, 1, strlen(output), fd);
        fclose(fd);
    }

}

void
JsonOut_free(json_object *obj) {
    json_object_put(obj); /* What the fuck */
}
