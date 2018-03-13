<!DOCTYPE html>
<html>
	<head>
		<title>Processing Summary</title>
		<link 
			rel="stylesheet" 
			href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" 
			integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" 
			crossorigin="anonymous">
		<link 
			rel="stylesheet" 
			href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css" 
			integrity="sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp" 
			crossorigin="anonymous">

	    <style type="text/css">
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




		<nav class="navbar navbar-inverse " role="navigation">
      		<div class="container-fluid">
        		<div class="navbar-header">
          			<a 
						style="padding-top:4px;" 
						class="navbar-brand" 
						target="_blank" href="http://astromatic.net">
							<img 
								style="height: 50px; margin-top:0px;" 
								alt="astromatic" 
								src="http://astromatic.net/xsl/astromatic.png">
					</a>
				</div>

				<div class="nav navbar-nav navbar-right">
					<p class="navbar-text pull-right">
						<strong>
							<a target="_blank" 
								href="https://github.com/astromatic/scamp">
									<span id="soft" 
										class="label label-primary" 
										style="font-size:50;"></span>
							</a>
						</strong> 
						completed on <strong><span id="date"></span></strong>
						at <strong><span id="time"></span></strong> 
						using <strong><span id="nthreads"></span> </strong>
						threads (run time: <strong><span id="runtime"></span></strong>)
						started by user <strong><span id="username"></span></strong> 
						in <strong><span id="rundir"></span></strong>.
					</p>
        		</div> <!-- navright -->
      		</div> <!--container-fluid-->
    	</nav> <!-- nav -->




		<div class="container-fluid role="main"">
			<div class="row-fluid">
				<div class="col-xs-0 col-sm-6 col-md-3">
					<div class="list-group">
						<a href="#inputFiles" class="list-group-item">Input files</a>
						<a href="#groupProperties" class="list-group-item">Group properties</a>
						<a href="#astroInstru" class="list-group-item">Astrometric Instruments</a>
						<a href="#photoInstru" class="list-group-item">Photometric Instruments</a>
						<a href="#configFile" class="list-group-item">Configuration file</a>
					</div>
				</div> <!-- col-md3 -->

				<div class="col-xs-12 col-sm-6 col-md-9">
					<div id ="warningDiv" class="alert alert-warning">
						<h3>Warnings</h3>
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
					</div> <!--alert -->

					<div id="inputFiles" class="panel panel-default">
						<div class="panel-heading text-center">Summary Table on Input Files</div>
						<div class="panel-body table-responsive">
							<table id="fieldsTable" class="table table-hover table-bordered table-striped">
			    				<thead>
									<tr>
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
					</div> <!--panel-body-->
				</div> <!--panel -->

				<div id="groupProperties" class="panel panel-default">
					<div class="panel-heading text-center">Group Properties</div>
					<div class="panel-body table-responsive">
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
					</div> <!--panel-body-->
				</div> <!--panel -->

				<div class="row">
					<div class="col-md-6"> 
						<div id="astroInstruments" class="panel panel-default">
							<div class="panel-heading text-center">Astrometric Instruments</div>
							<div class="panel-body table-responsive">
								<table id="astrometricInstrumentsTable" class="table table-striped" >
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
							</div> <!--panel-body-->
						</div> <!--panel -->
					</div>
		
					<div class="col-md-6"> 
						<div id="photoInstruments" class="panel panel-default">
							<div class="panel-heading text-center">Photometric Instruments</div>
							<div class="panel-body table-responsive">
		
								<table id="photometricInstrumentsTable" class="table t table-striped">
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
							</div> <!--panel-body-->
						</div> <!--panel -->
					</div>
				</div>

				<div id="configFile" class="panel panel-default">
					<div class="panel-heading text-center">Configuration File</div>
					<div class="panel-body table-responsive">
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
					</div> <!--panel-body-->
				</div> <!--panel -->
			</div> <!-- row -->
		</div> <!--container-->



		<!-- SCRIPTS BEGIN -->
		<script 
			src="https://code.jquery.com/jquery-3.2.1.slim.min.js" 
			integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" 
			crossorigin="anonymous"></script>
		<script 
			src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" 
			integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" 
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
             *                                                                     
             * Data contained in "scamp_data" object, is loaded at the very end 
             * of this html file is his own <script> tag.                          
             *                                                                     
             */                                                                    
                                                                                   
            /* from an array of object (data), return the "value" property of   
             * object havinig "str" as "name" property. */   
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

            /* From an array of object (data), take the one having "str" as        
             * "name" property, and return his "value" or "-". Used                
             * for flag column in field table */  
			function getFlagVal(str, t, data) {
				if (getElemVal(str, data))
					return t;
				return "-";
			}

            /* From an array of object, take the one aving "str" as property       
             * "name", add values (wich must be an array of numbers), and          
             * return his average */  
			function getElemAverageVal(str, data) {
				var value = 0.0;
				var n = 0;
				$.each(getElemVal(str, data), function(i, elem) {
					value += elem;
					n++;
				});
				return value / n;
			}

            /* From an array of object (data), take the one with "name" property
             * equal to "str", and return a formated string with numbers        
             * floating precision defined by "fix", and unit by "unit".         
             * Of course, the object "value" must be an array of numbers.       
             * Setting fix to negative value, do note limit precision. */ 
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

            /* From an array of objects (data), get the one with "name" property
             * equal to "str", and format a string with his "value" as a        
             * right ascention representation */
			function getRaVal(str, data) {
				var value = getElemVal(str, data);
				var a = Math.floor(value[0] / 15.0);
				var b = Math.floor((value[0] * 4) % 60);
				var c = Math.floor((value[0] *240) % 60);
				return a + ":" + b + ":" + c.toFixed(2);
			}

            /* From an array of objects (data), get the one with "name" property
             * equal to "str", and format a string with his "value" as a        
             * declination representation */  
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

				/* build status string */
				$('#soft').text(getElemVal("Name", scamp_data.Software)+" "+getElemVal("Version", scamp_data.Software));
				$('#date').text(getElemVal("Date", scamp_data.Software));
				$('#time').text(getElemVal("Time", scamp_data.Software));
				$('#nthreads').text(getElemVal("NThreads", scamp_data.Software));
				$('#runtime').text(getElemVal("Duration", scamp_data.Software) + " s");
				$('#username').text(getElemVal("User", scamp_data.Software));
				$('#rundir').text(getElemVal("Path", scamp_data.Software));

				/* show/hide match option and plots */
				var showmatch = getElemVal("MATCH", scamp_data.Configuration);
				var showplot  = getElemVal("CHECK_PLOT_DEV", scamp_data.Configuration);
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


				function generateImageCol(imageUrl) {
					value = "";
					value += "<td><a type='button' rel='popover' data-img='"+imageUrl+"'>";
					value += "<img width='100' src='"+imageUrl+"' />";
					value += "</a></td>";
					return value;
				}
				/* 
				 * build fields groups table 
				 */
				$.each(scamp_data.Fgroups, function(i, group) {
					var table_row = "";
					table_row += "<tr>";
					table_row += "<td>" +  getElemVal("Name", group) + "</td>";
					if (showplot) {
						table_row += generateImageCol(getElemVal("FgroupsPlot", group));
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
						table_row += generateImageCol(getElemVal("Chi2Plot", group));
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
						table_row += generateImageCol(getElemVal("IntErr1DimPlot", group));
						table_row += generateImageCol(getElemVal("IntErr2DimPlot", group));
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
						table_row += generateImageCol(getElemVal("RefErr1DimPlot", group));
						table_row += generateImageCol(getElemVal("RefErr2DimPlot", group));
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
						table_row += generateImageCol(getElemVal("PhotErrPlot", group));
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
					if (showplot) {
						table_row += generateImageCol(getElemVal("DistPlot", astroinstru));
					} else {
						table_row += "<td></td>";
					}
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
                    $('#astrometricInstrumentsTable th:nth-child(6)').hide();   
                    $('#astrometricInstrumentsTable td:nth-child(6)').hide();  
				}
				
				if (scamp_data.Warnings.length == 0) {
					$("#warningDiv").hide();
				}	
				$('a[rel=popover]').popover({
					animation: true, container: "body", html: true, placement: 'bottom', content: function() {return "<img src='"+$(this).data('img') + "' />";}
				});
				
			});
		</script>
		<!-- SCRIPTS END -->





	</body>
</html>
