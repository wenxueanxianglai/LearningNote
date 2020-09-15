function callback() {
  console.log("Done");
}

console.log("before setTimeout()");
setTimeout(callback, 1000);
console.log("after setTimeout");


function log(s) {
    console.log(s);
}

function test(resolve, reject) {
    var timeOut = Math.random() * 2;
    log('set timeout to: ' + timeOut + ' seconds');
    setTimeout(function() {
        if(timeOut < 1) {
            log('call resolve()..');
            resolve('200OK');
        }
        else {
            log('call reject()...');
            reject('timeout in ' + timeOut + ' seconds.');
        }
    }, timeOut * 1000);
}

var p1 = new Promise(test);
var p2 = p1.then(function (result) {
    console.log('成功：' + result);
});

var p3 = p2.catch(function(reason) {
    console.log('失败：' + reason);
});