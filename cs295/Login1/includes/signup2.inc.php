<?php
$dbname = 'usr_brandend_0';
$dbuser = 'brandend';
$dbpass = 'gfIoicqbBWq';
$dbhost = 'webpages.sou.edu:3306';

$link = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname) or die("Unable to Connect to '$dbhost'");
mysqli_select_db($conn, $dbname) or die("Could not open the db '$dbname'");
$first = mysqli_real_escape_string($link, $_REQUEST['first']);

$last = mysqli_real_escape_string($link, $_REQUEST['last']);

$email = mysqli_real_escape_string($link, $_REQUEST['email']);
$uid = mysqli_real_escape_string($link, $_REQUEST['userID']);
$pdw = mysqli_real_escape_string($link, $_REQUEST['pdw']);
 

// attempt insert query execution

$sql = "INSERT INTO persons(user_first, user_last, user_email, user_uid, user_pw) VALUES ('$first', '$last', '$email','$uid','$pdw')";

if(mysqli_query($link, $sql)){

    echo "Records added successfully.";

} else{

    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);

}
/*insert the user into the database
//				$sql = 'INSERT INTO user //(user_first, user_last,user_email, user_uid, user_pwd) VALUES('$first','$last','$email','$uid','$pwd');';
				$result=mysqli_query($conn, $sql);*/
				header("Location: ../signup.php?signup=success");
			exit();
			
	
	?>