<?php
function sign_up(($user_id, $user_first, $user_last, $user_email, $user_pw) {
    global $db;
    $query = "INSERT INTO login2
              VALUES
              ('$user_id', '$user_first','$user_last', '$user_email', '$user_pw')";
    $db->query($query);
}
?>
