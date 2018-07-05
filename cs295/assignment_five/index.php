<?php
  if(!isset($investment)) {$investment= '';}
  if(!isset($investment_rate)) {$investment_rate= '';}
  if(!isset($years)) {$years= '';}

  if(!isset($investment_f)) {$investment_f= '';}
  if(!isset($investment_rate_f)) {$investment_rate_f= '';}
  if(!isset($years_f)) {$years_f= '';}
  if(!isset($cmpRate)) {$cmpRate = 1;}
?>

<DOCTYPE! html>
<html>
  <head>
    <title>Future Value Calculator</title>
    <meta charset="UTF-8">
    <link rel="stylesheet" type="text/css" href="main.css">

  </head>
  <body>
    <main>
    <?php

    	if($_SERVER['REQUEST_METHOD'] === 'POST'){
		if(!empty($_POST['compound'])){
			$cmpRate = 12;
		}
		//get data from the form
      		$investment = filter_input(INPUT_POST, 'investment', FILTER_VALIDATE_FLOAT);
      		$investment_rate = filter_input(INPUT_POST, 'investment_rate', FILTER_VALIDATE_FLOAT);
      		$years = filter_input(INPUT_POST,'years',FILTER_VALIDATE_FLOAT);
      		$error_message = '';
		
     		//validate data 
      		if ($investment === FALSE or $investment <= 0){
        		$error_message = 'Must enter a valid investment amount.';
      		} else if ($investment_rate === FALSE or $investment_rate <= 0) {
        		$error_message = 'Must enter a valid rate greater than zero.';
      		} else if ($years === FALSE or $years <= 0) {
        		$error_message = 'Years must be valid number greater than zero.';
      		} else {
        		$error_message = '';
      		}

      		if ($error_message != ''){
        		;
      		}
		else{
      			//calculate future value
     	 		$futureValue = $investment;
      			for ($i = 1; $i <= $years; $i++){
        			$futureValue += $futureValue * ($investment_rate/$cmpRate) * 0.01;
      			}	

      			//apply formatting
      			$investment_f = "$".number_format($investment, 2);
      			$investment_rate_f = $investment_rate."%";
  			$futureValue_f = "$".number_format($futureValue,2);
      			$years_f = $years;

			$investment = '';
      			$years = '';
      			$investment_rate='';
      		}
	}
	?>
	

    <form action="index.php" method="post">
      <h1>Future Value Calculator</h1>
      <?php if(!empty(error_message)){?>
       <p class="error"><?php echo htmlspecialchars($error_message);?></p>
      <?php }?>
      <div id="data">
        <label>Investment Amount:</label>
        <input type="text" name="investment" />
        <br>
        <label>Yearly Interest Rate:</label>
        <input type="text" name="investment_rate" />
        <br>
        <label>Number of Years:</label>
        <input type="text" name="years" />
        <br>
	<label>Compound Monthly</label>
	<input type="checkbox" name="compound" value="monthly">
	<br>
      </div>

      <div id="buttons">
        <label>&nbsp;</label>
        <input type="submit" value="Calculate"><br>
      </div>

      <div id="data">
            <h1>Future Value Calculated</h1>
            <label>Investment Amount:</label>
            <span> <?php echo htmlspecialchars($investment_f)?> </span><br>
            <label>Yearly Interest Rate:</label>
            <span> <?php echo htmlspecialchars($investment_rate_f)?> </span><br>
            <label>Number of Years:</label>
            <span> <?php echo htmlspecialchars($years_f)?> </span><br>
            <label>Future Value:</label>
            <span> <?php echo htmlspecialchars($futureValue_f)?> </span><br>
	</div>

    </form>
  </body>
</html>
