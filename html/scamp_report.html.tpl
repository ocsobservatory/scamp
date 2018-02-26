<!DOCTYPE html>
<html>
	<head>
		<title>Processing Summary</title>
	</head>
	<body>

		<h1>Processing summary</h1>

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
				<td>{{DistPlot}}</td>
			</tr>
			{{/AstroInstruments}}
		</table>
		{{/AstroInstruments}}

	</body>
</html>

