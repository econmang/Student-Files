<?php
  define("SALES_TAX", 8);

  //get data from the form
  $product_description = filter_input(INPUT_POST, 'product_description');
  $list_price = filter_input(INPUT_POST, 'list_price', FILTER_VALIDATE_FLOAT);
  $discount_percent = filter_input(INPUT_POST,'discount_percent',FILTER_VALIDATE_FLOAT);
  $error_message = '';

  //validate data 
  if ($product_description === FALSE or empty($product_description)){
    $error_message = 'Description must be a valid item name';
  } else if ($list_price === FALSE or $list_price <= 0) {
    $error_message = 'Listing price must be a valid number greater than zero.';
  } else if ($dicount_percent === FALSE or $discount_percent <= 0) {
    $error_message = 'Discount percent must be a valid number greater than zero.';
  } else {
    $error_message = '';
  }

  //check for error
  if ($error_message != '') {
    include('indexOne.html');
    exit();
  }

  //calculate the discount and discounted price
  $discount = $list_price * $discount_percent * 0.01;
  $discount_price = $list_price - $discount;
  $tax_price = $discount_price * SALES_TAX * 0.01;
  $total_price = $discount_price + $tax_price;

  //apply formatting
  $list_price_f = "$".number_format($list_price, 2);
  $discount_percent_f = $discount_percent."%";
  $discount_f = "$".number_format($discount,2);
  $discount_price_f = "$".number_format($discount_price,2);
  $tax_percent_f = SALES_TAX."%";
  $total_price_f = "$".number_format($total_price,2);
?>


<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Product Discount Calculator</title>
    <link rel="stylesheet" type="text/css" href="main.css">
  </head>
  <body>
    <main>
      <h1>Product Discount Calculator</h1>

      <label>Proudct Description:</label>
      <span><?php echo htmlspecialchars($product_description); ?></span>
      <br>

      <label>List Price:</label>
      <span><?php echo htmlspecialchars($list_price_f); ?> </span>
      <br>
      <label>Standard Discount:</label>
      <span> <?php echo htmlspecialchars($discount_percent_f); ?></span>
      <br>

      <label>Discount Price:</label>
      <span><?php echo $discount_price_f; ?></span>
      <br>

      <label>Standard Tax:</label>
      <span><?php echo htmlspecialchars($tax_percent_f); ?></span>
      <br>

      <label>Total Cost:</label>
      <span><?php echo htmlspecialchars($total_price_f); ?></span>
      <br>
    </main>
  </body>
</html>
