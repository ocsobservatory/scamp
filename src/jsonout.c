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
    json_object *tables = json_object_new_object();
    json_object_object_add(main_obj, "Tables", tables);

    json_object *o;
    int i, j;

    char strbuff[MAXCHAR];
    int  strbuffpos;

    char *psuser, *pshost, *pspath;
    psuser = pshost = pspath = NULL;
#ifdef HAVE_GETENV
    if (!(psuser=getenv("USERNAME")))   /* Cygwin,... */
        psuser = getenv("LOGNAME");     /* Linux,... */
    pspath = getenv("PWD");
    pshost = getenv("HOSTNAME");
#endif /* HAVE_GETENV */

    /* soft meta */
    json_object *soft = json_object_new_object();

    o = new_json_object("Name", "char", "None", "meta.title;meta.software");
    json_object_object_add(o, "value", json_object_new_string(BANNER));
    json_object_object_add(soft, "Name", o);

    o = new_json_object("Version", "char", "None", "meta.version;meta.software");
    json_object_object_add(o, "value", json_object_new_string(MYVERSION));
    json_object_object_add(soft, "Version", o);

    o = new_json_object("Url", "char", "None", "meta.ref.url;meta.software");
    json_object_object_add(o, "value", json_object_new_string(WEBSITE));
    json_object_object_add(soft, "Url", o);

    o = new_json_object("Author", "char", "None", "meta.bib.author;meta.software");
    json_object_object_add(o, "value", json_object_new_string("Emmanuel Bertin"));
    json_object_object_add(soft, "Author", o);

    o = new_json_object("Ref", "char", "None", "meta.bib.bibcode;meta.software");
    json_object_object_add(o, "value", json_object_new_string("2006ASPC..351..112B"));
    json_object_object_add(soft, "Ref", o);

    o = new_json_object("NThreads", "int", "None", "meta.number;meta.software");
    json_object_object_add(o, "value", json_object_new_int(prefs.nthreads));
    json_object_object_add(soft, "NThreads", o);

    o = new_json_object("Date", "char", "None", "time.end;meta.software");
    json_object_object_add(o, "value", json_object_new_string(prefs.sdate_end));
    json_object_object_add(soft, "Date", o);

    o = new_json_object("Time", "char", "None", "time.end;meta.software");
    json_object_object_add(o, "value", json_object_new_string(prefs.stime_end));
    json_object_object_add(soft, "Time", o);

    o = new_json_object("Duration", "float", "None", "time.duration;meta.software");
    json_object_object_add(o, "value", json_object_new_double(prefs.time_diff));
    json_object_object_add(soft, "Duration", o);

    if (psuser) {
        o = new_json_object("User", "char", "None", "meta.curation");
        json_object_object_add(o, "value", json_object_new_string(psuser));
        json_object_object_add(soft, "User", o);
    }

    if (pshost) {
        o = new_json_object("Host", "char", "None", "meta.curation");
        json_object_object_add(o, "value", json_object_new_string(pshost));
        json_object_object_add(soft, "User", o);
    }

    if (pspath) {
        o = new_json_object("Path", "char", "None", "meta.dataset");
        json_object_object_add(o, "value", json_object_new_string(pspath));
        json_object_object_add(soft, "Path", o);
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

        o = new_json_object("AllSkyPlot", "char", "None", "meta.id;meta.dataset");
        json_object_object_add(o, "value", json_object_new_string(plotfilename));
        json_object_object_add(main_obj, "AllSkyPlot", o);

        cp[nplot++] = pngindex;
    }
