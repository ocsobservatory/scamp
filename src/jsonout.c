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
    json_object *field_array = json_object_new_array();

    int i;
    for (i=0; i<json_nfields; i++) {
        fieldstruct *field = json_fields[i];
        json_object *field_obj = json_object_new_object();
        json_object *o;

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Catalog_Number"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.record;meta.table;meta.file"));
        json_object_object_add(o, "value", json_object_new_int(field->fieldindex + 1));
        json_object_object_add(field_obj, "Catalog_Number", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Catalog_Name"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;meta.table;meta.file"));
        json_object_object_add(o, "value", json_object_new_string(field->rfilename));
        json_object_object_add(field_obj, "Catalog_Name", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Image_Ident"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;obs.field"));
        json_object_object_add(o, "value", json_object_new_string(field->ident));
        json_object_object_add(field_obj, "Image_Ident", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NExtensions"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.record"));
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_object_add(field_obj, "NExtensions", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NAxis"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.wcs.naxis"));
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_object_add(field_obj, "NAxis", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Lng_Axis"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;pos.eq.ra"));
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_object_add(field_obj, "Lng_Axis", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Lat_Axis"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id;pos.eq.dec"));
        json_object_object_add(o, "value", json_object_new_int(field->nset));
        json_object_object_add(field_obj, "Lat_Axis", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Ext_Header"));
        json_object_object_add(o, "datatype", json_object_new_string("boolean"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.code"));
        json_object_object_add(o, "value", json_object_new_boolean(0));
        json_object_object_add(field_obj, "Ext_Header", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDetect"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.number;src"));
        json_object_object_add(o, "value", json_object_new_int(0));
        json_object_object_add(field_obj, "NDetect", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Group"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id.parent;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_int(0));
        json_object_object_add(field_obj, "Group", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Astr_Instrum"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id.parent;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_string("hello"));
        json_object_object_add(field_obj, "Group", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Astr_Instrum"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id.parent;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_string("hello"));
        json_object_object_add(field_obj, "Astr_Instrum", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Phot_Instrum"));
        json_object_object_add(o, "datatype", json_object_new_string("char"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.id.parent;meta.dataset"));
        json_object_object_add(o, "value", json_object_new_string("hello"));
        json_object_object_add(field_obj, "Phot_Instrum", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Photom_Flag"));
        json_object_object_add(o, "datatype", json_object_new_string("boolean"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.code;phot"));
        json_object_object_add(o, "value", json_object_new_boolean(0));
        json_object_object_add(field_obj, "Photom_Flag", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Photom_Link"));
        json_object_object_add(o, "datatype", json_object_new_string("boolean"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("meta.code;phot"));
        json_object_object_add(o, "value", json_object_new_boolean(0));
        json_object_object_add(field_obj, "Photom_Link", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Observation_Date"));
        json_object_object_add(o, "datatype", json_object_new_string("double"));
        json_object_object_add(o, "unit", json_object_new_string("yr"));
        json_object_object_add(o, "ucd",  json_object_new_string("time.epoch;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "Observation_Date", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Exposure_Time"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("time.duration;obs.exposure"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "Exposure_Time", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AirMass"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("obs.airMass"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "AirMass", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Field_Coordinates"));
        json_object_object_add(o, "datatype", json_object_new_string("double"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.ra;pos.eq.dec;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "Field_Coordinates", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Pixel_Scale"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("instr.scale;instr.pixel;stat.mean"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "Pixel_Scale", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Max_Radius"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("phys.size.radius"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "Max_Radius", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("ZeroPoint_Corr"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("mag"));
        json_object_object_add(o, "ucd",  json_object_new_string("phot.mag;phot.calib;arith.zp"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "ZeroPoint_Corr", o);


        if (prefs.match_flag) {
            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("DPixelScale"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("None"));
            json_object_object_add(o, "ucd",  json_object_new_string("instr.scale;instr.pixel;arith.ratio"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_object_add(field_obj, "DPixelScale", o);


            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("DPosAngle"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("deg"));
            json_object_object_add(o, "ucd",  json_object_new_string("pos.posAng;obs.image;arith.diff"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_object_add(field_obj, "DPosAngle", o);


            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("AS_Contrast"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("None"));
            json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;arith.ratio"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_object_add(field_obj, "AS_Contrast", o);


            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("DX"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("deg"));
            json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.ra;arith.diff"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_object_add(field_obj, "DX", o);

            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("DY"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("deg"));
            json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.dec;arith.diff"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_object_add(field_obj, "DY", o);

            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("XY_Contrast"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("None"));
            json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;arith.ratio"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_object_add(field_obj, "XY_Contrast", o);

            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("Shear"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("None"));
            json_object_object_add(o, "ucd",  json_object_new_string("phys.size.axisRatio;obs.image"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_object_add(field_obj, "Shear", o);

            o = json_object_new_object();
            json_object_object_add(o, "name", json_object_new_string("Shear_PosAngle"));
            json_object_object_add(o, "datatype", json_object_new_string("float"));
            json_object_object_add(o, "unit", json_object_new_string("deg"));
            json_object_object_add(o, "ucd",  json_object_new_string("pos.posAng;obs.image"));
            json_object_object_add(o, "value", json_object_new_double(0.0));
            json_object_object_add(field_obj, "Shear_PosAngle", o);
        }

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Chi2_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "Chi2_Internal", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDeg_Internal"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.dof"));
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_object_add(field_obj, "NDeg_Internal", o);

        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Chi2_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "Chi2_Internal_HighSN", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDeg_Internal_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.dof"));
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_object_add(field_obj, "NDeg_Internal_HighSN", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromOffset_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.ra;pos.eq.dec;arith.diff;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "AstromOffset_Reference", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromSigma_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.stdev;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "AstromSigma_Reference", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromCorr_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "AstromCorr_Reference", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Chi2_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "Chi2_Reference", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDeg_Reference"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.dof"));
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_object_add(field_obj, "NDeg_Reference", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromOffset_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("pos.eq.ra;pos.eq.dec;arith.diff;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "AstromOffset_Reference_HighSN", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromSigma_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("%s"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.stdev;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "AstromSigma_Reference_HighSN", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("AstromCorr_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.correlation;pos.eq;obs.field"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "AstromCorr_Reference_HighSN", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("Chi2_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("float"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.chi2"));
        json_object_object_add(o, "value", json_object_new_double(0.0));
        json_object_object_add(field_obj, "Chi2_Reference_HighSN", o);


        o = json_object_new_object();
        json_object_object_add(o, "name", json_object_new_string("NDeg_Reference_HighSN"));
        json_object_object_add(o, "datatype", json_object_new_string("int"));
        json_object_object_add(o, "unit", json_object_new_string("None"));
        json_object_object_add(o, "ucd",  json_object_new_string("stat.fit.dof"));
        json_object_object_add(o, "value", json_object_new_int(0.0));
        json_object_object_add(field_obj, "NDeg_Reference_HighSN", o);


        json_object_array_add(field_array, field_obj);
    }

    json_object_object_add(main_obj, "fields", field_array);

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
