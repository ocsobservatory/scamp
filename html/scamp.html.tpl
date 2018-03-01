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

		<div id="cont" class="container" role="main">
		<h1>Processing summary</h1>
		<div class="alert alert-success">
		<strong><span id="soft"></span></strong> completed on <strong><span id="date"></span></strong>
			at <strong><span id="time"></span></strong> using <strong><span id="nthreads"></span> </strong>
			threads (run time: <strong><span id="runtime"></span></strong>)
			started by user <strong><span id="username"></span></strong> in <strong><span id="rundir"></span></strong>.
		</div>

		<div class="card">
			<div class="card-header text-center"><h2>Summary Table on Input Files</h2></div>
			<div class="card-body table-responsive">
				<table id="fieldsTable" class="table table-hover table-bordered table-striped">
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
			</div> <!--card-body-->
		</div> <!--card -->

		<div class="card">
			<div class="card-header text-center"><h2>Group Properties</h2></div>
			<div class="card-body table-responsive">
		<table id="groupsTable" class="table table-bordered table-striped">
			<thead>
				<tr>
					<th>Group name</th>
					<th class="showplot">Group Plot</th>
					<th>Index</th>
					<th>NFields</th>
					<th>Right Ascension</th>
					<th>Declination</th>
					<th>Pixel scale</th>
					<th>Maximum radius</th>
					<th>Astrom. Ref. Catalog</th>
					<th>Astrom. Ref. Band</th>
					<th class="showplot">&#967;2 Plot</th>
					<th>Astrom. &#963;int</th>
					<th>Astrom. &#961;int</th>
					<th>Astrom. &#967;2int</th>
					<th>Astrom. N2int</th>
					<th>Astrom. &#963;int High S/N</th>
					<th>Astrom. &#961;int High S/N</th>
					<th>Astrom. &#947;2int High S/N</th>
					<th>Astrom. N2int High S/N</th>
					<th class="showplot">Astrom. 1-D Int. Error Plot</th>
					<th class="showplot">Astrom. 2-D Int. Error Plot</th>
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
					<th class="showplot">Astrom. 1-D Ref. Error Plot</th>
					<th class="showplot">Astrom. 2-D Ref. Error Plot</th>
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
					<th class="showplot">Photom. Internal Error Plot</th>
				</tr>
			</thead>
			<tbody>
			</tbody>
		</table>
			</div> <!--card-body-->
		</div> <!--card -->

		<h2>Astrometric Instruments</h2>
		<table id="astrometricInstrumentsTable" class="table table-responsive table-striped" >
			<thead>
				<tr>
					<th>Name</th>
					<th>Index</th>
					<th>NFields</th>
					<th>Number of Keywords</th>
					<th>Keywords</th>
					<th class="showplot">Distortion Plot</th>
				</tr>
			</thead>
			<tbody>
			</tbody>
		</table>

		<h2>Photometric Instruments</h2>
		<table id="photometricInstrumentsTable" class="table t table-responsive table-striped">
			<thead>
				<tr>
					<th>Name</th>
					<th>Index</th>
					<th>NFields</th>
					<th>Output ZP</th>
					<th>Number of Keywords</th>
					<th>Keywords</th>
				</tr>
			</thead>
			<tbody>
			</tbody>
		</table>

		<h2>Configuration file</h2>
		<table id="configTable" class="table t table-responsive table-striped">
			<thead>
				<tr>
					<th>Config Parameter</th>
					<th>Value</th>
				</tr>
			</thead>
			<tbody>
			</tbody>
		</table>

		<h2>Warnings</h2>
		<table id="warningsTable" class="table table-responsive table-striped">
			<thead>
				<tr>
					<th>Date</th>
					<th>Time</th>
					<th>Message</th>
				</tr>
			</thead>
			<tbody>
			</tbody>
		</table>
		</div> <!-- #cont -->
		<!-- END HTML -->





		<!-- SCRIPTS BEGIN -->
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

			function getElemListValFixed(str, unit, fix, data) {
				var value = "";
				$.each(getElemVal(str, data), function(i, elem) {
					if (fix >= 0) {
						elem = elem.toFixed(fix);
					}
					value += elem + unit + " ";
				});
				return value;
			}

			function getElemListVal(str, unit, data) {
				return getElemListValFixed(str, unit, -1, data);
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

				$('#soft').text(getElemVal("Name", scamp_data.Software)+" "+getElemVal("Version", scamp_data.Software));
				$('#date').text(getElemVal("Date", scamp_data.Software));
				$('#time').text(getElemVal("Time", scamp_data.Software));
				$('#nthreads').text(getElemVal("NThreads", scamp_data.Software));
				$('#runtime').text(getElemVal("Duration", scamp_data.Software) + " s");
				$('#username').text(getElemVal("User", scamp_data.Software));
				$('#rundir').text(getElemVal("Path", scamp_data.Software));

				var showmatch = getElemVal("MATCH", scamp_data.Configuration);
				var showplot  = getElemVal("CHECK_PLOT_DEV");
				showplot = (showplot > "PNG" || showplot > "PNG" ) ? false : true;

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

					if (showmatch) {
						table_row += "<td>" +  getElemVal("DPixel_Scale", field).toFixed(4) + "</td>";
						table_row += "<td>" +  getElemVal("DPos_Angle", field) + "°" + "</td>";
						table_row += "<td>" +  getElemVal("AS_Contrast", field).toFixed(1) + "</td>";
						table_row += "<td>" +  getElemVal("DX", field).toExponential() + "°" + "</td>";
						table_row += "<td>" +  getElemVal("DY", field).toExponential() + "°" + "</td>";
						table_row += "<td>" +  getElemVal("XY_Contrast", field).toFixed(1) + "</td>";
					} else {
						table_row += "<td></td>";
						table_row += "<td></td>";
						table_row += "<td></td>";
						table_row += "<td></td>";
						table_row += "<td></td>";
						table_row += "<td></td>";
					}

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
					table_row += "<tr>";
					table_row += "<td>" +  getElemVal("Name", group) + "</td>";
					if (showplot) {
						table_row += "<td><img width=\"42\" src=\"" +  getElemVal("FgroupsPlot", group) + "\"></td>";
					} else {
						table_row += "<td></td>";
					}
					table_row += "<td>" +  getElemVal("Index", group) + "</td>";
					table_row += "<td>" +  getElemVal("NFields", group) + "</td>";
					table_row += "<td>" +  getRaVal("Field_Coordinates", group) + "</td>";
					table_row += "<td>" +  getDecVal("Field_Coordinates", group) + "</td>";
					table_row += "<td>" +  getElemAverageVal("Pixel_Scale", group).toFixed(4) + "''" + "</td>";
					table_row += "<td>" +  getElemVal("Max_Radius", group).toFixed(3) + "'" + "</td>";
					table_row += "<td>" +  getElemVal("AstRef_Catalog", group) + "</td>";
					table_row += "<td>" +  getElemVal("AstRef_Band", group) + "</td>";
					if (showplot) {
						table_row += "<td><img width=\"42\" src=\"" +  getElemVal("Chi2Plot", group) + "\"></td>";
					} else {
						table_row += "<td></td>";
					}
					table_row += "<td>" +  getElemListValFixed("AstromSigma_Internal", "'' ", 4, group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromCorr_Internal", group).toFixed(5) + "</td>";
					table_row += "<td>" +  getElemVal("AstromChi2_Internal", group).toFixed(1) + "</td>";
					table_row += "<td>" +  getElemVal("AstromNDets_Internal", group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("AstromSigma_Internal_HighSN", "'' ", 4, group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromCorr_Internal_HighSN", group).toFixed(5)  + "</td>";
					table_row += "<td>" +  getElemVal("AstromChi2_Internal_HighSN", group).toFixed(1) + "</td>";
					table_row += "<td>" +  getElemVal("AstromNDets_Internal_HighSN", group) + "</td>";
					if (showplot) {
						table_row += "<td><img width=\"42\" src=\"" +  getElemVal("IntErr1DimPlot", group) + "\"></td>";
						table_row += "<td><img width=\"42\" src=\"" +  getElemVal("IntErr2DimPlot", group) + "\"></td>";
					} else {
						table_row += "<td></td>";
						table_row += "<td></td>";
					}
					table_row += "<td>" +  getElemListValFixed("AstromOffset_Reference", "'' ", 4, group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("AstromSigma_Reference", "'' ", 3, group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromCorr_Reference", group).toFixed(4) + "</td>";
					table_row += "<td>" +  getElemVal("AstromChi2_Reference", group).toFixed(1) + "</td>";
					table_row += "<td>" +  getElemVal("AstromNDets_Reference", group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("AstromOffset_Reference_HighSN", "'' ", 4, group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("AstromSigma_Reference_HighSN", "'' ", 3, group) + "</td>";
					table_row += "<td>" +  getElemVal("AstromCorr_Reference_HighSN", group).toFixed(4) + "</td>";
					table_row += "<td>" +  getElemVal("AstromChi2_Reference_HighSN", group).toFixed(1) + "</td>";
					table_row += "<td>" +  getElemVal("AstromNDets_Reference_HighSN", group) + "</td>";
					if (showplot) {
						table_row += "<td><img width=\"42\" src=\"" +  getElemVal("RefErr1DimPlot", group) + "\"></td>";
						table_row += "<td><img width=\"42\" src=\"" +  getElemVal("RefErr2DimPlot", group) + "\"></td>";
					} else {
						table_row += "<td></td>";
						table_row += "<td></td>";
					}
					table_row += "<td>" +  getElemListVal("PhotInstru_Name",", ", group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("PhotSigma_Internal", " ", 6, group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("PhotChi2_Internal", " ", 4, group) + "</td>";
					table_row += "<td>" +  getElemListVal("PhotNDets_Internal", " ", group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("PhotSigma_Internal_HighSN", " ", 6, group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("PhotChi2_Internal_HighSN", " ", 2, group) + "</td>";
					table_row += "<td>" +  getElemListVal("PhotNDets_Internal_HighSN", " ", group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("PhotSigma_Reference", " ", 6, group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("PhotChi2_Reference", " ", 6, group) + "</td>";
					table_row += "<td>" +  getElemListVal("PhotNDets_Reference", " ", group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("PhotSigma_Reference_HighSN", " ", 6, group) + "</td>";
					table_row += "<td>" +  getElemListValFixed("PhotChi2_Reference_HighSN", " ", 6, group) + "</td>";
					table_row += "<td>" +  getElemListVal("PhotNDets_Reference_HighSN", " ", group) + "</td>";
					if (showplot) {
						table_row += "<td><img width=\"42\" src=\"" +  getElemVal("PhotErrPlot", group) + "\"></td>";
					} else {
						table_row += "<td></td>";
					}

					table_row += "</tr>";
					$(table_row).appendTo("#groupsTable tbody");
				});


				/* 
				 * build astrometric instruments table 
				 */
				$.each(scamp_data.AstroInstruments, function(i, astroinstru) {
					var table_row = "";
					table_row += "<tr>";
					table_row += "<td>" +  getElemVal("Name", astroinstru) + "</td>";
					table_row += "<td>" +  getElemVal("Index", astroinstru) + "</td>";
					table_row += "<td>" +  getElemVal("NFields", astroinstru) + "</td>";
					table_row += "<td>" +  getElemVal("NKeys", astroinstru) + "</td>";
					table_row += "<td>" +  getElemListVal("Keys", " ", astroinstru) + "</td>";
					table_row += "<td><img width=\"42\" src=\"" +  getElemVal("DistPlot", astroinstru) + "\"></td>";
					table_row += "</tr>";
					$(table_row).appendTo("#astrometricInstrumentsTable tbody");
				});


				/* 
				 * build photometric instruments table 
				 */
				$.each(scamp_data.PhotInstruments, function(i, photoinstru) {
					var table_row = "";
					table_row += "<tr>";
					table_row += "<td>" +  getElemVal("Name", photoinstru) + "</td>";
					table_row += "<td>" +  getElemVal("Index", photoinstru) + "</td>";
					table_row += "<td>" +  getElemVal("Index", photoinstru) + "</td>";
					table_row += "<td>" +  getElemVal("MagZeroPoint_Output", photoinstru) + "</td>";
					table_row += "<td>" +  getElemVal("NKeys", photoinstru) + "</td>";
					table_row += "<td>" +  getElemListVal("Keys", " ", photoinstru) + "</td>";
					table_row += "</tr>";
					$(table_row).appendTo("#photometricInstrumentsTable tbody");
				});


				/* 
				 * build configuration table 
				 */
				$.each(scamp_data.Configuration, function(i, config) {
					var table_row = "";
					table_row += "<tr>";
					table_row += "<td>" +  config.name + "</td>";

					var value = "";
					if (config.datatype.includes("array")) {
						for (var i = 0; i < config.value.length; i++) {
							value += config.value[i] + ", ";
						}
					} else {
						value = config.value;
					}
					table_row += "<td>" +  value + "</td>";
					table_row += "</tr>";
					$(table_row).appendTo("#configTable tbody");
				});


				/* 
				 * build warnings table 
				 */
				$.each(scamp_data.Warnings, function(i, warn) {
					var table_row = "";
					table_row += "<tr>";
					table_row += "<td>" +  getElemVal("Date", warn) + "</td>";
					table_row += "<td>" +  getElemVal("Time", warn) + "</td>";
					table_row += "<td>" +  getElemVal("Text", warn) + "</td>";
					$(table_row).appendTo("#warningsTable tbody");
				});

				/*
				 * Hide unused columns
				 */
				if (!showmatch) {
					$('#fieldsTable th:nth-child(17)').hide();
					$('#fieldsTable td:nth-child(17)').hide();
					$('#fieldsTable th:nth-child(18)').hide();
					$('#fieldsTable td:nth-child(18)').hide();
					$('#fieldsTable th:nth-child(19)').hide();
					$('#fieldsTable td:nth-child(19)').hide();
					$('#fieldsTable th:nth-child(20)').hide();
					$('#fieldsTable td:nth-child(20)').hide();
					$('#fieldsTable th:nth-child(21)').hide();
					$('#fieldsTable td:nth-child(21)').hide();
					$('#fieldsTable th:nth-child(22)').hide();
					$('#fieldsTable td:nth-child(22)').hide();
				}
				if (!showplot) {
					$('#groupsTable th:nth-child(2)').hide();
					$('#groupsTable td:nth-child(2)').hide();
					$('#groupsTable th:nth-child(11)').hide();
					$('#groupsTable td:nth-child(11)').hide();
					$('#groupsTable th:nth-child(20)').hide();
					$('#groupsTable td:nth-child(20)').hide();
					$('#groupsTable th:nth-child(21)').hide();
					$('#groupsTable td:nth-child(21)').hide();
					$('#groupsTable th:nth-child(32)').hide();
					$('#groupsTable td:nth-child(32)').hide();
					$('#groupsTable th:nth-child(33)').hide();
					$('#groupsTable td:nth-child(33)').hide();
					$('#groupsTable th:nth-child(47)').hide();
					$('#groupsTable td:nth-child(47)').hide();
				
				}
				
			});
		</script>
		<!-- SCRIPTS END -->





	</body>
</html>