#endif /* HAVE_PLPLOT */

    json_object *field_array = json_object_new_array();
    for (i=0; i<json_nfields; i++) {
        fieldstruct *field = json_fields[i];
        json_object *field_obj = json_object_new_object();
        json_object *field_cols = json_object_new_array();

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
        json_object_object_add(o, "value", json_object_new_int(field->naxis));
        json_object_array_add(field_cols, o);

        o = new_json_object("Lng_Axis", "int", "None", "meta.id;pos.eq.ra");
        json_object_object_add(o, "value", json_object_new_int(field->lng));
        json_object_array_add(field_cols, o);

        o = new_json_object("Lat_Axis", "int", "None", "meta.id;pos.eq.dec");
        json_object_object_add(o, "value", json_object_new_int(field->lat));
        json_object_array_add(field_cols, o);

        o = new_json_object("Ext_Header", "boolean", "None", "meta.code");
        json_object_object_add(o, "value", json_object_new_boolean(field->headflag));
        json_object_array_add(field_cols, o);

        o = new_json_object("NDetect", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_int(field->nsample));
        json_object_array_add(field_cols, o);

        o = new_json_object("Group", "int", "None", "meta.id.parent;meta.dataset");
        json_object_object_add(o, "value", json_object_new_int(field->fgroup->no));
        json_object_array_add(field_cols, o);

        o = new_json_object("Astr_Instrum", "char", "None", "meta.id.parent;meta.dataset");
        snprintf(strbuff, MAXCHAR, "A%d", field->astromlabel+1);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_cols, o);

        o = new_json_object("Phot_Instrum", "char", "None", "meta.id.parent;meta.dataset");
        snprintf(strbuff, MAXCHAR, "P%d", field->photomlabel+1);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_cols, o);

        o = new_json_object("Photom_Flag", "boolean", "None", "meta.code;phot");
        json_object_object_add(o, "value", json_object_new_boolean(field->photomflag));
        json_object_array_add(field_cols, o);

        o = new_json_object("Photom_Link", "boolean", "None", "meta.code;phot");
        json_object_object_add(o, "value", json_object_new_boolean(field->photomflag));
        json_object_array_add(field_cols, o);

        o = new_json_object("Observation_Date", "double", "yr", "time.epoch;obs.field");
        json_object_object_add(o, "value", json_object_new_double(field->epoch));
        json_object_array_add(field_cols, o);

        o = new_json_object("Exposure_Time", "float", "None", "time.duration;obs.exposure");
        json_object_object_add(o, "value", json_object_new_double(field->expotime));
        json_object_array_add(field_cols, o);

        o = new_json_object("AirMass", "float", "None", "obs.airMass");
        json_object_object_add(o, "value", json_object_new_double(field->airmass));
        json_object_array_add(field_cols, o);

        o = new_json_object("Field_Coordinates", "double", "%s", "pos.eq.ra;pos.eq.dec;obs.field");
        strbuffpos = 0;
        for (j=0; j<field->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.10g ", field->meanwcspos[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_cols, o);

        o = new_json_object("Pixel_Scale", "float", "%s", "instr.scale;instr.pixel;stat.mean");
        strbuffpos = 0;
        for (j=1; j<field->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", field->meanwcsscale[j] * deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_cols, o);

        o = new_json_object("Max_Radius", "float", "%s", "phys.size.radius");
        json_object_object_add(o, "value", json_object_new_double(field->maxradius*deg2arcmin));
        json_object_array_add(field_cols, o);

        o = new_json_object("ZeroPoint_Corr", "float", "mag", "phot.mag;phot.calib;arith.zp");
        json_object_object_add(o, "value", json_object_new_double(field->dmagzero));
        json_object_array_add(field_cols, o);

        if (prefs.match_flag) {
            o = new_json_object("DPixelScale", "float", "None", "instr.scale;instr.pixel;arith.ratio");
            json_object_object_add(o, "value", json_object_new_double(field->match_dscale));
            json_object_array_add(field_cols, o);

            o = new_json_object("DPosAngle", "float", "deg", "pos.posAng;obs.image;arith.diff");
            json_object_object_add(o, "value", json_object_new_double(field->match_dangle));
            json_object_array_add(field_cols, o);

            o = new_json_object("AS_Contrast", "float", "None", "stat.correlation;arith.ratio");
            json_object_object_add(o, "value", json_object_new_double(field->match_asig));
            json_object_array_add(field_cols, o);

            o = new_json_object("DX", "float", "deg", "pos.eq.ra;arith.diff");
            json_object_object_add(o, "value", json_object_new_double(field->match_dlng));
            json_object_array_add(field_cols, o);

            o = new_json_object("DY", "float", "deg", "pos.eq.dec;arith.diff");
            json_object_object_add(o, "value", json_object_new_double(field->match_dlat));
            json_object_array_add(field_cols, o);

            o = new_json_object("XY_Contrast", "float", "None", "stat.correlation;arith.ratio");
            json_object_object_add(o, "value", json_object_new_double(field->match_sig));
            json_object_array_add(field_cols, o);

            o = new_json_object("Shear", "float", "None", "phys.size.axisRatio;obs.image");
            json_object_object_add(o, "value", json_object_new_double(field->match_shear));
            json_object_array_add(field_cols, o);

            o = new_json_object("Shear_PosAngle", "float", "deg", "pos.posAng;obs.image");
            json_object_object_add(o, "value", json_object_new_double(field->match_sangle));
            json_object_array_add(field_cols, o);
        }

        o = new_json_object("Chi2_Internal", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(field->chi2_int));
        json_object_array_add(field_cols, o);

        o = new_json_object("NDeg_Internal", "int", "None", "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(field->nchi2_int));
        json_object_array_add(field_cols, o);

        o = new_json_object("Chi2_Internal_HighSN", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(field->chi2_int_hsn));
        json_object_array_add(field_cols, o);

        o = new_json_object("NDeg_Internal_HighSN", "int", "None", "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(field->nchi2_int_hsn));
        json_object_array_add(field_cols, o);

        o = new_json_object("AstromOffset_Reference", "float", "%s", "pos.eq.ra;pos.eq.dec;arith.diff;obs.field");
        strbuffpos = 0;
        for (j=0; j<field->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", (double) field->offset_ref[j] * deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_cols, o);

        o = new_json_object("AstromSigma_Reference", "float", "%s", "stat.stdev;pos.eq;obs.field");
        strbuffpos = 0;
        for (j=0; j<field->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", (double) field->sig_referr[j] * deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_cols, o);

        o = new_json_object("AstromCorr_Reference", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(field->sig_corr_ref));
        json_object_array_add(field_cols, o);

        o = new_json_object("Chi2_Reference", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(field->chi2_ref));
        json_object_array_add(field_cols, o);

        o = new_json_object("NDeg_Reference", "int", "None", "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(field->nchi2_ref));
        json_object_array_add(field_cols, o);

        o = new_json_object("AstromOffset_Reference_HighSN", "float", "%s", "pos.eq.ra;pos.eq.dec;arith.diff;obs.field");
        strbuffpos = 0;
        for (j=0; j<field->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", (double) field->offset_ref_hsn[j] * deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_cols, o);

        o = new_json_object("AstromSigma_Reference_HighSN", "float", "%s", "stat.stdev;pos.eq;obs.field");
        strbuffpos = 0;
        for (j=0; j<field->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", (double) field->sig_referr_hsn[j] * deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(field_cols, o);

        o = new_json_object("AstromCorr_Reference_HighSN", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double((double)field->sig_corr_ref_hsn));
        json_object_array_add(field_cols, o);

        o = new_json_object("Chi2_Reference_HighSN", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(field->chi2_ref_hsn));
        json_object_array_add(field_cols, o);

        o = new_json_object("NDeg_Reference_HighSN", "int", "None", "stat.fit.dof");
        json_object_object_add(o, "value", json_object_new_int(field->nchi2_ref_hsn));
        json_object_array_add(field_cols, o);

        json_object_object_add(field_obj, "id", json_object_new_int(field->fieldindex+1));
        json_object_object_add(field_obj, "cols", field_cols);
        json_object_array_add(field_array, field_obj);
    }

    o = json_object_new_object();
    json_object_object_add(o, "data", field_array);
    json_object_object_add(o, "number", json_object_new_int(json_nfields));
    json_object_object_add(tables, "Fields", o);


    /* fgroups */
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
        json_object *fgroup_obj = json_object_new_object();
        json_object *fgroup_cols = json_object_new_array();
        json_object *o;

        o = new_json_object("Name", "char", "None", "meta.id;meta.dataset");
        snprintf(strbuff, MAXCHAR, "G%d", i+1);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("Index", "int", "None", "meta.record;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(i+1));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("NFields", "int", "None", "meta.number;meta.dataset");
        json_object_object_add(o, "value", json_object_new_double(fgroup->nfield));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("NAxis", "int", "None", "pos.wcs.naxis");
        json_object_object_add(o, "value", json_object_new_double(fgroup->naxis));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("Lng_Axis", "int", "None", "meta.id;pos.eq.ra");
        json_object_object_add(o, "value", json_object_new_double(fgroup->lng));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("Lat_Axis", "int", "None", "meta.id;pos.eq.de");
        json_object_object_add(o, "value", json_object_new_double(fgroup->lat));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("Field_Coordinates", "double", "None", "pos.eq.ra;pos.eq.dec;obs.field");
        strbuffpos = 0;
        for (j=0; j<fgroup->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.10g ", fgroup->meanwcspos[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("Pixel_Scale", "float", "None", "instr.pixel;obs.field;stat.mean");
        strbuffpos = 0;
        for (j=0; j<fgroup->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.10g ", fgroup->meanwcsscale[j]*deg2arcmin);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("Max_Radius", "float", "None", "phys.size.radius;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->maxradius*deg2arcmin));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstRef_Catalog", "char", "None", "meta.id;meta.dataset");
        json_object_object_add(o, "value", json_object_new_string(astrefcats[(int)prefs.astrefcat].name));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstRef_Band", "char", "None", "instr.bandpass");
        json_object_object_add(o, "value", json_object_new_string(
            astrefcats[(int)prefs.astrefcat].bandname ? astrefcats[(int)prefs.astrefcat].bandname : "" ));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromSigma_Internal", "float", "None", "stat.stdev;pos.eq;obs.field");
        strbuffpos = 0;
        for (j=0; j<fgroup->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->sig_interr[j]*deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromCorr_Internal", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->sig_corr_int));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromChi2_Internal", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(fgroup->chi2_int));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromNDets_Internal", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(fgroup->nintmatch));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromSigma_Internal_HighSN", "float", "None", "stat.stdev;pos.eq;obs.field");
        strbuffpos = 0;
        for (j=0; j<fgroup->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->sig_interr_hsn[j]*deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromCorr_Internal_HighSN", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->sig_corr_int_hsn));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromChi2_Internal_HighSN", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(fgroup->chi2_int_hsn));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromNDets_Internal_HighSN", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_double(fgroup->nintmatch_hsn));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromOffset_Reference", "float", "None", "arith.diff;pos.eq;obs.field");
        strbuffpos = 0;
        for (j=0; j<fgroup->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->offset_ref[j]*deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromSigma_Reference", "float", "None", "stat.stdev;pos.eq;obs.field");
        strbuffpos = 0;
        for (j=0; j<fgroup->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->sig_referr[j]*deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromCorr_Reference", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->sig_corr_ref));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromChi2_Reference", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(fgroup->chi2_ref));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromNDets_Reference", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_int(fgroup->nrefmatch));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromOffset_Reference_HighSN", "float", "None", "arith.diff;pos.eq;obs.field");
        strbuffpos = 0;
        for (j=0; j<fgroup->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->offset_ref_hsn[j]*deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromSigma_Reference_HighSN", "float", "None", "stat.stDev;pos.eq;obs.field");
        strbuffpos = 0;
        for (j=0; j<fgroup->naxis; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->sig_referr_hsn[j]*deg2arcsec);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromCorr_Reference_HighSN", "float", "None", "stat.correlation;pos.eq;obs.field");
        json_object_object_add(o, "value", json_object_new_double(fgroup->sig_corr_ref_hsn));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromChi2_Reference_HighSN", "float", "None", "stat.fit.chi2");
        json_object_object_add(o, "value", json_object_new_double(fgroup->chi2_ref_hsn));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("AstromNDets_Reference_HighSN", "int", "None", "meta.number;src");
        json_object_object_add(o, "value", json_object_new_int(fgroup->nrefmatch_hsn));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("NPhotInstru", "int", "None", "meta.number;meta.em");
        json_object_object_add(o, "value", json_object_new_int(prefs.nphotinstrustr));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotInstru_Name", "char", "None", "meta.id;instr.bandpass");
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "P%d,", j+1);
        strbuff[strlen(strbuff)] = '\0';
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotSigma_Internal", "float", "None", "stat.error;phot.mag");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->sig_intmagerr[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotChi2_Internal", "float", "None", "stat.chi2;phot.mag");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->chi2_intmag[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotNDets_Internal", "int", "None", "meta.number;src");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%d ", fgroup->nintmagmatch[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotSigma_Internal_HighSN", "float", "None", "stat.error;phot.mag");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->sig_intmagerr_hsn[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotChi2_Internal_HighSN", "float", "None", "stat.chi2;phot.mag");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->chi2_intmag_hsn[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotNDets_Internal_HighSN", "int", "None", "meta.number;src");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%i ", fgroup->nintmagmatch_hsn[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotSigma_Reference", "float", "None", "stat.error;phot.mag");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->sig_refmagerr[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotChi2_Reference", "float", "None", "stat.chi2;phot.mag");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->chi2_refmag[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotNDets_Reference", "int", "None", "meta.number;src");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%d ", fgroup->nrefmagmatch[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotSigma_Reference_HighSN", "float", "None", "stat.error;phot.mag");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->sig_refmagerr_hsn[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotChi2_Reference_HighSN", "float", "None", "stat.chi2;phot.mag");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%.6g ", fgroup->chi2_refmag_hsn[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        o = new_json_object("PhotNDets_Reference_HighSN", "int", "None", "meta.number;src");
        strbuffpos = 0;
        for (j=0; j<prefs.nphotinstrustr; j++)
            snprintf(&strbuff[strbuffpos], MAXCHAR - strbuffpos, "%d ", fgroup->nrefmagmatch_hsn[j]);
        json_object_object_add(o, "value", json_object_new_string(strbuff));
        json_object_array_add(fgroup_cols, o);

        json_object_object_add(fgroup_obj, "id", json_object_new_int(i+1));
        json_object_object_add(fgroup_obj, "cols", fgroup_cols);
        json_object_array_add(fgroup_array, fgroup_obj);

    }

    o = json_object_new_object();
    json_object_object_add(o, "data", fgroup_array);
    json_object_object_add(o, "number", json_object_new_int(json_nfgroups));
    json_object_object_add(tables, "Fgroups", o);

    /* astro instru */
    json_object *astr_instru_array = json_object_new_array();
    for (i=0; i<prefs.nastrinstrustr; i++) {
        json_object *astr_instru_obj = json_object_new_object();
        json_object *astr_instru_cols = json_object_new_array();

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


