<?php include('../view/header.php'); ?>
<div id='main'>
    <table>
        <tr>
            <th>Customer Name</th>
            <th>Product</th>
            <th>Date Opened</th>
            <th>Password</th>
            <th></th>
        </tr>
        <?php foreach($techs as $tech) : ?>
        <tr>
            <td><?php echo $tech['firstName'] . " " . $tech['lastName'] ; ?></td>
            <td><?php echo $tech['email']; ?></td>
            <td><?php echo $tech['phone']; ?></td>
            <td><?php echo $tech['password']; ?></td>
            <td>
                <form action='.' method='post'>
                    <input type='hidden' name='action' 
                           value='delete_tech' />
                    <input type='hidden' name='techID' 
                           value='<?php echo $tech['techID']; ?>' />
                    <input type='submit' value='Delete' />
                </form>
            </td>
        </tr>
        <?php endforeach; ?>
    </table>
    <a href='add_tech.php'>Add Technician</a>
</div>

<?php include('../view/footer.php'); ?>

