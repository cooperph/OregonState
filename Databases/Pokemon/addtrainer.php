<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","cooperph-db","NKWCQdcXNLL2X6T6","cooperph-db");
if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
if(!($stmt = $mysqli->prepare("INSERT INTO Trainer(name, fk_city_id) VALUES (?,?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("si",$_POST['Name'],$_POST['Hometown']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " rows to Trainers.";
}
    
    if(!($stmt2 = $mysqli->prepare("INSERT INTO Holder(fk_badge_id, fk_trainer_id) values(9, (SELECT id FROM Trainer WHERE name= ? LIMIT 1))"))){
        echo "Prepare failed: "  . $stmt2->errno . " " . $stmt2->error;
    }
    if(!($stmt2->bind_param("s",$_POST['Name']))){
        echo "Bind failed: "  . $stmt2->errno . " " . $stmt2->error;
    }
    if(!$stmt2->execute()){
        echo "Execute failed: "  . $stmt2->errno . " " . $stmt2->error;
    } else {
        echo "Added " . $stmt2->affected_rows . " Trainer Badge.";
    }

;
    
?>
