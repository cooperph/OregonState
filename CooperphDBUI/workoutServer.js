var express = require('express');
var mysql = require('mysql');
var pool = mysql.createPool({
	host : 'localhost',
	user : 'student',
	password : 'default',
	database : 'student'
});

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var bodyParser = require('body-parser');

app.use(bodyParser.urlencoded({extended : false }));
app.use(bodyParser.json());

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);
app.use(express.static('public'));

app.use(function(req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  next();
});

app.post('/insert', function(req, res, next){
  pool.query("INSERT INTO workout (workout, reps, weight, wo_date, lbs) VALUES (?, ?, ?, ?, ?)", [req.body.workout, req.body.reps, req.body.weight, req.body.wo_date, req.body.lbs], function(err, result){ 
    if(err){
      next(err);
      return;
    }
    res.status(200).send(null);
    console.log("entry inserted into table.");
  });
});

app.post('/delete', function(req,res,next){
  pool.query("DELETE FROM workout WHERE id=?", [req.body.id], function(err,result){
    if(err){
      next(err);
      return;
    }
    res.status(200).send(null);
    console.log("Entry deleted.");
  });
});

app.post('/update', function(req,res,next){
  pool.query("UPDATE workout SET workout=?, reps=?, weight=?, wo_date=?, lbs=? WHERE id=?", [req.body.workout, req.body.reps, req.body.weight, req.body.wo_date, req.body.lbs, req.body.id], function(err,result){
    if(err){
      next(err);
      return;
    }
    res.status(200).send(null);
    console.log("Table updated.");
  });
});


app.post('/update-page', function(req, res,next){
  var result = {};
  pool.query("SELECT * FROM workout WHERE id=?", [req.body.id], function(err,rows,fields){
    if(err){
      next(err);
      return;
    }
    res.status(200).send(rows[0]);
  });
});

app.get('/select', function(req,res,next){
  pool.query("SELECT * from workout", function(err, rows, fields){
    if(err){
      next(err);
      return;
    }
    res.status(200).send(rows);
  });
});


app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + ';press Ctrl-C to terminate.');
});
