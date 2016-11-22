<?php
    //Turn on error reporting
    ini_set('display_errors', 'On');
    //Connects to the database
    $mysqli = new mysqli("oniddb.cws.oregonstate.edu","cooperph-db","NKWCQdcXNLL2X6T6","cooperph-db");
    if(!$mysqli || $mysqli->connect_errno){
        echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    
    if(!($stmt = $mysqli->prepare("INSERT INTO Holder(fk_trainer_id, fk_badge_id) VALUES (?,?)"))){
        echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!($stmt->bind_param("ii",$_POST['tName'],$_POST['tBadge']))){
        echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!$stmt->execute()){
        echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
    } else {
        echo "Added " . $stmt->affected_rows . " Badge to Trainer.";
    }
    ?>

<!-- printing to pokemon instead of holders -->
