<?php
    //Turn on error reporting
    ini_set('display_errors', 'On');
    //Connects to the database
    $mysqli = new mysqli("oniddb.cws.oregonstate.edu","cooperph-db","NKWCQdcXNLL2X6T6","cooperph-db");
    if(!$mysqli || $mysqli->connect_errno){
        echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    if(!($stmt = $mysqli->prepare("DELETE FROM Trainer WHERE id=?"))){
        echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!($stmt->bind_param("i",$_POST['trainer_id']))){
        echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!$stmt->execute()){
        echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
    } else {
        echo "Deleted " . $stmt->affected_rows . " rows to Trainers.";
    }
?>
