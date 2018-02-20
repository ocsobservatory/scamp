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

    void
Json_write(char *filename)
{
    json_object *main_obj = json_object_new_object();
    int i;


    /* fields */
    json_object *field_array = json_object_new_array();
    for (i=0; i<json_nfields; i++) {
        fieldstruct *field = json_fields[i];
        json_object *field_obj = json_object_new_object();
        json_object *field_cols = json_object_new_array();

        json_object *o;
        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Catalog_Number"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.record;meta.table;meta.file"));
        json_object_object_add(o, "value", json_object_new_int(field->fieldindex + 1));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Catalog_Name"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;meta.table;meta.file"));
        json_object_object_add(o, "value", json_object_new_string(field->rfilename));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Image_Ident"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;obs.field"));
        json_object_object_add(o, "value", json_object_new_string(field->ident));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NExtensions"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.record"));
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NAxis"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.wcs.naxis"));
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Lng_Axis"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;pos.eq.ra"));
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Lat_Axis"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;pos.eq.dec"));
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Ext_Header"));
        json_object_object_add(o, "datatype", json_object_new_string("boolean"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.code"));
        json_object_object_add(o, "value", json_object_new_boolean(0));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDetect"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
        json_object_object_add(o, "value", json_object_new_int(0));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Group"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id.parent;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_int(0));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Astr_Instrum"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id.parent;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_string("hello"));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Astr_Instrum"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id.parent;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_string("hello"));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Phot_Instrum"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id.parent;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_string("hello"));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Photom_Flag"));
        json_object_object_add(o, "datatype", json_object_new_string("boolean"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.code;phot"));
        json_object_object_add(o, "value", json_object_new_boolean(0));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Photom_Link"));
        json_object_object_add(o, "datatype", json_object_new_string("boolean"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.code;phot"));
        json_object_object_add(o, "value", json_object_new_boolean(0));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Observation_Date"));
        json_object_object_add(o, "datatype", json_object_new_string("double"));
        json_object_object_add(o, "unit", json_object_new_string("yr"));
        json_object_object_add(o, "ucd",  json_object_new_string("time.epoch;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Exposure_Time"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("time.duration;obs.exposure"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AirMass"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("obs.airMass"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Field_Coordinates"));
        json_object_object_add(o, "datatype", json_object_new_string("double"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.ra;pos.eq.dec;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Pixel_Scale"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("instr.scale;instr.pixel;stat.mean"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Max_Radius"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("phys.size.radius"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("ZeroPoint_Corr"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("mag"));
        json_object_object_add(o, "ucd",  json_object_new_string("phot.mag;phot.calib;arith.zp"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        if (prefs.match_flag) {
            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("DPixelScale"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("None"));
            json_object_object_add(o, "ucd",  json_object_new_string("instr.scale;instr.pixel;arith.ratio"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);


            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("DPosAngle"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("deg"));
            json_object_object_add(o, "ucd",  json_object_new_string("pos.posAng;obs.image;arith.diff"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);


            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("AS_Contrast"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("None"));
            json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;arith.ratio"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);


            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("DX"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("deg"));
            json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.ra;arith.diff"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);

            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("DY"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("deg"));
            json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.dec;arith.diff"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);

            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("XY_Contrast"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("None"));
            json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;arith.ratio"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);

            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("Shear"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("None"));
            json_object_object_add(o, "ucd",  json_object_new_string("phys.size.axisRatio;obs.image"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);

            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("Shear_PosAngle"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("deg"));
            json_object_object_add(o, "ucd",  json_object_new_string("pos.posAng;obs.image"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_array_add(field_cols, o);
        }

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Chi2_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDeg_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.dof"));
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_array_add(field_cols, o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Chi2_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDeg_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.dof"));
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromOffset_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.ra;pos.eq.dec;arith.diff;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromSigma_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.stdev;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromCorr_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Chi2_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDeg_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.dof"));
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromOffset_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.ra;pos.eq.dec;arith.diff;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromSigma_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.stdev;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromCorr_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Chi2_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(field_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDeg_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.dof"));
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

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Name"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Index"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.record;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NFields"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NAxis"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.wcs.naxis"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Lng_Axis"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;pos.eq.ra"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Lat_Axis"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;pos.eq.de"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Field_Coordinates"));
        json_object_object_add(o, "datatype", json_object_new_string("double"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.ra;pos.eq.dec;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Pixel_Scale"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("instr.pixel;obs.field;stat.mean"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Max_Radius"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("phys.size.radius;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstRef_Catalog"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstRef_Band"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("instr.bandpass"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromSigma_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.stdev;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromCorr_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromChi2_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromNDets_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromSigma_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.stdev;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromCorr_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromChi2_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromNDets_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromOffset_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("arith.diff;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromSigma_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.stdev;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromCorr_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromChi2_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromNDets_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromOffset_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("arith.diff;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromSigma_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.stDev;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromCorr_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromChi2_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromNDets_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NPhotInstru"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;meta.em"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotInstru_Name"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;instr.bandpass"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotSigma_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.error;phot.mag"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotChi2_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.chi2;phot.mag"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotNDets_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotSigma_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.error;phot.mag"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotChi2_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.chi2;phot.mag"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotNDets_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotSigma_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.error;phot.mag"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotChi2_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.chi2;phot.mag"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotNDets_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotSigma_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.error;phot.mag"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotChi2_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.chi2;phot.mag"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(fgroup_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("PhotNDets_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
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


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Name"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Index"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.record;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NFields"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("MagZeroPoint_Output"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("astr.mag;astr.calib;arith.zp"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NKeys"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(astr_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Keys"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.note"));
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


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Name"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Index"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.record;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NFields"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("MagZeroPoint_Output"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("phot.mag;phot.calib;arith.zp"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NKeys"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_array_add(phot_instru_cols, o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Keys"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.note"));
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


