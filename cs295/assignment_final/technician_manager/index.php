<?php 
require('../model/database.php');
require('../model/technician_db.php');

if (isSet($_POST['action'])) {
    $action = $_POST['action'];
}
else if (isSet($_GET['action'])) {
    $action = $_GET['action'];
}
else {
    $action = 'list_techs';
}

if ($action == 'list_techs') {
    $techs = get_technicians();
    include('technician_list.php');
}
else if ($action == 'delete_tech') {
    $techID = $_POST['techID'];
    delete_technician($techID);
    header("Location: .");
}
else if ($action == 'add_tech') {
    $firstName = $_POST['firstName'];
    $lastName = $_POST['lastName'];
    $email = $_POST['email'];
    $phone = $_POST['phone'];
    $password = $_POST['password'];
    if (empty($firstName) || empty($lastName) || empty($email) || 
            empty($phone) || empty($password)) {
        $error = "Please check that all fields are filled in correctly.";
        include('../errors/error.php');
    }
    else {
        add_technician($firstName, $lastName, $email,
                $phone, $password);
        header("Location: .");
    }
}

