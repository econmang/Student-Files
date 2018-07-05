<?php
require('../model/database.php');
require('../model/product_db.php');

if (isset($_POST['action'])) {
    $action = $_POST['action'];
} else if (isset($_GET['action'])) {
    $action = $_GET['action'];
} else {
    $action = 'list_products';
}

if ($action == 'list_products') {
    $products = get_products();
    include('product_list.php');
}
else if ($action == 'delete_product') {
    $product_code = $_POST['product_code'];
    delete_product($product_code);
    header("Location: .");
}
else if ($action == 'add_product') {
    $product_code = $_POST['product_code'];
    $name = $_POST['name'];
    $version = $_POST['version'];
    $release_date = $_POST['release_date'];
    
    if (empty($product_code) || empty($name) || empty($version) 
            || empty($release_date)) {
        $error = 'Please make sure all fields are entered correctly.';
        include('../errors/error.php');
    }
    else {
        add_product($product_code, $name, $version, $release_date);
        header("Location: .");
    }
}
?>
