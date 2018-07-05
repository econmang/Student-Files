<?php
require("../model/database.php");
require("../model/customer_db.php");
require("../model/product_db.php");
require("../model/registrations_db.php");

session_start();

if (isSet($_POST['action'])) {
    $action = $_POST['action'];
}
else if (isSet($_GET['action'])) {
    $action = $_GET['action'];
}
else if(isSet($_SESSION['email'])) {
    $action = 'verify_email';
}
else {
    $action = 'login';
}

switch($action) {
    case 'login':
        include('login.php');
        break;
    case 'verify_email':
        if(!isSet($_SESSION['email'])) {
            $_SESSION['email'] = $_POST['email'];
        }
        $customer = search_by_email($_SESSION['email']);
        $products = get_products();
        include('register_product.php');
        break;
    case 'register_product':
        if(!isSet($_SESSION['customerID'])) {
            $_SESSION['customerID'] = $_POST['customerID'];
        }
        $product_code = $_POST['productCode'];
        $date = date('Y-m-d');
        add_registration($_SESSION['customerID'], $product_code, $date);
        include('registration_confirmation.php');
        break;
}


