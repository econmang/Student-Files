<?php

function get_technicians() {
    global $db;
    $query = "SELECT * FROM technicians";
    $technicians = $db->query($query);
    return $technicians;
}

function delete_technician($techID) {
    global $db;
    $query = "DELETE FROM technicians
              WHERE techID = '$techID'";
    $db->exec($query);
}

function add_technician($firstName, $lastName, $email, $phone, $password) {
    global $db;
    $query = "INSERT INTO technicians
              VALUES ('', '$firstName', '$lastName', '$email', '$phone', 
              '$password')";
    $db->query($query);
}
?>
