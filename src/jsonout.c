/*
 * Generate scamp metadata report output
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <json.h>

#include "key.h"
#include "prefs.h"

extern pkeystruct key[];

static fieldstruct  **json_fields;
static fgroupstruct **json_fgroups;
static int json_nfields;
static int json_nfgroups;

    void
Json_set_data(
        fieldstruct     **fields,
        int             nfields,
        fgroupstruct    **fgroups,
        int             nfgroups)
{

    json_fields = fields;
    json_fgroups = fgroups;
    json_nfields = nfields;
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
    json_object_object_add(o, "unit", json_object_new_string(unit));
    json_object_object_add(o, "ucd",  json_object_new_string(ucd));

    return o;
}

    void
Json_write(char *filename)
{
    json_object *main_obj = json_object_new_object();
    int i;

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
    char plotfilename[MAXCHAR];
    char *pstr;
    nplot = pnplot = pngflag = 0;
    QCALLOC(cp, int, prefs.ncplot_type);
    for (i=0; i<prefs.ncplot_device; i++)
        if ((prefs.cplot_device[i] == CPLOT_PNG))
        {
            pngflag = 1;
            break;
        }

    /* Check-plots */
    if (pngflag && (pngindex=cplot_check(CPLOT_ALLSKY)) != RETURN_ERROR)
    {
        strcpy(plotfilename, prefs.cplot_name[pngindex]);
        if (!(pstr = strrchr(plotfilename, '.')))
            pstr = plotfilename+strlen(plotfilename);
        sprintf(pstr, "_1.png");

        json_object *p = new_json_object("AllSkyPlot", "char", "None", "meta.id;meta.dataset");
        json_object_object_add(p, "value", json_object_new_string(plotfilename));
        json_object_object_add(main_obj, "AllSkyPlot", p);

        cp[nplot++] = pngindex;
    }
