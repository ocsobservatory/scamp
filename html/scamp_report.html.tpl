<!DOCTYPE html>
<html>
	<head>
		<title>Processing Summary</title>
	</head>
	<body>

		<h1>Processing summary</h1>

		{{?Fields}}
		<h2>Summary Table on Input Files</h2>
			<table class="table table-striped">
			    <thead>
				</tr>
					<th>#</th>
					<th>Filename</th>
					<th>Identifier</th>
					<th>Next</th>
					<th>Ndet</th>
					<th>Flags</th>
					<th>G</th>
					<th>A</th>
					<th>P</th>
					<th>Date</th>
					<th>Exposure Time</th>
					<th>Air Mass</th>
					<th>Right Ascension</th>
					<th>Declination</th>
					<th>Radius</th>
					<th>Pixel scale</th>
		    {{?ShowMatch}}
					    <th>&#916;Pixel scale</th>
					    <th>&#916;Position Angle</th>
					    <th>A/S contrast</th>
					    <th>&#916;X</th>
					    <th>&#916;Y</th>
					    <th>X/Y contrast</th>
		    {{/ShowMatch}}
				    <th>&#967;2int</th>
					<th>&#967;2int High S/N</th>
					<th>&#967;2ref</th>
					<th>&#967;2ref High S/N</th>
					<th>Mag &#916;SP</th>
				</tr>
			    </thead>
				{{#Fields}}
				<tr>
					<td>{{Catalog_Number}}</td>
					<td>{{Catalog_Name}}</td>
					<td>{{Image_Ident}}</td>
					<td>{{NExtensions}}</td>
					<td>{{NDetect}}</td>
					<td>{{Flags}}</td>
					<td>{{Group}}</td>
					<td>{{Astr_Instrum}}</td>
					<td>{{Phot_Instrum}}</td>
					<td>{{Observation_Date}}</td>
					<td>{{Exposure_Time}}</td>
					<td>{{Air_Mass}}</td>
					<td>{{Right_Ascension}}</td>
					<td>{{Declination}}</td>
					<td>{{Max_Radius}}</td>
					<td>{{Pixel_Scale}}</td>
		    {{?ShowMatch}}
					    <td>{{DPixel_Scale}}</td>
					    <td>{{DPos_Angle}}</td>
					    <td>{{AS_Contrast}}</td>
					    <td>{{DX}}</td>
					    <td>{{DY}}</td>
					    <td>{{XY_Contrast}}</td>
		    {{/ShowMatch}}
					<td>{{Chi2_Internal}}</td>
					<td>{{Chi2_Internal_HighSN}}</td>
					<td>{{Chi2_Reference}}</td>
					<td>{{Chi2_Reference_HighSN}}</td>
					<td>{{ZeroPoint_Corr}}</td>
				</tr>
				{{/Fields}}
			</table>
		{{/Fields}}

		{{?Fgroups}}
		<h2>Group Properties</h2>
		<table>
			<tr>
				<th>Group name</th>
				<th>Index</th>
				<th>NFields</th>
				<th>Right Ascension</th>
				<th>Declination</th>
				<th>Pixel scale</th>
				<th>Maximum radius</th>
				<th>Astrom. Ref. Catalog</th>
				<th>Astrom. Ref. Band</th>
				<th>Astrom. &#963;int</th>
				<th>Astrom. &#961;int</th>
				<th>Astrom. &#967;2int</th>
				<th>Astrom. N2int</th>
				<th>Astrom. &#963;int High S/N</th>
				<th>Astrom. &#961;int High S/N</th>
				<th>Astrom. &#947;2int High S/N</th>
				<th>Astrom. N2int High S/N</th>
				<th>Astrom. &#916;RA ref, &#916; DEC ref</th>
				<th>Astrom. &#963;ref</th>
				<th>Astrom. &#961;ref</th>
				<th>Astrom. &#967;2ref</th>
				<th>Astrom. Nref</th>
				<th>Astrom. &#916;RA ref, &#916; DEC ref High S/N</th>
				<th>Astrom. &#963;ref High S/N</th>
				<th>Astrom. &#961;ref High S/N</th>
				<th>Astrom. &#947;2ref High S/N</th>
				<th>Astrom. Nref High S/N</th>
				<th>Photom. instruments</th>
				<th>Photom. &#963;int</th>
				<th>Photom. &#967;2int</th>
				<th>Photom. Nint</th>
				<th>Photom. &#963; High S/N</th>
				<th>Astrom. &#947;2int High S/N</th>
				<th>Photom. Nint High S/N</th>
				<th>Photom. &#963;ref</th>
				<th>Photom. &#967;2ref</th>
				<th>Photom. Nref</th>
				<th>Photom. &#963;ref High S/N</th>
				<th>Photom. &#947;2ref High S/N</th>
				<th>Photom. Nref High S/N</th>
			</tr>
			{{#Fgroups}}
			<tr>
				<td>{{Name}}</td>
				<td>{{Index}}</td>
				<td>{{NFields}}</td>
				<td>{{Right_Ascension}}</td>
				<td>{{Declination}}</td>
				<td>{{Pixel_Scale}}</td>
				<td>{{Max_Radius}}</td>
				<td>{{AstRef_Catalog}}</td>
				<td>{{AstRef_Band}}</td>
				<td>{{astr_qint}}</td>
				<td>{{astr_pint}}</td>
				<td>{{astr_x2int}}</td>
				<td>{{astr_nint}}</td>
				<td>{{astr_qint_hSN}}</td>
				<td>{{astr_pint_hSH}}</td>
				<td>{{astr_x2int_hSN}}</td>
				<td>{{astr_nint_hSH}}</td>
				<td>{{astr_dRAref_dDECref}}</td>
				<td>{{astr_qref}}</td>
				<td>{{astr_pref}}</td>
				<td>{{astr_x2ref}}</td>
				<td>{{astr_nref}}</td>
				<td>{{astr_dRAref_dDECref_hSN}}</td>
				<td>{{astr_qref_hSN}}</td>
				<td>{{astr_pref_hSN}}</td>
				<td>{{astr_x2ref_hSN}}</td>
				<td>{{astr_Nref_hSN}}</td>
				<td>{{pht_instru}}</td>
				<td>{{pht_qint}}</td>
				<td>{{pht_x2int}}</td>
				<td>{{pht_qint_hSN}}</td>
				<td>{{pht_x2int_hSN}}</td>
				<td>{{pht_Nint_hSN}}</td>
				<td>{{pht_qref}}</td>
				<td>{{pht_x2ref}}</td>
				<td>{{pht_Nref}}</td>
				<td>{{pht_qref_hSN}}</td>
				<td>{{pht_x2ref_hSN}}</td>
				<td>{{pht_Nref_hSN}}</td>
			</tr>
			{{/Fgroups}}
		</table>
		{{/Fgroups}}

		{{?AstroInstruments}}
		<h2>Astrometric Instruments</h2>
		<table>
			<tr>
				<th>Name</th>
				<th>Index</th>
				<th>NFields</th>
				<th>Number of Keywords</th>
				<th>Keywords</th>
				<th>DistPlot</th>
			</tr>
			{{#AstroInstruments}}
			<tr>
				<td>{{Name}}</td>
				<td>{{Index}}</td>
				<td>{{NFields}}</td>
				<td>{{NKeys}}</td>
				<td>{{Keys}}</td>
				<td><img src="{{DistPlot}}" alt="Distortion plot"></td>
			</tr>
			{{/AstroInstruments}}
		</table>
		{{/AstroInstruments}}

	</body>
</html>

