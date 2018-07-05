<?php
$dbhost = 'localhost:3306';
$dbname = 'usr_brandend_1';
$dbuser = 'brandend';
$dbpass = 'gfIoicqbBWq';


$conn = mysqli_connect($dbhost, $dbuser, $dbpass) or die("Unable to Connect to '$dbhost'");
mysqli_select_db($conn, $dbname) or die("Could not open the db '$dbname'");

?>