#endif /* HAVE_PLPLOT */

    /* fields */
    json_object *field_array = json_object_new_array();
    for (i=0; i<json_nfields; i++) {
        fieldstruct *field = json_fields[i];
        json_object *field_obj = json_object_new_object();
        json_object *field_cols = json_object_new_array();

        json_object *o;
        o = new_json_object("Catalog_Number", "int", "None", "meta.record;meta.table;meta.file");
        json_object_object_add(o, "value", json_object_new_int(field->fieldindex + 1));
        json_object_array_add(field_cols, o);

        o = new_json_object("Catalog_Name", "char", "None", "meta.id;meta.table;meta.file");
        json_object_object_add(o, "value", json_object_new_string(field->rfilename));
        json_object_array_add(field_cols, o);

        o = new_json_object("Image_Ident", "char", "None", "meta.id;obs.field");
        json_object_object_add(o, "value", json_object_new_string(field->ident));
        json_object_array_add(field_cols, o);

        o = new_json_object("NExtensions", "int", "None", "meta.record");
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_array_add(field_cols, o);

        o = new_json_object("NAxis", "int", "None", "pos.wcs.naxis");
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_array_add(field_cols, o);

        o = new_json_object("Lng_Axis", "int", "None", "meta.id;pos.eq.ra");
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_array_add(field_cols, o);

        o = new_json_object("Lat_Axis", "int", "None", "meta.id;pos.eq.dec");
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_array_add(field_cols, o);

        o = new_json_object("Ext_Header", "boolean", "None", "meta.code");
        json_object_object_add(o, "value", json_object_new_boolean(0));
        json_object_array_add(field_cols, o);

        o = new_json_object("NDetect", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_int(0));
        json_object_array_add(field_cols, o);

        o = new_json_object("Group", "int", "None", "meta.id.parent;meta.dataset");
        json_object_object_add(o, "value", json_object_new_int(0));
        json_object_array_add(field_cols, o);

        o = new_json_object("Astr_Instrum", "char", "None", "meta.id.parent;meta.dataset");
        json_object_object_add(o, "value", json_object_new_string("hello"));
        json_object_array_add(field_cols, o);

        o = new_json_object("Astr_Instrum", "char", "None", "meta.id.parent;meta.dataset");
        json_object_object_add(o, "value", json_object_new_string("hello"));
        json_object_array_add(field_cols, o);

        o = new_json_object("Phot_Instrum", "char", "None", "meta.id.parent;meta.dataset");
        json_object_object_add(o, "value", json_object_new_string("hello"));
        json_object_array_add(field_cols, o);

        o = new_json_object("Photom_Flag", "boolean", "None", "meta.code;phot");
        json_object_object_add(o, "value", json_object_new_boolean(0));
        json_object_array_add(field_cols, o);

        o = new_json_object("Photom_Link", "boolean", "None", "meta.code;phot");
        json_object_object_add(o, "value", json_object_new_boolean(0));
        json_object_array_add(field_cols, o);

        o = new_json_object("Observation_Date", "double", "yr", "time.epoch;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("Exposure_Time", "float", "None", "time.duration;obs.exposure");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("AirMass", "float", "None", "obs.airMass");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("Field_Coordinates", "double", "%s", "pos.eq.ra;pos.eq.dec;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("Pixel_Scale", "float", "%s", "instr.scale;instr.pixel;stat.mean");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("Max_Radius", "float", "%s", "phys.size.radius");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("ZeroPoint_Corr", "float", "mag", "phot.mag;phot.calib;arith.zp");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        if (prefs.match_flag) {
            o = new_json_object("DPixelScale", "float", "None", "instr.scale;instr.pixel;arith.ratio");
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);


            o = new_json_object("DPosAngle", "float", "deg", "pos.posAng;obs.image;arith.diff");
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);


            o = new_json_object("AS_Contrast", "float", "None", "stat.correlation;arith.ratio");
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);


            o = new_json_object("DX", "float", "deg", "pos.eq.ra;arith.diff");
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);

            o = new_json_object("DY", "float", "deg", "pos.eq.dec;arith.diff");
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);

            o = new_json_object("XY_Contrast", "float", "None", "stat.correlation;arith.ratio");
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);

            o = new_json_object("Shear", "float", "None", "phys.size.axisRatio;obs.image");
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);

            o = new_json_object("Shear_PosAngle", "float", "deg", "pos.posAng;obs.image");
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);
        }

        o = new_json_object("Chi2_Internal", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);

        o = new_json_object("NDeg_Internal", "int", "None", "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_array_add(field_cols, o);

        o = new_json_object("Chi2_Internal_HighSN", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("NDeg_Internal_HighSN", "int", "None", "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("AstromOffset_Reference", "float", "%s", "pos.eq.ra;pos.eq.dec;arith.diff;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("AstromSigma_Reference", "float", "%s", "stat.stdev;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("AstromCorr_Reference", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("Chi2_Reference", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("NDeg_Reference", "int", "None", "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("AstromOffset_Reference_HighSN", "float", "%s", "pos.eq.ra;pos.eq.dec;arith.diff;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("AstromSigma_Reference_HighSN", "float", "%s", "stat.stdev;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("AstromCorr_Reference_HighSN", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("Chi2_Reference_HighSN", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = new_json_object("NDeg_Reference_HighSN", "int", "None", "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_array_add(field_cols, o);


        json_object_object_add(field_obj, "params", field_cols);
        json_object_array_add(field_array, field_obj);
    }

    json_object_object_add(main_obj, "fields", field_array);
    json_object_object_add(main_obj, "nfields", json_object_new_int(json_nfields));


    /* fgroups */
    json_object *fgroup_array = json_object_new_array();
    for (i=0; i<json_nfgroups; i++) {
        fgroupstruct *fgroup = json_fgroups[i];
        json_object *fgroup_obj = json_object_new_object();
        json_object *fgroup_cols = json_object_new_array();
        json_object *o;

        o = new_json_object("Name", "char", "None", "meta.id;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("Index", "int", "None", "meta.record;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("NFields", "int", "None", "meta.number;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("NAxis", "int", "None", "pos.wcs.naxis");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("Lng_Axis", "int", "None", "meta.id;pos.eq.ra");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("Lat_Axis", "int", "None", "meta.id;pos.eq.de");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("Field_Coordinates", "double", "None", "pos.eq.ra;pos.eq.dec;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("Pixel_Scale", "float", "None", "instr.pixel;obs.field;stat.mean");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("Max_Radius", "float", "None", "phys.size.radius;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstRef_Catalog", "char", "None", "meta.id;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstRef_Band", "char", "None", "instr.bandpass");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromSigma_Internal", "float", "None", "stat.stdev;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromCorr_Internal", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromChi2_Internal", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromNDets_Internal", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromSigma_Internal_HighSN", "float", "None", "stat.stdev;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromCorr_Internal_HighSN", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromChi2_Internal_HighSN", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromNDets_Internal_HighSN", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromOffset_Reference", "float", "None", "arith.diff;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromSigma_Reference", "float", "None", "stat.stdev;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromCorr_Reference", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromChi2_Reference", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromNDets_Reference", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromOffset_Reference_HighSN", "float", "None", "arith.diff;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromSigma_Reference_HighSN", "float", "None", "stat.stDev;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromCorr_Reference_HighSN", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromChi2_Reference_HighSN", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("AstromNDets_Reference_HighSN", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("NPhotInstru", "int", "None", "meta.number;meta.em");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotInstru_Name", "char", "None", "meta.id;instr.bandpass");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotSigma_Internal", "float", "None", "stat.error;phot.mag");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotChi2_Internal", "float", "None", "stat.chi2;phot.mag");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotNDets_Internal", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotSigma_Internal_HighSN", "float", "None", "stat.error;phot.mag");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotChi2_Internal_HighSN", "float", "None", "stat.chi2;phot.mag");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotNDets_Internal_HighSN", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotSigma_Reference", "float", "None", "stat.error;phot.mag");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotChi2_Reference", "float", "None", "stat.chi2;phot.mag");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotNDets_Reference", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotSigma_Reference_HighSN", "float", "None", "stat.error;phot.mag");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotChi2_Reference_HighSN", "float", "None", "stat.chi2;phot.mag");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = new_json_object("PhotNDets_Reference_HighSN", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        json_object_object_add(fgroup_obj, "params", fgroup_cols);
        json_object_array_add(fgroup_array, fgroup_obj);

    }

    json_object_object_add(main_obj, "fgroups", fgroup_array);
    json_object_object_add(main_obj, "nfgroups", json_object_new_int(json_nfgroups));


    /* astro instru */
    json_object *astr_instru_array = json_object_new_array();
    for (i=0; i<prefs.nastrinstrustr; i++) {
        json_object *astr_instru_obj = json_object_new_object();
        json_object *astr_instru_cols = json_object_new_array();
        json_object *o;


        o = new_json_object("Name", "char", "None", "meta.id;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = new_json_object("Index", "int", "None", "meta.record;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = new_json_object("NFields", "int", "None", "meta.number;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = new_json_object("MagZeroPoint_Output", "float", "None", "astr.mag;astr.calib;arith.zp");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = new_json_object("NKeys", "int", "None", "meta.number");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = new_json_object("Keys", "char", "None", "meta.note");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);

        json_object_object_add(astr_instru_obj, "params", astr_instru_cols);
        json_object_array_add(astr_instru_array, astr_instru_obj);

    }

    json_object_object_add(main_obj, "astrinstr", astr_instru_array);
    json_object_object_add(main_obj, "nastrinstr", json_object_new_int(prefs.nastrinstrustr));



    /* phot instru */
    json_object *phot_instru_array = json_object_new_array();
    for (i=0; i<prefs.nphotinstrustr; i++) {
        json_object *phot_instru_obj = json_object_new_object();
        json_object *phot_instru_cols = json_object_new_array();
        json_object *o;


        o = new_json_object("Name", "char", "None", "meta.id;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = new_json_object("Index", "int", "None", "meta.record;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = new_json_object("NFields", "int", "None", "meta.number;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = new_json_object("MagZeroPoint_Output", "float", "None", "phot.mag;phot.calib;arith.zp");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = new_json_object("NKeys", "int", "None", "meta.number");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = new_json_object("Keys", "char", "None", "meta.note");
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);

        json_object_object_add(phot_instru_obj, "params", phot_instru_cols);
        json_object_array_add(phot_instru_array, phot_instru_obj);

    }

    json_object_object_add(main_obj, "photinstr", phot_instru_array);
    json_object_object_add(main_obj, "nphotinstr", json_object_new_int(prefs.nphotinstrustr));


    char *output = (char*) json_object_to_json_string(main_obj);

    json_object_put(main_obj); /* What the fuck */

    FILE *fd = fopen(filename, "w");
    if (!fd) {
        perror(filename);
    } else {
        fwrite(output, 1, strlen(output), fd);
        fclose(fd);
    }

}


