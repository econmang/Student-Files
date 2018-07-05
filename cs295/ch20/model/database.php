<?php
$host = 'localhost:3306';
$username = 'brandend';
$password = 'gfIoicqbBWq';
$database = 'usr_brandend_0';

$db = new mysqli($host, $username, $password, $database);

$error_message = $db->connect_error;
if ($error_message != null) {
    include 'errors/db_error_connect.php';
    exit;
}

function display_db_error($error_message) {
    global $app_path;
    include 'errors/db_error.php';
    exit;
}
?>