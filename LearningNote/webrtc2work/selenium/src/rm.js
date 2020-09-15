const rimraf = require('rimraf');
rimraf('./node_modules', function (err) { 
  console.log(err);
});