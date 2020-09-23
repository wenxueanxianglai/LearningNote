const http = require('http');
const fs = require('fs');

//readFile( path, CallBack)
fs.readFile('./www/test.txt', function(error, data){
    if(error) {
        console.log('read File failed');
    }else {
        console.log(data.toString());
    }
});



// writeFile(path, context, callback)
fs.writeFile('test.txt', 'hahahahaha', function(err){
    if(err) {
        console.log('write File failed');
    }
});