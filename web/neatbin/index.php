<?php
	include ("mysql.php");
	$sql = mysql_query("SELECT * FROM medicao ORDER BY id_medicao DESC") or die (mysql_error());
?>	
<html>
	<head> <title> TNR - NeatBin </title> </head>
	<body>
	<h1> NeatBin - Medições </h1>

		<table border='1'>
			<tr>
				<th> Lixeira </th>
				<th> Medição </th>
				<th> Data/Hora </th>
			<tr>
			<?php
			  while($row = mysql_fetch_array($sql)){
			?>
				<tr>
					<td> <?php echo $row['id_lixeira']; ?> </td>
					<td> <?php echo $row['med']; ?> </td>
					<td> <?php echo $row['hora']; ?> </td>
				</tr>
			<?php		
			  }
			?>
		</table>
	</body>
</html>