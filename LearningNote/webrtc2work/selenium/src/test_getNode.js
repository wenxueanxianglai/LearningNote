const Builder = require("selenium-webdriver");
const request = require("request");

request("http://192.168.0.105:4444/grid/console", function (
  error,
  response,
  body
) {
  if (!error && response.statusCode == 200) {
    console.log(body); // Show the HTML for the baidu homepage.
  }
});

// var http = require('http');
// var url = require('url');
// var util = require('util');

// http.get("http://192.168.0.105:4444/grid/console",function(data){
//     var str="";
//     data.on("data",function(chunk){
//         str+=chunk;//监听数据响应，拼接数据片段
//     })
//     data.on("end",function(){
//         console.log(str.toString())
//     })
// })
