<?php

function add_incident($customerID, $product_code, $title, $description) {
    global $db;
    $date = date('Y-m-d');
    $query = "INSERT INTO incidents
              VALUES
              (' ', '$customerID', '$product_code', '', '$date', '', 
                  '$title', '$description')";
    $db->query($query);
}

function get_incidents() {
    global $db;
    $query = "SELECT * FROM incidents
	      WHERE techID IS NULL";
    $db->query($query);
}
