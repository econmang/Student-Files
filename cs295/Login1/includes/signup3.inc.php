<?php
//include_once "db.inc.php";
$dbname = 'usr_brandend_0';
$dbuser = 'brandend';
$dbpass = 'gfIoicqbBWq';
$dbhost = 'webpages.sou.edu:3306';
$first = mysqli_real_escape_string($conn, $_REQUEST['first']);
$last = mysqli_real_escape_string($conn, $_REQUEST['last']);
$email = mysqli_real_escape_string($conn, $_REQUEST['email']);
$uid = mysqli_real_escape_string($conn, $_REQUEST['uid']);
$pdw = mysqli_real_escape_string($conn, $_REQUEST['pdw']);
 

// attempt insert query execution

$sql = "INSERT INTO user(user_first, user_last, user_email, user_uid, user_pdw) VALUES ('$first', '$last', '$email','$uid','$pdw')";

if(mysqli_query($conn, $sql)){

    header("Location: ../signup.php?signup=success");
			exit();

} else{

    echo "ERROR: Could not able to execute $sql. " . mysqli_error($conn);

}
	
	
	?>