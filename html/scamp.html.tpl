<!DOCTYPE html>
<html>
	<head>
		<title>Processing Summary</title>
		<script
			src="https://code.jquery.com/jquery-3.3.1.min.js"
			integrity="sha256-FgpCb/KJQlLNfOu91ta32o/NMZxltwRo8QtmkMRdAu8="
			crossorigin="anonymous"></script>
		<script>
			$(document).ready(function() {
				console.log(scamp_data);
				$("<tr><td>qslkdfjs</td></td>").appendTo("#fieldTable tbody");
			});
		</script>
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
					    <th>&#916;Pixel scale</th>
					    <th>&#916;Position Angle</th>
					    <th>A/S contrast</th>
					    <th>&#916;X</th>
					    <th>&#916;Y</th>
					    <th>X/Y contrast</th>
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
		<table id="groupsTable">
			<thead>
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
			</thead>
			<tbody>
			</tbody>
		</table>

		<h2>Astrometric Instruments</h2>
		<table id="instrumentsTable">
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
	</body>
</html>
