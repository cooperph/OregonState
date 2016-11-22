<!-- 
   Scott Cooper
    CS 340 - Final Project
    Pokemon Themed Database
-->
<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","cooperph-db","NKWCQdcXNLL2X6T6","cooperph-db");
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<body>
<div>
	<table>
		<tr>
			<td>Trainers</td>
		</tr>
		<tr>
			<td>Name</td>
			<td>Hometown</td>
			<td>Number of Pokemon</td>
            <td>Number of Badges</td>
		</tr>
<!-- php here to populate table -->
<?php
    if(!($stmt = $mysqli->prepare("SELECT t.name, c.name,COUNT(p.id), t.badges_earned FROM Trainer AS t
                                  INNER JOIN City AS c
                                  on t.fk_city_id= c.id
                                  INNER JOIN Ownership AS own
                                  on t.id= own.fk_trainer_id
                                  INNER JOIN Pokemon AS p
                                  on own.fk_pokemon_id= p.id
                                  INNER JOIN Holder AS h
                                  on t.id=h.fk_trainer_id
                                  INNER JOIN Badges AS b
                                  on h.fk_badge_id=b.id
                                  GROUP BY t.name"))){
        echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
    }
    
    if(!$stmt->execute()){
        echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    if(!$stmt->bind_result($name, $city, $numpoke, $numbadge)){
        echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    while($stmt->fetch()){
        echo "<tr>\n<td>\n" . $name . "\n</td>\n<td>\n" . $city . "\n</td>\n<td>\n" . $numpoke . "\n</td>\n<td>\n"  . $numbadge ."\n</td>\n</tr>";
    }
    $stmt->close();
?>
    </table>
</div>
<br><br>
    
<!-- Add a Trainer Form -->
<div>
	<form method="post" action="addtrainer.php"> 
      <fieldset>
        <legend>Add a trainer</legend>
		<fieldset>
			<legend>Trainer's Name</legend>
			<p>Name: <input type="text" name="Name" /></p>
        </fieldset>

		<fieldset>
			<legend>Hometown</legend>
			<select name="Hometown">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, name FROM City"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $pname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $pname . '</option>\n';
}
$stmt->close();
?>
			</select>
		</fieldset>
		<p><input type="submit" /></p>
      </fieldset>
	</form>
</div>
<br><br>

<!-- Remove a Trainer -->
<div>
    <form method="post" action="deletetrainer.php">
    <fieldset>
        <legend>Remove a Trainer</legend>
            <fieldset>
            <legend>Trainer's Name</legend>
            <select name="trainer_id">
<?php
    if(!($stmt = $mysqli->prepare("SELECT id, name FROM Trainer"))){
        echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
    }
    
    if(!$stmt->execute()){
        echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    if(!$stmt->bind_result($id, $name)){
        echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    while($stmt->fetch()){
        echo '<option value=" '. $id . ' "> ' . $name . '</option>\n';
    }
    $stmt->close();
    ?>
</select>
            </fieldset>
        <p><input type="submit" /></p>
    </fieldset>
</div>
</form>
<br><br>

<!-- Show Trainer with their Pokemon --> 
<div>
	<table>
		<tr>
			<td>Trainer's Pokemon</td>
		</tr>
		<tr>
			<td>Trainer Name</td>
			<td>Pokemon Name</td>
		</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT t.name, p.name FROM Ownership
INNER JOIN Pokemon AS p
  ON Ownership.fk_pokemon_id = p.id
INNER JOIN Trainer AS t
  ON Ownership.fk_trainer_id = t.id
ORDER BY t.name ASC "))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($tname, $pname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $tname . "\n</td>\n<td>\n" . $pname ."\n</td>\n</tr>";
}
$stmt->close();
?>
    </table>
</div>    
<br><br>   


<!-- ADD Pokemon to Trainer -->
<div>
	<form method="post" action="addpokemon.php"> 
      <fieldset>
        <legend>Add a Pokemon to Trainer</legend>
		<fieldset>
			<legend>Trainer's Name</legend>
            <select name="Name">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, name FROM Trainer"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $name)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $name . '</option>\n';
}
$stmt->close();
?>
            </select>
        </fieldset>

		<fieldset>
			<legend>Pokemon</legend>
            <select name="Pokemon">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, name FROM Pokemon"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $pname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $pname . '</option>\n';
}
$stmt->close();
?>
			</select>
		</fieldset>
		<p><input type="submit" /></p>
      </fieldset>
	</form>
</div>

    
<!-- Add Badge to Trainer -->
<div>
<form method="post" action="addbadges.php">
    <fieldset>
        <legend>Add a Badge to a Trainer</legend>
        <fieldset>
            <legend>Trainer's Name</legend>
            <select name="tName">
<?php
    if(!($stmt = $mysqli->prepare("SELECT id, name FROM Trainer"))){
        echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
    }
    
    if(!$stmt->execute()){
        echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    if(!$stmt->bind_result($id, $tname)){
        echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    while($stmt->fetch()){
        echo '<option value=" '. $id . ' "> ' . $tname . '</option>\n';
    }
    $stmt->close();
    ?>
            </select>
        </fieldset>

        <fieldset>
            <legend>Badge Name</legend>
            <select name="tBadge">
<?php
    if(!($stmt = $mysqli->prepare("SELECT id, name FROM Badges"))){
        echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
    }
    
    if(!$stmt->execute()){
        echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    if(!$stmt->bind_result($id, $bname)){
        echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
    }
    while($stmt->fetch()){
        echo '<option value=" '. $id . ' "> ' . $bname . '</option>\n';
    }
    $stmt->close();
    ?>
            </select>
        </fieldset>
        <p><input type="submit" /></p>
    </fieldset>
</form>
</div>
<br><br>
    
<!-- Print Region / City names -->
<div>
	<table>
		<tr>
			<td>Regions and Cities</td>
		</tr>
		<tr>
			<td>Region Name</td>
			<td>City City</td>
		</tr>
        <!-- php here -->
        <?php
if(!($stmt = $mysqli->prepare("SELECT r.name, c.name FROM City AS c
INNER JOIN Regions AS r
  ON c.fk_region_id = r.id "))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($region, $city)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $region . "\n</td>\n<td>\n" . $city . "\n</td>\n</tr>";
}
$stmt->close();
?>
    </table>
</div>
    
    
<!-- Add a city to a Region -->
    <div>
	<form method="post" action="addcity.php"> 
      <fieldset>
        <legend>Add a City</legend>
		<fieldset>
			<legend>City Name</legend>
			<p>Name: <input type="text" name="cName" /></p>
        </fieldset>

		<fieldset>
			<legend>Region</legend>
			<select name="Region">
<?php
if(!($stmt = $mysqli->prepare("SELECT id, name FROM Regions"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $pname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $pname . '</option>\n';
}
$stmt->close();
?>
			</select>
		</fieldset>
		<p><input type="submit" /></p>
      </fieldset>
	</form>
</div>
<br><br>

<!-- Show All Gyms Information -->
<div>
	<table>
		<tr>
			<td>Gyms</td>
		</tr>
		<tr>
			<td>Name</td>
			<td>City</td>
			<td>Region</td>
            <td>Pokemon Type</td>
            <td>Badge Name</td>
		</tr>
<?php
if(!($stmt = $mysqli->prepare("SELECT g.name, c.name, r.name, pt.type, b.name FROM Gym AS g 
INNER JOIN City AS c
  on g.fk_city_id = c.id
INNER JOIN Regions AS r
  on c.fk_region_id = r.id
INNER JOIN Pokemon_Type as pt
  on g.fk_type_id = pt.id
INNER JOIN Badges AS b
  on g.fk_badge_id = b.id "))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($gym, $city, $region, $type, $badge)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
 echo "<tr>\n<td>\n" . $gym . "\n</td>\n<td>\n" . $city . "\n</td>\n<td>\n" . $region . "\n</td>\n<td>\n" . $type . "\n</td>\n<td>\n" . $badge ."\n</td>\n</tr>";
}
$stmt->close();
?>
    </table>
</div>
<br><br>    

    
    
    
    
    
    
    
    