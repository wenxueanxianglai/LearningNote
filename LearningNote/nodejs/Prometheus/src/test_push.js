var http = require('http');  
  
var qs = require('querystring');  
  
var post_data = {  
    a: 123,  
    time: new Date().getTime()};//这是需要提交的数据  
  
  
var content = "another_metric     239128.283\n";
  
var options = {  
    hostname: '127.0.0.1',  
    port: 9091,  
    path: '/metrics/job/some_job/instance/whatinstance',  
    method: 'POST',  
    headers: {  
        'Content-Type': 'application/x-www-form-urlencoded; charset=UTF-8'  
    }  
};  
  
var req = http.request(options, function (res) {  
    console.log('HEADERS: ' + JSON.stringify(res.headers));  
    res.setEncoding('utf8');  
    res.on('data', function (chunk) {  
        console.log('BODY: ' + chunk);  
    });  
});  
  
req.on('error', function (e) {  
    console.log('problem with request: ' + e.message);  
});  
  
// 将数据写入请求体
req.write(content);//注意这个地方  
  
req.end();