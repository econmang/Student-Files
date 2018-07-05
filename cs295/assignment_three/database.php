<?php
$dsn = 'mysql:host=localhost;dbname=usr_conleye_1';
$dbuser = 'conleye';
$dbpass = 'zr9bkZmh9VgdqraSzXxPo0NIjb1hZL2x';

try {
    $db = new PDO($dsn, $dbuser, $dbpass);
} catch (PDOException $e) {
    $error_message = $e->getMessage();
    include('database_error.php');
    exit();
}
?>
