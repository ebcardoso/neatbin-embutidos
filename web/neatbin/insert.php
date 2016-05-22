<?php
	include ("mysql.php");

	$cod = $_GET["cod"];
	$med = $_GET["med"];

	$sql = mysql_query("INSERT INTO medicao (id_lixeira, med, hora) values ('$cod', '$med', now())") or die (mysql_error());
?>
