<!DOCTYPE html>
<html>
	<head>
		<title>Processing Summary</title>
		<link rel="stylesheet" 
			href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" 
			integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" 
			crossorigin="anonymous">
		<link rel="stylesheet" href="http://getbootstrap.com/2.3.2/assets/css/bootstrap-responsive.css">
	    <style type="text/css">
      		body {
        		padding-top: 60px;
        		padding-bottom: 40px;
      		}
      		.sidebar-nav {
        		padding: 9px 0;
      		}
		
      		@media (max-width: 980px) {
        		/* Enable use of floated navbar text */
        		.navbar-text.pull-right {
          			float: none;
          			padding-left: 5px;
          			padding-right: 5px;
        		}
      		}
			@-ms-viewport     { width: device-width; }
			@-o-viewport      { width: device-width; }
			@viewport         { width: device-width; }
    	</style>

		<!--[if lt IE 9]>
      		<script src="https://oss.maxcdn.com/html5shiv/3.7.3/html5shiv.min.js"></script>
      		<script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    	<![endif]-->
	</head>
	<body>

		<h1>Processing summary</h1>

		<h2>Summary Table on Input Files</h2>
			<table id="fieldsTable" class="table table-striped">
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
					<th class="showmatch">&#916;Pixel scale</th>
					<th class="showmatch">&#916;Position Angle</th>
					<th class="showmatch">A/S contrast</th>
					<th class="showmatch">&#916;X</th>
					<th class="showmatch">&#916;Y</th>
					<th class="showmatch">X/Y contrast</th>
				    <th>&#967;2int</th>
					<th>&#967;2int High S/N</th>
					<th>&#967;2ref</th>
					<th>&#967;2ref High S/N</th>
					<th>Mag &#916;SP</th>
				</tr>
			    </thead>
				<tbody>
				</tbody>
			</table>

		<h2>Group Properties</h2>
		<table id="groupsTable" class="table table-striped">
			<thead>
				<tr>
					<th>Group name</th>
					<th class="opt">Group Plot</th>
					<th>Index</th>
					<th>NFields</th>
					<th>Right Ascension</th>
					<th>Declination</th>
					<th>Pixel scale</th>
					<th>Maximum radius</th>
					<th>Astrom. Ref. Catalog</th>
					<th>Astrom. Ref. Band</th>
					<th class="opt">&#967;2 Plot</th>
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
			</thead>
			<tbody>
			</tbody>
		</table>

		<h2>Astrometric Instruments</h2>
		<table id="astrometricInstrumentsTable" class="table table-striped" >
			<thead>
				<tr>
					<th>Name</th>
					<th>Index</th>
					<th>NFields</th>
					<th>Number of Keywords</th>
					<th>Keywords</th>
					<th>DistPlot</th>
				</tr>
			</thead>
			<tbody>
			</tbody>
		</table>

		<h2>Photometric Instruments</h2>
		<table id="photometricInstrumentsTable" class="table table-striped">
			<thead>
				<tr>
					<th>Name</th>
					<th>Index</th>
					<th>NFields</th>
					<th>Number of Keywords</th>
					<th>Keywords</th>
					<th>DistPlot</th>
				</tr>
			</thead>
			<tbody>
			</tbody>
		</table>

		<h2>Configuration file</h2>
		<table id="configurationTable" class="table table-striped">
			<thead>
				<tr>
					<th>Name</th>
					<th>Index</th>
					<th>NFields</th>
					<th>Number of Keywords</th>
					<th>Keywords</th>
					<th>DistPlot</th>
				</tr>
			</thead>
			<tbody>
			</tbody>
		</table>

		<h2>Warnings</h2>
		<table id="warningsTable" class="table table-striped">
			<thead>
				<tr>
					<th>Name</th>
					<th>Index</th>
					<th>NFields</th>
					<th>Number of Keywords</th>
					<th>Keywords</th>
					<th>DistPlot</th>
				</tr>
			</thead>
			<tbody>
			</tbody>
		</table>

		<script 
			src="https://code.jquery.com/jquery-3.2.1.slim.min.js" 
			integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" 
			crossorigin="anonymous"></script>
		<script 
			src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" 
			integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" 
			crossorigin="anonymous"></script>
		<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" 
			integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" 
			crossorigin="anonymous"></script>
		<script>
			/*! 
			 * IE10 viewport hack for Surface/desktop Windows 8 bug
 			 * Copyright 2014-2015 Twitter, Inc.
 			 * Licensed under MIT (https://github.com/twbs/bootstrap/blob/master/LICENSE)
 			 */

			(
				function () {
  					'use strict';

  					if (navigator.userAgent.match(/IEMobile\/10\.0/)) {
    					var msViewportStyle = document.createElement('style')
    					msViewportStyle.appendChild(
      						document.createTextNode(
        						'@-ms-viewport{width:auto!important}'
      						)
    					)
    					document.querySelector('head').appendChild(msViewportStyle)
  					}
				} 
			)();
		</script>
		<script>
			/*
			 * Data contained in "scamp_data" object, is loaded at the very end
			 * of this html file is his own <script> tag.
			 */
			function getElemVal(str, data) {
				var value = "";
				$.each(data, function (i, elem) {
					if (elem.name == str) {
						value = elem.value;
						return;
					}
				});
				return value;
			}

			function getFlagVal(str, t, data) {
				if (getElemVal(str, data))
					return t;
				return "-";
			}

		
			function getElemAverageVal(str, data) {
				var value = 0.0;
				var n = 0;
				$.each(getElemVal(str, data), function(i, elem) {
					value += elem;
					n++;
				});
				return value / n;
			}

			function getElemListVal(str, unit, data) {
				var value = "";
				$.each(getElemVal(str, data), function(i, elem) {
					value += elem + unit + " ";
				});
				return value;
			}

			function buildDegreeVal(value) {
				if (value < 0)
					value = 0 - value;
				
			}

			function getRaVal(str, data) {
				var value = getElemVal(str, data);
				var a = Math.floor(value[0] / 15.0);
				var b = Math.floor((value[0] * 4) % 60);
				var c = Math.floor((value[0] *240) % 60);
				return a + ":" + b + ":" + c.toFixed(2);
			}

			function getDecVal(str, data) {
				var value = getElemVal(str, data);
				var sign = "";
				if (value[1] < 0) {
					sign = "-";
					value[1] = 0 - value[1];
				}
				var a = Math.floor(value[1]);
				var b = Math.floor((value[1] * 60) % 60);
				var c = Math.floor((value[1] * 3600) % 60);

				return sign + a + ":" + b + ":" + c.toFixed(2);
			}

			$(document).ready(function() {
				console.log(scamp_data);

				/* 
				 * build fields table 
				 */
				$.each(scamp_data.Fields, function(i, field) {
					var table_row = "";
					table_row += "<tr>";
					table_row += "<td>" +  getElemVal("Catalog_Number", field) + "</td>";
					table_row += "<td>" +  getElemVal("Catalog_Name", field) + "</td>";
					table_row += "<td>" +  getElemVal("Image_Ident", field) + "</td>";
					table_row += "<td>" +  getElemVal("NExtensions", field) + "</td>";
					table_row += "<td>" +  getElemVal("NDetect", field) + "</td>";
					table_row += "<td>" +  getFlagVal("Ext_Header", "H", field)  + getFlagVal("Photom_Flag", "P", field) +  "</td>";
					table_row += "<td>" +  getElemVal("Group", field) + "</td>";
					table_row += "<td>" +  getElemVal("Astr_Instrum", field) + "</td>";
					table_row += "<td>" +  getElemVal("Phot_Instrum", field) + "</td>";
					table_row += "<td>" +  getElemVal("Observation_Date", field) + "</td>";
					table_row += "<td>" +  getElemVal("Exposure_Time", field).toFixed(3) + "</td>";
					table_row += "<td>" +  getElemVal("Air_Mass", field).toFixed(2) + "</td>";
					table_row += "<td>" +  getRaVal("Field_Coordinates", field) + "</td>";
					table_row += "<td>" +  getDecVal("Field_Coordinates", field) + "</td>";
					table_row += "<td>" +  getElemVal("Max_Radius", field).toFixed(3) + "'" + "</td>";
					table_row += "<td>" +  getElemAverageVal("Pixel_Scale", field).toFixed(4) + "''" + "</td>";
					table_row += "<td>" +  getElemVal("DPixel_Scale", field).toFixed(4) + "</td>";
					table_row += "<td>" +  getElemVal("DPos_Angle", field) + "°" + "</td>";
					table_row += "<td>" +  getElemVal("AS_Contrast", field).toFixed(1) + "</td>";
					table_row += "<td>" +  getElemVal("DX", field).toExponential() + "</td>";
					table_row += "<td>" +  getElemVal("DY", field).toExponential() + "</td>";
					table_row += "<td>" +  getElemVal("XY_Contrast", field).toFixed(1) + "</td>";
					table_row += "<td>" +  getElemVal("Chi2_Internal", field).toFixed(2) + "</td>";
					table_row += "<td>" +  getElemVal("Chi2_Internal_HighSN", field).toFixed(2) + "</td>";
					table_row += "<td>" +  getElemVal("Chi2_Reference", field).toFixed(2) + "</td>";
					table_row += "<td>" +  getElemVal("Chi2_Reference_HighSN", field).toFixed(2) + "</td>";
					table_row += "<td>" +  getElemVal("ZeroPoint_Corr", field).toFixed(3) + "</td>";
					table_row += "</tr>";
					$(table_row).appendTo("#fieldsTable tbody");
				});

				/* 
				 * build fields groups table 
				 */
				$.each(scamp_data.Fgroups, function(i, group) {
					var table_row = "";
					console.log(group);
					table_row += "<tr>";
					table_row += "<td>" +  getElemVal("Name", group) + "</td>";
					table_row += "<td>" +  getElemVal("Index", group) + "</td>";
					table_row += "<td>" +  getElemVal("NFields", group) + "</td>";
					table_row += "<td>" +  "ra" + "</td>";
					table_row += "<td>" +  "dec" + "</td>";
					table_row += "<td>" +  getElemAverageVal("Pixel_Scale", group) + "</td>";
					table_row += "<td>" +  getElemVal("Max_Radius", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstRef_Catalog", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstRef_Band", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromSigma_Internal", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromCorr_Internal", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromChi2_Internal", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromNDets_Internal", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromSigma_Internal_HighSN", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromCorr_Internal_HighSN", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromChi2_Internal_HighSN", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromNDets_Internal_HighSN", group) + "</td>";
					table_row += "<td>" +  getElemListVal("AstromOffset_Reference", "''", group) + "</td>";
					table_row += "<td>" +  getElemListVal("AstromSigma_Reference", "''", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromCorr_Reference", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromCorr_Reference", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromChi2_Reference", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromNDets_Reference", group) + "</td>";
					table_row += "<td>" +  getElemListVal("AstromOffset_Reference_HighSN", "''", group) + "</td>";
					table_row += "<td>" +  getElemListVal("AstromSigma_Reference_HighSN", "''", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromCorr_Reference_HighSN", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromChi2_Reference_HighSN", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromNDets_Reference_HighSN", group) + "</td>";
					table_row += "<td>" +  getElemListVal("PhotInstru_Name", ",", group) + "</td>";
					table_row += "</tr>";
				
					$(table_row).appendTo("#groupsTable tbody");
				});

				
			});
		</script>

	</body>
</html>
