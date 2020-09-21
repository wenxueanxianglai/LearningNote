var MyArr = function () {};

MyArr.prototype = new Array();
MyArr.prototype.constructor = MyArr;

var mine = new MyArr();
mine.push(1, 2, 3);
console.log(mine.length);
console.log(mine instanceof Array);
