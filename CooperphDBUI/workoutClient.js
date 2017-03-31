document.addEventListener('DOMContentLoaded', insertItem);
document.addEventListener('DOMContentLoaded', updateItem);
document.addEventListener('DOMContentLoaded', displayTable);


function displayTable(e){
	var req = new XMLHttpRequest();

	req.open('GET', 'http://52.36.170.205:3000/select', true);
	req.addEventListener('load', function(){
		if(req.status >= 200 && req.status < 400){
			var response = JSON.parse(req.responseText);
			console.log(response);
			var tableElement = document.getElementById("workoutTable");
			if (tableElement !== null){
				tableElement.parentNode.removeChild(tableElement);
			}
			var headerElement = document.getElementById("newh2");
			if (headerElement !== null){
				headerElement.parentNode.removeChild(headerElement);
			}

			var newTable = document.createElement("table");
			newTable.id = "workoutTable";
			var newRow = document.createElement("tr");

			var headerName = ["Workout Name", "Number of Reps", "Weight Lifted", "Date of Workout", "Lbs?", ""];
			for (p in headerName){
				var newHeader = document.createElement("th");
				newHeader.textContent = headerName[p];
				newRow.appendChild(newHeader);
			}
			newTable.appendChild(newRow);
			for (p in response){
				var newRow = document.createElement("tr");
				newRow.id = response[p].id;

				var workoutData = document.createElement("td");
				workoutData.textContent = response[p].workout;
				newRow.appendChild(workoutData);

				var repData = document.createElement("td");
				repData.textContent = response[p].reps;
				newRow.appendChild(repData);

				var weightData = document.createElement("td");
				weightData.textContent = response[p].weight;
				newRow.appendChild(weightData);

				var dateData = document.createElement("td");
				dateData.textContent = response[p].wo_date;
				newRow.appendChild(dateData);

				var lbsData = document.createElement("td");
				lbsData.textContent = response[p].lbs;
				newRow.appendChild(lbsData);


				var deleteButton = document.createElement("button");
				deleteButton.addEventListener('click', deleteItem, false);
				deleteButton.textContent = "Delete";
				newRow.appendChild(deleteButton);

				var updateButton = document.createElement("button");
				updateButton.addEventListener('click', showEditForm, false);
				updateButton.textContent = "Edit";
				newRow.appendChild(updateButton);

				newTable.appendChild(newRow);
			}
			var newHeading = document.createElement("h2");
			newHeading.id = "newh2";
			newHeading.textContent = "Your Workout Data";
			var tablePut = document.getElementById("tablePut");
			tablePut.appendChild(newHeading);
			tablePut.appendChild(newTable);
			
		}
		else {
			console.log("Error in network request:" + req.statusText);
		}
	});
	req.send(null);
	e.preventDefault();
	
}

function insertItem(){
	document.getElementById('workoutSubmit').addEventListener('click', function(e){
		var req = new XMLHttpRequest();
		var payload = {};
		payload.workout = document.getElementById('workout').value;
		payload.reps = document.getElementById('reps').value;
		payload.weight = document.getElementById('weight').value;
		payload.wo_date = document.getElementById('wo_date').value;
		payload.lbs = document.getElementById('lbs').value;
		req.open('POST', 'http://52.36.170.205:3000/insert', true);
		req.setRequestHeader('Content-Type', 'application/json');
		req.addEventListener('load', function(){
			if(req.status >= 200 && req.status < 400){
				//var response = JSON.parse(req.responseText);
			
				displayTable(e);
			}
			else {
				console.log("Error in network request:" + req.statusText);
			}
		});
		req.send(JSON.stringify(payload));
		e.preventDefault();
	});
}

function deleteItem(e){
	var req = new XMLHttpRequest();
	var payload = {};
	payload.id = this.parentNode.id;
	
	req.open('POST', 'http://52.36.170.205:3000/delete', true);
	req.setRequestHeader('Content-Type', 'application/json');
	req.addEventListener('load', function(){
		if(req.status >= 200 && req.status < 400){
			//var response = JSON.parse(req.responseText);

			displayTable(e);
		}
		else {
			console.log("Error in network request:" + req.statusText);
		}
	});
	req.send(JSON.stringify(payload));
	e.preventDefault();
}

function showEditForm(e){
	var modal = document.getElementById('editModal');
	modal.style.display = "block";
    var span = document.getElementsByClassName("close")[0];
    span.onclick = function(){ modal.style.display = "none";}
    window.onclick = function(event){
    	if(event.target == modal){
    		modal.style.display = "none";
    	}
    }

    var req = new XMLHttpRequest();
    var payload = {};
    payload.id = this.parentNode.id;
    req.open('POST', 'http://52.36.170.205:3000/update-page', true);
	req.setRequestHeader('Content-Type', 'application/json');
	req.addEventListener('load', function(){
		if(req.status >= 200 && req.status < 400){
			var response = JSON.parse(req.responseText);
			document.getElementById('edit_id').value = response.id;
			document.getElementById('edit_workout').value = response.workout;
			document.getElementById('edit_reps').value = response.reps;
			document.getElementById('edit_weight').value = response.weight;
			document.getElementById('edit_wo_date').value = response.wo_date;
			document.getElementById('edit_lbs').value = response.lbs;
		}
		else {
			console.log("Error in network request:" + req.statusText);
		}
	});
	req.send(JSON.stringify(payload));
	e.preventDefault();
}

function updateItem(){
	document.getElementById('editWorkout').addEventListener('click', function(e){
		var req = new XMLHttpRequest();
		var payload = {};
		payload.id = document.getElementById('edit_id').value;
		payload.workout = document.getElementById('edit_workout').value;
		payload.reps = document.getElementById('edit_reps').value;
		payload.weight = document.getElementById('edit_weight').value;
		payload.wo_date = document.getElementById('edit_wo_date').value;
		payload.lbs = document.getElementById('edit_lbs').value;
		req.open('POST', 'http://52.36.170.205:3000/update', true);
		req.setRequestHeader('Content-Type', 'application/json');
		req.addEventListener('load', function(){
			if(req.status >= 200 && req.status < 400){
				//var response = JSON.parse(req.responseText);
			
				displayTable(e);
			}
			else {
				console.log("Error in network request:" + req.statusText);
			}
		});
		req.send(JSON.stringify(payload));
		document.getElementById('editModal').style.display = "none";
		e.preventDefault();
	});
}
