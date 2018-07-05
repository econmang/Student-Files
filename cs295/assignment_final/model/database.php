<?php
    $dsn = 'mysql:host=localhost;dbname=usr_conleye_0';
    $username = 'conleye';
    $password = 'zr9bkZmh9VgdqraSzXxPo0NIjb1hZL2x';

    try {
        $db = new PDO($dsn, $username, $password);
    } catch (PDOException $e) {
        $error_message = $e->getMessage();
        include('../errors/database_error.php');
        exit();
    }
?>
