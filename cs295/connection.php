<?php
$dbname = 'usr_conleye_1';
$dbuser = 'conleye';
$dbpass = 'zr9bkZmh9VgdqraSzXxPo0NIjb1hZL2x';
$dbhost = 'webpages.sou.edu:3306';

$link = mysqli_connect($dbhost,$dbuser,$dbpass) or die("Unable to connect to '$dbhost'");
mysqli_select_db($link, $dbname) or die("Could not open the db '$dbname'");

$test_query = "select * from Customer";
$result = mysqli_query($link,$test_query);

/*
if (!$result){
  exit("SQL Statement Error: " . $SQL);
}
$test_query = "SHOW TABLES FROM $dbname";
$result = mysqli_query($link, $test_query);
$tblCnt = 0;
while($tbl = mysqli_fetch_array($results)) {
  $tblCnt++;
}
if (!$tblCnt){
  echo "There are no tables\n";
} else {
  echo "There are $tblCnt tables\n";
}*/
?>
