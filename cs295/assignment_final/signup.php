<?php 
	include_once 'view/header.php';
	include('../model/signup_db.php');
?>

<section class="main-container">
        <div class="main-wrapper">
                <h2>Signup</h2>
                <form class="signup-form" action="." method="POST">
                        <input type="text" name="first" placeholder="Firstname">
                        <input type="text" name="last" placeholder="Lastname">
                        <input type="text" name="email" placeholder="E-mail">
                        <input type="text" name="uid" placeholder="Username">
                        <input type="password" name="pdw" placeholder="Password">
                        <button type="submit" name="submit">Sign up</button>
                </form>
        </div>
</section>

<?php
        include_once 'view/footer.php';
?>

