<?php
	include ("mysql.php");

	$sql0 = mysql_query("SELECT * FROM lixeira") or die (mysql_error());
	$row0 = mysql_fetch_array($sql0);

	$sql = mysql_query("SELECT * FROM medicao ORDER BY id_medicao DESC limit 5") or die (mysql_error());
?>	
<html>
	<head>
		<link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" rel="stylesheet">
		<link href='https://fonts.googleapis.com/css?family=Oswald' rel='stylesheet' type='text/css'>
		<link href='https://fonts.googleapis.com/css?family=Open+Sans' rel='stylesheet' type='text/css'>
		<style>
			table {
				border-collapse: collapse;
				width: 100%;
			}

			th, td {
				text-align: center;
				padding: 8px;
			}

			tr:nth-child(even){background-color: #f2f2f2}

			th {
				background-color: #1a53ff;
				color: white;
			}

		.title {
			font-size: 56px;
			font-family: 'Oswald';
			text-align: center;
		}
		body {
			font-family: 'Open Sans';
		}
		.success{
			font-size: 18px;
			text-align: left;
		}
		.table-pull-right{
			font-size: 14px;
		}


		</style>

		<title> NeatBin - Medições </title>
		<meta http-equiv="refresh" content="5">
	</head>

	<body>
	<div class="title">Neatbin - Medições da Lixeira</div>

		<table border='1'>
			<tr>
				<th> Lixeira </th>
				<th> Altura </th>
				<th> Medição </th>
				<th> Usado </th>
				<th> Situação </th>
				<th> Última Medição </th>
			<tr>
			<?php
			  while($row = mysql_fetch_array($sql)){
			  	$medi = $row['med'];
			  	$altu = $row0['altura'];
			  	$nivel = intval((100*($row0['altura']-$row['med'])/$row0['altura']));
			?>
				<tr>
					<td> <center> <?php echo $row['id_lixeira']; ?> </center> </td>
					<td> <center> <?php echo $altu."cm"; ?> </center> </td>
					<td> <center> <?php echo ($altu-$medi)."cm"; ?> </center>  </td>
					<td> <center> <?php echo intval((100*($altu-$medi)/$altu))."%";?> </center> </td>
					<td>
						<center>
						<?php
							if ($nivel <= 30) {
								echo "<font color='blue'>Tranquila</font>";
							}
							if ($nivel > 30 && $nivel < 80) {
								echo "<font color='green'>Média</font>";
							}
							if ($nivel >= 80) {
								echo "<font color='red'>Esvaziar</font>";
							}
  						?>
						</center>
					</td>
					<td> <center> <?php echo $row['hora']; ?> </center> </td>
				</tr>
			<?php		
			  }
			?>
		</table>
	</body>
</html>
